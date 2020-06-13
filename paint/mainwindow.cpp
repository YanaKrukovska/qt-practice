#include <QtWidgets>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    canvasArea = new Canvas;
    setCentralWidget(canvasArea);
    createActions();
    createMenus();
    setWindowTitle(tr("Paint"));
    resize(500, 500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybeSave()){
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::open()
{
    if(maybeSave()){
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open File"),
                                                        QDir::currentPath());

        if(!fileName.isEmpty()){
            canvasArea->openImage((fileName));
        }

    }
}

void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::brushColor()
{
    QColor newColor = QColorDialog::getColor(canvasArea->brushColor());
    if(newColor.isValid()){
        canvasArea->setBrushColor(newColor);
    }
}

void MainWindow::brushWidth()
{
    bool ok;
    // min=1, max=50, step=1
    int newWidth = QInputDialog::getInt(this,
                                        tr("Draw"),
                                        tr("Select brush width: "),
                                        canvasArea->penWidth(),
                                        1, 50, 1, &ok);
    if(ok){
        canvasArea->setBrushWidth(newWidth);
    }
}


void MainWindow::createActions()
{
    openAction = new QAction(tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());
        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActionsList.append(action);
    }


    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    setBrushColorAction = new QAction(tr("&Pen Color..."), this);
    connect(setBrushColorAction, SIGNAL(triggered()), this, SLOT(brushColor()));

    setBrushWidthAction = new QAction(tr("&Pen Width..."), this);
    connect(setBrushWidthAction, SIGNAL(triggered()), this, SLOT(brushWidth()));

    clearAction = new QAction(tr("&Clear Screen..."), this);
    clearAction->setShortcut(tr("Ctrl+L"));
    connect(clearAction, SIGNAL(triggered()), canvasArea, SLOT(clearImage()));
}

void MainWindow::createMenus()
{
    saveAsMenu = new QMenu(tr("&Save As"), this);
    foreach(QAction *action, saveAsActionsList){
        saveAsMenu->addAction(action);
    }

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAction);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(setBrushColorAction);
    optionMenu->addAction(setBrushWidthAction);
    optionMenu->addSeparator();
    optionMenu->addAction(clearAction);


    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
}

bool MainWindow::maybeSave()
{
    if(canvasArea->isModified()){
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Paint"),
                                   tr("The image has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save |
                                   QMessageBox::Discard |
                                   QMessageBox::Cancel);

        if(ret == QMessageBox::Save){
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel){
            return false;
        }
    }

    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    initialPath,
                                                    tr("&1 Files (*.%2;; All Files(*")
                                                    .arg(QString::fromLatin1(fileFormat.toUpper()))
                                                    .arg(QString::fromLatin1(fileFormat)));
    if(fileName.isEmpty()){
        return false;
    } else {
        return canvasArea->saveImage(fileName, fileFormat.constData());
    }
}




#include "mainwindow.h"
#include "canvas.h"
#include "canvascreator.h"
#include <QInputDialog>
#include "ui_mainwindow.h"

QColor MainWindow::colour = QColorConstants::Black;
int MainWindow::brushSize = 1;

void MainWindow::setDefaultParameters()
{
    isDrawingEnabled = 1;
    isRectangleEnable = 0;
    isCircleEnabled = 0;
    isLineEnabled = 0;
    isFillingEnabled=0;
    isErasingEnabled=0;
}


MainWindow::MainWindow():  QMainWindow(),
                           ui(new Ui::MainWindow)
{
    Canvas *canvas = new Canvas(this);
    CanvasCreator *fenetretaille = new CanvasCreator(canvas);
    setCentralWidget(canvas);

    ui->setupUi(this);



    connect(ui->actionNew, SIGNAL(triggered(bool)), fenetretaille, SLOT(showCanvas()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), canvas, SLOT(saveCanvasArea()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), canvas, SLOT(openCanvasArea()));
    connect(ui->actionColour,SIGNAL(triggered(bool)),this,SLOT(slotColour()));
    connect(ui->actionBrush,SIGNAL(triggered(bool)),this,SLOT(slotDraw()));
    connect(ui->actionBrush_Size,SIGNAL(triggered(bool)),this,SLOT(slotSize()));
    connect(ui->actionEraser,SIGNAL(triggered(bool)),this,SLOT(slotErase()));
    connect(ui->actionLine,SIGNAL(triggered(bool)),this,SLOT(slotDrawLine()));
    connect(ui->actionCircle,SIGNAL(triggered(bool)),this,SLOT(slotDrawCircle()));
    connect(ui->actionRectangle,SIGNAL(triggered(bool)),this,SLOT(slotDrawRectangle()));

    connect(ui->actionFiller,SIGNAL(triggered(bool)),this,SLOT(slotFill()));
    connect(ui->actionUndo,SIGNAL(triggered(bool)),canvas,SLOT(undoCanvasArea()));
    setDefaultParameters();

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::getIsDrawingEnabled()
{
    return isDrawingEnabled;
}
bool MainWindow::getIsErasingEnabled()
{
    return isErasingEnabled;
}
bool MainWindow::getIsRectangleEnabled()
{
    return isRectangleEnable;
}
bool MainWindow::getIsCircleEnabled()
{
    return isCircleEnabled;
}
bool MainWindow::getIsLineEnabled()
{
    return isLineEnabled;
}

bool MainWindow::getIsFillingEnabled()
{
    return isFillingEnabled;
}

QColor MainWindow::getColour()
{
    return colour;
}
int MainWindow::getBrushSize()
{
    return brushSize;
}

void MainWindow::slotDraw()
{
    isDrawingEnabled = 1;
    isErasingEnabled = 0;
    isRectangleEnable = 0;
    isCircleEnabled = 0;
    isFillingEnabled = 0;
    isLineEnabled = 0;
}

void MainWindow::slotErase()
{
    isErasingEnabled = 1;
    isDrawingEnabled = 0;
    isRectangleEnable = 0;
    isCircleEnabled = 0;
    isFillingEnabled = 0;
    isLineEnabled = 0;
}

void MainWindow::slotDrawRectangle()
{
    isDrawingEnabled = 0;
    isRectangleEnable = 1;
    isCircleEnabled = 0;
    isFillingEnabled = 0;
    isLineEnabled = 0;
    isErasingEnabled = 0;
}
void MainWindow::slotDrawCircle()
{
    isDrawingEnabled = 0;
    isRectangleEnable = 0;
    isCircleEnabled = 1;
    isFillingEnabled = 0;
    isLineEnabled = 0;
    isErasingEnabled = 0;
}
void MainWindow::slotFill()
{
    isDrawingEnabled = 0;
    isRectangleEnable = 0;
    isCircleEnabled = 0;
    isFillingEnabled = 1;
    isLineEnabled = 0;
    isErasingEnabled = 0;
}

void MainWindow::slotDrawLine()
{
    isDrawingEnabled = 0;
    isRectangleEnable = 0;
    isCircleEnabled = 0;
    isFillingEnabled = 0;
    isLineEnabled = 1;
    isErasingEnabled = 0;
}

void MainWindow::slotColour()
{
    colour = QColorDialog::getColor(colour);
}

void MainWindow::slotSize()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Brush Size"),tr("Select brush size (1-50):"), brushSize,
                                        1, 50, 1, &ok);
    if (ok){
        brushSize = newWidth;
    }
}



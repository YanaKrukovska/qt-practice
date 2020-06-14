#include "mainwindow.h"
#include "canvas.h"
#include "canvascreator.h"
#include <QInputDialog>

void MainWindow::setDefaultParameters()
{
    isDrawingEnabled = 1;
    isRectangleEnable = 0;
    isCircleEnabled = 0;
    isLineEnabled = 0;
    isFillingEnabled=0;
    isErasingEnabled=0;
    brushSize = 1;
}

MainWindow::MainWindow()
{
    resize(500,500);
    setDefaultParameters();

    Canvas *canvas = new Canvas(this);
    CanvasCreator *fenetretaille = new CanvasCreator(canvas);
    setCentralWidget(canvas);

    QMenu *menuFile= menuBar()->addMenu("File");
    QAction *newFileAction = new QAction("New",this);
    menuFile->addAction(newFileAction);
    QAction *saveFileAction = new QAction("Save",this);
    menuFile->addAction(saveFileAction);
    QAction *openFileAction = new QAction("Open",this);
    menuFile->addAction(openFileAction);

    connect(newFileAction,SIGNAL(triggered(bool)),fenetretaille,SLOT(showCanvas()));
    connect(saveFileAction,SIGNAL(triggered(bool)),canvas,SLOT(saveCanvasArea()));
    connect(openFileAction,SIGNAL(triggered(bool)),canvas,SLOT(openCanvasArea()));

    QToolBar *toolBar = addToolBar("Tools");
    QToolButton *colourButton = new QToolButton;
    colourButton->setText("Colour");
    toolBar->addWidget(colourButton);

    QToolButton *brushSizeButton = new QToolButton;
    brushSizeButton->setText("Brush Size");
    toolBar->addWidget(brushSizeButton);


    QToolButton *brushButton = new QToolButton;
    brushButton->setText("Brush");
    toolBar->addWidget(brushButton);


    QToolButton *eraserButton = new QToolButton;
    eraserButton->setText("Eraser");
    toolBar->addWidget(eraserButton);

    QToolButton *lineButton = new QToolButton;
    lineButton->setText("Line");
    toolBar->addWidget(lineButton);

    QToolButton *circleButton = new QToolButton;
    circleButton->setText("Circle");
    toolBar->addWidget(circleButton);


    QToolButton *rectangleButton = new QToolButton;
    rectangleButton->setText("Rectangle");
    toolBar->addWidget(rectangleButton);

    QToolButton *fillButton = new QToolButton;
    fillButton->setText("Fill");
    toolBar->addWidget(fillButton);


    QToolButton *undoButton = new QToolButton;
    undoButton->setText("Undo");
    undoButton->setShortcut(QKeySequence("Ctrl+Z"));
    toolBar->addWidget(undoButton);

    connect(colourButton,SIGNAL(clicked(bool)),this,SLOT(slotColour()));
    connect(fillButton,SIGNAL(clicked(bool)),this,SLOT(slotFill()));
    connect(lineButton,SIGNAL(clicked(bool)),this,SLOT(slotLine()));
    connect(brushButton,SIGNAL(clicked(bool)),this,SLOT(slotDraw()));
    connect(eraserButton,SIGNAL(clicked(bool)),this,SLOT(slotErase()));
    connect(circleButton,SIGNAL(clicked(bool)),this,SLOT(slotCircle()));
    connect(rectangleButton,SIGNAL(clicked(bool)),this,SLOT(slotRectangle()));
    connect(brushSizeButton,SIGNAL(clicked(bool)),this,SLOT(slotSize()));
    connect(undoButton,SIGNAL(clicked(bool)),canvas,SLOT(undoCanvasArea()));
}

bool MainWindow::getIsDrawwingEnabled()
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

void MainWindow::slotRectangle()
{
    isDrawingEnabled = 0;
    isRectangleEnable = 1;
    isCircleEnabled = 0;
    isFillingEnabled = 0;
    isLineEnabled = 0;
    isErasingEnabled = 0;
}
void MainWindow::slotCircle()
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

void MainWindow::slotLine()
{
    isDrawingEnabled = 0;
    isRectangleEnable = 0;
    isCircleEnabled = 0;
    isFillingEnabled = 0;
    isLineEnabled = 1;
    isErasingEnabled = 0;
}

void MainWindow::slotColour()
{   colour = QColorDialog::getColor(colour);
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



#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}


class MainWindow : public QMainWindow
{

    Q_OBJECT

public:

    static QColor colour;
    static int brushSize;

    MainWindow();
    ~MainWindow();
    bool getIsDrawingEnabled();
    bool getIsErasingEnabled();
    bool getIsRectangleEnabled();
    bool getIsCircleEnabled();
    bool getIsLineEnabled();
    bool getIsFillingEnabled();

    QColor getColour();
    int getBrushSize();
    void setDefaultParameters();

public slots :

    void slotDraw();
    void slotErase();
    void slotDrawRectangle();
    void slotDrawCircle();
    void slotDrawLine();
    void slotFill();
    void slotColour();
    void slotSize();

private:

    Ui::MainWindow *ui;
    bool isDrawingEnabled;
    bool isErasingEnabled;
    bool isRectangleEnable;
    bool isCircleEnabled;
    bool isLineEnabled;
    bool isFillingEnabled;
};

#endif

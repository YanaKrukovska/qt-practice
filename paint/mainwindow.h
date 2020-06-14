#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include <QtWidgets>

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    MainWindow();
    bool getIsDrawwingEnabled();
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
    void slotRectangle();
    void slotCircle();
    void slotLine();
    void slotFill();
    void slotColour();
    void slotSize();

private:
    bool isDrawingEnabled;
    bool isErasingEnabled;
    bool isRectangleEnable;
    bool isCircleEnabled;
    bool isLineEnabled;
    bool isFillingEnabled;
    int brushSize;
    QColor colour;
};

#endif

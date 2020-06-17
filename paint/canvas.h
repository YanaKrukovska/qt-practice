#ifndef CANVAS_H
#define CANVAS_H

#include <mainwindow.h>
#include <QtWidgets>

class Canvas : public QWidget {
    Q_OBJECT

public :

    Canvas(MainWindow *parent);
    ~Canvas();

    void draw();
    void erase();
    void drawRectangle();
    void drawCircle();
    void drawLine();
    void drawFilledLine();
    void drawFilledRectangle();
    void drawFilledCircle();
    void fill();
    int performFilling(int xPressed, int yPressed, QRgb chosenColour, QRgb neededColour);

    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void setPenParameters();
    void updatePainter();
    void updatePixels();

public slots:

    void newCanvasArea();
    void saveCanvasArea();
    void openCanvasArea();
    void undoCanvasArea();

private :
    int currentPixel;
    int xMove;
    int yMove;
    int xPressed;
    int yPressed;
    int xReleased;
    int yReleased;
    int xMax;
    int yMax;

    QPen pen;
    QPainter *painter;
    QLabel *label;
    QImage *image;
    MainWindow *window;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QVector<QPixmap *> canvasPixels;
    QPainterPath *path;
};

#endif

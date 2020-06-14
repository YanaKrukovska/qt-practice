
#ifndef CANVASAREA
#define CANVASAREA
#include <QtWidgets>
#include <mainwindow.h>


class Canvas : public QWidget
{
    Q_OBJECT

public :

    Canvas(MainWindow *p);
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
    int filling4(int x,int y,QRgb col1, QRgb col2);

    void paintEvent(QPaintEvent* event);

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

public slots:
            void newCanvasArea();
    void saveCanvasArea();
    void openCanvasArea();
    void undoCanvasArea();

private :
    int pixCur;
    int xMax;
    int yMax;

    int xMove;
    int yMove;
    int xPress;
    int yPress;
    int xRelease;
    int yRelease;

    QPainter *painter;
    QLabel *label;
    MainWindow *window;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QImage *image;
    QVector<QPixmap*> mapPixels;
    QPainterPath *path;
};

class Point{
public:
    Point(int a,int b) : x(a),y(b) {}
    ~Point();
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }

private:
    int x;
    int y;
};
#endif

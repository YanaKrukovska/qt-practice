#ifndef CANVASCREATOR_H
#define CANVASCREATOR_H

#include <canvas.h>
#include <QtWidgets>

class CanvasCreator : public QWidget
{
    Q_OBJECT

public:
    CanvasCreator(Canvas *canvas );
    int getWidth();
    int getHeight();

public slots:
            void showCanvas();
    void getWidthInput();
    void getHeightInput();

private:
    static int width;
    static int height;
    QLabel *widthLabel;
    QLabel *heightLabel;
    QPushButton *getWidthButton;
    QPushButton *getHeightButton;
    QPushButton *createButton;
};

#endif

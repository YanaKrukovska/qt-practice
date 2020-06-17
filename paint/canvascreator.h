#ifndef CANVASCREATOR_H
#define CANVASCREATOR_H

#include "canvas.h"
#include <QWidget>
#include <QtWidgets>

namespace Ui {
    class CanvasCreator;
}

class CanvasCreator : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasCreator(Canvas *canvas);
    ~CanvasCreator();
    int getWidth();
    int getHeight();

private:
    Ui::CanvasCreator *ui;
    static int width;
    static int height;

public slots:
    void showCanvas();

private slots:
    void on_widthButton_clicked();
    void on_heightButton_clicked();
    void on_createButton_clicked();

};

#endif // CANVASCREATOR_H

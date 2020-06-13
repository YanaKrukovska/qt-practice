#ifndef CANVAS_H
#define CANVAS_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class Canvas : public QWidget
{
    Q_OBJECT

public:
    Canvas(QWidget *parent = 0);

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setBrushColor(const QColor &newColor);
    void setBrushWidth(int newWidth);

    bool isModified() const { return modified; }
    QColor brushColor() const { return currentBrushColor; }
    int penWidth() const { return currentPenWidth; }

public slots:
    void clearImage();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    bool isDrawingNow;
    int currentPenWidth;
    QColor currentBrushColor;
    QImage image;
    QPoint lastPoint;
};

#endif
// CANVAS_H

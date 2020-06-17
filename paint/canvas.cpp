#include <canvas.h>
#include "canvascreator.h"

Canvas::Canvas(MainWindow *parent) : QWidget() {
    window = parent;
    xMax = 500;
    yMax = 500;
    label = new QLabel(this);
    canvasPixels.push_back(new QPixmap(xMax, yMax));
    currentPixel = canvasPixels.size() - 1;
    canvasPixels[currentPixel]->fill();
    painter = new QPainter(canvasPixels[currentPixel]);
    label->setPixmap(*canvasPixels[currentPixel]);
}

Canvas::~Canvas() {}

void Canvas::paintEvent(QPaintEvent *event) {
    //needed to be able to draw
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (window->getIsDrawingEnabled()) {
        xMove = event->pos().x();
        yMove = event->pos().y();
        draw();
    }
    if (window->getIsErasingEnabled()) {
        xMove = event->pos().x();
        yMove = event->pos().y();
        erase();
    }
    if (window->getIsRectangleEnabled()) {
        xMove = event->pos().x();
        yMove = event->pos().y();
        drawFilledRectangle();
    }
    if (window->getIsCircleEnabled()) {
        xMove = event->pos().x();
        yMove = event->pos().y();
        drawFilledCircle();
    }
    if (window->getIsLineEnabled()) {
        xMove = event->pos().x();
        yMove = event->pos().y();
        drawFilledLine();
    }

}

void Canvas::mousePressEvent(QMouseEvent *event) {
    if (window->getIsRectangleEnabled() || window->getIsCircleEnabled()
        || window->getIsFillingEnabled() || window->getIsLineEnabled()) {
        xPressed = event->pos().x();
        yPressed = event->pos().y();

    }
    if (window->getIsDrawingEnabled()) {
        canvasPixels.push_back(new QPixmap(xMax, yMax));
        currentPixel = currentPixel + 1;
        canvasPixels[currentPixel]->operator=(*canvasPixels[currentPixel - 1]);
        painter->end();
        delete painter;
        painter = new QPainter(canvasPixels[currentPixel]);
    }
    if (window->getIsDrawingEnabled()) {
        xPressed = event->pos().x();
        yPressed = event->pos().y();
        path = new QPainterPath(QPointF(xPressed, yPressed));
        path->moveTo(xPressed, yPressed);
    }
    if (window->getIsErasingEnabled()) {
        canvasPixels.push_back(new QPixmap(xMax, yMax));
        currentPixel = currentPixel + 1;
        canvasPixels[currentPixel]->operator=(*canvasPixels[currentPixel - 1]);
        painter->end();
        delete painter;
        painter = new QPainter(canvasPixels[currentPixel]);
    }
    if (window->getIsErasingEnabled()) {
        xPressed = event->pos().x();
        yPressed = event->pos().y();
        path = new QPainterPath(QPointF(xPressed, yPressed));
        path->moveTo(xPressed, yPressed);
    }

}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    if (window->getIsRectangleEnabled()) {
        xReleased = event->pos().x();
        yReleased = event->pos().y();
        drawRectangle();
    }
    if (window->getIsCircleEnabled()) {
        xReleased = event->pos().x();
        yReleased = event->pos().y();
        drawCircle();

    }
    if (window->getIsLineEnabled()) {
        xReleased = event->pos().x();
        yReleased = event->pos().y();
        drawLine();
    }
    if (window->getIsFillingEnabled()) {
        xReleased = event->pos().x();
        yReleased = event->pos().y();
        fill();
    }
    if (window->getIsDrawingEnabled()) {
        delete path;
    }
    if (window->getIsErasingEnabled()) {
        delete path;
    }

}

void Canvas::setPenParameters() {
    pen.setColor(window->colour);
    pen.setWidth(window->getBrushSize());
}

void Canvas::updatePainter() {
    painter->end();
    delete painter;
    painter = new QPainter(canvasPixels[currentPixel]);
    painter->setPen(pen);
}

void Canvas::updatePixels() {
    canvasPixels.push_back(new QPixmap(xMax, yMax));
    currentPixel = currentPixel + 1;
    canvasPixels[currentPixel]->operator=(*canvasPixels[currentPixel - 1]);
}

void Canvas::draw() {
    path->lineTo(xMove, yMove);
    setPenParameters();
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath(*path);
    label->setPixmap(*canvasPixels[currentPixel]);
}

void Canvas::erase() {
    path->lineTo(xMove, yMove);
    setPenParameters();
    pen.setColor(QColorConstants::White);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath(*path);
    label->setPixmap(*canvasPixels[currentPixel]);
}

void Canvas::drawRectangle() {
    setPenParameters();
    updatePixels();
    updatePainter();
    painter->drawRect(xPressed, yPressed, xReleased - xPressed, yReleased - yPressed);
    label->setPixmap(*canvasPixels[currentPixel]);
}

void Canvas::drawFilledRectangle() {
    setPenParameters();
    updatePixels();
    updatePainter();
    painter->drawRect(xPressed, yPressed, xMove - xPressed, yMove - yPressed);
    label->setPixmap(*canvasPixels[currentPixel]);
    canvasPixels.remove(currentPixel);
    currentPixel = canvasPixels.size() - 1;
}

void Canvas::drawCircle() {
    setPenParameters();
    updatePixels();
    updatePainter();
    painter->drawEllipse(xPressed, yPressed, xReleased - xPressed, yReleased - yPressed);
    label->setPixmap(*canvasPixels[currentPixel]);
}

void Canvas::drawFilledCircle() {
    setPenParameters();
    canvasPixels.push_back(new QPixmap(xMax, yMax));
    currentPixel = currentPixel + 1;
    canvasPixels[currentPixel]->operator=(*canvasPixels[currentPixel - 1]);
    updatePainter();
    painter->drawEllipse(xPressed, yPressed, xMove - xPressed, yMove - yPressed);
    label->setPixmap(*canvasPixels[currentPixel]);
    canvasPixels.remove(currentPixel);
    currentPixel = canvasPixels.size() - 1;
}

void Canvas::drawLine() {
    setPenParameters();
    canvasPixels.push_back(new QPixmap(xMax, yMax));
    currentPixel = currentPixel + 1;
    canvasPixels[currentPixel]->operator=(*canvasPixels[currentPixel - 1]);
    updatePainter();
    painter->drawLine(xPressed, yPressed, xReleased, yReleased);
    label->setPixmap(*canvasPixels[currentPixel]);

}

void Canvas::drawFilledLine() {
    setPenParameters();
    canvasPixels.push_back(new QPixmap(xMax, yMax));
    currentPixel = currentPixel + 1;
    canvasPixels[currentPixel]->operator=(*canvasPixels[currentPixel - 1]);
    updatePainter();
    painter->drawLine(xPressed, yPressed, xMove, yMove);
    label->setPixmap(*canvasPixels[currentPixel]);
    canvasPixels.remove(currentPixel);
    currentPixel = canvasPixels.size() - 1;
}

void Canvas::fill() {
    painter->end();
    delete painter;
    QRgb chosenColour;
    QRgb neededColour;
    canvasPixels.push_back(new QPixmap(xMax, yMax));
    currentPixel = currentPixel + 1;
    canvasPixels[currentPixel]->operator=(*canvasPixels[currentPixel - 1]);
    image = new QImage(xMax, yMax, QImage::Format_RGB32);
    *image = canvasPixels[currentPixel]->toImage();
    chosenColour = image->pixel(xPressed, yPressed);
    neededColour = window->colour.rgb();
    performFilling(xPressed, yPressed, chosenColour, neededColour);
    canvasPixels[currentPixel]->convertFromImage(*image);
    painter = new QPainter(canvasPixels[currentPixel]);
    delete image;
    label->setPixmap(*canvasPixels[currentPixel]);
}

int Canvas::performFilling(int xPressed, int yPressed, QRgb chosenColour, QRgb neededColour) {
    int positionX, positionY;
    int lastPosition;
    QVector < QPoint * > positions;

    if (image->pixel(xPressed, yPressed) != chosenColour) {
        return 1;
    }

    if (xPressed < 0 || yPressed < 0 || xPressed > (xMax - 1) || yPressed > (yMax - 1) ||
        chosenColour == neededColour) {
        return 0;
    }

    positions.push_back(new QPoint(xPressed, yPressed));

    while (positions.empty() == 0) {
        positionX = positions[positions.size() - 1]->x();
        positionY = positions[positions.size() - 1]->y();

        if (positionX == 1 || positionY == 1 || positionX == (xMax - 1) || positionY == (yMax - 1)) {
            for (int i = 0; i < xMax; i++) {
                image->setPixel(i, 0, neededColour);
                image->setPixel(i, yMax - 1, neededColour);
            }
            for (int i = 0; i < yMax; i++) {
                image->setPixel(0, i, neededColour);
                image->setPixel(xMax - 1, i, neededColour);
            }
        }
        lastPosition = positions.size() - 1;
        positions.remove(lastPosition);

        image->setPixel(positionX, positionY, neededColour);

        if (image->pixel(positionX, positionY - 1) == chosenColour) {
            positions.push_back(new QPoint(positionX, positionY - 1));
        }

        if (image->pixel(positionX, positionY + 1) == chosenColour) {
            positions.push_back(new QPoint(positionX, positionY + 1));
        }
        if (image->pixel(positionX + 1, positionY) == chosenColour) {
            positions.push_back(new QPoint(positionX + 1, positionY));
        }
        if (image->pixel(positionX - 1, positionY) == chosenColour) {
            positions.push_back(new QPoint(positionX - 1, positionY));
        }
    }
    return 1;
}


void Canvas::saveCanvasArea() {
    QString file = QFileDialog::getSaveFileName(0, "Save image", QString(), "Images (*.jpg)");
    canvasPixels[currentPixel]->save(file);
}

void Canvas::openCanvasArea() {
    QString file = QFileDialog::getOpenFileName(0, "Open image", QString(), "Images (*.jpg)");
    painter->end();
    delete painter;
    canvasPixels.remove(currentPixel);
    canvasPixels.push_back(new QPixmap(file));
    painter = new QPainter(canvasPixels[currentPixel]);
    label->setPixmap(*canvasPixels[currentPixel]);
}

void Canvas::newCanvasArea() {
    painter->end();
    delete painter;
    canvasPixels.erase(canvasPixels.begin(), canvasPixels.end());
    delete label;

    CanvasCreator *dialog = new CanvasCreator(this);
    xMax = dialog->getWidth();
    yMax = dialog->getHeight();
    if (xMax > 300) {
        window->resize(xMax, yMax);
    }

    canvasPixels.push_back(new QPixmap(xMax, yMax));
    currentPixel = canvasPixels.size() - 1;
    canvasPixels[currentPixel]->fill();

    label = new QLabel(this);
    label->setPixmap(*canvasPixels[currentPixel]);
    label->show();
    painter = new QPainter(canvasPixels[currentPixel]);

}

void Canvas::undoCanvasArea() {
    if (currentPixel == 0) {
        return;
    }

    canvasPixels.remove(currentPixel);
    currentPixel = canvasPixels.size() - 1;
    painter->end();
    delete painter;
    painter = new QPainter(canvasPixels[currentPixel]);
    label->setPixmap(*canvasPixels[currentPixel]);
}

#include <canvas.h>
#include "CanvasCreator.h"


Canvas::Canvas(MainWindow *parent) : QWidget()
{
    window = parent;
    xMax = 800;
    yMax = 800;
    label = new QLabel(this);
    canvasPixels.push_back(new QPixmap(xMax,yMax));
    currentPixel = canvasPixels.size()-1;
    canvasPixels[currentPixel]->fill();
    painter = new QPainter(canvasPixels[currentPixel]);
    label->setPixmap(*canvasPixels[currentPixel]);
}
Canvas::~Canvas(){}
void Canvas::paintEvent(QPaintEvent *event){}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if(window->getIsDrawingEnabled())
    {
        xMove = event->pos().x();
        yMove = event->pos().y();
        draw();
    }
    if(window->getIsErasingEnabled())
    {
        xMove = event->pos().x();
        yMove = event->pos().y();
        erase();
    }
    if(window->getIsRectangleEnabled())
    {
        xMove = event->pos().x();
        yMove = event->pos().y();
        drawFilledRectangle();
    }
    if(window->getIsCircleEnabled())
    {
        xMove = event->pos().x();
        yMove = event->pos().y();
        drawFilledCircle();
    }
    if(window->getIsLineEnabled())
    {
        xMove = event->pos().x();
        yMove = event->pos().y();
        drawFilledLine();
    }

}
void Canvas::mousePressEvent(QMouseEvent* event)
{
    if(window->getIsRectangleEnabled()||window->getIsCircleEnabled()
       ||window->getIsFillingEnabled()||window->getIsLineEnabled())
    {
        xPressed = event->pos().x();
        yPressed = event->pos().y();

    }
    if(window->getIsDrawingEnabled())
    {
        canvasPixels.push_back(new QPixmap(xMax,yMax));
        currentPixel = currentPixel+1;
        canvasPixels[currentPixel]->operator =(*canvasPixels[currentPixel-1]);
        painter->end();
        delete painter;
        painter = new QPainter(canvasPixels[currentPixel]);
    }
    if(window->getIsDrawingEnabled())
    {
        xPressed = event->pos().x();
        yPressed = event->pos().y();
        path = new QPainterPath(QPointF(xPressed,yPressed));
        path->moveTo(xPressed,yPressed);
    }
    if(window->getIsErasingEnabled())
    {
        canvasPixels.push_back(new QPixmap(xMax,yMax));
        currentPixel = currentPixel+1;
        canvasPixels[currentPixel]->operator =(*canvasPixels[currentPixel-1]);
        painter->end();
        delete painter;
        painter = new QPainter(canvasPixels[currentPixel]);
    }
    if(window->getIsErasingEnabled())
    {
        xPressed = event->pos().x();
        yPressed = event->pos().y();
        path = new QPainterPath(QPointF(xPressed,yPressed));
        path->moveTo(xPressed,yPressed);
    }

}
void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if(window->getIsRectangleEnabled())
    {
        xReleased = event->pos().x();
        yReleased = event->pos().y();
        drawRectangle();
    }
    if(window->getIsCircleEnabled())
    {
        xReleased = event->pos().x();
        yReleased = event->pos().y();
        drawCircle();

    }
    if(window->getIsLineEnabled())
    {
        xReleased = event->pos().x();
        yReleased = event->pos().y();
        drawLine();
    }
    if(window->getIsFillingEnabled())
    {
        xReleased = event->pos().x();
        yReleased = event->pos().y();
        fill();
    }
    if(window->getIsDrawingEnabled())
    {
        delete path;
    }
    if(window->getIsErasingEnabled())
    {
        delete path;
    }

}

void Canvas::draw()
{
    QPen pen;
    path->lineTo(xMove,yMove);
    pen.setColor(window->colour);
    pen.setWidth(window->getBrushSize());
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath(*path);

    label->setPixmap(*canvasPixels[currentPixel]);
}

void Canvas::erase()
{
    QPen pen;
    path->lineTo(xMove,yMove);
    pen.setColor(QColor("white"));
    pen.setWidth(window->getBrushSize());
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath(*path);
    label->setPixmap(*canvasPixels[currentPixel]);
}

void Canvas::drawRectangle()
{
    QPen pen;
    pen.setColor(window->getColour());
    pen.setWidth(window->getBrushSize());

    canvasPixels.push_back(new QPixmap(xMax,yMax));
    currentPixel = currentPixel+1;
    canvasPixels[currentPixel]->operator =(*canvasPixels[currentPixel-1]);
    painter->end();
    delete painter;
    painter = new QPainter(canvasPixels[currentPixel]);

    painter->setPen(pen);
    painter->drawRect(xPressed,yPressed,xReleased-xPressed,yReleased-yPressed);

    label->setPixmap(*canvasPixels[currentPixel]);
}
void Canvas::drawFilledRectangle()
{
    QPen pen;
    pen.setColor(window->getColour());
    pen.setWidth(window->getBrushSize());

    canvasPixels.push_back(new QPixmap(xMax,yMax));
    currentPixel = currentPixel+1;
    canvasPixels[currentPixel]->operator =(*canvasPixels[currentPixel-1]);
    painter->end();
    delete painter;
    painter = new QPainter(canvasPixels[currentPixel]);
    painter->setPen(pen);
    painter->drawRect(xPressed,yPressed,xMove-xPressed,yMove-yPressed);
    label->setPixmap(*canvasPixels[currentPixel]);
    canvasPixels.remove(currentPixel);
    currentPixel = canvasPixels.size()-1;
}

void Canvas::drawCircle()
{
    QPen pen;
    pen.setColor(window->getColour());
    pen.setWidth(window->getBrushSize());

    canvasPixels.push_back(new QPixmap(xMax,yMax));
    currentPixel = currentPixel+1;
    canvasPixels[currentPixel]->operator =(*canvasPixels[currentPixel-1]);
    painter->end();
    delete painter;
    painter = new QPainter(canvasPixels[currentPixel]);

    painter->setPen(pen);
    painter->drawEllipse(xPressed,yPressed,xReleased-xPressed,yReleased-yPressed);
    label->setPixmap(*canvasPixels[currentPixel]);
}
void Canvas::drawFilledCircle()
{
    QPen pen;
    pen.setColor(window->getColour());
    pen.setWidth(window->getBrushSize());

    canvasPixels.push_back(new QPixmap(xMax,yMax));
    currentPixel = currentPixel+1;
    canvasPixels[currentPixel]->operator =(*canvasPixels[currentPixel-1]);
    painter->end();
    delete painter;
    painter = new QPainter(canvasPixels[currentPixel]);

    painter->setPen(pen);
    painter->drawEllipse(xPressed,yPressed,xMove-xPressed,yMove-yPressed);
    label->setPixmap(*canvasPixels[currentPixel]);
    canvasPixels.remove(currentPixel);
    currentPixel = canvasPixels.size()-1;
}

void Canvas::drawLine()
{
    QPen pen;
    pen.setColor(window->getColour());
    pen.setWidth(window->getBrushSize());

    canvasPixels.push_back(new QPixmap(xMax,yMax));
    currentPixel = currentPixel+1;
    canvasPixels[currentPixel]->operator =(*canvasPixels[currentPixel-1]);
    painter->end();
    delete painter;
    painter = new QPainter(canvasPixels[currentPixel]);

    painter->setPen(pen);
    painter->drawLine(xPressed,yPressed,xReleased,yReleased);
    label->setPixmap(*canvasPixels[currentPixel]);

}
void Canvas::drawFilledLine()
{
    QPen pen;
    pen.setColor(window->getColour());
    pen.setWidth(window->getBrushSize());

    canvasPixels.push_back(new QPixmap(xMax,yMax));
    currentPixel = currentPixel+1;
    canvasPixels[currentPixel]->operator =(*canvasPixels[currentPixel-1]);
    painter->end();
    delete painter;
    painter = new QPainter(canvasPixels[currentPixel]);

    painter->setPen(pen);
    painter->drawLine(xPressed,yPressed,xMove,yMove);
    label->setPixmap(*canvasPixels[currentPixel]);
    canvasPixels.remove(currentPixel);
    currentPixel = canvasPixels.size()-1;
}

void Canvas::fill()
{
    painter->end();
    delete painter;
    QRgb colourChosen;
    QRgb currentColour;

    canvasPixels.push_back(new QPixmap(xMax,yMax));
    currentPixel = currentPixel+1;
    canvasPixels[currentPixel]->operator =(*canvasPixels[currentPixel-1]);

    image = new QImage(xMax,yMax,QImage::Format_RGB32);
    *image = canvasPixels[currentPixel]->toImage();
    colourChosen = image->pixel(xPressed,yPressed);
    currentColour = window->colour.rgb();

    filling4(xPressed,yPressed,colourChosen,currentColour);
    canvasPixels[currentPixel]->convertFromImage(*image);
    painter = new QPainter(canvasPixels[currentPixel]);
    delete image;
    label->setPixmap(*canvasPixels[currentPixel]);
}

int Canvas::filling4(int x,int y,QRgb col1, QRgb col2)
{
    int a,b,i;
    int lastPos;
    QVector<QPoint*> lPos;
    if(image->pixel(x,y)!= col1)
    {
        return 1;
    }
    if(x<0||y<0||x>(xMax-1)||y>(yMax-1)||col1==col2)
    {
        return 0;
    }
    lPos.push_back(new QPoint(x,y));
    while(lPos.empty()==0)
    {
        a = lPos[lPos.size()-1]->x();
        b = lPos[lPos.size()-1]->y();
        if(a==1||b==1||a==(xMax-1)||b==(yMax-1))
        {
            for(i=0;i<xMax;i++)
            {
                image->setPixel(i,0,col2);
                image->setPixel(i,yMax-1,col2);
            }
            for(i=0;i<yMax;i++)
            {
                image->setPixel(0,i,col2);
                image->setPixel(xMax-1,i,col2);
            }
        }
        lastPos = lPos.size()-1;
        lPos.remove(lastPos);

        image->setPixel(a,b,col2);

        if(image->pixel(a,b-1)==col1)
        {
            lPos.push_back(new QPoint(a,b-1));
        }

        if(image->pixel(a,b+1)==col1)
        {
            lPos.push_back(new QPoint(a,b+1));
        }
        if(image->pixel(a+1,b)==col1)
        {
            lPos.push_back(new QPoint(a+1,b));
        }
        if(image->pixel(a-1,b)==col1)
        {
            lPos.push_back(new QPoint(a-1,b));
        }
    }
    return 1;
}


void Canvas::saveCanvasArea()
{
    QString file = QFileDialog::getSaveFileName(0, "Save image", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    canvasPixels[currentPixel]->save(file);
}

void Canvas::openCanvasArea()
{
    QString file = QFileDialog::getOpenFileName(0,"Open image",QString(),"Images (*.png *.gif *.jpg *.jpeg)");
    painter->end();
    delete painter;
    canvasPixels.remove(currentPixel);
    canvasPixels.push_back(new QPixmap(file));
    painter = new QPainter(canvasPixels[currentPixel]);
    label->setPixmap(*canvasPixels[currentPixel]);

}

void Canvas::newCanvasArea()
{
    painter->end();
    delete painter;
    canvasPixels.erase(canvasPixels.begin(),canvasPixels.end());
    delete label;

    CanvasCreator *dialog = new CanvasCreator(this);
    xMax = dialog->getWidth();
    yMax = dialog->getHeight();

    if (xMax > 300){
        window->resize(xMax, yMax);
    }
    canvasPixels.push_back(new QPixmap(xMax,yMax));
    currentPixel = canvasPixels.size()-1;
    canvasPixels[currentPixel]->fill();

    label = new QLabel(this);
    label->setPixmap(*canvasPixels[currentPixel]);
    label->show();
    painter = new QPainter(canvasPixels[currentPixel]);
}
void Canvas::undoCanvasArea()
{
    if(currentPixel ==0){
        return;
    }
    canvasPixels.remove(currentPixel);
    currentPixel = canvasPixels.size()-1;
    painter->end();
    delete painter;
    painter = new QPainter(canvasPixels[currentPixel]);
    label->setPixmap(*canvasPixels[currentPixel]);

}

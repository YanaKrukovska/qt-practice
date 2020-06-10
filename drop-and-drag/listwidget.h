#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QListWidget>
#include <QDragMoveEvent>

class ListWidget : public QListWidget{

public:
    ListWidget(QWidget * parent) :
    QListWidget(parent) {}

protected:
    void dragMoveEvent(QDragMoveEvent *event) override {
        {
            if (event->source() != this) {
                event->accept();
            } else {
                event->ignore();
            }
        }
    }

};

#endif // LISTWIDGET_H

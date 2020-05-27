#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>
#include"contact.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_treeWidget_itemClicked(Contact *item, int column);

private:
    Ui::Widget *ui;
    int treeCount(QTreeWidget *, QTreeWidgetItem *);
    void DeleteItem (QTreeWidgetItem *currentItem);
    void InsertItem (QTreeWidgetItem *, QString);
    void showAll(void);
    int count;
    QTreeWidgetItem *currentItem;
    int currentColumn;

    QString showInputDialog(QString dialogHeader, QString prompt);

};

#endif // WIDGET_H

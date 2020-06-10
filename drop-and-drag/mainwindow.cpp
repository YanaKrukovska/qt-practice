#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::fillData()
{
    QList<QString> list1Names = {
        QString("Adam"),
        QString("Amanda"),
        QString("Alex"),
        QString("Andy"),
        QString("Aurora"),
        QString("Andrew"),
        QString("Aristotle"),
    };

    QList<QString> list2Names = {
        QString("Taylor"),
        QString("Tyler"),
        QString("Tom"),
        QString("Thomas"),
        QString("Tony"),
        QString("Todrick"),
        QString("Troye"),
        QString("Tori"),
    };

    for (int i=0; i<list1Names.size();i++) {
        ui->list1Widget->addItem(list1Names.value(i));
    }
    for (int i=0; i<list2Names.size();i++) {
        ui->list2Widget->addItem(list2Names.value(i));
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fillData();

    ui->list1Widget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->list1Widget->setDragEnabled(true);
    ui->list1Widget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->list1Widget->viewport()->setAcceptDrops(true);
    ui->list1Widget->setDropIndicatorShown(true);
    ui->list1Widget->setDefaultDropAction(Qt::MoveAction);

    ui->list2Widget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->list2Widget->setDragEnabled(true);
    ui->list2Widget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->list2Widget->viewport()->setAcceptDrops(true);
    ui->list2Widget->setDropIndicatorShown(true);
    ui->list2Widget->setDefaultDropAction(Qt::MoveAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

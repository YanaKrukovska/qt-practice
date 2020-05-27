#include "widget.h"
#include "ui_widget.h"
#include <QInputDialog>

Widget::Widget(QWidget *parent) :  QWidget(parent), ui(new Ui::Widget) {
 ui->setupUi(this);
 count = 0;
 ui->treeWidget->setColumnCount(1);
 QStringList headers;
 headers << tr("Contacts");
 ui->treeWidget->setHeaderLabels(headers);
 currentItem = NULL;
 currentColumn = 0;
}

Widget::~Widget() { delete ui; }

int Widget::treeCount(QTreeWidget *tree, QTreeWidgetItem *parent = 0) {
 tree->expandAll();
 int count = 0;
 if (parent == 0) {
  int topCount = tree->topLevelItemCount();
  for (int i = 0; i < topCount; i++) {
   QTreeWidgetItem *item = tree->topLevelItem(i);
   if (item->isExpanded()) {
    count += treeCount(tree, item);
   }
  }
  count += topCount;
 }
 else {
  int childCount = parent->childCount();
  for (int i = 0; i < childCount; i++) {
   QTreeWidgetItem *item = parent->child(i);
   if (item->isExpanded()) {
    count += treeCount(tree, item);
   }
  }
  count += childCount;
 }
 return count;
}

void Widget::DeleteItem (QTreeWidgetItem *currentItem) {
 QTreeWidgetItem *parent = currentItem->parent();
 int index;
 if (parent) {
  index = parent->indexOfChild(ui->treeWidget->currentItem());
  delete parent->takeChild(index);
 }
 else {
  index = ui->treeWidget->indexOfTopLevelItem(ui->treeWidget->currentItem());
  delete ui->treeWidget->takeTopLevelItem(index);
 }
}

void Widget::InsertItem (QTreeWidgetItem *parent, QString text) {
 if (parent->isExpanded()==false) parent->setExpanded(true);
 QTreeWidgetItem *newItem = new QTreeWidgetItem(parent, ui->treeWidget->currentItem());
 newItem->setText (currentColumn, text);
 newItem->setExpanded(true);
}


void Widget::on_addButton_clicked() {
 if (currentItem) {
  QString newNumber = QInputDialog::getText(nullptr,"New number","Insert number");

  InsertItem  (currentItem, newNumber);
 }
 else {
  QTreeWidgetItem *newItem = new QTreeWidgetItem(ui->treeWidget, ui->treeWidget->currentItem());
  QString newParentName = QInputDialog::getText(nullptr,"New contact","Insert name");
  newItem->setText (currentColumn, newParentName);
  newItem->setFlags(Qt::TextEditable);
  newItem->setExpanded(true);
 }
 currentItem = NULL;
 showAll();
}

void Widget::on_deleteButton_clicked() {
 if (currentItem) {
  DeleteItem (currentItem);
  currentItem = NULL;
 }
 showAll();
}

void Widget::showAll(void) {
 int cnt = treeCount (ui->treeWidget);
 QString str(tr("Amount of contacts: ")+QString("%1").arg(cnt));
 setWindowTitle(str);
}

void Widget::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column) {
 currentItem = item;
 currentColumn = column;
}

void Widget::on_treeWidget_itemClicked(Contact *item, int column) {
 currentItem = item;
 currentColumn = column;
}

QString Widget::showInputDialog(QString dialogHeader, QString prompt) {
   /* bool ok;
    QString text = QInputDialog::getText(this, dialogHeader,
                                         prompt, QLineEdit::Normal,
                                         placeholder, &ok);
    if(!ok) {
        return "";
    }*/

    return "text";
}

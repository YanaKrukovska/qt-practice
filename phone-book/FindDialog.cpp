#include <QtWidgets>
#include "finddialog.h"

FindDialog::FindDialog(QWidget *parent)
        : QDialog(parent)
{
    QLabel *findLabel = new QLabel(tr("Enter the name of a contact:"));
    nameInputField = new QLineEdit;

    findByNameButton = new QPushButton(tr("&Find by name"));
    findByNameText = "";

    QLabel *findByTextLabel = new QLabel(tr("or enter the number of a contact:"));
    findByNumberButton =  new QPushButton(tr("&Find by number"));
    numberInputField = new QLineEdit;
    findByNumberText = "";

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(findLabel, 0, 0);
    layout->addWidget(nameInputField, 0, 1);
    layout->addWidget(findByNameButton, 0, 2);

    layout->addWidget(findByTextLabel, 1, 0);
    layout->addWidget(numberInputField, 1,1);
    layout->addWidget(findByNumberButton, 1, 2);


    setLayout(layout);
    setWindowTitle(tr("Find a Contact"));
    connect(findByNameButton, &QPushButton::clicked,
            this, &FindDialog::findByNameClicked);
    connect(findByNameButton, &QPushButton::clicked,
            this, &FindDialog::accept);

    connect(findByNumberButton, &QPushButton::clicked,
            this, &FindDialog::findByNumberClicked);
    connect(findByNumberButton, &QPushButton::clicked,
            this, &FindDialog::accept);
}

void FindDialog::findByNameClicked()
{
    QString text = nameInputField->text();

    if (text.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"),
                                 tr("Please enter a name."));
        return;
    } else {
        findByNameText = text;
        nameInputField->clear();
        hide();
    }
}
void FindDialog::setFindByNameTextEmpty(){
    findByNameText = "";
}

void FindDialog::setFindByNumberTextEmpty(){
    findByNumberText = "";
}

void FindDialog::findByNumberClicked()
{
    QString text = numberInputField->text();

    if (text.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"),
                                 tr("Please enter a number."));
        return;
    } else {
        findByNumberText = text;
        numberInputField->clear();
        hide();
    }
}


QString FindDialog::getFindByNameText()
{
    return findByNameText;
}

QString FindDialog::getFindByNumberText()
{
    return findByNumberText;
}


#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    FindDialog(QWidget *parent = nullptr);
    QString getFindByNameText();
    QString getFindByNumberText();
    void setFindByNameTextEmpty();
    void setFindByNumberTextEmpty();


public slots:
    void findByNameClicked();
    void findByNumberClicked();


private:
    QPushButton *findByNameButton;
    QLineEdit *nameInputField;
    QString findByNameText;

    QPushButton *findByNumberButton;
    QLineEdit *numberInputField;
    QString findByNumberText;
};

#endif

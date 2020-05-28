#ifndef TELEPHONEBOOK_H
#define TELEPHONEBOOK_H

#include <QWidget>
#include <QMap>
#include "finddialog.h"

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
class QLineEdit;
class QTextEdit;
QT_END_NAMESPACE


class TelephoneBook : public QWidget
{
    Q_OBJECT

public:
    TelephoneBook(QWidget *parent = nullptr);
    enum Mode { NavigationMode, AddingMode, EditingMode, AddingNumberMode };

public slots:
            void addContact();
    void editContact();
    void addNumberToContact();
    void submitContact();
    void cancel();
    void removeContact();
    void findContact();
    void next();
    void previous();


private:
    void updateInterface(Mode mode);

    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QPushButton *findButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;
    QPushButton *nextButton;
    QPushButton *previousButton;
    QPushButton *addNumberButton;


    QLineEdit *nameLine;
    QTextEdit *addressText;

    QMultiMap<QString, QString> contacts;

    FindDialog *dialog;
    QString oldName;
    QString oldAddress;
    Mode currentMode;
};

#endif

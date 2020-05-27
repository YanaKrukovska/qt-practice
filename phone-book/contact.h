#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>
#include <QTreeWidgetItem>

class Contact : public QTreeWidgetItem
{
    QString name;
    QVector<QString>* phoneNumbers;

public:
    Contact();
    Contact(QString name);
    ~Contact();

    QString getName() const;
    void setName(QString);
    void editName(QString);

    void addNumber(QString);
    QVector<QString>* getPhoneNumbers();

};

#endif // CONTACT_H

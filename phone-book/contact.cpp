#include "contact.h"

Contact::Contact()
{

}



Contact::Contact(QString name) : name(name), QTreeWidgetItem(1)
{
    phoneNumbers = new QVector<QString>;
    phoneNumbers->reserve(100);
}

QString Contact::getName() const {
    return this->name;
}

void Contact::setName(QString name) {
    this->name = name;
}

void Contact::editName(QString newName) {
    this->name = newName;
}

void Contact::addNumber(QString newNumber){
    this->phoneNumbers->append(newNumber);
}

QVector<QString>* Contact::getPhoneNumbers(){
    return this->phoneNumbers;
}


Contact::~Contact() {
    delete this->phoneNumbers;
}

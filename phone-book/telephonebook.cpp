#include <QtWidgets>
#include "telephonebook.h"

TelephoneBook::TelephoneBook(QWidget *parent)
        : QWidget(parent)
{
 QLabel *nameLabel = new QLabel(tr("Name:"));
 nameLine = new QLineEdit;
 nameLine->setReadOnly(true);

 QLabel *addressLabel = new QLabel(tr("Phone number:"));
 addressText = new QTextEdit;
 addressText->setReadOnly(true);

 addButton = new QPushButton(tr("&Add"));
 addNumberButton = new QPushButton(tr("&Add Number"));
 addNumberButton->setEnabled(false);
 editButton = new QPushButton(tr("&Edit"));
 editButton->setEnabled(false);
 removeButton = new QPushButton(tr("&Remove"));
 removeButton->setEnabled(false);
 findButton = new QPushButton(tr("&Find"));
 findButton->setEnabled(false);
 submitButton = new QPushButton(tr("&Submit"));
 submitButton->hide();
 cancelButton = new QPushButton(tr("&Cancel"));
 cancelButton->hide();

 nextButton = new QPushButton(tr("&Next"));
 nextButton->setEnabled(false);
 previousButton = new QPushButton(tr("&Previous"));
 previousButton->setEnabled(false);


 dialog = new FindDialog(this);

 connect(addButton, &QPushButton::clicked,
         this, &TelephoneBook::addContact);
 connect(addNumberButton, &QPushButton::clicked,
         this, &TelephoneBook::addNumberToContact);
 connect(submitButton, &QPushButton::clicked,
         this, &TelephoneBook::submitContact);
 connect(editButton, &QPushButton::clicked,
         this, &TelephoneBook::editContact);
 connect(removeButton, &QPushButton::clicked,
         this, &TelephoneBook::removeContact);
 connect(cancelButton, &QPushButton::clicked,
         this, &TelephoneBook::cancel);
 connect(findButton, &QPushButton::clicked,
         this, &TelephoneBook::findContact);
 connect(nextButton, &QPushButton::clicked,
         this, &TelephoneBook::next);
 connect(previousButton, &QPushButton::clicked,
         this, &TelephoneBook::previous);

 QVBoxLayout *panelLayout = new QVBoxLayout;
 panelLayout->addWidget(addButton);
 panelLayout->addWidget(addNumberButton);
 panelLayout->addWidget(editButton);
 panelLayout->addWidget(removeButton);
 panelLayout->addWidget(findButton);
 panelLayout->addWidget(submitButton);
 panelLayout->addWidget(cancelButton);
 panelLayout->addStretch();

 QHBoxLayout *controlsLayout = new QHBoxLayout;
 controlsLayout->addWidget(previousButton);
 controlsLayout->addWidget(nextButton);

 QGridLayout *viewLayout = new QGridLayout;
 viewLayout->addWidget(nameLabel, 0, 0);
 viewLayout->addWidget(nameLine, 0, 1);
 viewLayout->addWidget(addressLabel, 1, 0, Qt::AlignTop);
 viewLayout->addWidget(addressText, 1, 1);
 viewLayout->addLayout(panelLayout, 1, 2);
 viewLayout->addLayout(controlsLayout, 2, 1);

 setLayout(viewLayout);
 setWindowTitle(tr("Telephone Book"));
}

void TelephoneBook::addContact()
{
 oldName = nameLine->text();
 oldAddress = addressText->toPlainText();

 nameLine->clear();
 addressText->clear();

 updateInterface(AddingMode);
}

void TelephoneBook::addNumberToContact()
{
 oldName = nameLine->text();
 oldAddress = addressText->toPlainText();
 QString text = QInputDialog::getText(this,tr("Adding new number"),tr("new number: "));
 contacts.insert(oldName, text);

 QString numbers = "";
 QList<QString> values = contacts.values(oldName);
 for (int i = 0; i < values.size(); i++){
  numbers.append(values.at(i)).append("\n");
 }
 addressText->clear();
 addressText->setPlainText(numbers);

 updateInterface(AddingNumberMode);
}


void TelephoneBook::editContact()
{
 oldName = nameLine->text();
 oldAddress = addressText->toPlainText();

 updateInterface(EditingMode);
}

void TelephoneBook::submitContact()
{
 QString name = nameLine->text();
 QString address = addressText->toPlainText();


 if (name.isEmpty() || address.isEmpty()) {
  QMessageBox::information(this, tr("Empty Field"),
                           tr("Please enter a name and phone number."));
  return;
 }
 if (currentMode == AddingMode) {

  if (!contacts.contains(name)) {
   contacts.insert(name, address);
   QMessageBox::information(this, tr("Add Successful"),
                            tr("\"%1\" has been added to your telphone book.").arg(name));
  } else {
   QMessageBox::information(this, tr("Error"),
                            tr("Sorry, \"%1\" is already in your telphone book.").arg(name));
  }
 } else if (currentMode == EditingMode) {

  if (oldName != name) {
   if (!contacts.contains(name)) {
    QMessageBox::information(this, tr("Edit Successful"),
                             tr("\"%1\" has been edited in your telphone book.").arg(oldName));
    contacts.remove(oldName);
    contacts.insert(name, address);
   } else {
    QMessageBox::information(this, tr("Error"),
                             tr("Sorry, \"%1\" is already in your telphone book.").arg(name));
   }
  }
 }
 updateInterface(NavigationMode);
}

void TelephoneBook::cancel()
{
 nameLine->setText(oldName);
 addressText->setText(oldAddress);
 updateInterface(NavigationMode);
}

void TelephoneBook::removeContact()
{
 QString name = nameLine->text();
 QString address = addressText->toPlainText();

 if (contacts.contains(name)) {

  int button = QMessageBox::question(this,
                                     tr("Confirm Remove"),
                                     tr("Are you sure you want to remove \"%1\"?").arg(name),
                                     QMessageBox::Yes | QMessageBox::No);

  if (button == QMessageBox::Yes) {

   previous();
   contacts.remove(name);

   QMessageBox::information(this, tr("Remove Successful"),
                            tr("\"%1\" has been removed from your telphone book.").arg(name));
  }
 }

 updateInterface(NavigationMode);
}

void TelephoneBook::next()
{
 QString name = nameLine->text();
 QMap<QString, QString>::iterator i = contacts.find(name);

 if (i != contacts.end())
  i++;

 if (i == contacts.end())
  i = contacts.begin();

 nameLine->setText(i.key());
 QString numbers = "";
 QList<QString> values = contacts.values(name);
 for (int i = 0; i < values.size(); i++){
  numbers.append(values.at(i)).append("\n");
 }
 addressText->clear();
 addressText->setPlainText(numbers);

}

void TelephoneBook::previous()
{
 QString name = nameLine->text();
 QMap<QString, QString>::iterator i = contacts.find(name);

 if (i == contacts.end()) {
  nameLine->clear();
  addressText->clear();
  return;
 }

 if (i == contacts.begin())
  i = contacts.end();

 i--;
 nameLine->setText(i.key());

 QString numbers = "";
 QList<QString> values = contacts.values(name);
 for (int i = 0; i < values.size(); i++){
  numbers.append(values.at(i)).append("\n");
 }
 addressText->clear();
 addressText->setPlainText(numbers);
}

void TelephoneBook::findContact()
{
 dialog->show();

 if (dialog->exec() == 1) {
  QString contactName = dialog->getFindText();

  if (contacts.contains(contactName)) {
   nameLine->setText(contactName);
   addressText->setText(contacts.value(contactName));
  } else {
   QMessageBox::information(this, tr("Contact Not Found"),
                            tr("Sorry, \"%1\" is not in your telphone book.").arg(contactName));
   return;
  }
 }

 updateInterface(NavigationMode);
}
void TelephoneBook::updateInterface(Mode mode)
{
 currentMode = mode;

 switch (currentMode) {

  case AddingMode:
   nameLine->setReadOnly(false);
   nameLine->setFocus(Qt::OtherFocusReason);
   addressText->setReadOnly(false);

   addButton->setEnabled(false);
   editButton->setEnabled(false);
   removeButton->setEnabled(false);

   nextButton->setEnabled(false);
   previousButton->setEnabled(false);

   submitButton->show();
   cancelButton->show();


   break;


  case AddingNumberMode:
   nameLine->setReadOnly(true);
   nameLine->setFocus(Qt::OtherFocusReason);
   addressText->setReadOnly(true);
   addButton->setEnabled(false);
   editButton->setEnabled(false);
   removeButton->setEnabled(false);
   nextButton->setEnabled(true);
   previousButton->setEnabled(true);

   submitButton->hide();
   cancelButton->show();


   break;


  case EditingMode:

   nameLine->setReadOnly(false);
   nameLine->setFocus(Qt::OtherFocusReason);
   addressText->setReadOnly(true);

   addButton->setEnabled(false);
   editButton->setEnabled(false);
   removeButton->setEnabled(false);

   nextButton->setEnabled(false);
   previousButton->setEnabled(false);

   submitButton->show();
   cancelButton->show();


   break;



  case NavigationMode:

   if (contacts.isEmpty()) {
    nameLine->clear();
    addressText->clear();
   }

   nameLine->setReadOnly(true);
   addressText->setReadOnly(true);
   addButton->setEnabled(true);

   int number = contacts.size();
   editButton->setEnabled(number >= 1);
   addNumberButton->setEnabled(number >= 1);
   removeButton->setEnabled(number >= 1);
   findButton->setEnabled(number > 1);
   nextButton->setEnabled(number > 1);
   previousButton->setEnabled(number > 1);

   submitButton->hide();
   cancelButton->hide();

   break;


 }
}

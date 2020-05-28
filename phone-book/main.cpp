#include <QtWidgets>
#include "telephonebook.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TelephoneBook addressBook;
    addressBook.show();

    return app.exec();
}
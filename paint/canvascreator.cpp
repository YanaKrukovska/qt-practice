#include "canvascreator.h"

int CanvasCreator::width = 900;
int CanvasCreator::height = 900;

CanvasCreator::CanvasCreator(Canvas *CanvasArea) : QWidget()
{
    setWindowTitle("New Canvas");
    resize(300,150);

    widthLabel = new QLabel;
    heightLabel = new QLabel;

    QVBoxLayout *layout = new QVBoxLayout(this);
    QFormLayout *form = new QFormLayout;

    form->addRow("Width:",widthLabel);
    form->addRow("Height:",heightLabel);

    getWidthButton = new QPushButton("Set width");
    getHeightButton = new QPushButton("Set Height");
    createButton = new QPushButton("Create");

    layout->addLayout(form);
    layout->addWidget(getWidthButton);
    layout->addWidget(getHeightButton);
    layout->addWidget(createButton);

    connect(getWidthButton,SIGNAL(clicked(bool)),this,SLOT(getWidthInput()));
    connect(getHeightButton,SIGNAL(clicked(bool)),this,SLOT(getHeightInput()));
    connect(createButton,SIGNAL(clicked(bool)),CanvasArea,SLOT(newCanvasArea()));
    connect(createButton,SIGNAL(clicked(bool)),this,SLOT(close()));
}


void CanvasCreator::showCanvas()
{
    this->show();
}

void CanvasCreator::getWidthInput()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Canvas width"),tr("Select canvas width (1-900):"), width,
                                        1, 900, 1, &ok);
    if (ok){
        CanvasCreator::width = newWidth;
        widthLabel->setText(tr("\%1").arg( CanvasCreator::width));
    }

}
void CanvasCreator::getHeightInput()
{
    bool ok;
    int newHeight = QInputDialog::getInt(this, tr("Canvas height"),tr("Select canvas height (1-900):"), width,
                                         1, 900, 1, &ok);
    if (ok){
        CanvasCreator::height = newHeight;
        heightLabel->setText(tr("\%1").arg(CanvasCreator::height));
    }
}

int CanvasCreator::getWidth()
{
    return width;
}

int CanvasCreator::getHeight()
{
    return height;
}

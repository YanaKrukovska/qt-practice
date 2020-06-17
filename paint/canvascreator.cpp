#include "canvascreator.h"
#include "ui_canvascreator.h"

int CanvasCreator::width = 500;
int CanvasCreator::height = 500;

CanvasCreator::CanvasCreator(Canvas *canvas) : QWidget(),
                                               ui(new Ui::CanvasCreator) {
    ui->setupUi(this);
    connect(ui->createButton, SIGNAL(clicked(bool)), canvas, SLOT(newCanvasArea()));
}

CanvasCreator::~CanvasCreator() {
    delete ui;
}

void CanvasCreator::showCanvas() {
    this->show();
}

int CanvasCreator::getWidth() {
    return width;
}

int CanvasCreator::getHeight() {
    return height;
}

void CanvasCreator::on_widthButton_clicked() {
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Canvas width"), tr("Select canvas width (10-800):"), width,
                                        10, 800, 1, &ok);
    if (ok) {
        CanvasCreator::width = newWidth;
        ui->widthLabel->setText(tr("Width: %1").arg(CanvasCreator::width));
    }
}

void CanvasCreator::on_heightButton_clicked() {
    bool ok;
    int newHeight = QInputDialog::getInt(this, tr("Canvas height"), tr("Select canvas height (10-800):"), width,
                                         10, 800, 1, &ok);
    if (ok) {
        CanvasCreator::height = newHeight;
        ui->heightLabel->setText(tr("Height: %1").arg(CanvasCreator::height));
    }
}

void CanvasCreator::on_createButton_clicked() {
    this->close();
}

//
// Created by user on 03.06.2020.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getFilePath(){
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Text files (*.txt)"));
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);

    QStringList filePath;
    if (dialog.exec()){
        filePath = dialog.selectedFiles();
        return filePath.last();
    }

    // To prevent crashing when no file was chosen
    return "";
}

void MainWindow::on_chooseInputButton_clicked()
{
    ui->inputFilepathView->setText(getFilePath());
}

void MainWindow::on_chooseOutputButton_clicked()
{
    ui->outputFilepathView->setText(getFilePath());
}

void MainWindow::on_pushButton_clicked()
{
    QFile inputFile(ui->inputFilepathView->text());
    QFile outputFile(ui->outputFilepathView->text());

    if (!inputFile.exists() || !outputFile.exists()){
        QMessageBox::information(this, tr("Error"), tr("Please choose files"));
        return;
    }


    if (inputFile.open(QIODevice::ReadOnly) && outputFile.open(QIODevice::WriteOnly))
    {
        QTextStream in(&inputFile);
        QTextStream out(&outputFile);

        while (!in.atEnd())
        {
            QString line = in.read(1);
            if (QString::compare(line, "\t", Qt::CaseInsensitive) == 0){
                out << " ";
            } else if (QString::compare(line, "\n", Qt::CaseInsensitive) != 0 && QString::compare(line, "\r", Qt::CaseInsensitive) != 0){
                out << line;
            }
        }

        inputFile.close();
        outputFile.close();
    }

    QMessageBox::information(this, tr("Success"), tr("Your files have been processed"));
}

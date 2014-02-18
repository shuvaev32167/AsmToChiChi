#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
    ui->textBrowser->clear();
    ui->textBrowser_2->clear();
}

void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser_2->clear();
    try
    {
        AsmToBin asmToBin(ui->textEdit->toPlainText());
    }
    catch (QString str)
    {
        QMessageBox::warning(this, "Error", str);
    }

//    QString *string = new QString(ui->textEdit->toPlainText());
//    qDebug() << *string;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    text = "";
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
    char type;
    if (ui->radioButton->isChecked())
        type = 0;
    else
        if (ui->radioButton_2->isChecked())
            type = 1;
    AsmToBin *asmToBin;
    try
    {
        asmToBin = new AsmToBin(ui->textEdit->toPlainText(),type);
        text = asmToBin->getBinText();
        ui->textBrowser->setPlainText(text);
    }
    catch (QString str)
    {
        QMessageBox::warning(this, "Error", str);
    }
    text = convertBinToHex(text);
    ui->textBrowser_2->setPlainText(text);
//    QString *string = new QString(ui->textEdit->toPlainText());
    //    qDebug() << *string;
}

QString MainWindow::convertBinToHex(QString binText)
{
    QString hexText, bufHexText;
    QStringList qslBinText = binText.split('\n');
    char size = qslBinText.size();
    for (char i =0; i < size; ++i)
    {
        if (qslBinText[i] == "")
            continue;
        bufHexText = QString::number(binText.split('\n')[i].toLongLong(0,2),16);
        if (bufHexText.size()%2 != 0)
            bufHexText="0"+bufHexText;
        hexText += "\n" + bufHexText;
    }
    hexText.remove(0,1);
    return hexText;
}

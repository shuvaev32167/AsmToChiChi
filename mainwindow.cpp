#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    text = "";
    ui->setupUi(this);

    this->installEventFilter(this);

#ifdef __WIN32__ || __WIN64__
    QMessageBox::information(this,"Великое сообщение!",
                             "Братья и сёстры.\nВо имя уничтожения империи грифона:\n\"Повеливаю перейти на сторону добра и света!\"");
    QDesktopServices::openUrl(QUrl("http://gentoo.org"));
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonClear_clicked()
{
    ui->textEditAsm->clear();
    ui->textEditBin->clear();
    ui->textEditHex->clear();
}

void MainWindow::on_pushButtonStart_clicked()
{
    ui->textEditBin->clear();
    ui->textEditHex->clear();
    char type;
    if (ui->radioButtonByte->isChecked())
        type = 0;
    else
        if (ui->radioButtonWord->isChecked())
            type = 1;
    AsmToBin *asmToBin;
    try
    {
        asmToBin = new AsmToBin(ui->textEditAsm->toPlainText(),type);
        text = asmToBin->getBinText();
        ui->textEditBin->setPlainText(text);
    }
    catch (QString str)
    {
        QMessageBox::warning(this, "Error", str);
    }
    text = convertBinToHex(text);
    ui->textEditHex->setPlainText(text);
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

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::Close)
        if (QMessageBox::information(this,"Великое объявление","Смерть Имериии Грифона!",
                                     QMessageBox::Yes,QMessageBox::No) == QMessageBox::No)
            QMessageBox::warning(this, "Смерть грифонцам!", "Гори в аду грифонец!\nЛюций уже ждёт тебя!");
    return 0;
}

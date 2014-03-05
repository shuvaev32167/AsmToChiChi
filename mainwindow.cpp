#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    text = "";
    ui->setupUi(this);

    ui->comboBoxAddrK->addItem("Регистр");
    ui->comboBoxAddrK->addItem("Память");

    ui->comboBoxAddrM->setModel(ui->comboBoxAddrK->model());
    ui->comboBoxAddrN->setModel(ui->comboBoxAddrK->model());
    ui->comboBoxAddrR->setModel(ui->comboBoxAddrK->model());

    ui->comboBoxRegistersK->addItem("AX");
    ui->comboBoxRegistersK->addItem("CX");
    ui->comboBoxRegistersK->addItem("DX");
    ui->comboBoxRegistersK->addItem("BX");
    ui->comboBoxRegistersK->addItem("SP");
    ui->comboBoxRegistersK->addItem("BP");
    ui->comboBoxRegistersK->addItem("SI");
    ui->comboBoxRegistersK->addItem("SI");

    ui->comboBoxRegistersM->setModel(ui->comboBoxRegistersK->model());
    ui->comboBoxRegistersN->setModel(ui->comboBoxRegistersK->model());
    ui->comboBoxRegistersR->setModel(ui->comboBoxRegistersK->model());

    ui->lineEditValueM->setText("");
    ui->comboBoxAddrM->setCurrentIndex(1);
    ui->lineEditAddrMemoryM->setText("0504");

    ui->lineEditValueK->setText("0060");
    ui->comboBoxAddrK->setCurrentIndex(1);
    ui->lineEditAddrMemoryK->setText("0500");


//    this->installEventFilter(this);

//#ifdef __WIN32__ || __WIN64__
//    QMessageBox::information(this,"Великое сообщение!",
//                             "Братья и сёстры.\nВо имя уничтожения империи грифона:\n\"Повеливаю перейти на сторону добра и света!\"");
//    QDesktopServices::openUrl(QUrl("http://gentoo.org"));
//#endif
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
    if (ui->textEditAsm->toPlainText() == "")
    {
        QMessageBox::information(this, "Нет данных", "Необходимо заполнить код на асме");
        return;
    }
    ui->textEditBin->clear();
    ui->textEditHex->clear();
    char type;
    if (ui->radioButtonByte->isChecked())
        type = Type::byte;
    else
        if (ui->radioButtonWord->isChecked())
            type = Type::word;
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
        bufHexText = QString::number(qslBinText[i].toLongLong(0,2),16);
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

void MainWindow::on_pushButtonToAsm_clicked()
{
}

void MainWindow::on_radioButtonWord_clicked()
{
    ui->comboBoxRegistersK->addItem("AX");
    ui->comboBoxRegistersK->addItem("CX");
    ui->comboBoxRegistersK->addItem("DX");
    ui->comboBoxRegistersK->addItem("BX");
    ui->comboBoxRegistersK->addItem("SP");
    ui->comboBoxRegistersK->addItem("BP");
    ui->comboBoxRegistersK->addItem("SI");
    ui->comboBoxRegistersK->addItem("SI");

    ui->comboBoxRegistersM->setModel(ui->comboBoxRegistersK->model());
    ui->comboBoxRegistersN->setModel(ui->comboBoxRegistersK->model());
    ui->comboBoxRegistersR->setModel(ui->comboBoxRegistersK->model());
}

void MainWindow::on_radioButtonByte_clicked()
{
    ui->comboBoxRegistersK->addItem("AL");
    ui->comboBoxRegistersK->addItem("CL");
    ui->comboBoxRegistersK->addItem("DL");
    ui->comboBoxRegistersK->addItem("BL");
    ui->comboBoxRegistersK->addItem("AH");
    ui->comboBoxRegistersK->addItem("CH");
    ui->comboBoxRegistersK->addItem("DH");
    ui->comboBoxRegistersK->addItem("BH");

    ui->comboBoxRegistersM->setModel(ui->comboBoxRegistersK->model());
    ui->comboBoxRegistersN->setModel(ui->comboBoxRegistersK->model());
    ui->comboBoxRegistersR->setModel(ui->comboBoxRegistersK->model());
}

void MainWindow::on_comboBoxAddrM_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        ui->lineEditAddrMemoryM->hide();
        ui->comboBoxRegistersM->show();
        break;
    case 1:
        ui->comboBoxRegistersM->hide();
        ui->lineEditAddrMemoryM->show();
        break;
    }
}

void MainWindow::on_comboBoxAddrK_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        ui->lineEditAddrMemoryK->hide();
        ui->comboBoxRegistersK->show();
        break;
    case 1:
        ui->comboBoxRegistersK->hide();
        ui->lineEditAddrMemoryK->show();
        break;
    }
}

void MainWindow::on_comboBoxAddrR_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        ui->lineEditAddrMemoryR->hide();
        ui->comboBoxRegistersR->show();
        break;
    case 1:
        ui->comboBoxRegistersR->hide();
        ui->lineEditAddrMemoryR->show();
        break;
    }
}

void MainWindow::on_comboBoxAddrN_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        ui->lineEditAddrMemoryN->hide();
        ui->comboBoxRegistersN->show();
        break;
    case 1:
        ui->comboBoxRegistersN->hide();
        ui->lineEditAddrMemoryN->show();
        break;
    }
}

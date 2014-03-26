#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTextEdit>
#include <QMessageBox>
//#include <QDialogButtonBox>
//#include <QDesktopServices>

#include "AsmToBin.h"
//#include "BinToHex.h"
//#include <QTime>
//#include <QSpacerItem>

#include "ErrorAsm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonClear_clicked();

    void on_pushButtonStart_clicked();

    void on_pushButtonToAsm_clicked();

    void on_radioButtonWord_clicked();

    void on_radioButtonByte_clicked();

    void on_comboBoxAddrM_currentIndexChanged(int index);

    void on_comboBoxAddrK_currentIndexChanged(int index);

    void on_comboBoxAddrR_currentIndexChanged(int index);

    void on_comboBoxAddrN_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    QString text;

    QString convertBinToHex(QString binText);

protected:
    virtual bool eventFilter(QObject *object, QEvent *event);
};

#endif // MAINWINDOW_H

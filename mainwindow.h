#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTextEdit>
#include <QMessageBox>
//#include <QDialogButtonBox>
//#include <QDesktopServices>

#include "AsmToBin.h"
#include "BinToHex.h"
#include <QTime>

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

private:
    Ui::MainWindow *ui;

    QString text;

    QString convertBinToHex(QString binText);

protected:
    virtual bool eventFilter(QObject *object, QEvent *event);
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qf(":/tr/qt_ru.qm");
    if (qf.exists())
        qDebug() << 123;
    else
        qDebug() << ":/translate/qt_"+QLocale::system().name();
    QTranslator *qtTranslator = new QTranslator(qApp);
//    qtTranslator->load("qt_" + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    if (!qtTranslator->load("qt_ru.qm", "./"))
    {
        qDebug() << "Fail1";
        QTranslator *translator = new QTranslator(qApp);
    //    qtTranslator->load("qt_" + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        if (!translator->load("qt_ru","tr"))
        {
            qDebug() << "Fail2";
            QString locale = QLocale::system().name();

            QTranslator *QtTranslator = new QTranslator(qApp);
            //    qtTranslator->load("qt_" + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
            if (!QtTranslator->load("qt_ru", "translations"))
                qDebug() << "Fail3";
            qApp->installTranslator(QtTranslator);
        }
        qApp->installTranslator(translator);
    }
    qApp->installTranslator(qtTranslator);

    MainWindow w;
    w.show();

    return a.exec();
}

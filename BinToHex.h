#ifndef BINTOHEX_H
#define BINTOHEX_H

#include <QString>
#include <QStringList>
#include <QChar>
#include <QMap>

class BinToHex
{
public:
    BinToHex(const QString &binText);
    BinToHex(const int &value);

    QString getHexText();

    void binToHex(const QString &binText);
private:
    QString binText;
    QString hexText;

//    void binToHex(const QString &binText);
};

#endif // BINTOHEX_H

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

    QString getHexText();
private:
    QString binText;
    QString hexText;

    void binToHex();
};

#endif // BINTOHEX_H

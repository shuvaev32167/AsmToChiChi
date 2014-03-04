#ifndef ASMTOBIN_H
#define ASMTOBIN_H

#include <QString>
#include <QStringList>
#include <QDebug>
#include <QMap>

namespace Type
{
    enum {byte = 0, word = 1};
}

class AsmToBin
{
public:
    AsmToBin(QString str, char type);

    QString getBinText();
private:
    QString asmText;
    QString binText;

    QMap<QString, QString> registers;

    char type;

    void asmToBin();

    void move(QStringList qslBufZPT);
    void sub(QStringList qslBufZPT);
    void add(QStringList qslBufZPT);
};

#endif // ASMTOBIN_H

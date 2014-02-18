#ifndef ASMTOBIN_H
#define ASMTOBIN_H

#include <QString>
#include <QStringList>
#include <QDebug>
#include <QMap>

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

    void move(QStringList qslBufSpace, QStringList qslBufZPT);
    void sub(QStringList qslBufSpace, QStringList qslBufZPT);
};

#endif // ASMTOBIN_H

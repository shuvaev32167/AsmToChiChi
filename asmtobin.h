#ifndef ASMTOBIN_H
#define ASMTOBIN_H

#include <QString>
#include <QStringList>
#include <QDebug>

class AsmToBin
{
public:
    AsmToBin(QString str, char type);

    QString getBinText();
private:
    QString asmText;
    QString binText;

    char type;

    void asmToBin();
};

#endif // ASMTOBIN_H

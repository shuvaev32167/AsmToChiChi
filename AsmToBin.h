#ifndef ASMTOBIN_H
#define ASMTOBIN_H

#include <QString>
#include <QStringList>
#include <QDebug>
#include <QMap>

#include "ErrorAsm.h"

namespace Type
{
    enum {byte = 0, word = 1};
}

class AsmToBin
{
public:
    AsmToBin(const QString &str, const char &type);

    QString getBinText() const;
private:
    QString asmText;
    QString binText;

    QMap<QString, QString> registers;

    char type;

    void asmToBin();

    void move(QStringList qslBufZPT);
    void sub(QStringList qslBufZPT);
    void add(QStringList qslBufZPT);

    void convertHexToBin(const QString &input, const bool& chislo);
};

#endif // ASMTOBIN_H

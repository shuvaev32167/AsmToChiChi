#ifndef ERRORASM_H
#define ERRORASM_H

#include <QString>

class ErrorAsm
{
public:
    ErrorAsm(const QString &str, const int &row);

    QString str;

    int row;
};

#endif // ERRORASM_H

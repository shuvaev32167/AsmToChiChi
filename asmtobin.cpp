#include "asmtobin.h"

AsmToBin::AsmToBin(QString str, char type)
{
    asmText = str;
    this->type = type;
    asmToBin();
}

QString AsmToBin::getBinText()
{
    return binText;
}

void AsmToBin::asmToBin()
{
    QStringList qslAsmCommand = asmText.split('\n'), qslBufSpace, qslBufZPT;
    if (qslAsmCommand.last() == "")
        qslAsmCommand.removeLast();
    int size = qslAsmCommand.count();
    if (size <= 0)
        throw QString("Нулевой размер команд asm");
    for (int i = 0; i < size; ++i)
    {
        qslBufSpace.clear();
        qslBufZPT.clear();
        qslBufSpace = qslAsmCommand[i].split(' ');
        if (qslBufSpace.count() == 2)
            qslBufZPT = qslBufSpace.last().split(',');
        if (qslBufZPT.empty())
            if (qslBufSpace.first() == "NOP" || qslBufSpace.first() == "nop")
            {
                binText += "\n10010000";
                continue;
            }
        if (qslBufSpace.first() == "MOVE" || qslBufSpace.first() == "move")
        {
            if (qslBufZPT.empty()|| qslBufZPT.first() == "")
                throw QString("MOVE без данных");
            else
                if (qslBufZPT.count() != 2 || qslBufZPT.last() == "")
                    throw QString("Не верное число параметров у MOVE");
            if (qslBufZPT.last()[0] == "[" && (qslBufZPT.first() == "AX" || qslBufZPT.first() == "AX"))
            {
                binText += "\n1010";
                if (type == 1)
                    binText +="0001";
                char size = qslBufZPT.last().count()-1;
                QString buf ="";
                for (char i = 1; i < size; ++i)
                {
                    buf = QString::number(qslBufZPT.last()[i]);
                    if (buf != "")
                        binText += buf;
                    else
                        if (i != size-1)
                            throw QString("Не верно казан адресс памяти у MOVE");
                }
            }
        }
    }
}

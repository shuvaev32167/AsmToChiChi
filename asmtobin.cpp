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
            if (qslBufZPT.last()[0] == '[' && (qslBufZPT.first() == "AX" || qslBufZPT.first() == "ax"))
            {
                binText += "\n1010";
                if (type == 1)
                    binText +="0001";
                char size = qslBufZPT.last().count()-1;
                QString nakop="";
                QChar buf;
                for (char i = 1; i < size; ++i)
                {
                    buf = qslBufZPT.last()[i];
                    if (buf != 'H' || buf !='h')
                        nakop += buf;
                    else
                        if (i != size-1)
                            throw QString("Не верно казан адресс памяти у MOVE");
                }
//                size = nakop.size();
                for (char i = 0; i < 4; ++i)
                {
                    if (nakop[i] == '0')
                        binText+="0000";
                    else
                        if (nakop[i] == '1')
                            binText+="0001";
                        else
                            if (nakop[i]=='2')
                                binText+="0010";
                            else
                                if (nakop[i] == '3')
                                    binText+="0011";
                                else
                                    if (nakop[i]=='4')
                                        binText+="0100";
                                    else
                                        if (nakop[i] == '5')
                                            binText+="0101";
                                        else
                                            if (nakop[i]=='6')
                                                binText+="0110";
                                            else
                                                if (nakop[i] == '7')
                                                    binText+="0111";
                                                else
                                                    if (nakop[i]=='8')
                                                        binText+="1000";
                                                    else
                                                        if (nakop[i] == '9')
                                                            binText+="1001";
                                                        else
                                                            if (nakop[i]=='A')
                                                                binText+="1010";
                                                            else
                                                                if (nakop[i] == 'B')
                                                                    binText+="1011";
                                                                else
                                                                    if (nakop[i]=='C')
                                                                        binText+="1100";
                                                                    else
                                                                        if (nakop[i] == 'D')
                                                                            binText+="1101";
                                                                        else
                                                                            if (nakop[i]=='E')
                                                                                binText+="1110";
                                                                            else
                                                                                if (nakop[i] == 'F')
                                                                                    binText+="1111";
                }
//                binText += QString::number(nakop.toInt(0,16),2);
            }
        }
        binText.remove(0,1);
        qDebug() << binText;
        qDebug() << binText.toLongLong(0,2);
        qDebug () << QString::number(binText.toLongLong(0,2),16);
    }
}

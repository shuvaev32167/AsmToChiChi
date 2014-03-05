#include "AsmToBin.h"

AsmToBin::AsmToBin(QString str, char type)
{
    /*if (registers.contains("AX"))
        qDebug() << "yes";*/
    asmText = str;
    if (type == Type::word)
    {
        registers.insert("AX","000");
        registers.insert("CX","001");
        registers.insert("DX","010");
        registers.insert("BX","011");
        registers.insert("SP","100");
        registers.insert("BP","101");
        registers.insert("SI","110");
        registers.insert("DI","111");

        registers.insert("ax","000");
        registers.insert("cx","001");
        registers.insert("dx","010");
        registers.insert("bx","011");
        registers.insert("sp","100");
        registers.insert("bp","101");
        registers.insert("si","110");
        registers.insert("di","111");
    }
    else
        if (type == Type::byte)
        {
            registers.insert("AL","000");
            registers.insert("CL","001");
            registers.insert("DL","010");
            registers.insert("BL","011");
            registers.insert("AH","100");
            registers.insert("CH","101");
            registers.insert("DH","110");
            registers.insert("BH","111");

            registers.insert("al","000");
            registers.insert("cl","001");
            registers.insert("dl","010");
            registers.insert("bl","011");
            registers.insert("ah","100");
            registers.insert("ch","101");
            registers.insert("dh","110");
            registers.insert("bh","111");
        }
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
        if (qslBufSpace.first() == "MOV" || qslBufSpace.first() == "mov")
        {
            move(qslBufZPT);
            continue;
        }
        else
            if (qslBufSpace.first() == "SUB" || qslBufSpace.first() == "sub")
            {
                sub(qslBufZPT);
                continue;
            }
            else
                if (qslBufSpace.first() == "ADD" || qslBufSpace.first() == "add")
                {
                    add(qslBufZPT);
                    continue;
                }
                else
                    if (qslBufSpace.first() != "" && qslBufSpace.size() != 2)
                        throw QString("Данна команда не обрабатывается (пока?)");
    }
    binText.remove(0,1);
    //    qDebug() << binText;
    //    for (int i =0; i < binText.split('\n').size(); ++i)
    //    {
    //        qDebug() << asmText.split('\n')[i];
    //        qDebug() << binText.split('\n')[i].toLongLong(0,2);
    //        qDebug () << QString::number(binText.split('\n')[i].toLongLong(0,2),16);
    //    }
    //    qDebug() << binText.split('\n').first().toLongLong(0,2);
    //    qDebug () << QString::number(binText.split('\n').first().toLongLong(0,2),16);
    //    qDebug() << binText.split('\n').last().toLongLong(0,2);
    //    qDebug () << QString::number(binText.split('\n').last().toLongLong(0,2),16);
}

void AsmToBin::move(QStringList qslBufZPT)
{
    if (qslBufZPT.empty()|| qslBufZPT.first() == "")
        throw QString("MOV без данных");
    else
        if (qslBufZPT.count() != 2 || qslBufZPT.last() == "")
            throw QString("Не верное число параметров у MOV");
    if (qslBufZPT.last()[0] == '[' && (qslBufZPT.first() == "AX" || qslBufZPT.first() == "ax" ||
                                       qslBufZPT.first() == "AL" || qslBufZPT.first() == "al"))
    {
        binText += "\n1010";
        if (type == Type::word)
            binText +="0001";
        else
            if (type == Type::byte)
                binText +="0000";
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
        size = nakop.size();
        for (char i = 2; i < size; ++i)
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
        for (char i = 0; i < 2; ++i)
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
    else
    {
        if (qslBufZPT.first()[0] == '[' && (qslBufZPT.last() == "AX" || qslBufZPT.first() == "ax" ||
                                            qslBufZPT.first() == "AL" || qslBufZPT.first() == "al"))
        {
            binText += "\n1010";
            if (type == Type::word)
                binText +="0011";
            else
                if (type == Type::byte)
                    binText+="0010";
            char size = qslBufZPT.first().count()-1;
            QString nakop="";
            QChar buf;
            for (char i = 1; i < size; ++i)
            {
                buf = qslBufZPT.first()[i];
                if (buf != 'H' || buf !='h')
                    nakop += buf;
                else
                    if (i != size-1)
                        throw QString("Не верно казан адресс памяти у MOVE");
            }
            size = nakop.size();
            for (char i = 2; i < size; ++i)
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
            for (char i = 0; i < 2; ++i)
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
        else
            if (registers.contains(qslBufZPT.first()) && registers.contains(qslBufZPT.last()))
            {
                binText+="\n1000101";
                if (type == Type::word)
                    binText+="111";
                else
                    if (type == Type::byte)
                        binText+="011";
                binText+=registers[qslBufZPT.first()] + registers[qslBufZPT.last()];
            }
            else
                if (registers.contains(qslBufZPT.first()) && qslBufZPT.last().size() == 5)
                {
                    binText += "\n1011";
                    if (type == Type::word)
                        binText += "1";
                    else
                        if (type == Type::byte)
                            binText += "0";
                    binText += registers[qslBufZPT.first()];
                    char size = qslBufZPT.last().count()-1;
                    QString nakop="";
                    QChar buf;
                    for (char i = 1; i < size; ++i)
                    {
                        buf = qslBufZPT.first()[i];
                        if (buf != 'H' || buf !='h')
                            nakop += buf;
                        else
                            if (i != size-1)
                                throw QString("Не верно казан адресс памяти у MOVE");
                    }
                    size = nakop.size();
                    for (char i = 2; i < size; ++i)
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
                    for (char i = 0; i < 2; ++i)
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
                }
                else
                    throw QString("Данные параметры у MOV не обрабатываются (пока?)");
    }
}

void AsmToBin::sub(QStringList qslBufZPT)
{
    if (qslBufZPT.empty()|| qslBufZPT.first() == "")
        throw QString("SUB без данных");
    else
        if (qslBufZPT.count() != 2 || qslBufZPT.last() == "")
            throw QString("Не верное число параметров у SUB");
    binText += "\n0010101";
    if (type == Type::word)
        binText += "111";
    else
        if (type == Type::byte)
            binText += "011";
    if (registers.contains(qslBufZPT.first()) && registers.contains(qslBufZPT.last()))
    {
        binText+=registers[qslBufZPT.first()] + registers[qslBufZPT.last()];
    }
    else
        throw QString("Данные параметры у SUB не обрабатываются (пока?)");
}

void AsmToBin::add(QStringList qslBufZPT)
{
    if (qslBufZPT.empty()|| qslBufZPT.first() == "")
        throw QString("ADD без данных");
    else
        if (qslBufZPT.count() != 2 || qslBufZPT.last() == "")
            throw QString("Не верное число параметров у ADD");
    if (qslBufZPT.last().size() == 2)
    {
        binText+="\n0000001";
        if (type == Type::word)
            binText+="111";
        else
            if (type == Type::byte)
                binText+="011";
        if (registers.contains(qslBufZPT.first()) && registers.contains(qslBufZPT.last()))
        {
            binText+=registers[qslBufZPT.first()] + registers[qslBufZPT.last()];
        }
        else
            throw QString("Данные параметры у add не обрабатываются (пока?)");
    }
    else
        if (qslBufZPT.last().size() == 5)
        {
            binText+="\n0000010";
            if (type == Type::word)
                binText+="1";
            else
                if (type == Type::byte)
                    binText+="0";
            char size = qslBufZPT.last().count();
            QString nakop="";
            QChar buf;
            for (char i = 0; i < size; ++i)
            {
                buf = qslBufZPT.last()[i];
                if (buf != 'H' || buf !='h')
                    nakop += buf;
                else
                    if (i != size-1)
                        throw QString("Не верно казан адресс памяти у MOVE");
            }
            size = nakop.size();
            for (char i = 2; i < size; ++i)
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
            for (char i = 0; i < 2; ++i)
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
        }
        else
            throw QString("Данные параметры у add не обрабатываются (пока?)");
}

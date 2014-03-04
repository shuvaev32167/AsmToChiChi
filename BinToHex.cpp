#include "BinToHex.h"

BinToHex::BinToHex(const QString &binText)
{
    this->binText = binText;
}

QString BinToHex::getHexText()
{
    return hexText;
}

void BinToHex::binToHex()
{
    QStringList qls = binText.split('\n');
//    int size = binText.size();
    QString buf;
    for (QString qs : qls)
    {
        hexText += '\n';
        int size = qs.size();
        while (size != 0)
        {
            buf = "";
            for (int i = size-5; i < size; ++i)
                buf += qs[i];
//            qs.remove(size-5,4);
            size -= 4;
            if (buf == "0000")
                hexText += '0';
            else
                if (buf == "0001")
                    hexText += '1';
                else
                    if (buf == "0010")
                        hexText += '2';
                    else
                        if (buf == "0011")
                            hexText += '3';
                        else
                            if (buf == "0100")
                                hexText += '4';
                            else
                                if (buf == "0101")
                                    hexText += '5';
                                else
                                    if (buf == "0110")
                                        hexText += '6';
                                    else
                                        if (buf == "0111")
                                            hexText += '7';
                                        else
                                            if (buf == "1000")
                                                hexText += '8';
                                            else
                                                if (buf == "1001")
                                                    hexText += '9';
                                                else
                                                    if (buf == "1010")
                                                        hexText += 'A';
                                                    else
                                                        if (buf == "1011")
                                                            hexText += 'B';
                                                        else
                                                            if (buf == "1100")
                                                                hexText += 'C';
                                                            else
                                                                if (buf == "1101")
                                                                    hexText += 'D';
                                                                else
                                                                    if (buf == "1110")
                                                                        hexText += 'E';
                                                                    else
                                                                        if (buf == "1111")
                                                                            hexText += 'F';
            if (size < 4 && size != 0)
                if (size == 3)
                {
                    size -= 3;
                    if (qs == "000")
                        hexText += '0';
                    else
                        if (qs == "001")
                            hexText += '1';
                        else
                            if (qs == "010")
                                hexText += '2';
                            else
                                if (qs == "011")
                                    hexText += '3';
                                else
                                    if (qs == "100")
                                        hexText += '4';
                                    else
                                        if (qs == "101")
                                            hexText += '5';
                                        else
                                            if (qs == "110")
                                                hexText += '6';
                                            else
                                                if (qs == "111")
                                                    hexText += '7';
                }
                else
                    if (size == 2)
                    {
                        size -= 2;
                        if (qs == "00")
                            hexText += '0';
                        else
                            if (qs == "01")
                                hexText += '1';
                            else
                                if (qs == "10")
                                    hexText += '2';
                                else
                                    if (qs == "11")
                                        hexText += '3';
                    }
                    else
                        if (size == 1)
                        {
                            size -= 1;
                            if (qs == "0")
                                hexText += '0';
                            else
                                if (qs == "1")
                                    hexText += '1';
                        }
        }
    }
    hexText.remove(0,1);
}

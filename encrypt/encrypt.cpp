#include "encrypt.h"
#include <QString>
#include <string>
using namespace std;
QString encrypt(QString msg,QString key)
{
    string msg1 = msg.toStdString();
    string key1 = key.toStdString();
    if (msg1.length() > key1.length())
        {
            while (msg1.length() >= key1.length())
                key1 += key1;
        }
    for (size_t i = 0; i < msg1.length(); i++)
        {
            msg1[i] ^= key1[i];
            msg1[i] += 32;
        }
    return QString::fromStdString(msg1);
}

QString decrypt(QString msg,QString key)
{
    string msg1 = msg.toStdString();
    string key1 = key.toStdString();
    if (msg1.length() > key1.length())
        {
            while (msg1.length() >= key1.length())
                key1 += key1;
        }
    for (size_t i = 0; i < msg1.length(); i++)
        {
            msg1[i] -= 32;
            msg1[i] ^= key1[i];
        }
    return QString::fromStdString(msg1);
}

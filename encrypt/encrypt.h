#ifndef ENCRYPT_H
#define ENCRYPT_H
#include <QString>
#include <string>
using namespace std;

QString encrypt(QString msg,QString key);
QString decrypt(QString msg,QString key);
#endif // ENCRYPT_H

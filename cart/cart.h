#ifndef CART_H
#define CART_H
#include <QDialog>
#include "connect/databaseconnection.h"
namespace Ui {
class Cart;
}
class Cart : public QDialog
{
    Q_OBJECT

public:
    QString account;
    explicit Cart(QString acc,QWidget *parent = 0);
    ~Cart();
    connectDatabase connect;
private slots:
    void on_pushButton_3_clicked();
    void on_backup();
    void on_pushButton_clicked();

private:
    Ui::Cart *ui;
};

#endif // CART_H

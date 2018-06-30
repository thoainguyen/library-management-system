#ifndef SIGNIN_H
#define SIGNIN_H
#include <QDialog>
#include "mainwindow/mainwindow.h"
extern QString proname;
namespace Ui {
class SignIn;
}

class SignIn : public QDialog
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = 0);
    ~SignIn();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::SignIn *ui;
};

#endif // SIGNIN_H

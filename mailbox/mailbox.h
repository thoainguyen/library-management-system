#ifndef MAILBOX_H
#define MAILBOX_H
#include "connect/databaseconnection.h"
#include <QTableView>
#include <QDialog>

namespace Ui {
class MailBox;
}

class MailBox : public QDialog
{
    Q_OBJECT

public:
    connectDatabase cnect;
    QString accName;
    explicit MailBox(QString ac,QWidget *parent = 0);
    ~MailBox();
public slots:
    void show_table_thuden(QTableView * t);
    void show_table_thugui(QTableView *t);
    void show_thuden(QString st);
    void show_thugui(QString st);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MailBox *ui;
};

#endif // MAILBOX_H

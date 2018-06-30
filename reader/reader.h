#ifndef READER_H
#define READER_H

#include <QWidget>

namespace Ui {
class reader;
}

class reader : public QWidget
{
    Q_OBJECT

public:
    QString accname;
    explicit reader(QString n,QWidget *parent = 0);
    ~reader();

private slots:
    void on_clear_tam();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();



private:
    Ui::reader *ui;
};

#endif // READER_H

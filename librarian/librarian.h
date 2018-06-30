#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include <QWidget>
#include <QString>
#include <QTableView>

namespace Ui {
class librarian;
}

class librarian : public QWidget
{
    Q_OBJECT

public:
    explicit librarian(QWidget *parent = 0);
    ~librarian();




private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void showbook_1(QTableView *w);
    void showbook_2(QTableView *w);
    void showbook_3(QTableView *w);
    void refresh();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_12_clicked();



    void on_pushButton_2_clicked();


    void on_pushButton_13_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::librarian *ui;
};

#endif // LIBRARIAN_H

#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QDialog>

namespace Ui {
class addbook;
}

class addbook : public QDialog
{
    Q_OBJECT
public:
    int idbook = 0;

public:

    explicit addbook(QWidget *parent = 0);
    explicit addbook(QModelIndex &index,QWidget *parent = 0);
    ~addbook();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_btn_clicked();

private:
    Ui::addbook *ui;
};

#endif // ADDBOOK_H

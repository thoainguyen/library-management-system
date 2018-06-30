#ifndef NOIQUY_H
#define NOIQUY_H

#include <QDialog>

namespace Ui {
class noiquy;
}

class noiquy : public QDialog
{
    Q_OBJECT

public:
    explicit noiquy(QWidget *parent = 0);
    ~noiquy();

private slots:
    void on_pushButton_clicked();



private:
    Ui::noiquy *ui;
};

#endif // NOIQUY_H

#ifndef FORGETPASS_H
#define FORGETPASS_H

#include <QDialog>

namespace Ui {
class forgetpass;
}

class forgetpass : public QDialog
{
    Q_OBJECT

public:
    explicit forgetpass(QWidget *parent = 0);
    ~forgetpass();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::forgetpass *ui;
};

#endif // FORGETPASS_H

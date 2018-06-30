#ifndef EDITUSER_H
#define EDITUSER_H

#include <QDialog>

namespace Ui {
class editUSER;
}

class editUSER : public QDialog
{
    Q_OBJECT

public:
    explicit editUSER(QWidget *parent = 0);
    explicit editUSER(QString profile);
    //explicit editUSER(QString cmnd,QString hoten,QString taikhoan,QString email,QString nghenghiep,QString ngaysinh,
                      //QString gioitinh,QString resetpass,bool docgia,bool thuthu,bool quanli,bool act);
    ~editUSER();

private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_deall_clicked();

    void on_pushButton_lock_clicked();

    void on_pushButton_changepass_clicked();

    void on_pushButton_savepass_clicked();

private:
    Ui::editUSER *ui;
};

#endif // EDITUSER_H

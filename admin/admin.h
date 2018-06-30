#ifndef ADMIN_H
#define ADMIN_H
#include <QWidget>
extern QString cmnd,hoten,taikhoan,email,nghenghiep,ngaysinh,gioitinh,resetpass;
extern bool docgia,thuthu,quanli,act;
namespace Ui {
class admin;
}

class admin : public QWidget
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = 0);
    ~admin();

private slots:
    void on_pushButton_5_clicked();

    void on_tableView_activated(const QModelIndex &index);



    void on_pushButton_addaccount_clicked();

    void on_tableView_tacvu_activated(const QModelIndex &index);

    void on_pushButton_clicked();



private:
    Ui::admin *ui;
};

#endif // ADMIN_H

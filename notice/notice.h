#ifndef NOTICE_H
#define NOTICE_H

#include <QDialog>

namespace Ui {
class notice;
}

class notice : public QDialog
{
    Q_OBJECT

public:
    explicit notice(QString thongbao);
    explicit notice(bool user);
    explicit notice(QWidget *parent = 0);
    ~notice();

private slots:
    void on_pushButton_refresh_clicked();

    void on_pushButton_dang_clicked();

    void on_pushButton_sua_clicked();

    void on_pushButton_huy_clicked();

    void on_pushButton_capnhat_clicked();

    void on_pushButton_xoa_clicked();

    void on_pushButton_xem_clicked();

private:
    Ui::notice *ui;
};

#endif // NOTICE_H

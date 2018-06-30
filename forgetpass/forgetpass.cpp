#include "forgetpass.h"
#include "ui_forgetpass.h"
#include "admin/admin.h"
#include "connect/databaseconnection.h"
#include "signin/signin.h"
#include "mainwindow/mainwindow.h"
#include "encrypt/encrypt.h"
#include <QSql>
#include <QMessageBox>
#include <QClipboard>
forgetpass::forgetpass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forgetpass)
{
    ui->setupUi(this);
    this->setFixedSize(265,185);
    ui->groupBox_2->setVisible(false);

}

forgetpass::~forgetpass()
{
    delete ui;
}

void forgetpass::on_pushButton_clicked()
{
    QString now=QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    connectDatabase data;
    data.openConnection();
    QSqlQuery qry1,qry2,qry3,qry4,qry5;
    qry1.exec("select * from NGUOIDUNG where TAIKHOAN ='" + ui->lineEdit_tk->text()
                 + "' and CMND ='"+ui->lineEdit_id->text()+"' and EMAIL='"+ui->lineEdit_email->text()+"'");
    qry2.prepare("insert into YEUCAU values ('QUANLY','"+ui->lineEdit_tk->text()+"','[?] "+ui->lineEdit_tk->text()+" yêu cầu đặt lại mật khẩu ', '"+now+"','chưa xử lý')");
    qry3.exec("select * from YEUCAU where NOIDUNG= '[#] "+ui->lineEdit_tk->text()+" đã được tạo lại mật khẩu'");
    qry4.prepare("update YEUCAU set NOIDUNG= '[#] "+ui->lineEdit_tk->text()+" đã được tạo lại mật khẩu.' where NOIDUNG= '[#] "+ui->lineEdit_tk->text()+" đã được tạo lại mật khẩu'");


    if(qry1.next()){
        if(!qry3.next()){
            qry2.exec();
            QMessageBox::information(this,"Thành công","Yêu cầu của bạn đã được gửi tới quản lý hệ thống để giải quyết.");
            MainWindow *mw = new MainWindow;
            mw->show();
            this->close();
        }
        else {
            QMessageBox::about(this,"Thành công","Quản lý hệ thống đã giải quyết yêu cầu của bạn \n ");
            ui->groupBox_2->setVisible(true);
            ui->groupBox->setVisible(false);
            qry4.exec();
            qry5.exec("select MATKHAU from TAIKHOAN where TAIKHOAN='"+ui->lineEdit_tk->text()+"'");
            qry5.next();
            ui->lineEdit_pass->setText(decrypt(qry5.value(0).toString(),ui->lineEdit_tk->text()));

        }
    }
    else {
        QMessageBox::warning(this,"Lỗi","Thông tin nhập sai.");
    }

    data.closeConnection();
}

void forgetpass::on_pushButton_2_clicked()
{
    SignIn *sn=new SignIn;
    this->close();
    sn->show();
}

void forgetpass::on_pushButton_3_clicked()
{
    QClipboard *clip = QApplication::clipboard();
    QString input = ui->lineEdit_pass->text();
    clip->setText(input);
    QMessageBox::about(this,"","Đã copy vào clipboard.\n Mời bạn đăng nhập với mật khẩu mới.");

}

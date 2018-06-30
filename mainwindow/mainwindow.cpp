#include "connect/databaseconnection.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signup/signup.h"
#include "ui_admin.h"
#include "ui_librarian.h"
#include "ui_reader.h"
#include "reader/reader.h"
#include "admin/admin.h"
#include "ui_home.h"
#include "home/home.h"
#include "librarian/librarian.h"
#include "edituser/edituser.h"
#include "noiquy/noiquy.h"
#include "notice/notice.h"
#include "mailbox/mailbox.h"
#include "contact/contact.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSql>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1000,600);
    ui->tabWidget->close();
    ui->toolBar->close();
    Home *home = new Home();
    QVBoxLayout *layout = new QVBoxLayout;
         layout->addWidget(home);
    QWidget *p = new QWidget();
    p->setLayout(layout);
    setCentralWidget(p);
}
MainWindow::MainWindow(bool badmin,bool breader, bool blibrarian, QString pin,QString name,QWidget * par) :
    QMainWindow(par),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar_2->close();

    accReader = breader;accAdmin = badmin;accLibrarian = blibrarian;
    PIN = pin;accName = name;
    if(accReader){
        reader *rea = new reader(accName);
        ui->tabWidget->addTab(rea,QString("Độc giả"));
    }
    if(accLibrarian){
        librarian *lib = new librarian();
        ui->tabWidget->addTab(lib,QString("Thủ thư"));
    }
    if(accAdmin){
        admin *ad = new admin();
        ui->tabWidget->addTab(ad,QString("Quản lý"));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionSignUp_triggered()
{
    SignUpDialog  sd;
    sd.setModal(true);
    sd.exec();
}

void MainWindow::on_actionSignIn_triggered()
{
    this->deleteLater();
    SignIn si;
    si.setModal(true);
    si.exec();
}

void MainWindow::on_actionSignOut_triggered()
{
    this->deleteLater();
}

void MainWindow::on_actionHome_triggered()
{
    this->deleteLater();
    MainWindow * wn = new MainWindow();
    wn->setWindowTitle("Trang Chủ");
    wn->show();
}

void MainWindow::on_actionabout_triggered()
{
    QMessageBox::information(this,"Thông tin tác giả","<p><b>Nhóm 1, L01, Trường ĐHBK Tp HCM</b></p> <p>Nguyễn Quốc Anh</p> <p>Nguyễn Huỳnh Thoại</p><p>Huỳnh Song Anh Quân</p><p>Nguyễn Thị Như Ý</p>");

}

void MainWindow::on_actionrule_triggered()
{
    noiquy nquy;
    nquy.setModal(true);
    nquy.exec();
}

void MainWindow::on_actionUser_triggered()
{
    editUSER *pro = new editUSER(accName);
    pro->setModal(true);
    pro->exec();
}

void MainWindow::on_actionNotice_triggered()
{
    connectDatabase data;
    data.openConnection();
    QSqlQuery qry1;
    qry1.exec("select THUTHU,QUANLY from TAIKHOAN where TAIKHOAN='"+proname+"'");
    qry1.next();
    if(qry1.value(0).toBool()==0&&qry1.value(1).toBool()==0){
        notice *tbreader = new notice(true);
        tbreader->setModal(true);
        tbreader->exec();
    }
    else{
        notice tb;
        tb.setModal(true);
        tb.exec();
    }
    data.closeConnection();

}

void MainWindow::on_actionMail_triggered()
{
    MailBox mail(proname);
    mail.setModal(true);
    mail.exec();
}

void MainWindow::on_actioncontact_triggered()
{
    contact lienhe;
    lienhe.setModal(true);
    lienhe.exec();
}

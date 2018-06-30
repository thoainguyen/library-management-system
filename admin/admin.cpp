#include "admin.h"
#include "ui_admin.h"
#include "connect/databaseconnection.h"
#include "edituser/edituser.h"
#include "signup/signup.h"
#include "notice/notice.h"
#include <QTableView>
QString cmnd,hoten,taikhoan,email,nghenghiep,ngaysinh,gioitinh,resetpass;
bool docgia=false,thuthu=false,quanli=false,act;
admin::admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    this->on_pushButton_clicked();
    connectDatabase data;
    data.openConnection();
    QSqlQueryModel* databaseModel = new QSqlQueryModel;

    QSqlQuery* aqry = new QSqlQuery(data.mydb);
    aqry->exec("select t.CMND, t.TAIKHOAN, n.HOTEN,t.ACTIVE from TAIKHOAN as t "
                  "JOIN NGUOIDUNG as n on t.TAIKHOAN=n.TAIKHOAN");
    databaseModel->setQuery(*aqry);
    ui->tableView->setModel(databaseModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    data.closeConnection();
}

admin::~admin()
{
    delete ui;
}

void admin::on_pushButton_5_clicked()
{
    connectDatabase searchDB;

    if(!searchDB.openConnection()){
        QMessageBox::critical(this,"Database Error!","Error Connecting to Database! Please try again or Check Database.");
    }

    searchDB.openConnection();

    QSqlQueryModel* databaseModel = new QSqlQueryModel;

    QSqlQuery* aqry = new QSqlQuery(searchDB.mydb);


    if(ui->comboBox_2->currentText() == "Tên tài khoản"){
        aqry->prepare("select t.CMND, t.TAIKHOAN, n.HOTEN,t.ACTIVE from TAIKHOAN as t JOIN NGUOIDUNG as n on t.TAIKHOAN=n.TAIKHOAN where t.TAIKHOAN like '%'||:taikhoan||'%';");
        aqry->bindValue(":taikhoan",ui->lineEdit_2->text());
        aqry->exec();
    }

    else if(ui->comboBox_2->currentText() == "CMND/MSSV"){

        aqry->prepare("select t.CMND, t.TAIKHOAN, n.HOTEN,t.ACTIVE from TAIKHOAN as t JOIN NGUOIDUNG as n on t.TAIKHOAN=n.TAIKHOAN where t.CMND like '%'||:cmnd||'%';");
        aqry->bindValue(":cmnd",ui->lineEdit_2->text());
        aqry->exec();
    }

    else if(ui->comboBox_2->currentText() == "Người dùng"){

        aqry->prepare("select t.CMND, t.TAIKHOAN, n.HOTEN,t.ACTIVE from TAIKHOAN as t JOIN NGUOIDUNG as n on t.TAIKHOAN=n.TAIKHOAN where n.HOTEN like '%'||:hoten||'%';");
        aqry->bindValue(":hoten",ui->lineEdit_2->text());
        aqry->exec();
    }

    else if(ui->comboBox_2->currentText() == "Vai trò"){
        QString vaitro=ui->lineEdit_2->text();
        if(vaitro=="thu thu"||vaitro=="thủ thư"||vaitro=="Thủ thư"){
            aqry->prepare("SELECT t.TAIKHOAN,n.HOTEN,t.CMND,t.ACTIVE FROM TAIKHOAN as t JOIN NGUOIDUNG as n on t.TAIKHOAN=n.TAIKHOAN where t.THUTHU='true'");
            aqry->exec();
        }
        else if(vaitro=="quan ly"||vaitro=="quản lý"||vaitro=="Quản lý"){
            aqry->prepare("SELECT t.TAIKHOAN,n.HOTEN,t.CMND,t.ACTIVE FROM TAIKHOAN as t JOIN NGUOIDUNG as n on t.TAIKHOAN=n.TAIKHOAN where t.QUANLY='true'");
            aqry->exec();
        }
        else if(vaitro=="độc giả"||vaitro=="doc gia"||vaitro=="đọc giả"||vaitro=="Độc giả"){
            aqry->prepare("SELECT t.TAIKHOAN,n.HOTEN,t.CMND,t.ACTIVE FROM TAIKHOAN as t JOIN NGUOIDUNG as n on t.TAIKHOAN=n.TAIKHOAN where t.DOCGIA='true'");
            aqry->exec();
        }
    }


    databaseModel->setQuery(*aqry);
    ui->tableView->setModel(databaseModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    searchDB.closeConnection();
}

void admin::on_tableView_activated(const QModelIndex &index)
{
    QString gtri=ui->tableView->model()->data(index).toString();

    connectDatabase data;
    data.openConnection();

    QSqlQuery* qry = new QSqlQuery(data.mydb);
    qry->prepare("select * from TAIKHOAN as t JOIN NGUOIDUNG as n on t.TAIKHOAN=n.TAIKHOAN where t.TAIKHOAN=:giatri or n.HOTEN=:giatri or t.CMND=:giatri;");
    qry->bindValue(":giatri",gtri);
    if(qry->exec()){
        while(qry->next()){
            cmnd=qry->value(0).toString();
            taikhoan=qry->value(1).toString();
            docgia=qry->value(3).toBool();
            thuthu=qry->value(4).toBool();
            quanli=qry->value(5).toBool();
            act=qry->value(6).toBool();
            hoten=qry->value(7).toString();
            email=qry->value(10).toString();
            ngaysinh=qry->value(11).toString();
            nghenghiep=qry->value(12).toString();
            gioitinh=qry->value(13).toString();
            editUSER edit ;
            edit.setModal(true);
            edit.exec();
        }
    }
    data.closeConnection();

}



void admin::on_pushButton_addaccount_clicked()
{
    SignUpDialog *adduser = new SignUpDialog(true);
    adduser->setModal(true);
    adduser->exec();
}

void admin::on_tableView_tacvu_activated(const QModelIndex &index)
{
    QString gtri=ui->tableView_tacvu->model()->data(index).toString();

    connectDatabase data;
    data.openConnection();

    QSqlQuery* qry = new QSqlQuery(data.mydb);
    qry->prepare("select * from TAIKHOAN as t JOIN NGUOIDUNG as n on t.TAIKHOAN=n.TAIKHOAN where t.TAIKHOAN=(select GUI from YEUCAU where GUI=:giatri or THOIGIAN=:giatri or NOIDUNG=:giatri or TRANGTHAI=:giatri)");
    qry->bindValue(":giatri",gtri);
    if(qry->exec()){
        while(qry->next()){
            cmnd=qry->value(0).toString();
            taikhoan=qry->value(1).toString();
            docgia=qry->value(3).toBool();
            thuthu=qry->value(4).toBool();
            quanli=qry->value(5).toBool();
            act=qry->value(6).toBool();
            hoten=qry->value(7).toString();
            email=qry->value(10).toString();
            ngaysinh=qry->value(11).toString();
            nghenghiep=qry->value(12).toString();
            gioitinh=qry->value(13).toString();
            editUSER edit ;
            edit.setModal(true);
            edit.exec();
        }
    }
    data.closeConnection();
}

void admin::on_pushButton_clicked()
{
    connectDatabase data;
    data.openConnection();

    QSqlQueryModel* databaseModel = new QSqlQueryModel;

    QSqlQuery* qry = new QSqlQuery(data.mydb);

    qry->exec("select THOIGIAN, GUI, NOIDUNG, TRANGTHAI from YEUCAU where NHAN='QUANLY' order by THOIGIAN DESC");

    databaseModel->setQuery(*qry);
    ui->tableView_tacvu->setModel(databaseModel);
    //ui->tableView_tacvu->AdjustToContentsOnFirstShow();
    ui->tableView_tacvu->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_tacvu->sortByColumn(0,Qt::DescendingOrder);
    data.closeConnection();
}



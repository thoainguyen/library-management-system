#include "home.h"
#include "ui_home.h"
#include "ui_signin.h"
#include "signin/signin.h"
#include "connect/databaseconnection.h"
#include "ui_signup.h"
#include "signup/signup.h"
#include "notice/notice.h"
#include "connect/databaseconnection.h"
Home::Home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);
    this->on_pushButton_2_clicked();
    connectDatabase data;
    data.openConnection();

    QSqlQuery *qry1 = new QSqlQuery(data.mydb);
    QSqlQueryModel* databaseModel = new QSqlQueryModel;

    qry1->exec("select THOIGIAN, TIEUDE, NOIDUNG from THONGBAO order by THOIGIAN DESC");

    databaseModel->setQuery(*qry1);
    ui->tableView_thongbao->setModel(databaseModel);

    ui->tableView_thongbao->AdjustToContentsOnFirstShow;
    ui->tableView_thongbao->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_thongbao->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    data.closeConnection();

}

Home::~Home()
{
    delete ui;
}

void Home::on_pushButton_2_clicked()
{
    connectDatabase searchDB;
        if(!searchDB.openConnection()){
            QMessageBox::critical(this,"Lỗi kết nối!","Không kết nối được cơ sở dữ liệu, liên hệ admin.");
        }
        searchDB.openConnection();
        QSqlQueryModel* databaseModel = new QSqlQueryModel;
        QSqlQuery* aqry = new QSqlQuery(searchDB.mydb);
        if(ui->comboBox->currentText() == "ISBN"){
            aqry->prepare("select TUADE,TACGIA,ISBN,NHAXUATBAN,NAM from SACH where ISBN like '%'||:isbn||'%';");
            aqry->bindValue(":isbn",ui->lineEdit->text().toInt());
            aqry->exec();
        }
        else if(ui->comboBox->currentText() == "Tựa đề"){
            aqry->prepare("select TUADE,TACGIA,ISBN,NHAXUATBAN,NAM from SACH where TUADE like '%'||:name||'%';");
            aqry->bindValue(":name",ui->lineEdit->text());
            aqry->exec();
        }
        else if(ui->comboBox->currentText() == "Tác giả"){
            aqry->prepare("select TUADE,TACGIA,ISBN,NHAXUATBAN,NAM from SACH where TACGIA like '%'||:author||'%';");
            aqry->bindValue(":author",ui->lineEdit->text());
            aqry->exec();
        }
        else if(ui->comboBox->currentText() == "Năm"){
            aqry->prepare("select TUADE,TACGIA,ISBN,NHAXUATBAN,NAM from SACH where NAM = :year;");
            aqry->bindValue(":year",ui->lineEdit->text().toInt());
            aqry->exec();
        }
        else if(ui->comboBox->currentText() == "NXB"){
            aqry->prepare("select TUADE,TACGIA,ISBN,NHAXUATBAN,NAM from SACH where NHAXUATBAN like '%'||:nxb||'%';");
            aqry->bindValue(":nxb",ui->lineEdit->text());
            aqry->exec();
        }
        else if(ui->comboBox->currentText() == "Tất cả sách"){

            aqry->exec("select TUADE,TACGIA,ISBN,NHAXUATBAN,NAM from SACH;");
        }
        databaseModel->setQuery(*aqry);
        ui->tableView->setModel(databaseModel);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        searchDB.closeConnection();
}

void Home::on_pushButton_muon_clicked()
{
    QMessageBox::information(this,"Thông báo","Để mượn sách bạn phải đăng nhập trước đã!");

}
void Home::on_pushButton_clicked()
{
    QModelIndex index = ui->tableView_thongbao->currentIndex();
        if(!index.isValid())
            QMessageBox::critical(this,"","Chọn 1 thông báo rồi ấn xem chi tiết.");
        else{
            int row = index.row();
            QString thongbao = index.sibling(row, 0).data().toString();
            notice *tb = new notice(thongbao);
            tb->setModal(true);
            tb->exec();
        }
}

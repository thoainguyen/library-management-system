#include "reader.h"
#include "ui_reader.h"
#include "signup/signup.h"
#include "connect/databaseconnection.h"
#include "cart/cart.h"
#include "signin/signin.h"
#include "ui_cart.h"

reader::reader(QString n,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reader)
{
    ui->setupUi(this);
    accname = n;
    ui->textBrowser->close();
    ui->pushButton_5->close();
    this->on_pushButton_clicked();
    this->on_pushButton_9_clicked();
}

reader::~reader()
{
    this->on_clear_tam();
    delete ui;
}

void reader::on_clear_tam(){
    connectDatabase cn;
    cn.openConnection();
    QSqlQuery *q = new QSqlQuery(cn.mydb);
    q->exec("delete from TAM");
    cn.closeConnection();
}

void reader::on_pushButton_clicked()
{
    connectDatabase searchDB;
        if(!searchDB.openConnection()){
            QMessageBox::critical(this,"Lỗi kết nối!","Không kết nối được cơ sở dữ liệu, liên hệ admin.");
        }
        searchDB.openConnection();
        QSqlQueryModel* databaseModel = new QSqlQueryModel;
        QSqlQuery* aqry = new QSqlQuery(searchDB.mydb);
        if(ui->comboBox->currentText() == "ISBN"){
            aqry->prepare("select TUADE,TACGIA,NHAXUATBAN,NAM,SOLUONG,IDSACH from SACH where ISBN like '%'||:isbn||'%';");
            aqry->bindValue(":isbn",ui->lineEdit->text().toInt());
            aqry->exec();
        }
        else if(ui->comboBox->currentText() == "Tựa đề"){
            aqry->prepare("select TUADE,TACGIA,NHAXUATBAN,NAM,SOLUONG,IDSACH from SACH where TUADE like '%'||:name||'%';");
            aqry->bindValue(":name",ui->lineEdit->text());
            aqry->exec();
        }
        else if(ui->comboBox->currentText() == "Tác giả"){
            aqry->prepare("select TUADE,TACGIA,NHAXUATBAN,NAM,SOLUONG,IDSACH from SACH where TACGIA like '%'||:author||'%';");
            aqry->bindValue(":author",ui->lineEdit->text());
            aqry->exec();
        }
        else if(ui->comboBox->currentText() == "Năm"){
            aqry->prepare("select TUADE,TACGIA,NHAXUATBAN,NAM,SOLUONG,IDSACH from SACH where NAM = :year;");
            aqry->bindValue(":year",ui->lineEdit->text().toInt());
            aqry->exec();
        }
        else if(ui->comboBox->currentText() == "NXB"){
            aqry->prepare("select TUADE,TACGIA,NHAXUATBAN,NAM,SOLUONG,IDSACH from SACH where NHAXUATBAN like '%'||:nxb||'%';");
            aqry->bindValue(":nxb",ui->lineEdit->text());
            aqry->exec();
        }
        else if(ui->comboBox->currentText() == "Tất cả"){
            aqry->exec("select TUADE,TACGIA,NHAXUATBAN,NAM,SOLUONG,IDSACH from SACH;");
        }
        databaseModel->setQuery(*aqry);
        ui->tableView->setModel(databaseModel);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        searchDB.closeConnection();
}

void reader::on_pushButton_3_clicked()
{
    QModelIndex idex = ui->tableView->currentIndex();
    if(!idex.isValid()){
        QMessageBox::about(this,"Lỗi","Xin chọn một sách trước !");
    }
    else{
        connectDatabase cn;
        cn.openConnection();
        QSqlQuery rem;
        rem.prepare("insert into TAM values(:id,:title);");
        rem.bindValue(":id",idex.sibling(idex.row(), 5).data().toInt());
        rem.bindValue(":title",idex.sibling(idex.row(), 0).data().toString());
        if(!rem.exec()){
            QMessageBox::warning(this,"Lỗi","Sách đã có trong giỏ hàng");
        }
        else{
            int sum = 0;
            QSqlQuery s;
            s.exec("select count(*) from TAM;");
            if(s.next()){
               sum = s.value(0).toInt();
            }
            QString txt;
            txt.setNum(sum);
            ui->label_5->setText(txt);
        }
        cn.closeConnection();
    }
}

void reader::on_pushButton_6_clicked()
{
    Cart cart(accname);
    cart.setModal(true);
    cart.exec();
}

void reader::on_pushButton_9_clicked()
{

    connectDatabase cp ;
    cp.openConnection();
    QSqlQuery * sq = new QSqlQuery(cp.mydb);
    QSqlQueryModel* databaseModel = new QSqlQueryModel;
    sq->exec("select NOIDUNG,THOIGIAN,TRANGTHAI from YEUCAU where GUI='"+proname+"' or NHAN='"+proname+"'  order by THOIGIAN DESC");

    databaseModel->setQuery(*sq);
    ui->tableView1->setModel(databaseModel);
    cp.closeConnection();
}

void reader::on_pushButton_4_clicked()
{
    QModelIndex idex = ui->tableView1->currentIndex();
    ui->textBrowser->show();
    ui->pushButton_5->show();
    ui->pushButton_4->close();
    ui->pushButton_9->close();
    ui->tableView1->close();
    if(!idex.isValid()){
        QMessageBox::warning(this,"Lỗi","Xin chọn một thông báo trước !");
    }
    else{
        QString nd = idex.sibling(idex.row(), 0).data().toString();
        QString tg = idex.sibling(idex.row(), 1).data().toString();
        QString tt = idex.sibling(idex.row(), 2).data().toString();
        ui->textBrowser->setText("\nNỘI DUNG\n-----------\n"+nd+"\n\nTHỜI GIAN\n---------------\n"+tg+"\n\nTRẠNG THÁI\n---------\n"+tt);
    }
}

void reader::on_pushButton_5_clicked()
{
    ui->textBrowser->close();
    ui->pushButton_5->close();
    ui->pushButton_4->show();
    ui->pushButton_9->show();
    ui->tableView1->show();
    this->on_pushButton_9_clicked();
}


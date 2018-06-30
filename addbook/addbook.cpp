#include "addbook.h"
#include "ui_addbook.h"
#include "connect/databaseconnection.h"
#include "ui_librarian.h"
#include "librarian/librarian.h"
#include <QPushButton>
addbook::addbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addbook)
{
    ui->setupUi(this);
}
addbook::addbook(QModelIndex &index,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addbook)
{
    ui->setupUi(this);
    //
    idbook = index.sibling(index.row(), 6).data().toInt();
    //
    this->setWindowTitle("Chỉnh sửa sách");
    ui->buttonBox->close();
    //
    QPushButton * btn = new QPushButton("Cập nhật");
    ui->formLayout->addWidget(btn);
    //
    ui->lineEdit->setText(index.sibling(index.row(), 0).data().toString());//tựa đề
    ui->lineEdit_2->setText(index.sibling(index.row(), 1).data().toString());//tác giả
    ui->lineEdit_3->setText(index.sibling(index.row(), 5).data().toString());//isbn
    ui->lineEdit_4->setText(index.sibling(index.row(), 2).data().toString());//nxb
    ui->spinBox->setValue(index.sibling(index.row(), 4).data().toInt());//số lượng
    ui->spinBox_2->setValue(index.sibling(index.row(), 3).data().toInt());//năm
    //
    connect(btn, &QPushButton::clicked, this, &addbook::on_btn_clicked);
}

addbook::~addbook()
{
    delete ui;
}

void addbook::on_buttonBox_accepted()
{
    connectDatabase add;
    add.openConnection();

    if(ui->lineEdit->text()=="" || ui->lineEdit_2->text()=="" || ui->lineEdit_3->text()=="" || ui->lineEdit->text()==""){
            QMessageBox::about(this,"Không thành công !"," Vui lòng điền đầy đủ các trường thông tin.");
    }
    else{

        QSqlQuery writeQry;
        writeQry.exec("select count(*) from SACH;");
        int sum;
        if(writeQry.next()){
            sum = writeQry.value(0).toInt();
        }
        writeQry.prepare("insert into SACH values(:idsach,:tuade,:tacgia,:isbn,:nxb,:nam,:soluong);");
        writeQry.bindValue(":idsach",sum);
        writeQry.bindValue(":tuade",ui->lineEdit->text());
        writeQry.bindValue(":tacgia",ui->lineEdit_2->text());
        writeQry.bindValue(":isbn",ui->lineEdit_3->text());
        writeQry.bindValue(":nxb",ui->lineEdit_4->text());
        writeQry.bindValue(":nam",ui->spinBox_2->text().toInt());
        writeQry.bindValue(":soluong",ui->spinBox->text().toInt());

        while(!writeQry.exec()){
            sum ++;
            writeQry.prepare("insert into SACH values(:idsach,:tuade,:tacgia,:isbn,:nxb,:nam,:soluong);");
            writeQry.bindValue(":idsach",sum);
            writeQry.bindValue(":tuade",ui->lineEdit->text());
            writeQry.bindValue(":tacgia",ui->lineEdit_2->text());
            writeQry.bindValue(":isbn",ui->lineEdit_3->text());
            writeQry.bindValue(":nxb",ui->lineEdit_4->text());
            writeQry.bindValue(":nam",ui->spinBox_2->text().toInt());
            writeQry.bindValue(":soluong",ui->spinBox->text().toInt());
        }

        QMessageBox::about(this,"Thành công!","Cập nhật sách thành công.");

        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");
        ui->lineEdit_3->setText("");
        ui->lineEdit_4->setText("");

    }
}

void addbook::on_buttonBox_rejected()
{
    this->close();
}

void addbook::on_btn_clicked(){
    connectDatabase editDB;
    bool isCorrectEntry;
    editDB.openConnection();
            QSqlQuery editQry;


            if(ui->lineEdit_2->text() == "" || ui->lineEdit_3->text() == "" || ui->lineEdit_4->text() == "" || ui->lineEdit->text() == ""){
                QMessageBox::about(this,"Thất bại!","Đừng bỏ trống trường dữ liệu nào!");
            }

            if(ui->lineEdit->text()!=""){
              editQry.prepare("update SACH set TUADE = :title where IDSACH = :id");
              editQry.bindValue(":title",ui->lineEdit->text());
              editQry.bindValue(":id",idbook);
              isCorrectEntry = editQry.exec();
            }

            if(ui->lineEdit_2->text()!=""){
              editQry.prepare("update SACH set TACGIA = :newauthor where IDSACH = :id");
              editQry.bindValue(":newauthor",ui->lineEdit_2->text());
              editQry.bindValue(":id",idbook);
              isCorrectEntry = editQry.exec();
            }

            if(ui->lineEdit_3->text()!=""){
              editQry.prepare("update SACH set ISBN = :newisbn where IDSACH = :id");
              editQry.bindValue(":newisbn",ui->lineEdit_3->text());
              editQry.bindValue(":id",idbook);
              isCorrectEntry = editQry.exec();
            }

            if(ui->lineEdit_4->text()!=""){
              editQry.prepare("update SACH set NHAXUATBAN = :newpl where IDSACH = :id");
              editQry.bindValue(":newpl",ui->lineEdit_4->text());
              editQry.bindValue(":id",idbook);
              isCorrectEntry = editQry.exec();
            }
            //
            editQry.prepare("update SACH set NAM = :newyr where IDSACH = :id");
            editQry.bindValue(":newyr",ui->spinBox_2->text().toInt());
            editQry.bindValue(":id",idbook);

           //
            editQry.prepare("update SACH set SOLUONG = :newsl where IDSACH = :id");
            editQry.bindValue(":newsl",ui->spinBox->text().toInt());
            editQry.bindValue(":id",idbook);
            //
    editDB.closeConnection();
    if(isCorrectEntry){
        QMessageBox::about(this,"Thành công!","Sách đã được chỉnh sửa!");
    }
}

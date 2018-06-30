#include "cart.h"
#include "ui_cart.h"
#include "connect/databaseconnection.h"

Cart::Cart(QString n,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cart)
{
    account = n;
    ui->setupUi(this);
    connect.openConnection();
    this->on_backup();
}
Cart::~Cart()
{
    delete ui;
    connect.closeConnection();
}
void Cart::on_backup(){
    QSqlQueryModel* databaseModel = new QSqlQueryModel;
    QSqlQuery* aqry = new QSqlQuery(connect.mydb);
    aqry->exec("select * from TAM");
    databaseModel->setQuery(*aqry);
    ui->tableView->setModel(databaseModel);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void Cart::on_pushButton_3_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if(!index.isValid()){
        QMessageBox::about(this,"Lỗi","Chọn sách cần huỷ trước");
    }
    else
    {
        int id = index.sibling(index.row(), 0).data().toInt();
        QSqlQuery* qry = new QSqlQuery(connect.mydb);
        qry->prepare("delete from tam where idsach = :id");
        qry->bindValue(":id",id);
        qry->exec();
        this->on_backup();
    }
}

void Cart::on_pushButton_clicked()
{
    QModelIndex dex = ui->tableView->currentIndex();
    if(!dex.isValid()){
        QMessageBox::about(this,"Lỗi","Chọn sách xác nhận mượn trước");
    }
    else
    {
        QString now = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
        int id = dex.sibling(dex.row(), 0).data().toInt();
        QString tuade = dex.sibling(dex.row(), 1).data().toString();
        QSqlQuery *qry = new QSqlQuery(connect.mydb);
        qry->exec("select count(*) from MUONSACH;");
        int sum;
        if(qry->next()){
            sum = qry->value(0).toInt();
        }
        QSqlQuery *qry2 = new QSqlQuery(connect.mydb);
        qry2->prepare("insert into MUONSACH values( :no,'false',:taikhoan,:idsach,:tuade,:soluong,:ngaymuon,:songay,'0','0');");
        qry2->bindValue(":no",sum);
        qry2->bindValue(":taikhoan",account);
        qry2->bindValue(":idsach",id);
        qry2->bindValue(":tuade",tuade);
        qry2->bindValue(":soluong",ui->spinBox->text().toInt());
        qry2->bindValue(":ngaymuon",now);
        qry2->bindValue(":songay",ui->spinBox_2->text().toInt());

        QMessageBox::StandardButton xacnhan = QMessageBox::question(this,"Xác nhân","Bạn xác nhận mượn sách ?",QMessageBox::Yes|QMessageBox::No);
        if(xacnhan == QMessageBox::Yes){

            while(!qry2->exec()){
                sum++;
                qry2->prepare("insert into MUONSACH values( :no,'false',:taikhoan,:idsach,:tuade,:soluong,:ngaymuon,:songay,'0','0');");
                qry2->bindValue(":no",sum);
                qry2->bindValue(":taikhoan",account);
                qry2->bindValue(":idsach",id);
                qry2->bindValue(":tuade",tuade);
                qry2->bindValue(":soluong",ui->spinBox->text().toInt());
                qry2->bindValue(":ngaymuon",now);
                qry2->bindValue(":songay",ui->spinBox_2->text().toInt());
            }
            QMessageBox::information(this,"Thành công","Thư viện sẽ xét duyệt yêu cầu của bạn sớm nhất có thể ");
            int id = dex.sibling(dex.row(), 0).data().toInt();
            QSqlQuery* qry = new QSqlQuery(connect.mydb);
            qry->prepare("delete from tam where idsach = :id");
            qry->bindValue(":id",id);
            qry->exec();
            this->on_backup();
        }
    }
}

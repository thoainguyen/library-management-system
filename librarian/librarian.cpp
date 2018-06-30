#include "librarian.h"
#include "ui_librarian.h"
#include "connect/databaseconnection.h"
#include "addbook/addbook.h"
#include "ui_addbook.h"
#include "mailbox/mailbox.h"
#include "ui_mailbox.h"
librarian::librarian(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::librarian)
{
    ui->setupUi(this);
    this->on_pushButton_5_clicked();
    this->refresh();
}

librarian::~librarian()
{
    delete ui;
}
void librarian::refresh(){
    this->showbook_1(ui->tableView_2);
    this->showbook_2(ui->tableView_3);
    this->showbook_3(ui->tableView_4);
};
void librarian::on_pushButton_5_clicked()
{
        connectDatabase searchDB;

        if(!searchDB.openConnection()){
            QMessageBox::critical(this,"Lỗi kết nối!","Không kết nối được cơ sở dữ liệu, liên hệ admin.");
        }

        searchDB.openConnection();

        QSqlQueryModel* databaseModel = new QSqlQueryModel;

        QSqlQuery* aqry = new QSqlQuery(searchDB.mydb);


        if(ui->comboBox_2->currentText() == "ISBN"){
            aqry->prepare("select TUADE,TACGIA,NHAXUATBAN,NAM,SOLUONG,ISBN,IDSACH from SACH where ISBN like '%'||:isbn||'%';");
            aqry->bindValue(":isbn",ui->lineEdit->text().toInt());
            aqry->exec();
        }
        else if(ui->comboBox_2->currentText() == "Tựa đề"){
            aqry->prepare("select TUADE,TACGIA,NHAXUATBAN,NAM,SOLUONG,ISBN,IDSACH from SACH where TUADE like '%'||:name||'%';");
            aqry->bindValue(":name",ui->lineEdit->text());
            aqry->exec();
        }
        else if(ui->comboBox_2->currentText() == "Tác giả"){
            aqry->prepare("select TUADE,TACGIA,NHAXUATBAN,NAM,SOLUONG,ISBN,IDSACH from SACH where TACGIA like '%'||:author||'%';");
            aqry->bindValue(":author",ui->lineEdit->text());
            aqry->exec();
        }
        else if(ui->comboBox_2->currentText() == "Năm"){
            aqry->prepare("select TUADE,TACGIA,NHAXUATBAN,NAM,SOLUONG,ISBN,IDSACH from SACH where NAM = :year;");
            aqry->bindValue(":year",ui->lineEdit->text().toInt());
            aqry->exec();
        }
        else if(ui->comboBox_2->currentText() == "NXB"){
            aqry->prepare("select TUADE,TACGIA,NHAXUATBAN,NAM,SOLUONG,ISBN,IDSACH from SACH where NHAXUATBAN like '%'||:nxb||'%';");
            aqry->bindValue(":nxb",ui->lineEdit->text());
            aqry->exec();
        }
        else if(ui->comboBox_2->currentText() == "Tất cả"){
            aqry->exec("select TUADE,TACGIA,NHAXUATBAN,NAM,SOLUONG,ISBN,IDSACH from SACH;");
        }

        databaseModel->setQuery(*aqry);
        ui->tableView->setModel(databaseModel);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        //QModelIndexList ids = ui->tableView->selectionModel()->selectedRows();
        //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        searchDB.closeConnection();
}

void librarian::on_pushButton_6_clicked()
{
    addbook ab;
    ab.setModal(true);
    ab.exec();
}

void librarian::on_pushButton_8_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if(!index.isValid()){
        QMessageBox::about(this,"Lỗi","Xin chọn sách cần xoá");
    }
    else{
        int row = index.row();
        int id = index.sibling(row, 6).data().toInt();

        connectDatabase cn_1;
        cn_1.openConnection();
        QSqlQuery rev;

        rev.prepare("delete from SACH where IDSACH = :id");
        rev.bindValue(":id",id);
        //
        QMessageBox xoasach;
        QPushButton *ok=xoasach.addButton(tr("Xoá") ,QMessageBox::ActionRole);
        xoasach.addButton(tr("Huỷ"),QMessageBox::NoRole);

        xoasach.setWindowTitle("Cảnh báo!");
        xoasach.setText("Sách sẽ bị xóa khỏi hệ thống \n Bạn có chắc chắn muốn XÓA?");
        xoasach.exec();
        if(xoasach.clickedButton()==ok){
            rev.exec();
            this->on_pushButton_5_clicked();
        }
        //
        cn_1.closeConnection();
    }
}


void librarian::on_pushButton_7_clicked()
{
    QModelIndex index1 = ui->tableView->currentIndex();
    if(!index1.isValid()){
        QMessageBox::about(this,"Lỗi","Chọn sách cần chỉnh sửa trước");
    }
    else
    {
        addbook eb(index1,0);
        eb.setModal(true);
        eb.exec();
    }
}

void librarian::showbook_1(QTableView *w){
    connectDatabase s;
    s.openConnection();
    QSqlQuery* qry = new QSqlQuery(s.mydb);
    QSqlQueryModel* databaseModel = new QSqlQueryModel;
    //
    qry->exec("select taikhoan,tuade,soluong,ngaymuon,songay,no,idsach from MUONSACH where TINHTRANG = 'false'");
    databaseModel->setQuery(*qry);
    w->setModel(databaseModel);
    w->setSelectionBehavior(QAbstractItemView::SelectRows);
    s.closeConnection();
}
void librarian::showbook_2(QTableView *w){
    connectDatabase s;
    s.openConnection();
    QSqlQuery* qry = new QSqlQuery(s.mydb);
    QSqlQueryModel* databaseModel = new QSqlQueryModel;
    //
    qry->prepare("select taikhoan,tuade,soluong,ngaymuon,ntradk,no,idsach from MUONSACH where TINHTRANG = 'true' and ntradk > :day ");
    qry->bindValue(":day",QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"));
    qry->exec();
    databaseModel->setQuery(*qry);
    w->setModel(databaseModel);
    w->setSelectionBehavior(QAbstractItemView::SelectRows);
    s.closeConnection();
}
void librarian::showbook_3(QTableView *w){
    connectDatabase s;
    s.openConnection();
    QSqlQuery* qry = new QSqlQuery(s.mydb);
    QSqlQueryModel* databaseModel = new QSqlQueryModel;
    qry->prepare("select taikhoan,tuade,soluong,ngaymuon,ntradk,no,idsach from MUONSACH where TINHTRANG = 'true' and ntradk < :day ");
    qry->bindValue(":day",QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"));
    qry->exec();
    databaseModel->setQuery(*qry);
    w->setModel(databaseModel);
    w->setSelectionBehavior(QAbstractItemView::SelectRows);
    s.closeConnection();
}

void librarian::on_pushButton_9_clicked()//Cho Muon sach
{
    QModelIndex index2 = ui->tableView_2->currentIndex();
    if(!index2.isValid()){
        QMessageBox::about(this,"Lỗi","Bạn chưa chọn đối tượng");
    }
    else
    {
        int id = index2.sibling(index2.row(), 5).data().toInt();
        QString tk = index2.sibling(index2.row(), 0).data().toString();
        QString tile = index2.sibling(index2.row(), 1).data().toString();
        int ngaymuon = index2.sibling(index2.row(), 4).data().toInt();
        connectDatabase cm;
        cm.openConnection();
        QSqlQuery* qry = new QSqlQuery(cm.mydb);
        QSqlQuery* qry1 = new QSqlQuery(cm.mydb);
        QSqlQuery* qry2 = new QSqlQuery(cm.mydb);
        QSqlQuery* qry3 = new QSqlQuery(cm.mydb);


        qry->prepare("update MUONSACH set TINHTRANG = 'true' where NO = :id");
        qry->bindValue(":id",id);

        qry1->prepare("update MUONSACH set NGAYMUON = '" + QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")+"' where NO = :id");
        qry1->bindValue(":id",id);

        QDateTime ntdk = QDateTime::currentDateTime().addDays(ngaymuon);

        qry2->prepare("update MUONSACH set NTRADK = '" + ntdk.toString("yyyy/MM/dd hh:mm:ss")+"' where NO = :id");
        qry2->bindValue(":id",id);

        qry3->prepare("insert into YEUCAU values('THUTHU',:tk,'Sách Tựa Đề : "+tile+" được cho mượn',:tg,'đã xử lý')");
                qry3->bindValue(":tk",tk);
                qry3->bindValue(":tg",QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss"));



        QMessageBox::StandardButton confirm = QMessageBox::question(this,"Xác nhân","Bạn chắc chắn muốn cho mượn không? ",QMessageBox::Yes|QMessageBox::No);
        if(confirm == QMessageBox::Yes){
            qry->exec();
            qry1->exec();
            qry2->exec();
            qry3->exec();
        }
        this->showbook_1(ui->tableView_2);
        this->showbook_2(ui->tableView_3);
        this->showbook_3(ui->tableView_4);
        cm.closeConnection();

    }
}


void librarian::on_pushButton_12_clicked()
{
    QModelIndex index2 = ui->tableView_2->currentIndex();
    if(!index2.isValid()){
        QMessageBox::about(this,"Lỗi","Xin chọn đối tượng cần huỷ yêu cầu");
    }
    else{
        QString tk = index2.sibling(index2.row(), 0).data().toString();
        QString tile = index2.sibling(index2.row(), 1).data().toString();
        QString ngaymuon = index2.sibling(index2.row(), 3).data().toString();

        connectDatabase cn;
        cn.openConnection();
        QSqlQuery rem;
        QSqlQuery *qs = new QSqlQuery(cn.mydb);
        QString now =  QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");

        qs->prepare("insert into YEUCAU values ('"+tk+"','THUTHU','Mượn sách "+tile+" ngày "+ngaymuon+" không chấp nhận','"+now+"','đã xử lý')");
        //qs->prepare("update THONGTIN set NOIDUNG = 'Thư viện huỷ yêu cầu mượn sách'"+tile+"' ngày '"+ngaymuon+"' của bạn where TAIKHOAN = '"+tk+"';");
        rem.prepare("delete from muonsach where no = :id");
        rem.bindValue(":id",index2.sibling(index2.row(), 5).data().toInt());

        QMessageBox::StandardButton confirm2 = QMessageBox::question(this,"Xác nhận","Bạn chắc chắn muốn huỷ yêu cầu không ?",QMessageBox::Yes|QMessageBox::No);
        if(confirm2 == QMessageBox::Yes){
            rem.exec();
            qs->exec();
            this->showbook_1(ui->tableView_2);
        }
        this->showbook_1(ui->tableView_2);
        this->showbook_2(ui->tableView_3);
        this->showbook_3(ui->tableView_4);
        cn.closeConnection();
    }
}

void librarian::on_pushButton_2_clicked()
{
    QModelIndex index = ui->tableView_3->currentIndex();
        if(!index.isValid()){
            QMessageBox::warning(this,"","Chưa chọn đối tượng.");
        }
        else{
            QString tk = index.sibling(index.row(), 0).data().toString();
            QString tile = index.sibling(index.row(), 1).data().toString();
            QString now =  QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");

            connectDatabase cn;
            cn.openConnection();
            QSqlQuery rem;
            QSqlQuery *qs = new QSqlQuery(cn.mydb);
            qs->prepare("insert into YEUCAU values ('"+tk+"','THUTHU','Đã xác nhận trả sách "+tile+" của bạn','"+now+"','đã xử lý')");
            qs->exec();
            rem.prepare("delete from MUONSACH where NO = :id");
            rem.bindValue(":id",index.sibling(index.row(), 5).data().toInt());
            QMessageBox::StandardButton confirm2 = QMessageBox::question(this,""," Xác nhận người đọc trả sách?",QMessageBox::Yes|QMessageBox::No);
            if(confirm2 == QMessageBox::Yes){
                rem.exec();

            }
            cn.closeConnection();
            this->refresh();
        }
    //qr->exec("update THONGTIN set NOIDUNG = 'Thư viện xác nhận bạn trả sách tựa đề '"+tile+"' ngày '"+now+"'where TAIKHOAN = '"+tk+"'';");
}


void librarian::on_pushButton_13_clicked()
{
    this->refresh();
}

void librarian::on_pushButton_11_clicked()
{
    QModelIndex index = ui->tableView_4->currentIndex();
        if(!index.isValid()){
            QMessageBox::warning(this,"","Chưa chọn đối tượng.");
        }
        else{
            QString acc = index.sibling(index.row(), 0).data().toString();
            int id = index.sibling(index.row(), 5).data().toInt();
            QString tile = index.sibling(index.row(), 1).data().toString();
            QString tk = index.sibling(index.row(), 4).data().toString();
            int yr = tk.mid(0,4).toInt();
            int month = tk.mid(5,2).toInt();
            int day = tk.mid(8,2).toInt();
            int ngaythem = ui->spinBox->text().toInt();
            QString nthem;
            nthem.setNum(ngaythem);
            tk = tk.mid(10,tk.length()-1);
            QDate temp(yr,month,day);
            QDate h = temp.addDays(ngaythem);
            QString tun = h.toString("yyyy/MM/dd")+tk;

            connectDatabase cm;
            cm.openConnection();
            QSqlQuery* qry2 = new QSqlQuery(cm.mydb);
            QSqlQuery* qry3 = new QSqlQuery(cm.mydb);

            qry2->prepare("update MUONSACH set NTRADK = '" + tun+"' where NO = :id");
            qry2->bindValue(":id",id);

            qry3->prepare("insert into YEUCAU values('THUTHU',:tk,'Đã gia hạn thêm : "+nthem+" ngày cho sách "+ tile+" bạn mượn',:tg,'đã xử lý')");
            qry3->bindValue(":tk",acc);
            qry3->bindValue(":tg",QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss"));

            QMessageBox::StandardButton confirm = QMessageBox::question(this,"Xác nhân","Bạn chắc chắn cho gia hạn thêm không? ",QMessageBox::Yes|QMessageBox::No);
            if(confirm == QMessageBox::Yes){
                qry2->exec();
                qry3->exec();
                this->refresh();
            }
        }

}

void librarian::on_pushButton_10_clicked()
{
    QModelIndex index = ui->tableView_4->currentIndex();
        if(!index.isValid()){
            QMessageBox::warning(this,"","Chưa chọn đối tượng.");
        }
        else{
            QString acc = index.sibling(index.row(), 0).data().toString();
            QString tile = index.sibling(index.row(), 1).data().toString();
            connectDatabase cm;
            cm.openConnection();
            QSqlQuery* qry3 = new QSqlQuery(cm.mydb);

            qry3->prepare("insert into YEUCAU values('THUTHU',:tk,'Thư viện phạt bạn mượn sách: "+tile+" quá hạn ',:tg,'đã xử lý')");
            qry3->bindValue(":tk",acc);
            qry3->bindValue(":tg",QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss"));

            QMessageBox::StandardButton confirm = QMessageBox::question(this,"Xác nhân","Bạn chắc chắn sẽ phạt tài khoản này ? ",QMessageBox::Yes|QMessageBox::No);
            if(confirm == QMessageBox::Yes){
                qry3->exec();
            }
        }
}

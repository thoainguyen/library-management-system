#include "mailbox.h"
#include "ui_mailbox.h"

MailBox::MailBox(QString n,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MailBox)
{
    accName = n;
    cnect.openConnection();
    ui->setupUi(this);
    ui->textBrowser_2->close();
    ui->pushButton_6->close();
    ui->textBrowser_3->close();
    ui->pushButton_7->close();
    this->show_table_thugui(ui->tableView_3);
    this->show_table_thuden(ui->tableView);

}

MailBox::~MailBox()
{
    cnect.closeConnection();
    delete ui;
}

void MailBox::show_table_thuden(QTableView *t){//Hộp thư đến
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery * qry = new QSqlQuery(cnect.mydb);
    qry->prepare("select nguoigui,noidung,thoigian from hopthu where nguoinhan = :nnhan order by THOIGIAN DESC");
    qry->bindValue(":nnhan",accName);
    qry->exec();
    modal->setQuery(*qry);
    t->setModel(modal);
}

void MailBox::show_table_thugui(QTableView *t){//Thư đã gửi
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery * qry = new QSqlQuery(cnect.mydb);
    qry->prepare("select nguoinhan,noidung,thoigian from hopthu where nguoigui = :ngui order by THOIGIAN DESC");
    qry->bindValue(":ngui",accName);
    qry->exec();
    modal->setQuery(*qry);
    t->setModel(modal);
}

void MailBox::show_thuden(QString tg){
    QString nguoigui = "";
    QString noidung = "";
    QSqlQuery * qry = new QSqlQuery(cnect.mydb);
    qry->prepare("select nguoigui,noidung,thoigian from hopthu where thoigian = :tg order by THOIGIAN DESC");
    qry->bindValue(":tg",tg);
    qry->exec();
    if(qry->next()){
        nguoigui = qry->value(0).toString();
        noidung = qry->value(1).toString();
    }
    noidung = "NGƯỜI GỬI :\n--------------\n"+nguoigui+"\n\nNỘI DUNG:\n----------------\n"+noidung+"\n\nTHỜI GIAN:\n---------------\n"+tg;
     ui->textBrowser_2->setText(noidung);
}

void MailBox::show_thugui(QString tg){
    QString nguoinhan = "";
    QString noidung = "";
    QSqlQuery * qry = new QSqlQuery(cnect.mydb);
    qry->prepare("select nguoinhan,noidung,thoigian from hopthu where thoigian = :tg");
    qry->bindValue(":tg",tg);
    qry->exec();
    if(qry->next()){
        nguoinhan = qry->value(0).toString();
        noidung = qry->value(1).toString();
    }
    noidung = "NGƯỜI NHẬN :\n--------------\n"+nguoinhan+"\n\nNỘI DUNG:\n----------------\n"+noidung+"\n\nTHỜI GIAN:\n---------------\n"+tg;
    ui->textBrowser_3->setText(noidung);
}

void MailBox::on_pushButton_2_clicked()//Xoá thư đến
{
    QModelIndex index = ui->tableView->currentIndex();
    if(!index.isValid()){
        QMessageBox::about(this,"Lỗi","Chọn tin nhắn cần xoá trước");
    }
    else
    {
        QString tg = index.sibling(index.row(), 2).data().toString();
        QSqlQuery* qry = new QSqlQuery(cnect.mydb);
        qry->prepare("delete from HOPTHU where THOIGIAN = :tg");
        qry->bindValue(":tg",tg);
        qry->exec();
        this->show_table_thuden(ui->tableView);
    }
}

void MailBox::on_pushButton_5_clicked()//Xoá thư đã gửi
{
    QModelIndex index = ui->tableView_3->currentIndex();
    if(!index.isValid()){
        QMessageBox::about(this,"Lỗi","Chọn tin nhắn cần xoá trước");
    }
    else
    {
        QString tg = index.sibling(index.row(), 2).data().toString();
        QSqlQuery* qry = new QSqlQuery(cnect.mydb);
        qry->prepare("delete from HOPTHU where THOIGIAN = :tg");
        qry->bindValue(":tg",tg);
        qry->exec();
        this->show_table_thugui(ui->tableView_3);
    }
}

void MailBox::on_pushButton_clicked()//Đọc hộp thư đến
{
    ui->textBrowser_2->show();
    ui->pushButton_6->show();
    ui->tableView->close();
    ui->pushButton->close();
    ui->pushButton_2->close();
    QModelIndex index = ui->tableView->currentIndex();
    if(!index.isValid()){
        QMessageBox::about(this,"Lỗi","Chọn tin nhắn cần xem trước");
    }
    else
    {
        QString tg = index.sibling(index.row(), 2).data().toString();
        this->show_thuden(tg);
    }
}

void MailBox::on_pushButton_6_clicked()//Trở về từ hộp thư đến
{
    ui->textBrowser_2->close();
    ui->pushButton_6->close();
    ui->tableView->show();
    ui->pushButton->show();
    ui->pushButton_2->show();
    this->show_table_thuden(ui->tableView);
}

void MailBox::on_pushButton_4_clicked()//Đọc thư đã gửi
{
    ui->textBrowser_3->show();
    ui->pushButton_7->show();
    ui->tableView_3->close();
    ui->pushButton_4->close();
    ui->pushButton_5->close();
    QModelIndex index = ui->tableView_3->currentIndex();
    if(!index.isValid()){
        QMessageBox::about(this,"Lỗi","Chọn tin nhắn cần xem trước");
    }
    else
    {
        QString tg = index.sibling(index.row(), 2).data().toString();
        this->show_thugui(tg);
    }
}

void MailBox::on_pushButton_7_clicked()//Trở về từ hộp thư đã gửi
{
    ui->textBrowser_3->close();
    ui->pushButton_7->close();
    ui->tableView_3->show();
    ui->pushButton_4->show();
    ui->pushButton_5->show();
    this->show_table_thugui(ui->tableView_3);
}

void MailBox::on_pushButton_3_clicked()//Tạo mới một thư
{
    QSqlQuery *inbox = new QSqlQuery(cnect.mydb);
    inbox->prepare("insert into HOPTHU values(:nguoigui,:nguoinhan,:noidung,:thoigian);");
    inbox->bindValue(":nguoigui",accName);
    inbox->bindValue(":nguoinhan",ui->lineEdit->text());
    inbox->bindValue(":noidung",ui->plainTextEdit->toPlainText());
    inbox->bindValue(":thoigian",QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"));
    if(ui->lineEdit->text()==""||ui->plainTextEdit->toPlainText() ==""){
        QMessageBox::warning(this,"Lỗi","Bạn không được bỏ trống thông tin");
        return;
    }
    else{
        if(inbox->exec()){
            QMessageBox::about(this,"Thành công","Bạn đã gửi thành công một tin nhắn");
        }
        ui->lineEdit->setText("");
        ui->plainTextEdit->clear();
        this->show_table_thuden(ui->tableView);
        this->show_table_thugui(ui->tableView_3);
    }
}

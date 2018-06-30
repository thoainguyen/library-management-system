#include "notice.h"
#include "ui_notice.h"
#include "signin/signin.h"
#include "connect/databaseconnection.h"
#include <QSql>
#include <QModelIndex>
notice::notice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notice)
{
    ui->setupUi(this);
    this->on_pushButton_refresh_clicked();
    ui->pushButton_capnhat->setVisible(false);
    ui->pushButton_huy->setVisible(false);
    ui->groupBox_dangtb->setTitle("Đăng Thông báo mới");
    ui->label_ndang->setVisible(false);
    ui->label_tgian->setVisible(false);
    ui->lineEdit_ndang->setVisible(false);
    ui->lineEdit_tgian->setVisible(false);
}

notice::notice(QString thongbao):
    QDialog(),
    ui(new Ui::notice)
{
    ui->setupUi(this);
    this->on_pushButton_refresh_clicked();
    this->on_pushButton_sua_clicked();
    ui->groupBox_xemtb->setVisible(false);
    ui->pushButton_dang->setVisible(false);
    ui->pushButton_dang->setVisible(false);
    ui->pushButton_huy->setVisible(false);
    ui->pushButton_capnhat->setVisible(false);
    ui->groupBox_dangtb->setTitle("Xem thông báo");
    connectDatabase tb;
    tb.openConnection();
    QSqlQuery qry1;
    qry1.exec("select * from THONGBAO where THOIGIAN = '"+thongbao+"'");
    qry1.next();
    ui->lineEdit_tgian->setText(qry1.value(0).toString());
    ui->lineEdit_tieude->setText(qry1.value(1).toString());
    ui->plainTextEdit_noidung->setPlainText(qry1.value(2).toString());
    QString ndang = qry1.value(3).toString() + " ("+qry1.value(4).toString()+")";

    ui->lineEdit_ndang->setText(ndang);

    ui->plainTextEdit_noidung->setTextInteractionFlags(Qt::TextSelectableByKeyboard);
    ui->lineEdit_tieude->setReadOnly(true);
    ui->label_ndang->setVisible(true);ui->label_ndang->setEnabled(false);
    ui->label_tgian->setVisible(true);ui->label_tgian->setEnabled(false);
    ui->lineEdit_ndang->setVisible(true);ui->lineEdit_ndang->setEnabled(false);
    ui->lineEdit_tgian->setVisible(true);ui->lineEdit_tgian->setEnabled(false);
    tb.closeConnection();
}

notice::notice(bool user) :
    QDialog(),
    ui(new Ui::notice)
{
    ui->setupUi(this);user;
    this->on_pushButton_refresh_clicked();
    ui->pushButton_capnhat->setVisible(false);
    ui->pushButton_huy->setVisible(false);
    ui->pushButton_dang->setVisible(false);
    ui->pushButton_xoa->setVisible(false);
    ui->pushButton_sua->setVisible(false);

    ui->groupBox_dangtb->setTitle("Xem Thông báo ");
    ui->label_ndang->setVisible(false);
    ui->label_tgian->setVisible(false);
    ui->lineEdit_ndang->setVisible(false);
    ui->lineEdit_tgian->setVisible(false);
    ui->lineEdit_tieude->setReadOnly(true);
    ui->plainTextEdit_noidung->setTextInteractionFlags(Qt::TextSelectableByKeyboard);
}

notice::~notice()
{
    delete ui;
}

void notice::on_pushButton_refresh_clicked()
{
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

void notice::on_pushButton_dang_clicked()
{
    QString now=QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss"),vaitro="";
    connectDatabase newnotice;
    newnotice.openConnection();

    QSqlQuery qry1,qry2;
    qry1.prepare("insert into THONGBAO values('"+now+"','"+ui->lineEdit_tieude->text()+
                 "','"+ui->plainTextEdit_noidung->toPlainText()+"','"+proname+"',:vaitro)");
    qry2.exec("select THUTHU,QUANLY from TAIKHOAN where TAIKHOAN = '"+proname+"'");
    qry2.next();
    if(qry2.value(0).toBool()==1) vaitro+="thủ thư.";
    if(qry2.value(1).toBool()==1) vaitro+=" quản lý";
    qry1.bindValue(":vaitro",vaitro);
    if(ui->lineEdit_tieude->text()==""||ui->lineEdit_tieude->text()=="")
        QMessageBox::critical(this,"Lỗi","Tiêu đề và nội dung không được bỏ trống.");
    else{
        qry1.exec();
        QMessageBox::information(this,"Thành công","Bạn đã đăng xong thông báo mới.");
        this->on_pushButton_refresh_clicked();
        ui->lineEdit_tieude->clear();
        ui->plainTextEdit_noidung->clear();
    }

    newnotice.closeConnection();
}

void notice::on_pushButton_sua_clicked()
{
    QModelIndex index = ui->tableView_thongbao->currentIndex();
    int row = index.row();
    QString thongbao = index.sibling(row, 0).data().toString(),ndang="";

    connectDatabase tb;
    tb.openConnection();
    QSqlQuery qry1;
    qry1.exec("select * from THONGBAO where THOIGIAN = '"+thongbao+"'");
    qry1.next();
    ui->lineEdit_tgian->setText(qry1.value(0).toString());
    ui->lineEdit_tieude->setText(qry1.value(1).toString());
    ui->plainTextEdit_noidung->setPlainText(qry1.value(2).toString());
    ndang = qry1.value(3).toString() + " ("+qry1.value(4).toString()+")";

    ui->lineEdit_ndang->setText(ndang);

    ui->pushButton_dang->setVisible(false);
    ui->pushButton_capnhat->setVisible(true);
    ui->pushButton_huy->setVisible(true);
    ui->groupBox_dangtb->setTitle("Sửa thông báo");

    ui->label_ndang->setVisible(true);ui->label_ndang->setEnabled(false);
    ui->label_tgian->setVisible(true);ui->label_tgian->setEnabled(false);
    ui->lineEdit_ndang->setVisible(true);ui->lineEdit_ndang->setEnabled(false);
    ui->lineEdit_tgian->setVisible(true);ui->lineEdit_tgian->setEnabled(false);
    tb.closeConnection();
}

void notice::on_pushButton_huy_clicked()
{
    ui->lineEdit_tieude->clear();
    ui->plainTextEdit_noidung->clear();
    ui->pushButton_dang->setVisible(true);
    ui->pushButton_capnhat->setVisible(false);
    ui->pushButton_huy->setVisible(false);

    ui->label_ndang->setVisible(false);
    ui->label_tgian->setVisible(false);
    ui->lineEdit_ndang->setVisible(false);
    ui->lineEdit_tgian->setVisible(false);
}

void notice::on_pushButton_capnhat_clicked()
{
    connectDatabase tb;
    tb.openConnection();
    QSqlQuery qry1;
    qry1.prepare("update THONGBAO set TIEUDE='"+ui->lineEdit_tieude->text()+
                 "',NOIDUNG='"+ui->plainTextEdit_noidung->toPlainText()+
                 "' where THOIGIAN='"+ui->lineEdit_tgian->text()+"' ");
    if(!qry1.exec())
        QMessageBox::critical(this,"Lỗi","Tiêu đề và nội dung không được bỏ trống");
    else{
        QMessageBox::information(this,"Thành công","Hoàn thành cập nhật thông báo này.");
        this->on_pushButton_refresh_clicked();
    }
    tb.closeConnection();
}

void notice::on_pushButton_xoa_clicked()
{
    QModelIndex index = ui->tableView_thongbao->currentIndex();
    int row = index.row();
    QString thoigian = index.sibling(row, 0).data().toString();//cot thoigian
    connectDatabase tb;
    tb.openConnection();
    QSqlQuery qry1;
    qry1.prepare("delete from THONGBAO where THOIGIAN = '"+thoigian+"'");
    QMessageBox xoatb;
    QPushButton *ok=xoatb.addButton(tr("XÓA") ,QMessageBox::ActionRole);
    xoatb.addButton(tr("Huỷ"),QMessageBox::NoRole);

    xoatb.setWindowTitle("Cảnh báo!");
    xoatb.setText("Thông báo này sẽ bị xóa khỏi hệ thống \n Bạn có chắc chắn muốn XÓA?");
    xoatb.exec();
    if(xoatb.clickedButton()==ok){
        qry1.exec();
        QMessageBox::information(this,"Đã xóa","Thông báo đã bị xóa.");
        this->on_pushButton_huy_clicked();
        this->on_pushButton_refresh_clicked();
    }
    tb.closeConnection();
}

void notice::on_pushButton_xem_clicked()
{
    on_pushButton_sua_clicked();
    ui->pushButton_huy->setVisible(false);
    ui->pushButton_capnhat->setVisible(false);
}

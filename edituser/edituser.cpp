#include "edituser.h"
#include "ui_edituser.h"
#include "signin/signin.h"
#include "admin/admin.h"
#include "connect/databaseconnection.h"
#include <QSql>
#include <random>
#include "encrypt/encrypt.h"
editUSER::editUSER(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editUSER)
{
    ui->setupUi(this);
    this->setFixedSize(506,354);

    ui->lineEdit_cmnd->setText(cmnd);ui->lineEdit_cmnd->setEnabled(false);
    ui->lineEdit_email->setText(email);ui->lineEdit_email->setEnabled(false);
    ui->lineEdit_hoten->setText(hoten);ui->lineEdit_hoten->setEnabled(false);
    ui->lineEdit_ngaysinh->setText(ngaysinh);ui->lineEdit_ngaysinh->setEnabled(false);
    ui->lineEdit_nghenghiep->setText(nghenghiep);ui->lineEdit_nghenghiep->setEnabled(false);

    if(docgia==1) ui->checkBox_dg->setChecked(true);ui->checkBox_dg->setEnabled(false);
    if(thuthu==1) ui->checkBox_tt->setChecked(true);ui->checkBox_tt->setEnabled(false);
    if(quanli==1) ui->checkBox_ql->setChecked(true);ui->checkBox_ql->setEnabled(false);

    ui->lineEdit_taikhoan->setText(taikhoan);ui->lineEdit_taikhoan->setDisabled(true);
    ui->lineEdit_gioitinh->setText(gioitinh);ui->lineEdit_gioitinh->setDisabled(true);
    ui->pushButton_update->setEnabled(false);
    if (!act) ui->status->setText("<b><p>Tài khoản bị khoá</p></b>");
    else ui->status->setText("Tài khoản hợp lệ");

    ui->groupBox_pass->setVisible(false);
    ui->groupBox_profile->setVisible(false);
    ui->groupBox_admin->setVisible(true);

}

editUSER::editUSER(QString profile)://phan chinh sua profile cua moi user

    ui(new Ui::editUSER)
{
    ui->setupUi(this);
    this->setFixedSize(488,354);

    connectDatabase data;
    data.openConnection();
    QString prcmnd,prtaikhoan,prdocgia,prthuthu,prquanli, pract,prhoten,premail,prngaysinh,prnghenghiep,prgioitinh;
    QSqlQuery* qry = new QSqlQuery(data.mydb);
    qry->prepare("select * from TAIKHOAN as t JOIN NGUOIDUNG as n on t.TAIKHOAN=n.TAIKHOAN where t.TAIKHOAN=:giatri");
    qry->bindValue(":giatri",profile);
    if(qry->exec()){
        while(qry->next()){
            prcmnd=qry->value(0).toString();
            prtaikhoan=qry->value(1).toString();
            prdocgia=qry->value(3).toBool();
            prthuthu=qry->value(4).toBool();
            prquanli=qry->value(5).toBool();
            pract=qry->value(6).toBool();
            prhoten=qry->value(7).toString();
            premail=qry->value(10).toString();
            prngaysinh=qry->value(11).toString();
            prnghenghiep=qry->value(12).toString();
            prgioitinh=qry->value(13).toString();

        }
    }
    data.closeConnection();

    ui->lineEdit_cmnd->setText(prcmnd);ui->lineEdit_cmnd->setEnabled(false);
    ui->lineEdit_email->setText(premail);ui->lineEdit_email->setEnabled(false);
    ui->lineEdit_hoten->setText(prhoten);ui->lineEdit_hoten->setEnabled(false);
    ui->lineEdit_ngaysinh->setText(prngaysinh);ui->lineEdit_ngaysinh->setEnabled(false);
    ui->lineEdit_nghenghiep->setText(prnghenghiep);ui->lineEdit_nghenghiep->setEnabled(false);

    if(prdocgia==1) ui->checkBox_dg->setChecked(true);ui->checkBox_dg->setEnabled(false);
    if(prthuthu==1) ui->checkBox_tt->setChecked(true);ui->checkBox_tt->setEnabled(false);
    if(prquanli==1) ui->checkBox_ql->setChecked(true);ui->checkBox_ql->setEnabled(false);

    ui->lineEdit_taikhoan->setText(prtaikhoan);ui->lineEdit_taikhoan->setDisabled(true);
    ui->lineEdit_gioitinh->setText(prgioitinh);ui->lineEdit_gioitinh->setDisabled(true);
    ui->pushButton_update->setEnabled(false);

    ui->status->setVisible(false);
    ui->groupBox_pass->setVisible(true);ui->groupBox_pass->setEnabled(false);
    ui->groupBox_profile->setVisible(true);
    ui->groupBox_admin->setVisible(false);
    ui->pushButton_savepass->setEnabled(false);

}

editUSER::~editUSER()
{
    delete ui;
}

void editUSER::on_pushButton_ok_clicked()
{
    this->close();
}

void editUSER::on_pushButton_2_clicked()
{
    ui->pushButton_update->setEnabled(true);
    ui->groupBox->setEnabled(true);
    ui->groupBox_pass->setEnabled(false);

    ui->lineEdit_cmnd->setEnabled(true);
    ui->lineEdit_email->setEnabled(true);
    ui->lineEdit_hoten->setEnabled(true);
    ui->lineEdit_ngaysinh->setEnabled(true);
    ui->lineEdit_nghenghiep->setEnabled(true);


    if(proname!=ui->lineEdit_taikhoan->text()&&!ui->checkBox_ql->isChecked()) ui->checkBox_dg->setEnabled(true);
    if(proname!=ui->lineEdit_taikhoan->text()&&!ui->checkBox_ql->isChecked()) ui->checkBox_tt->setEnabled(true);
    if(proname!=ui->lineEdit_taikhoan->text()&&!ui->checkBox_ql->isChecked()) ui->checkBox_ql->setEnabled(true);
}

void editUSER::on_pushButton_update_clicked()
{
    QString dg="false",tt="false",ql="false";
    if(ui->checkBox_dg->isChecked()) dg="true";
    if(ui->checkBox_tt->isChecked()) tt="true";
    if(ui->checkBox_ql->isChecked()) ql="true";


    connectDatabase data;
    data.openConnection();

    QSqlQuery qry1,qry2,qry3;

    qry1.prepare("update NGUOIDUNG set hoten=:ht,cmnd=:cm,email=:em,ngaysinh=:ns,congviec=:nn where CMND='"+cmnd+"'");
    qry1.bindValue(":ht",ui->lineEdit_hoten->text());
    qry1.bindValue(":cm",ui->lineEdit_cmnd->text());
    qry1.bindValue(":em",ui->lineEdit_email->text());
    qry1.bindValue(":ns",ui->lineEdit_ngaysinh->text());
    qry1.bindValue(":nn",ui->lineEdit_nghenghiep->text());

    qry2.prepare("update TAIKHOAN set cmnd=:cm,docgia=:dg,thuthu=:tt,quanly=:ql where taikhoan='"+ taikhoan +"'");
    qry2.bindValue(":cm",ui->lineEdit_cmnd->text());
    qry2.bindValue(":dg",dg);
    qry2.bindValue(":tt",tt);
    qry2.bindValue(":ql",ql);

    qry3.prepare("update YEUCAU set TRANGTHAI='đã xử lý' where GUI='"+ taikhoan +"'");

    QMessageBox saveupdate;
    QPushButton *ok=saveupdate.addButton(tr("Đồng ý") ,QMessageBox::ActionRole);
    saveupdate.addButton(QMessageBox::Cancel);

    saveupdate.setWindowTitle("Thông báo");
    saveupdate.setText("Bạn có chắc chắn muốn thay đổi thông tin của tài khoản này?");
    saveupdate.exec();
    if(saveupdate.clickedButton()==ok){
        qry1.exec();
        qry2.exec();
        qry3.exec();
        QMessageBox::information(this,"Thành công","Cập nhật thông tin thành công.");
        this->close();
    }
    ui->pushButton_update->setEnabled(false);

    data.closeConnection();
}

void editUSER::on_pushButton_reset_clicked()
{
    QString now=QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    connectDatabase data;
    data.openConnection();

    QSqlQuery qry,qry2;

    if(act){
        qry.exec("update TAIKHOAN set ACTIVE='false' where TAIKHOAN='"+taikhoan+"'  ");
        QMessageBox::information(this,tr("Đã khoá"),tr("Tài khoản này đã bị khoá."));
        ui->status->setText("<b><p>Tài khoản bị khoá</p></b>");
        act=0;
        qry2.exec("update YEUCAU set THOIGIAN='"+now+"',GUI='"+taikhoan+"',NOIDUNG='[!!] "+taikhoan+" đã bị khoá',TRANGTHAI='đã xử lý' where GUI='"+taikhoan+"' ");
    }
    else if(!act){
        qry.exec("update TAIKHOAN set ACTIVE='true' where TAIKHOAN='"+taikhoan+"'  ");
        QMessageBox::information(this,tr("Mở khoá"),tr("Đã mở khoá cho tài khoản"));
        ui->status->setText("Tài khoản  hợp lệ");
        act=1;
        qry2.exec("update YEUCAU set THOIGIAN='"+now+"',GUI='"+taikhoan+"',NOIDUNG='[!] "+taikhoan+" đã được mở khoá',TRANGTHAI='đã xử lý' where GUI='"+taikhoan+"' ");
    }

    data.closeConnection();
}

void editUSER::on_pushButton_del_clicked()
{
    QString now=QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    connectDatabase data2;
    data2.openConnection();

    QSqlQuery qry1,qry2,qry3,qry4,qry5;
    qry1.prepare("delete from TAIKHOAN where TAIKHOAN='"+taikhoan+"'");
    qry2.prepare("delete from NGUOIDUNG where TAIKHOAN='"+taikhoan+"'");
    qry3.prepare("insert into YEUCAU values ('QUANLY','HE THONG','[-] "+taikhoan+" đã bị xoá ', '"+now+"','đã xử lý')");
    qry4.exec("select * from TAIKHOAN where TAIKHOAN='"+taikhoan+"' and QUANLY='true'");
    qry5.exec("select TAIKHOAN from TAIKHOAN where TAIKHOAN='"+taikhoan+"'");
    if(proname==qry5.value(0).toString())
        QMessageBox::critical(this,"Lỗi","Bạn không thể xóa chính mình.");
    else if(qry4.next())
        QMessageBox::critical(this,"Lỗi","Bạn không thể xóa quản lý.");
    else{
        QMessageBox delacc;
        QPushButton *ok=delacc.addButton(tr("XÓA") ,QMessageBox::ActionRole);
        delacc.addButton(tr("Huỷ"),QMessageBox::NoRole);

        delacc.setWindowTitle("Cảnh báo!");
        delacc.setText("Tài khoản này sẽ bị xoá hoàn toàn khỏi hệ thống \n Bạn có chắc chắn muốn XÓA?");
        delacc.exec();
        if(delacc.clickedButton()==ok){
            qry3.exec();
            qry1.exec();
            qry2.exec();
            QMessageBox::information(this,"Đã xóa","Tài khoản đã bị xóa.");
            this->close();
        }
    }

    data2.closeConnection();
}

void editUSER::on_pushButton_deall_clicked()
{
    QString now=QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    connectDatabase data2;
    data2.openConnection();

    QSqlQuery qry1,qry2,qry3;
    qry1.prepare("delete from NGUOIDUNG where taikhoan = (select taikhoan from TAIKHOAN where cmnd='"+cmnd+
                 "' and QUANLY!='true')");
    qry2.prepare("delete from TAIKHOAN where cmnd='"+cmnd+"' and QUANLY!='true'");

    qry3.prepare("insert into YEUCAU values ('QUANLY','HE THONG','[--] "+hoten+
                 " đã bị xóa cùng với các tài khoản đã đăng kí.', '"+now+"','đã xử lý')");
    QMessageBox delacc;
    QPushButton *ok=delacc.addButton(tr("XÓA") ,QMessageBox::ActionRole);
    delacc.addButton(tr("Huỷ"),QMessageBox::NoRole);

    delacc.setWindowTitle("Cảnh báo!");
    delacc.setText("Người dùng này sẽ bị xoá hoàn toàn khỏi hệ thống \n (bao gồm tất cả tài khoản đã đăng kí) \n \n Bạn có chắc chắn muốn XÓA?");
    delacc.exec();
    if(delacc.clickedButton()==ok){
        qry3.exec();
        qry1.exec();
        qry2.exec();
        QMessageBox::information(this,"Đã xóa","Người dùng và các tài khoản đăng kí đã bị xóa.");
        this->close();
    }
    data2.closeConnection();
}

void editUSER::on_pushButton_lock_clicked()//tạo lại mật khẩu
{
    QString now=QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> len(1,10);
    std::uniform_int_distribution<int> dis(32,126);


    connectDatabase data;
    data.openConnection();

    QSqlQuery qry1,qry2,qry3;

    qry2.exec("select * from YEUCAU where GUI='"+taikhoan+"' and NOIDUNG='[?] "+
                 taikhoan+" yêu cầu đặt lại mật khẩu ' and TRANGTHAI='chưa xử lý' ");
    qry3.prepare("update YEUCAU set THOIGIAN='"+now+"',GUI='"+taikhoan+"',NOIDUNG='[#] "+
                 taikhoan+" đã được tạo lại mật khẩu',TRANGTHAI='đã xử lý' where GUI='"+taikhoan+"' ");

    if(!qry2.next()){
        QMessageBox::critical(this,"Lỗi","Tài khoản này không yêu cầu đặt lại mật khẩu.");
    }
    else{
        QMessageBox delacc;
        QPushButton *ok=delacc.addButton(tr("Có") ,QMessageBox::ActionRole);
        delacc.addButton(tr("Huỷ"),QMessageBox::NoRole);

        delacc.setWindowTitle("Cảnh báo!");
        delacc.setText("Mật khẩu của tài khoản sẽ được tạo lại(ngẫu nhiên) \n \n Bạn có chắc chắn?");
        delacc.exec();
        if(delacc.clickedButton()==ok){
            for(int i=0;i<len(rng);i++){
                resetpass+=(char)dis(rng);
            }
            QString resetpass2 = encrypt(resetpass,taikhoan);
            qry1.exec("update TAIKHOAN set MATKHAU='"+resetpass2+"' where taikhoan='"+taikhoan+"'");
            qry3.exec();
            QMessageBox::information(this,"Thành công","Người dùng sẽ nhận được mật khẩu mới khi đăng nhập.");
            this->close();
        }
    }
    data.closeConnection();
}

void editUSER::on_pushButton_changepass_clicked()
{
    ui->groupBox_pass->setVisible(true);
    ui->groupBox_pass->setEnabled(true);
    ui->pushButton_savepass->setEnabled(true);
    ui->groupBox->setEnabled(false);
}

void editUSER::on_pushButton_savepass_clicked()
{
    connectDatabase data;
    data.openConnection();
    QString mkcu=encrypt(ui->lineEdit_mkcu->text(),ui->lineEdit_taikhoan->text()),
            mkmoi=encrypt(ui->lineEdit_mkmoi->text(),ui->lineEdit_taikhoan->text()),
            xacnhan=encrypt(ui->lineEdit_xacnhan->text(),ui->lineEdit_taikhoan->text());
    if(mkmoi!=xacnhan||mkmoi=="")
        QMessageBox::critical(this,"Lỗi","Mật khẩu không trùng khớp");
    else{
        QSqlQuery qry,qry2;
        qry.exec("select MATKHAU from TAIKHOAN where TAIKHOAN='"+ui->lineEdit_taikhoan->text()+
                     "' and MATKHAU='"+mkcu+"'");
        qry2.prepare("update TAIKHOAN set MATKHAU='"+mkmoi+
                  "' where TAIKHOAN='"+ui->lineEdit_taikhoan->text()+"' and MATKHAU='"+mkcu+"'");


        if(!qry.next())
            QMessageBox::critical(this,"Lỗi","Sai mật khẩu.");
        else{
            qry2.exec("update TAIKHOAN set MATKHAU='"+mkmoi+
                      "' where TAIKHOAN='"+ui->lineEdit_taikhoan->text()+"' and MATKHAU='"+mkcu+"'");
            QMessageBox::information(this,"Thành công","Mật khẩu thay đổi thành công.");
            ui->pushButton_savepass->setEnabled(false);
        }
    }
    data.closeConnection();
}

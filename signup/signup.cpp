#include "signup.h"
#include "ui_signup.h"
#include "connect/databaseconnection.h"
#include <QMessageBox>
#include <QSql>
#include <QDateTime>
#include "encrypt/encrypt.h"
SignUpDialog::SignUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    ui->setupUi(this);
    this->setFixedSize(435,543);
    QString filename=QCoreApplication::applicationDirPath()+"/noiquy.txt";
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "error open file "<<filename;
    }
    ui->xacthuc->setVisible(false);
    ui->xacthuc->setChecked(true);
    QString line;
    ui->plainTextEdit_2->clear();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while (!stream.atEnd()){
            line = stream.readLine();
            ui->plainTextEdit_2->setPlainText(ui->plainTextEdit_2->toPlainText()+line+"\n");
            //ui->label->setText(line);

        }
       // ui->plainTextEdit->setDisabled(true);
        ui->plainTextEdit_2->setTextInteractionFlags(Qt::TextSelectableByKeyboard);
    }

    file.close();
}

SignUpDialog::SignUpDialog(bool adduser):
    QDialog(),
    ui(new Ui::SignUpDialog)
{
    this->setFixedSize(435,400);
    this->setWindowTitle("Thêm tài khoản");
    if(adduser){
        ui->setupUi(this);
        ui->plainTextEdit_2->setVisible(false);
        ui->read->setVisible(false);
        ui->xacthuc->setVisible(true);
        ui->read->setChecked(true);
    }
}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}
void SignUpDialog::on_pushButton_clicked()
{
    this->close();
}


bool reader=0, librarian=0, admin=0, confirm;
QString gender="";
void SignUpDialog::on_pushButton_2_clicked()
{
    confirm =1;
    if (!(ui->read->isChecked())){
        QMessageBox::warning(this,"Lỗi","Bạn chưa đọc quy định!");
        confirm =0;
    }
    if (!(ui->xacthuc->isChecked())){
        QMessageBox::warning(this,"Lỗi","Tài khoản phải được xác thực!");
        confirm =0;
    }
    if (ui->checkBox_reader->isChecked())
    {
        reader = 1;
    }
    if (ui->checkBox_librarian->isChecked())
    {
       librarian = 1;
    }
    if (ui->checkBox_admin->isChecked())
    {
        admin  = 1;
    }
    if (ui->radioButton_male->isChecked())
    {
        gender  = "Nam";
    }
    if (ui->radioButton_female->isChecked())
    {
        gender  = "Nữ";
    }
    if (ui->radioButton_others->isChecked())
    {
        gender  = "Khác";
    }

    QString accountname =  ui->lineEdit_account->text();

    QString CMND = ui->lineEdit_id->text();
    QString Pass = ui->lineEdit_pass -> text();
    QString pass = encrypt(Pass, accountname);
    QString confirmpass = ui->lineEdit_confirm -> text();
    confirmpass = encrypt(confirmpass, accountname);
    if (confirmpass != pass){
        QMessageBox :: warning (this, "Lỗi", "Mật khẩu không trùng khớp!");
        ui->lineEdit_pass ->setText ("");
        ui->lineEdit_confirm ->setText ("");
        confirm=0;
    }
    QString email = ui->lineEdit_email->text() + '@' + ui->lineEdit_email2->text() + ui->comboBox->currentText();
    QString username =  ui->lineEdit_username->text();
    QString job = ui->lineEdit_job->text();
    QString bd = ui->spinBox_d->text() + '/' + ui->spinBox_m->text() +'/'+ ui->spinBox_y->text() ;
    if (gender=="" || accountname=="" ||CMND == "" || pass =="" || email =="" ||username=="" || job =="" )
    {
        QMessageBox :: warning (this, "Lỗi", "Bạn phải điền đủ thông tin!");
        confirm =0;
     }


    connectDatabase DB;
    if(!DB.openConnection()){
       QMessageBox::critical(this,"Database Error!","Error Connecting to Database! Please try again or Check Database.");
    }

    DB.openConnection();
    QSqlQuery qry,qry2,qry3;
    if(qry.exec("select TAIKHOAN from TAIKHOAN where TAIKHOAN ='" + accountname +"';")){
        if(qry.next()){
            QMessageBox :: warning (this, "Lỗi", "Tài khoản đã được sử dụng!");
            confirm = 0;
        }
    }

    if(qry.exec("select HOTEN from NGUOIDUNG where CMND ='" + CMND +"';")){
        if(qry.next()){
            QString hoten= qry.value(0).toString();
            if (hoten != username){
                QMessageBox :: warning(this,"Lỗi","Họ tên không trùng khớp với CMND đã đăng kí!");
                confirm =0;
            }
        }
    }

    if (confirm==1){

        qry.prepare("insert into NGUOIDUNG VALUES(:acc,:taikhoan,:cmnd,:email,:ngaysinh,:congviec,:gioitinh)");
        qry.bindValue(":acc",username);
        qry.bindValue(":email",email);
        qry.bindValue(":cmnd",CMND);
        qry.bindValue(":ngaysinh",bd);
        qry.bindValue(":congviec",job);
        qry.bindValue(":taikhoan",accountname);
        qry.bindValue(":gioitinh",gender);

        qry2.prepare("insert into TAIKHOAN VALUES(:cmnd,:taikhoan,:matkhau,:docgia,:thuthu,:quanli,:hoatdong)");
        qry2.bindValue(":cmnd",CMND);
        qry2.bindValue(":taikhoan",accountname);
        qry2.bindValue(":matkhau",pass);
        if (reader)
            qry2.bindValue(":docgia","true");
        else
            qry2.bindValue(":docgia","false");
        qry2.bindValue(":thuthu","false");
        qry2.bindValue(":quanli","false");
        qry2.bindValue(":hoatdong","true");

        if (qry.exec() && qry2.exec()){
             QMessageBox :: about (this, "Chúc mừng!", "Bạn đã đăng kí thành công!");

             QString content = "[+]Tài khoản " + accountname + " đã được tạo. ";
             if (librarian==1){
                 content += "Yêu cầu làm thủ thư. ";
             }
             if (admin==1){
                 content += "Yêu cầu làm quản lý.";
             }

             QString now=QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
             qry3.prepare("insert into YEUCAU VALUES ('QUANLY',:taikhoan,:noidung,:tg,'chưa xử lý')");
             qry3.bindValue(":taikhoan",accountname);
             qry3.bindValue(":noidung",content);
             qry3.bindValue(":tg",now);
             qry3.exec();

             this->close();
        }


    }
}

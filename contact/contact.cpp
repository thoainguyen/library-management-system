#include "contact.h"
#include "ui_contact.h"
#include "connect/databaseconnection.h"
#include <QSql>
contact::contact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::contact)
{
    ui->setupUi(this);
    connectDatabase data;
    data.openConnection();

    QSqlQueryModel* databaseModel = new QSqlQueryModel;

    QSqlQuery* qry = new QSqlQuery(data.mydb);

    qry->exec("select n.HOTEN,n.TAIKHOAN,n.EMAIL from NGUOIDUNG as n join TAIKHOAN as t on t.taikhoan=n.taikhoan where t.thuthu='true' or t.quanly='true'");

    databaseModel->setQuery(*qry);
    ui->tableView->setModel(databaseModel);

    ui->tableView->AdjustToContentsOnFirstShow;
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    data.closeConnection();
}

contact::~contact()
{
    delete ui;
}

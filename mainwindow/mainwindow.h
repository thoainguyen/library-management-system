#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "signin/signin.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
public:
    bool accReader= false,accAdmin = false,accLibrarian=true,accActive = false;
    QString PIN = "",accName = "";
    Q_OBJECT
public:
    explicit MainWindow(bool admin,bool reader, bool librarian,
                        QString pin,QString name,QWidget * par = 0);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSignUp_triggered();

    void on_actionSignIn_triggered();

    void on_actionSignOut_triggered();

    void on_actionHome_triggered();

    void on_actionabout_triggered();

    void on_actionrule_triggered();

    void on_actionUser_triggered();

    void on_actionNotice_triggered();

    void on_actionMail_triggered();

    void on_actioncontact_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

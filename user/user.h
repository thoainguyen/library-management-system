#ifndef USER_H
#define USER_H

#include <QWidget>

namespace Ui {
class user;
}

class user : public QWidget
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = 0);
    ~user();

private:
    Ui::user *ui;
};

#endif // USER_H

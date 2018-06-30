#-------------------------------------------------
#
# Project created by QtCreator 2017-05-21T12:28:34
#
#-------------------------------------------------

QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LIBPRO
TEMPLATE = app
RC_FILE = libpro.rc

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    addbook/addbook.cpp \
    admin/admin.cpp \
    cart/cart.cpp \
    contact/contact.cpp \
    edituser/edituser.cpp \
    encrypt/encrypt.cpp \
    forgetpass/forgetpass.cpp \
    home/home.cpp \
    librarian/librarian.cpp \
    mailbox/mailbox.cpp \
    mainwindow/mainwindow.cpp \
    noiquy/noiquy.cpp \
    notice/notice.cpp \
    reader/reader.cpp \
    signin/signin.cpp \
    signup/signup.cpp \
    user/user.cpp

HEADERS  += addbook/addbook.h \
    admin/admin.h \
    cart/cart.h \
    connect/databaseconnection.h \
    contact/contact.h \
    edituser/edituser.h \
    encrypt/encrypt.h \
    forgetpass/forgetpass.h \
    home/home.h \
    librarian/librarian.h \
    mailbox/mailbox.h \
    mainwindow/mainwindow.h \
    noiquy/noiquy.h \
    notice/notice.h \
    reader/reader.h \
    signin/signin.h \
    signup/signup.h \
    user/user.h

FORMS    += addbook/addbook.ui \
    admin/admin.ui \
    cart/cart.ui \
    contact/contact.ui \
    edituser/edituser.ui \
    forgetpass/forgetpass.ui \
    home/home.ui \
    librarian/librarian.ui \
    mailbox/mailbox.ui \
    mainwindow/mainwindow.ui \
    noiquy/noiquy.ui \
    notice/notice.ui \
    reader/reader.ui \
    signin/signin.ui \
    signup/signup.ui \
    user/user.ui

RESOURCES +=  src.qrc

DISTFILES += \
    images/iconwindow.ico \
    images/del.png \
    images/lock.png \
    images/reset.png \
    images/update.png \
    images/update2.png \
    images/update3.ico \
    images/reset2.png \
    data/database.sqlite \
    images/contact-icon.gif \
    images/images.jpg \
    images/imes.jpg \
    images/index.jpg \
    images/25.png \
    images/52-128.png \
    images/about-us-icon-15.png \
    images/acc.png \
    images/add.png \
    images/b.png \
    images/Button-Close-icon.png \
    images/button_cancel.png \
    images/cart.png \
    images/contact.png \
    images/contactus-icon.png \
    images/copy_icon.png \
    images/database-remove-icon.png \
    images/del.png \
    images/del2.png \
    images/del3.png \
    images/floppy-disk.png \
    images/Home.png \
    images/icon-account-dark.png \
    images/icon-select.png \
    images/iconwindow.png \
    images/images.png \
    images/info.png \
    images/lock.png \
    images/m.png \
    images/mail.png \
    images/Misc-New-Database-icon.png \
    images/notice.png \
    images/pen.png \
    images/Pencil-icon.png \
    images/reset.png \
    images/reset2.png \
    images/reset22.png \
    images/rule.png \
    images/search-icon.png \
    images/select_code-512.png \
    images/signin1.png \
    images/signo.png \
    images/signupbg.png \
    images/signupicon.png \
    images/ucontract.png \
    images/update.png \
    images/update2.png \
    images/users.png \
    images/Delete.ico \
    images/home.ico \
    images/iconwindow.ico \
    images/Oxygen-Icons.org-Oxygen-Apps-preferences-contact-list.ico \
    images/signin.ico \
    images/signout.ico \
    images/update3.ico \
    images/user.ico \
    data/noiquy.txt

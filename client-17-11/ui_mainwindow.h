/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Nov 17 17:26:04 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_5;
    QPushButton *pushButton_5;
    QPushButton *pushButton_7;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_4;
    QWidget *tab_2;
    QLabel *label_8;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_7;
    QLabel *label_9;
    QLabel *label_10;
    QPushButton *pushButton_8;
    QPushButton *pushButton;
    QWidget *tab_3;
    QListWidget *listWidget;
    QPushButton *pushButton_6;
    QPushButton *pushButton_2;
    QWidget *widget;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(797, 627);
        MainWindow->setMinimumSize(QSize(0, 0));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(100, 10, 671, 351));
        tabWidget->setIconSize(QSize(18, 18));
        tabWidget->setTabsClosable(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(270, 30, 121, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Bitstream Charter"));
        font.setPointSize(16);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label_6->setFont(font);
        label_7 = new QLabel(tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 180, 121, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Serif"));
        font1.setPointSize(16);
        font1.setBold(false);
        font1.setItalic(true);
        font1.setWeight(50);
        label_7->setFont(font1);
        label_5 = new QLabel(tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 100, 91, 41));
        label_5->setFont(font1);
        pushButton_5 = new QPushButton(tab);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(350, 260, 301, 41));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Serif"));
        font2.setPointSize(13);
        font2.setBold(true);
        font2.setItalic(true);
        font2.setWeight(75);
        pushButton_5->setFont(font2);
        pushButton_7 = new QPushButton(tab);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(20, 260, 301, 41));
        pushButton_7->setFont(font2);
        lineEdit_5 = new QLineEdit(tab);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(190, 180, 451, 41));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Serif"));
        font3.setPointSize(13);
        font3.setBold(false);
        font3.setItalic(true);
        font3.setWeight(50);
        lineEdit_5->setFont(font3);
        lineEdit_5->setEchoMode(QLineEdit::Password);
        lineEdit_4 = new QLineEdit(tab);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(190, 100, 451, 41));
        lineEdit_4->setFont(font3);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        label_8 = new QLabel(tab_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 130, 121, 21));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Bitstream Charter"));
        font4.setPointSize(16);
        font4.setBold(false);
        font4.setItalic(false);
        font4.setWeight(50);
        label_8->setFont(font4);
        lineEdit_3 = new QLineEdit(tab_2);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(240, 60, 401, 41));
        lineEdit_6 = new QLineEdit(tab_2);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(240, 180, 401, 41));
        lineEdit_6->setEchoMode(QLineEdit::Password);
        lineEdit_7 = new QLineEdit(tab_2);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(240, 120, 401, 41));
        lineEdit_7->setEchoMode(QLineEdit::Password);
        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(30, 180, 181, 31));
        label_9->setFont(font4);
        label_10 = new QLabel(tab_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(30, 70, 131, 31));
        label_10->setFont(font4);
        pushButton_8 = new QPushButton(tab_2);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(20, 250, 401, 41));
        QFont font5;
        font5.setItalic(false);
        pushButton_8->setFont(font5);
        pushButton_8->setAutoDefault(false);
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(442, 250, 201, 41));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        listWidget = new QListWidget(tab_3);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 10, 521, 291));
        listWidget->setSelectionMode(QAbstractItemView::NoSelection);
        listWidget->setIconSize(QSize(20, 20));
        pushButton_6 = new QPushButton(tab_3);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(550, 70, 101, 41));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Sans Serif"));
        font6.setPointSize(10);
        pushButton_6->setFont(font6);
        pushButton_2 = new QPushButton(tab_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(550, 10, 101, 41));
        tabWidget->addTab(tab_3, QString());
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 50, 191, 41));
        QFont font7;
        font7.setFamily(QString::fromUtf8("Sans Serif"));
        font7.setPointSize(16);
        label->setFont(font7);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 140, 201, 20));
        label_2->setFont(font7);
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(260, 50, 281, 41));
        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(260, 126, 281, 41));
        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(490, 230, 131, 41));
        pushButton_3->setFont(font7);
        tabWidget->addTab(widget, QString());
        MainWindow->setCentralWidget(centralWidget);
        QWidget::setTabOrder(listWidget, pushButton_6);

        retranslateUi(MainWindow);
        QObject::connect(pushButton_6, SIGNAL(clicked()), MainWindow, SLOT(closeAndSend()));
        QObject::connect(pushButton_7, SIGNAL(clicked()), MainWindow, SLOT(tryConnect()));
        QObject::connect(pushButton_5, SIGNAL(clicked()), MainWindow, SLOT(closeApplication()));
        QObject::connect(tabWidget, SIGNAL(selected(QString)), MainWindow, SLOT(NewAccountTab(QString)));
        QObject::connect(pushButton_8, SIGNAL(clicked()), MainWindow, SLOT(NewAccount()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), MainWindow, SLOT(NewServerAddress()));

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Welcome!", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Password", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Login", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("MainWindow", "Login", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Avtorization", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Password", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Confirm password", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "Login", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("MainWindow", "Ok", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Home", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Registration", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "Home", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Contact_List", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Enter  server ip", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Enter server port", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("MainWindow", "Apply", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(widget), QApplication::translate("MainWindow", "Setting", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

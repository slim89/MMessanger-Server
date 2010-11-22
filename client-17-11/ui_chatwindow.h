/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created: Thu Nov 18 12:58:28 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chatWindow
{
public:
    QWidget *centralwidget;
    QTextBrowser *textBrowser;
    QPushButton *pushButton_5;
    QLineEdit *lineEdit_3;

    void setupUi(QMainWindow *chatWindow)
    {
        if (chatWindow->objectName().isEmpty())
            chatWindow->setObjectName(QString::fromUtf8("chatWindow"));
        chatWindow->resize(666, 351);
        centralwidget = new QWidget(chatWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(20, 20, 631, 241));
        QFont font;
        font.setFamily(QString::fromUtf8("URW Chancery L"));
        font.setPointSize(18);
        font.setItalic(true);
        textBrowser->setFont(font);
        textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser->setTabChangesFocus(false);
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(540, 280, 111, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("URW Chancery L"));
        font1.setPointSize(18);
        pushButton_5->setFont(font1);
        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(20, 280, 501, 51));
        chatWindow->setCentralWidget(centralwidget);
        QWidget::setTabOrder(lineEdit_3, pushButton_5);
        QWidget::setTabOrder(pushButton_5, textBrowser);

        retranslateUi(chatWindow);
        QObject::connect(pushButton_5, SIGNAL(clicked()), chatWindow, SLOT(sendMessage()));

        QMetaObject::connectSlotsByName(chatWindow);
    } // setupUi

    void retranslateUi(QMainWindow *chatWindow)
    {
        chatWindow->setWindowTitle(QApplication::translate("chatWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        textBrowser->setHtml(QApplication::translate("chatWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'URW Chancery L'; font-size:18pt; font-weight:400; font-style:italic;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">           </p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-weight:600; color:#dd0000;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-weight:600; color:#dd0000;\"></p></td"
                        "></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("chatWindow", "Send", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class chatWindow: public Ui_chatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H

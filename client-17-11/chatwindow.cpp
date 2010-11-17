#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <QMessageBox>
#include "mainwindow.h"
#include <QTime>
#include <QDate>

extern QPointer<chatWindow> newWindow[10];
extern int socketSender;
extern QString ourNick;

chatWindow::chatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chatWindow)
{
    ui->setupUi(this);
    this->setGeometry(300,400,671,351);
    this->setMaximumSize(671,351);
    this->setMinimumSize(671,351);
}

chatWindow::~chatWindow()
{

    delete ui;
}

void chatWindow::closeEvent(QCloseEvent *event)
{
    int i;

    for(i = 0; i < 10; i++)
    {
        if(newWindow[i] != NULL)
            {
            if(this->windowTitle() == newWindow[i]->windowTitle())
            {
                  newWindow[i] = NULL;
             }
        }
    }
this->deleteLater();
}

void chatWindow::addMessage(QString from, QString msg)
{
   QTime messageTime;
   this->ui->textBrowser->setTextColor(Qt::red);
   this->ui->textBrowser->append("");
   this->ui->textBrowser->append(from+"("+messageTime.currentTime().toString()+ ")");
   this->ui->textBrowser->append(msg);
}
void chatWindow::sendMessage()
{
    QString To,Msg;
    To = this->windowTitle();
    Msg = ui->lineEdit_3->text();
    string message = "#type/send#r/"+ To.toStdString() + "#m/" +  Msg.toStdString();
    send(socketSender, message.c_str(), 80, 0);
    QTime messageTime;
    this->ui->textBrowser->setTextColor(Qt::black);
    this->ui->textBrowser->append("");
    this->ui->textBrowser->append(ourNick+"("+messageTime.currentTime().toString()+ ")");
    this->ui->textBrowser->append(Msg);
    this->ui->lineEdit_3->setText("");
}



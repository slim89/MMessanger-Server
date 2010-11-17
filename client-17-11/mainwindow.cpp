#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <chatwindow.h>
#include <recvthread.h>
#include <QMessageBox>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>

int globalPort = htons(3425);
int globalIP =0x68000D0A;

int max_count_prefix=10;
QPointer<chatWindow> newWindow[10] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
extern int socketSender;
extern QString ourNick;
extern QString globalbuff [2][50];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
             ui->setupUi(this);
             this->setWindowTitle("MeegoMessanger");
             this->setGeometry(300,400,671,351);
             this->setMaximumSize(671,351);
             this->setMinimumSize(671,351);
             ui->tabWidget->setGeometry(5,5,661,341);
             ui->tabWidget->setCurrentIndex(0);
             connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(NewWindow()));

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::tryConnect()
{
    QString loginMsg,
            passwMsg;
int res;
   bool loginSendOk    = true;

   if(socketSender == -1)
    {
       Conected();
    }

if(socketSender != -1)
   {

        loginMsg = ui->lineEdit_4->text();
        passwMsg = ui->lineEdit_5->text();
        ourNick = loginMsg;
        char answ[80];
        string message = "#type/log#o/login#l/"+ loginMsg.toStdString() + "#p/" +  passwMsg.toStdString();
        res = send(socketSender, message.c_str(), 80, 0);
        recv(socketSender, answ, 80, 0);
        if( res < 0)
                  {
                      QMessageBox::information(this,"Message","Sorry! But you have problem with sending you \"login\" to server!");
                      loginSendOk = false;
                   }

        if(!strncmp("*good login/password", answ, 21))
          {

              ui->tabWidget->setCurrentIndex(2);
              RecvThread *thread1 = new RecvThread(this,
                                                   ui->listWidget,
                                                   socketSender,
                                                   *newWindow);

              thread1->start();
          }
         else
          {
            QMessageBox::information(this,"Message","Incorrect login or password! Try again!");
             socketSender=-1;
          }

      }


}

void MainWindow::changeMessageDelivered()
{
    //ui->label_5->setText(ui->listWidget->currentItem()->text());
}
void MainWindow::closeApplication()
{
    this->close();
}
void MainWindow::NewWindow()
{
    bool newClient = true;
    int i,j;
    QString Nick;
    Nick = ui->listWidget->currentItem()->text();

    for(i = 0; i < 10; i++)
    {
        if( newWindow[i] != NULL)
           {
            if(!strcmp(newWindow[i]->windowTitle().toAscii(),Nick.toAscii()))
                {
                    newClient = false;
                    newWindow[i]->show();
                }
           }
    }

 if( newClient == true )
    {
     ui->listWidget->currentItem()->setTextColor(Qt::black);

      for(i = 0; i < 10; i++)
      {
         if(newWindow[i] == NULL)
          {

             newWindow[i] = new chatWindow(this);
             newWindow[i]->setWindowTitle(Nick);
             newWindow[i]->show();
             for(j = 0; j< 50; j++)
             {
                 if(globalbuff[0][j] == Nick)
                 {
                      newWindow[i]->addMessage(globalbuff [0][j],globalbuff [1][j]);
                      globalbuff [0][j] = "";
                      globalbuff [1][j]= "";
                 }
             }
             break;
          }
      }
   }



}
void MainWindow::NewAccountTab(QString name)
{
        if(name=="Registration")
        {

            if( socketSender == -1)
             {
                 Conected();
            }
            if( socketSender == -1)
             {
               ui->tabWidget->setCurrentIndex(0);
            }

        }
}
void MainWindow::Conected()
{

    int res;
    bool socketInitOk = true;
    struct sockaddr_in srv_addr;
    socketSender = socket(AF_INET,SOCK_STREAM,0);
    if(socketSender < 0)
    {
            QMessageBox::information(this,"Message","Sorry! But you have problem with socket init! Try again!");
            socketInitOk = false;

    }

    if(socketInitOk)
    {

          srv_addr.sin_family=AF_INET;
          srv_addr.sin_port = globalPort;
          srv_addr.sin_addr.s_addr=globalIP;
          res = ::connect(socketSender,(struct sockaddr*)&srv_addr,sizeof(srv_addr));
          if(res < 0)
          {
                    QMessageBox::information(this,"Message","Sorry! But you have problem with connect to server! Try again");
                    socketSender=-1;

             }

     }

}
void MainWindow::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
    exit(0);
}
void MainWindow::closeAndSend()
{
    send(socketSender, "exitcli", 80, 0);
    send(socketSender,"exitcli", 80, 0);
    this->deleteLater();
    exit(0);
}
void MainWindow::NewAccount()
{
    bool passwOk = true;
    if( ui->lineEdit_7->text() != ui->lineEdit_6->text())
   {
        QMessageBox::information(this,"Please, enter you password again!",
                                 "Fiels \"Password\" and \"Confirm password do not match\"");
        this->ui->lineEdit_6->setText("");
        this->ui->lineEdit_7->setText("");
        passwOk = false;
   }
    if( passwOk )
    {
            QString Nick, Pass;
            int res;
            bool OkSend = true;
            char answ[80];
            Nick = ui->lineEdit_3->text();
            Pass = ui->lineEdit_7->text();
            string buf = "#type/log#o/registration#l/" + Nick.toStdString() + "#p/" + Pass.toStdString();
            res = send(socketSender,buf.c_str(), 80, 0);
            if( res < 0 )
            {
                OkSend = false;
            }

            sleep(1);


            res = recv(socketSender, answ, 80, 0);
            QString qAnsw = QString::fromAscii(answ);
            if(qAnsw == "*good registration")
            {
                QMessageBox::information(this,"Congratulation!","You have registered successfully!");
                ui->tabWidget->setCurrentIndex(0);

            }
            else
            {
                QMessageBox::information(this,"Sorry!","Registrations is failed,because this nick-name already used!Restart you programm and try again!");
                //this->close();
            }

     }
}
void MainWindow::NewServerAddress()
{
    QString qip, qport;
    struct in_addr addrptr;
    qip = ui->lineEdit->text();
    qport = ui->lineEdit_2->text();
    char const *cip;
    cip = qPrintable(qip);
    int res= inet_aton(cip, (struct in_addr*) &addrptr);
    if(res ==1)
    {

            int cport = qport.toInt();
            globalPort = htons(cport);
            globalIP = addrptr.s_addr;
             QMessageBox::information(this,"Message","Successfull");
            ui->lineEdit->setText("");
             ui->lineEdit_2->setText("");
     }
     else
     {
            QMessageBox::information(this,"ERROR","Erorr translate port and ip. Check ip or port");
     }
}


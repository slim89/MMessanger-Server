#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "recvthread.h"
#include <QPointer>
#include "chatwindow.h"
#include "mainwindow.h"
//#include <QtGui/QApplication>
#include "message.h"
extern QPointer<chatWindow> newWindow[10];
extern QString ourNick;
extern QString globalbuff [2][50];
int oo=0;

RecvThread::RecvThread(QObject *parent,
                       QListWidget *list,
                       int recvSocket,
                       chatWindow *win ) :
                           QThread()
                       {
    ourWin = win;
    socketSender = recvSocket;
    listOfContact = list;

}

void RecvThread::run()
{
    int res;
    char from[80];
   // fcntl(socketSender, F_SETFL, O_NONBLOCK);

     while(1)
     {
            fd_set readset;
            FD_SET(socketSender, &readset);
            select(socketSender+1, &readset, NULL, NULL, NULL);
            if(FD_ISSET(socketSender, &readset))
            {
                    bool messageRecvOk = false;
                    cout<<"до"<<endl;
                    int i=0;
                    res = recv(socketSender,from,80,MSG_PEEK);
                    cout<<res<<endl;
                    while (from[i]!='\0')
                        i++;
                    cout<<i<<endl;
                    recv(socketSender,from,i+1,NULL);
                    cout<<from[18]<<endl;
                    cout<<"после"<<endl;
                    string mess = from;
                    Message* m = new Message(mess);
                    m->Parse();
                    QString msg = QString::fromStdString(m->GetPart("o"));
                    QString msg_nick= QString::fromStdString(m->GetPart("s"));
                    QString msgg= QString::fromStdString(m->GetPart("m"));
                    if("connect" == msg)
                    {

                         cout<<"Connect"<<msg_nick.toStdString()<<endl;
                         if (ourNick!=msg_nick)
                         {listOfContact->addItem(msg_nick);}
                         continue;

                     }
                     if("disconnect" == msg)
                     {
                         for( int i = 0; i < 10; i++)
                          {
                             if(newWindow[i] != NULL )
                              {
                                 QString winTit;
                                 winTit = newWindow[i]->windowTitle();

                                   if( msg_nick ==  winTit )
                                    {
                                      newWindow[i]->deleteLater();
                                      newWindow[i]= NULL;
                                      break;
                                    }
                                }
                            }
                         listOfContact->setCurrentItem(listOfContact->findItems(msg_nick,0).first());
                         listOfContact->takeItem(listOfContact->currentRow());
                         listOfContact->update();


                        }
                        else
                         {
                                 messageRecvOk = false;
                                 cout<<mess<<endl;

                                 for( int i = 0; i < 10; i++)
                                 {
                                    if(newWindow[i] != NULL )
                                    {
                                            QString winTit;
                                            winTit = newWindow[i]->windowTitle();
                                            cout<<"WinTit"<< winTit.toStdString()<<endl;
                                            if( msg_nick ==  winTit )
                                            {
                                                newWindow[i]->addMessage(msg_nick,msgg);
                                                messageRecvOk = true;
                                                break;
                                            }
                                      }
                                  }
                        }


                        if(messageRecvOk == false && "disconnect" != msg)
                         {
                                 int j = 0;
                             listOfContact->setCurrentItem(listOfContact->findItems(msg_nick,0).first());
                             listOfContact->currentItem()->setTextColor(Qt::red);
                             listOfContact->currentItem()->setSelected(0);
                             for(j = 0; j< 50; j++)
                             {
                                 if(globalbuff[0][j] == "")
                                 {
                                     globalbuff [0][j] = msg_nick;
                                     globalbuff [1][j]= msgg;
                                      break;
                                }
                             }

                     }
                }

        }

}

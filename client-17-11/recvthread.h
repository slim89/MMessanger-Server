#ifndef RECVTHREAD_H
#define RECVTHREAD_H

#include <QThread>
#include <QTextBrowser>
#include <QListWidget>
#include <QPointer>
#include "chatwindow.h"
#include "mainwindow.h"

class RecvThread : public QThread
{
    Q_OBJECT
public:
    explicit RecvThread(QObject *parent,
                        QListWidget *list,
                        int recvSocket,
                        chatWindow *win
                       );

    chatWindow* ourWin;
    QListWidget*  listOfContact;
    int socketSender;
    void run();
signals:

public slots:

};

#endif // RECVTHREAD_H

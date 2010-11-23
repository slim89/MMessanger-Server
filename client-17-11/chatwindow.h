#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QMessageBox>


namespace Ui {
    class chatWindow;
}

class chatWindow: public QMainWindow
{
    Q_OBJECT

public:
    explicit chatWindow(QWidget *parent = 0);
    ~chatWindow();
    void addMessage(QString from,QString msg);
    void closeEvent(QCloseEvent *event);

     Ui::chatWindow *ui;
private:
private slots:
     void sendMessage();
};

#endif // chatWindow

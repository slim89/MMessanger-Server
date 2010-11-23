#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include <QMessageBox>
#include <string>
using namespace std;

class RecvThread;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Conected();
    void SetColorNick();
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
private slots:
    void tryConnect();
    void changeMessageDelivered();
    void closeApplication();
    void closeAndSend();
    void NewWindow();
    void NewAccount();

public slots:
    void NewAccountTab(QString);
    void NewServerAddress();
};

#endif // MAINWINDOW_H

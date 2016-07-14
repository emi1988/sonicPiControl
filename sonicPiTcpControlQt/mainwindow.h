#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QtNetwork>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpServer *tcpServer;
    QTcpSocket *socket;
    QTimer *timer;
    QByteArray m_sendBuffer;

    QNetworkSession *networkSession;

    int m_testCounter;

 QTcpSocket *clientConnection;
 //int m_connectionCounter;
    void sendMessage(QString message);

    void waitForConnection();

private slots:
    void openConnection();
    void disconnected();
    void timerReady();


    void on_pushButton_clicked();
    void on_horizontalSlider_valueChanged(int value);
};

#endif // MAINWINDOW_H

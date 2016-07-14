#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTcpSocket>
#include <stdlib.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), tcpServer(0), networkSession(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_testCounter = 0;

    //m_connectionCounter = 0;
    m_sendBuffer.append("Hello\n");


    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::LocalHost, 2016)) {
        qDebug() <<"Unable to start the server: " <<tcpServer->errorString();
        close();
        return;
    }
    qDebug() << "wait for incomming connection";
    connect(tcpServer, &QTcpServer::newConnection, this, &MainWindow::openConnection);
   // waitForConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::timerReady()
{

    if(!m_sendBuffer.isEmpty())
    {
        qDebug() << "message send:" << m_sendBuffer;

        clientConnection->write(m_sendBuffer);
       // currentConnection->write(m_sendBuffer);
        m_sendBuffer.clear();
    }
    else
    {
        QByteArray block;
        //block.append(QString::number(-1));
        block.append(" ");
        //block.append("\n");
        //currentConnection->write(block);
        clientConnection->write(block);

        //m_testCounter++;

        qDebug() << "message send:" << block;

    }

}



void MainWindow::openConnection()
{
    qDebug() << "connection established";

    clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected, clientConnection, &QObject::deleteLater);


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerReady()));
    timer->start(300);

}

void MainWindow::disconnected()
{
    timer->stop();
}



void MainWindow::sendMessage(QString message)
{
//    QByteArray block;
//    //QDataStream out(&block, QIODevice::WriteOnly);
//    //out.setVersion(QDataStream::Qt_4_0);

//    block.append(message);
//    block.append("\n");
    m_sendBuffer.append(";");
    m_sendBuffer.append(message);
    m_sendBuffer.append(";");
    //m_sendBuffer.append("\n");

//    try
//    {
//        clientConnection->write(block);
//    }
//    catch(...)
//    {4

//        qDebug() << "send problem";
//    }

    // clientConnection->disconnectFromHost();


   // QThread::sleep(200);
}


void MainWindow::on_pushButton_clicked()
{

   QString messageToSend = ui->lineEditInput->text();

   sendMessage(messageToSend);

}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    sendMessage(QString::number(value));

    qDebug() << "slider value changed: " << value;
}

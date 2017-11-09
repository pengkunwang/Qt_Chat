#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>
#include <QtGui>
#include<QMessageBox>
#include<QScrollBar>
#include<QFileDialog>
#include<QColorDialog>
#include "tcpclient.h"
#include "tcpserver.h"
#include <QEvent>
namespace Ui {
    class Widget;
}

enum MessageType{Message,NewParticipant,ParticipantLeft,FileName,Refuse};
//枚举变量标志信息的类型，分别为消息，新用户加入，和用户退出
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QString getUserName();  //获取用户名
    QString getMessage();   //获取消息

protected:
    void sendMessage(MessageType type,QString serverAddress="");    //发送消息
    void newParticipant(QString userName,QString localHostName,QString ipAddress);  //新用户加入
    void participantLeft(QString userName,QString localHostName,QString time);  //用户离开
    void closeEvent(QCloseEvent *);
    void hasPendingFile(QString userName,QString serverAddress,
                        QString clientAddress,QString fileName);    //接收文件

     bool eventFilter(QObject *target, QEvent *event);//事件过滤器
private:
    Ui::Widget *ui;
    QUdpSocket *udpSocket;
    qint16 port;
    QString fileName;
    TcpServer *server;  //tcp服务器连接对象

    QString getIP();

    bool saveFile(const QString& fileName);//保存聊天记录
private slots:

    void on_clear_clicked();
    void on_save_clicked();


    void on_close_clicked();
    void on_sendfile_clicked();
    void on_send_clicked();
    void processPendingDatagrams();
    void sentFileName(QString);

};



#endif // WIDGET_H

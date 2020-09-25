#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

enum emResultState
{
    Idle = 0,               // 空闲状态
    UpdateSuccess = 1,      // 升级成功
    RestoreSuccess = 2,     // 恢复成功
    UpdateImageError = 3,	// 升级镜像错误
    RestoreImageError = 4,  // 备份镜像错误
    Updating = 5,           // 升级中
};

typedef struct tagMSG
{
    long type;
    int data;
}MSG;

class MyServer : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.tcp.server")
public:
    explicit MyServer(QObject *parent = nullptr);

signals:
    void updateSuccess();

public slots:
        void onAcceptConnection();
        void onDisconnected();

private:

    QTcpServer *m_pServer;
    QTcpSocket *m_pSocket;

    int m_msgid;
};

#endif // MYSERVER_H

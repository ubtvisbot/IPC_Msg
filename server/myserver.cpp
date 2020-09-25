#include "myserver.h"
#include <QDebug>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusMessage>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
//#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <QProcess>

const static quint16 kPort = 57822;
const static int kKeyValue = 456701;
QProcess prcs;

MyServer::MyServer(QObject *parent) : QObject(parent)
{
    qDebug() << "init ...";
    m_pServer = new QTcpServer();
    m_pServer->listen(QHostAddress::Any, kPort);
    connect(m_pServer, SIGNAL(newConnection()), this, SLOT(onAcceptConnection()));

    QDBusConnection::sessionBus().unregisterService("com.tcp.server");
    QDBusConnection::sessionBus().registerService("com.tcp.server");
    QDBusConnection::sessionBus().registerObject("/com/tcpserver", this,
                                                 QDBusConnection::ExportAllSlots | QDBusConnection::ExportAllSignals);

    key_t key = ftok("/tmp/ota_key", 6);
    qDebug() << key;
    qDebug() << "ftok key: " << key;
    if (key < 0)
    {
        key = (key_t)kKeyValue;
        qDebug() << "ftok key: " << key;
    }
    m_msgid = msgget(key, IPC_CREAT | 0666); // O_WRONLY IPC_CREAT
    if (m_msgid < 0)
    {
        qDebug() << "msgget error";
    }
    qDebug() << "m_msgid" << m_msgid;
}

void MyServer::onAcceptConnection()
{
    qDebug() << "enter " << __func__;

//    m_pSocket = m_pServer->nextPendingConnection();

//    QString ip =  m_pSocket->peerAddress().toString();
//    quint16 port = m_pSocket->peerPort();
//    QString log = QString("[%1:%2] connect sucess").arg(ip).arg(port);

////    connect(m_pSocket, SIGNAL(readyRead()), this, SLOT(onReadFromClient()));
//    connect(m_pSocket, &QTcpSocket::disconnected, this, &MyServer::onDisconnected);


//    QDBusMessage updateMsg = QDBusMessage::createSignal("/com/tcpserver", "com.tcp.server", "updateSuccess");
//    QDBusConnection::sessionBus().send(updateMsg);

    int n = 5;
    while(n-- > 1)
    {

        MSG m;
        m.data = n;
        m.type = 1;

        int id = msgsnd(m_msgid, &m,  sizeof(m) - sizeof(m.type), 0);
        qDebug() << id;
        sleep(1);
    }

//    msgctl(m_msgid, IPC_RMID, NULL);
//    prcs.start("/home/oneai/build-client-unknown-Debug/clt");
//    prcs.waitForStarted(1000);
}

void MyServer::onDisconnected()
{
    qDebug() << "enter " << __func__;
    qDebug() << "Disconnected address " << m_pSocket->peerAddress();
    qDebug() << "Disconnected port" <<m_pSocket->peerPort();

//    prcs.close();
//    prcs.waitForFinished(1000);
}

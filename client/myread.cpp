#include "myread.h"
#include <QDebug>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>


MyRead::MyRead(QObject *parent) : QThread(parent)
{
//    m_w = new MainWindow;
//    m_w->hide();

}

void MyRead::run()
{
    key_t key = ftok("/home/oneai/open", 6);
    qDebug() << key;
    int m_msgid = msgget(key, O_RDONLY);
    if (m_msgid < 0)
    {
        qDebug() << "msgget error";
    }
    qDebug() << m_msgid;

    MSG m;
    m.data = -1;
    long type = 0;

    MainWindow m_w;

    while(1)
    {
        int id = msgrcv(m_msgid, &m, sizeof(m)-sizeof(m.type), type, 0);
        if (id >= 0)
        {
            qDebug() << "mesg: " << m.data;
            qDebug() << "mesg: " << m.type;

            if (m.data % 2 == 0)
            {
                m_w.show();
            }
            else
            {
                m_w.hide();
            }
        }
        else
        {
            qDebug() << "!!!!!!!!!!!!!!!!!";
        }
        sleep(2);
    }
    msgctl(m_msgid, IPC_RMID, NULL);
}

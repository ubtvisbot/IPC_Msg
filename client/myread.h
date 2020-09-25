#ifndef MYREAD_H
#define MYREAD_H

#include <QObject>
#include <QThread>
#include "mainwindow.h"

typedef struct tagMSG
{
    long type;
    int data;
}MSG;

class MyRead : public QThread
{
    Q_OBJECT
public:
    explicit MyRead(QObject *parent = nullptr);

signals:

public slots:

protected:
    void run();

private:
//    MainWindow m_w;
};

#endif // MYREAD_H

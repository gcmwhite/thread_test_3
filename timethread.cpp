#include "timethread.h"
#include <QDebug>

TimeThread::TimeThread(QThread *parent)
    :QThread(parent)
{
    isPause = false;
}

void TimeThread::run()
{
    qDebug() << "子线程启动：" << QThread::currentThread();
    int count = 0;
    isStop = false;
    while (!isStop)
    {
        emit countSignal(count++);
        QThread::msleep(200);
        mutex.lock();
        mutex.unlock();
    }
    qDebug() << "子线程：" << QThread::currentThread() << "退出！";
}

void TimeThread::pause()
{
    if (!isRunning())
    {
        qDebug() << "线程未启动！";
        return ;
    }
    qDebug() << "线程：" << QThread::currentThread() << "暂停";
    isPause = !isPause;
    if (isPause)
    {
        mutex.lock();
    } else {
        mutex.unlock();
    }
}

void TimeThread::close()
{
    if (!isRunning())
    {
        qDebug() << "线程未启动！";
        return ;
    }
    isStop = true;
    if (isPause)
        mutex.unlock();
    isPause = false;
    wait();
}

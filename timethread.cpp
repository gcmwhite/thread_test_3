#include "timethread.h"
#include <QDebug>
#include <QMutexLocker>

TimeThread::TimeThread(QThread *parent)
    :QThread(parent)
{
    QMutexLocker lock(&mutex2);
    isPause = false;
}

void TimeThread::run()
{
    qDebug() << "子线程启动：" << QThread::currentThread();
    int count = 0;
    mutex2.lock();
    isStop = false;
    mutex2.unlock();
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
    QMutexLocker lock(&mutex2);
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
    QMutexLocker lock(&mutex2);
    isStop = true;
    if (isPause)
        mutex.unlock();
    isPause = false;
    wait();
}

#ifndef TIMETHREAD_H
#define TIMETHREAD_H

#include <QThread>
#include <QMutex>


class TimeThread : public QThread
{
    Q_OBJECT
public:
    explicit TimeThread(QThread *parent = nullptr);
    void run();
    void pause();
    void close();

private:
    bool isStop;
    bool isPause;
    QMutex mutex;

private:


signals:
    void countSignal(int);

};

#endif // TIMETHREAD_H

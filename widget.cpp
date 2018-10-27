#include "widget.h"
#include "ui_widget.h"
#include "timethread.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    qDebug() << "主线程启动：" << QThread::currentThread();

    ui->setupUi(this);

    TimeThread *t1 = new TimeThread;
    TimeThread *t2 = new TimeThread;

    connect(ui->startBtn_1,&QPushButton::clicked,this,[=](){

        t1->start();
    });
    connect(ui->startBtn_2,&QPushButton::clicked,this,[=](){

        t2->start();
    });

    connect(t1,&TimeThread::countSignal,this,[=](int count){
        ui->lcdNumber_1->display(count);
    });

    connect(t2,&TimeThread::countSignal,this,[=](int count){
        ui->lcdNumber_2->display(count);
    });

    connect(ui->pauseBtn_1,&QPushButton::clicked,this,[=](){
        t1->pause();
    });

    connect(ui->pauseBtn_2,&QPushButton::clicked,this,[=](){
        t2->pause();
    });

    connect(ui->stopBtn_1,&QPushButton::clicked,this,[=](){
        t1->close();
        ui->lcdNumber_1->display(0);
//        t1->wait();
//        t1->deleteLater();
    });


    connect(ui->stopBtn_2,&QPushButton::clicked,this,[=](){
        t2->close();
        ui->lcdNumber_2->display(0);
//        t2->wait();
//        t2->deleteLater();
    });

    connect(this,&Widget::destroyed,this,[=](){
        qDebug() << "正在进入退出程序！";
        if (t1->isRunning())
        {
            t1->close();
            t1->wait();
            t1->deleteLater();
        }
        if (t2->isRunning())
        {
            t2->close();
            t2->wait();
            t2->deleteLater();
        }
        qDebug() << "程序已完全退出！";
    });

}

Widget::~Widget()
{
    delete ui;
}

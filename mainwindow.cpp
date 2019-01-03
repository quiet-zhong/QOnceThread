#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << this->parent();

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(slotMainShowInfo()));
    m_timer.setInterval(1000 * 1); //所有状态信息的轮询间隔时间
    m_timer.start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotMainShowInfo()
{
    qDebug() << "Hello world!" << XThread::count();
}


void MainWindow::on_pushButton_clicked()
{
    auto func1 = [&]()
    {
        int times = 30;
        while(times--)
        {
            qDebug() << QString("thread1") << times;
            QThread::msleep(100);
        }
    };

    auto func2 = [&](int &ret)
    {
        int times = 40;
        while(times--)
        {
            qDebug() << QString("thread2") << times;
            QThread::msleep(100);
        }
        ret = 999999;//线程返回结果
    };

    auto func3 = [&](QString &retStr)
    {
        int times = 50;
        while(times--)
        {
            qDebug() << QString("thread3") << times;
            QThread::msleep(100);
        }
        retStr = "nice"; //线程返回结果
    };



    //! example 1
    XThread *thread1 = new XThread;
    thread1->setCallback(func1);
    thread1->start();

//    XThread *thread1 = new XThread(func1);
//    thread1->start();

    //! example 2
    XThread *thread2 = new XThread(func2);
    connect(thread2,SIGNAL(signalFinishResult(int)),this,SLOT(slotDebug(int)));
    thread2->start();

    //! example 3
    XThread *thread3 = new XThread(func3);
    connect(thread3,SIGNAL(signalFinishResult(QString)),this,SLOT(slotDebug(QString)));
    thread3->start();
}

void MainWindow::slotDebug(QString str)
{
    QMessageBox::information(this,"tips",str);
    qDebug() << str;
}

void MainWindow::slotDebug(int val)
{
    qDebug() << val;
    QMessageBox::information(this,"tips", QString::number(val) );
}


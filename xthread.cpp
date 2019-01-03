#include "xthread.h"
#include <QApplication>
#include <QDebug>

int XThread::m_count = 0;

void XThread::initBuild()
{
    m_count++;

    m_funcVoid = nullptr;
    m_funcInt = nullptr;
    m_funcString = nullptr;

    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));

    createTimer();
}

void XThread::createTimer()
{
    //    m_timer = NULL;
    //    m_timerInterval = 1000;
    //    m_timerTimeoutCounter = 0;

    //    m_timer = new QTimer();//不能指定父对象
    //    m_timer->moveToThread(this);
    //    m_timer->setInterval(m_timerInterval);
    //    connect(this, SIGNAL(started()), m_timer, SLOT(start()));
    //    connect(m_timer,SIGNAL(timeout()),this,SLOT(slotTimerTimeout()),Qt::DirectConnection);
}


XThread::XThread(QObject *parent)
    : QThread(parent)
{
    initBuild();
}

XThread::XThread(XTHREAD_VOID_FUNC func, QObject *parent)
    : QThread(parent)
{
    initBuild();
    m_funcVoid = func;
}

XThread::XThread(XTHREAD_INT_FUNC func, QObject *parent)
    : QThread(parent)
{
    initBuild();
    m_funcInt = func;
}

XThread::XThread(XTHREAD_STRING_FUNC func, QObject *parent)
    : QThread(parent)
{
    initBuild();
    m_funcString = func;
}


XThread::~XThread()
{
    m_count--;
}

void XThread::run()
{
    runCallbackFunc();
//  exec(); //如果创建了timer，必须运行exec才能生效
}

int XThread::count()
{
    return m_count;
}

void XThread::setCallback(XTHREAD_VOID_FUNC func)
{
    m_funcVoid = func;
}

void XThread::setCallback(XTHREAD_INT_FUNC func)
{
    m_funcInt = func;
}

void XThread::setCallback(XTHREAD_STRING_FUNC func)
{
    m_funcString = func;
}

void XThread::runCallbackFunc()
{
    if (m_funcVoid != nullptr)
    {
        m_funcVoid();
    }
    else if (m_funcInt != nullptr)
    {
        int ret = -1;
        m_funcInt( ret );
        emit signalFinishResult(ret);
    }
    else if (m_funcString != nullptr)
    {
        QString str = "";
        m_funcString( str );
        emit signalFinishResult(str);
    }
}

//void XThread::setTimerInterval(int msec)
//{
//    m_timerInterval = msec;
//}

//int XThread::timerInterval() const
//{
//    return m_timerInterval;
//}

//void XThread::slotTimerTimeout()
//{
//    m_timerTimeoutCounter++;
//    emit signalTimerTimeout(m_timerTimeoutCounter);
//}

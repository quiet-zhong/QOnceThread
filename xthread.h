#ifndef XTHREAD_H
#define XTHREAD_H

#include <QThread>
#include <QTimer>
#include <functional>


class XThread : public QThread
{
    Q_OBJECT

    //! 定义回调函数类型
    typedef std::function<void(void)> XTHREAD_VOID_FUNC;
    typedef std::function<void(int &)> XTHREAD_INT_FUNC;
    typedef std::function<void(QString &)> XTHREAD_STRING_FUNC;

public:
    XThread(QObject *parent = NULL);

    XThread(XTHREAD_VOID_FUNC func, QObject *parent = NULL);
    XThread(XTHREAD_INT_FUNC func, QObject *parent = NULL);
    XThread(XTHREAD_STRING_FUNC func, QObject *parent = NULL);

    ~XThread();

    //类实例化个数
    static int count();

signals:
    //线程结束发送运行结果信号
    void signalFinishResult(int);
    void signalFinishResult(QString);

    //线程内部计时器超时发送信号,参数为第几次产生的超时信号
//    void signalTimerTimeout(int);

public:
    //线程执行回调函数，参数为线程运行结束返回信号类型
    void setCallback(XTHREAD_VOID_FUNC  func);
    void setCallback(XTHREAD_INT_FUNC   func);
    void setCallback(XTHREAD_STRING_FUNC func);

//    int timerInterval() const;
//    void setTimerInterval(int msec);

protected:
    virtual void run();

//private slots:
//    void slotTimerTimeout();

private:
    void initBuild();
    void runCallbackFunc();

    static int m_count;

    XTHREAD_VOID_FUNC   m_funcVoid;
    XTHREAD_INT_FUNC    m_funcInt;
    XTHREAD_STRING_FUNC m_funcString;

//    QTimer *m_timer;
//    int m_timerInterval;
//    int m_timerTimeoutCounter;

    void createTimer();
};

#endif // XTHREAD_H

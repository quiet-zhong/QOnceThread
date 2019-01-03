#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "xthread.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slotMainShowInfo();

    void on_pushButton_clicked();

    void slotDebug(QString str);
    void slotDebug(int val);

private:
    Ui::MainWindow *ui;

    QTimer m_timer;

};

#endif // MAINWINDOW_H

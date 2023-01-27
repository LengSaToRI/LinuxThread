#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QMutex>
extern QStringList info;
extern int infotimes;
extern QString tip[200];

class Customer : public QThread
{
public:
    Customer(int current, int need)
    {
        m_current = current;
        m_need = need;
    }
    void addMoney(int m);
    int backMoney();
    int current();
    int need();

protected:
    int m_need;
    volatile int m_current;
    QMutex m_mutex;
    void run();
    MainWindow * GUI;
private:
    volatile bool condition=true;
};
#endif // CUSTOMER_H

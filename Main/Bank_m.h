#ifndef BANK_M_H
#define BANK_M_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Customer.h>
#include <QList>

class Bank : public QThread
{
protected:
    QList<Customer*> m_list;
    int m_total;
    void run();
    MainWindow * GUI;
public:
    Bank(int total)
    {
        m_total = total;
    }
    void addCustomer(Customer *customer);
};

#endif

#include <Customer.h>
QStringList info;
int infotimes=0;
QString tip[200];

void Customer::run()
{
    tip[infotimes]="线程[";
    tip[infotimes]+=objectName();
    tip[infotimes]+="]";
    tip[infotimes]+="开始运行";
    infotimes++;

    do
    {
        m_mutex.lock();
        condition = (m_current < m_need);
        m_mutex.unlock();
        msleep(10);
    }
    while(condition);
    condition = false;
    tip[infotimes]="线程[";
    tip[infotimes]+=objectName();
    tip[infotimes]+="]";
    tip[infotimes]+="线程完成资源分配";
    infotimes++;
}

int Customer::current()
{
    int ret = 0;
    m_mutex.lock();
    ret = m_current;
    m_mutex.unlock();
    return ret;
}

int Customer::need()
{
    return m_need;
}

int Customer::backMoney()
{
    int ret = 0;
    m_mutex.lock();
    ret = m_current;
    m_current = 0;
    m_mutex.unlock();
    return ret;
}

void Customer::addMoney(int m)
{
    m_mutex.lock();
    m_current += m;
    m_mutex.unlock();
}


#include <Bank_m.h>
#include "mainwindow.h"

void Bank::run()
{
    int index = -1;
    tip[infotimes]="成功创建系统【";
    tip[infotimes]+=objectName();
    tip[infotimes]+="】";
    tip[infotimes]+="现有资源";
    tip[infotimes]+=QString::number(m_total);
    tip[infotimes]+="点,开始运行银行家算法";
    infotimes++;
    do
    {
        index = -1;
        for(int i=0; i<m_list.count(); i++)
        {
            if( m_list[i]->current() == m_list[i]->need() )
            {  
                tip[infotimes]="系统【";
                tip[infotimes]+=objectName();
                tip[infotimes]+="】";
                tip[infotimes]+="释放了";
                tip[infotimes]+="线程[";
                tip[infotimes]+=m_list[i]->objectName();
                tip[infotimes]+="]";
                tip[infotimes]+="从而回收了";
                tip[infotimes]+= QString::number(m_list[i]->need());
                tip[infotimes]+= "点资源";
                infotimes++;
                m_total += m_list[i]->backMoney();
            }
        }
        tip[infotimes]="系统【";
        tip[infotimes]+=objectName();
        tip[infotimes]+="】";
        tip[infotimes]+="现有资源";
        tip[infotimes]+=QString::number(m_total);
        tip[infotimes]+="点";
        infotimes++;
        int toGet = 0x00FFFFFF;
        for(int i=0; i<m_list.count(); i++)
        {
            if( m_list[i]->isRunning() )
            {
                int tmp = m_list[i]->need() - m_list[i]->current();
                if( toGet > tmp )
                {
                    index = i;
                    toGet = tmp;
                }
            }
        }
        if( index >=0 )
        {
            if( toGet <= m_total )
            {
                tip[infotimes]="系统【";
                tip[infotimes]+=objectName();
                tip[infotimes]+="】";
                tip[infotimes]+="分配资源给线程:";
                tip[infotimes]+=m_list[index]->objectName();
                infotimes++;
                m_total--;
                m_list[index]->addMoney(1);
            }
            else
            {
                tip[infotimes]="系统【";
                tip[infotimes]+=objectName();
                tip[infotimes]+="】";
                tip[infotimes]+="由于其需求资源大于实际资源便终止了线程:";
                tip[infotimes]+="线程[";
                tip[infotimes]+=m_list[index]->objectName();
                tip[infotimes]+="]";
                infotimes++;
                m_total += m_list[index]->backMoney();
                m_list[index]->terminate();
            }
        }
        sleep(1);
    }
    while( index >= 0 );
    tip[infotimes]="系统【";
    tip[infotimes]+=objectName();
    tip[infotimes]+="】";
    tip[infotimes]+="结束分配后存有资源";
    tip[infotimes]+=QString::number(m_total);
    tip[infotimes]+="点";
    infotimes++;
}

void Bank::addCustomer(Customer *customer)
{
    m_list.append(customer);
}

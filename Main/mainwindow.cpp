#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Customer.h>
#include <Bank_m.h>
#include <R_W.h>
#include <unistd.h>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("进程同步与死锁");
    ui->frame_3->hide();
    ui->radio_r->setChecked(true);
}

static Customer *p[30];
static int thread_num=0;

static Bank *bank[10];
static int bank_num=0;

static struct data* d[10];
static int r_w_num=0,id[10];
static QString role[10];

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cadd_btn_clicked()
{
    if(ui->src_have->text()==NULL||ui->src_need->text()==NULL||ui->src_name->text()==NULL)
    {
        QMessageBox::warning(this, tr("Warning"),
                             tr("线程缺少参数"),
                             QMessageBox::Yes);
    }
    else
    {
        int src_have,src_need;
        src_have=ui->src_have->text().toInt();
        src_need=ui->src_need->text().toInt();
        p[thread_num]=new Customer(src_have, src_need);
        p[thread_num]->setObjectName(ui->src_name->text());
        QString tip="";
        tip="加入了线程";
        tip+="[";
        tip+=ui->src_name->text();
        tip+="]";
        tip+="现有资源";
        tip+=ui->src_have->text();
        tip+="点,";
        tip+="总共请求资源";
        tip+=ui->src_need->text();
        tip+="点";
        ui->listWidget->addItem(tip);
        thread_num++;
        ui->src_have->clear();
        ui->src_need->clear();
        ui->src_name->clear();
    }

}

void MainWindow::on_os_btn_clicked()
{
    if(ui->os_name->text()==NULL||ui->src_os->text()==NULL)
    {
        QMessageBox::warning(this, tr("Warning"),
                             tr("操作系统缺少参数"),
                             QMessageBox::Yes);
    }
    else
    {
        bank[bank_num]=new Bank(ui->src_os->text().toInt());
        bank[bank_num]->setObjectName(ui->os_name->text());

        for (int i=0;i<thread_num;i++)
        {
            bank[bank_num]->addCustomer(p[i]);
        }

        for (int i=0;i<thread_num;i++)
        {
            p[i]->start();
        }
        usleep(100);
        bank[bank_num]->start();

        for (int i=0;i<thread_num;i++)
        {
            p[i]->wait();
        }
        bank[bank_num]->wait();

        for (int i=0;i<infotimes;i++)
        {
            ui->listWidget->addItem(tip[i]);
            ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
            sleep(1);
            qApp->processEvents();
        }
        bank_num++;
    }
}

void MainWindow::on_clean_btn_clicked()
{
    ui->listWidget->clear();
    for(int i=0;i<thread_num;i++)
    {
        delete p[i];
        p[i]=NULL;
    }
    for(int i=0;i<bank_num;i++)
    {
        delete bank[i];
        bank[i]=NULL;
    }

    thread_num=0;
    bank_num=0;

    for(int i=0;i<infotimes;i++)
    {
        tip[i].clear();
    }
    infotimes=0;
    ui->src_os->clear();
    ui->os_name->clear();
    ui->src_have->clear();
    ui->src_need->clear();
    ui->ed_id->clear();
    ui->ed_optime->clear();
    ui->ed_lastTime->clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    exit(0);
}

void MainWindow::on_action_triggered()
{
    ui->show->setText("读写者算法");
    ui->frame->hide();
    ui->frame_2->hide();
    ui->frame_3->show();
}

void MainWindow::on_action_2_triggered()
{
    ui->show->setText("银行家算法");
    ui->frame->show();
    ui->frame_2->show();
    ui->frame_3->hide();
}

void MainWindow::on_R_W_btn_clicked()
{
    id[r_w_num]=ui->ed_id->text().toInt();
    if (ui->radio_r->isChecked())
    {
        role[r_w_num]='R';
    }
    else
    {
        role[r_w_num]='W';
    }
    int opTime=ui->ed_optime->text().toInt();//operating time
    int lastTime=ui->ed_lastTime->text().toInt();//run time
    d[r_w_num]=(struct data*)malloc(sizeof(struct data));
    d[r_w_num]->id = id[r_w_num];
    d[r_w_num]->opTime=opTime;
    d[r_w_num]->lastTime=lastTime;
    QString tip;
    tip="创建线程[";
    tip+=QString::number(id[r_w_num]);
    tip+="]";
    tip+="类型:";
    tip+=role[r_w_num];
    tip+="opTime:";
    tip+=QString::number(opTime);
    tip+=" ";
    tip+="lastTime:";
    tip+=QString::number(lastTime);
    ui->listWidget->addItem(tip);
    r_w_num++;
    ui->ed_id->clear();
    ui->ed_optime->clear();
    ui->ed_lastTime->clear();
}

void MainWindow::on_R_W_RUN_clicked()
{
    pthread_t tid; // the thread identifier
    pthread_attr_t attr; //set of thread attributes

    /* get the default attributes */
    pthread_attr_init(&attr);

    //initial the semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    readCount=0;
    for (int i=0;i<r_w_num;i++)
    {
        if(role[i]=='R')
        {
            tip[infotimes]="启动线程[";
            tip[infotimes]+=QString::number(id[i]);
            tip[infotimes]+="]";
            tip[infotimes]+="类型：读线程Read";
            infotimes++;
            pthread_create(&tid,&attr,Reader,d[i]);
        }
        else if(role[i]=='W')
        {
            tip[infotimes]="启动线程[";
            tip[infotimes]+=QString::number(id[i]);
            tip[infotimes]+="]";
            tip[infotimes]+="类型：写线程Write";
            infotimes++;
            pthread_create(&tid,&attr,Writer,d[i]);
        }
    }
    sleep(3);
    for (int i=0;i<infotimes;i++)
    {
        ui->listWidget->addItem(tip[i]);
        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
        sleep(1);
        qApp->processEvents();
    }
}

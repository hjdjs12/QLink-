#include "timebar.h"
#include "ui_timebar.h"

TimeBar::TimeBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeBar)
{
    ui->setupUi(this);
    timer =new QTimer;
    timer->start(1000);

    static QTime leftTime(0,5,0);
    static int i=300;
    QTime zero(0,0,0);
    ui->label->setText("剩余时间："+leftTime.toString("mm:ss"));
    ui->progressBar->setRange(0,i);
    ui->progressBar->setValue(i);
    connect(timer,&QTimer::timeout,[=](){
        leftTime=leftTime.addSecs(-1);
        ui->label->setText("剩余时间："+leftTime.toString("mm:ss"));
        ui->progressBar->setValue(--i);
        if(leftTime==zero){timer->stop();}
    });

}

TimeBar::~TimeBar()
{
    delete ui;
}

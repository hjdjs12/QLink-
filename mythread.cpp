#include "mythread.h"
#include<QPainter>
#include<QRandomGenerator>
#include<playscene.h>
MyThread::MyThread(QObject *parent) : QObject(parent)
{

}
void MyThread::slotDrawImage(){
    QPixmap a;
    QPainter painter(&a);
    QPixmap pixmap;
    pixmap.load(":/Image/background1.png");
    painter.drawPixmap(0,0,pixmap.width(),pixmap.height(),pixmap);
    int PixmapData[ROW_COUNT][COLUMN_COUNT];
    QVector<int>*Exist=new QVector<int>(ROW_COUNT/2*COLUMN_COUNT,0);
    for(int i=0;i<ROW_COUNT/2;++i){
        for(int j=0;j<COLUMN_COUNT;++j){
            int type=QRandomGenerator::global()->generate()%10+1;
            //先生成前一半
            PixmapData[i][j]=type;
            PixmapData[i+7][j]=type;
        }
    }
    for(int i=0;i<ROW_COUNT;++i){
        for(int j=0;j<COLUMN_COUNT;++j)
        {
             painter.drawPixmap(200+j*IMAGE_WIDHT,200+i*IMAGE_HEIGHT,IMAGE_WIDHT,IMAGE_HEIGHT,
                                        QPixmap(QString(":/Image/%1.png").arg(PixmapData[i][j])));
        }
    }
    emit signalDrawUp(a);
}

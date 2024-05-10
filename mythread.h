#ifndef MYTHREAD_H
#define MYTHREAD_H
#include<QObject>
#include<QThread>
#include<QPixmap>
class MyThread:public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    void slotDrawImage();
signals:
        void signalDrawUp(QPixmap img);
};

#endif // MYTHREAD_H

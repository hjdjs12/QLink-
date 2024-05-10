#ifndef TEST_H
#define TEST_H

#include <QObject>
//#include <QtTest/QtTest>
#include<QTest>
#include"mainwindow.h"
#include<QSignalSpy>
#include<qtestmouse.h>
#include <QWidget>
#include<QMainWindow>
#include"doublescene.h"
#include"startscene.h"


class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr){};
    PlayScene *example1;
    PlayScene *example2;
    PlayScene *example3;
    PlayScene *example4;
    DoubleScene *example5;
    StartScene example6;
    PlayScene * example7;
    PlayScene *example8;
    int **map;
    bool closeFlag;

private Q_SLOTS:
    void initTestCase(){
        closeFlag=false;
        map=new int *[14];
        for(int i=0;i<14;i++){
            map[i]=new int [14];
        }
        ROW_COUNT=14;
        COLUMN_COUNT=14;
    }
    void cleanupTestCase(){}
    void case1(){
        for(int i=0;i<14;i++){
            for(int j=0;j<14;j++){
                map[i][j]=0;
            }
        }
        example1=new PlayScene(300,1,1,0,map);
        example1->timer->stop();
        QVERIFY(example1->checkRemain()==false);
    }
    void case2(){
        QBENCHMARK;
    }
    void case3(){
        map[5][4]=4;
        map[2][7]=4;
        example2=new PlayScene(300,1,1,0,map);
        example2->timer->stop();
        QVERIFY(example2->inTwoLine(5,4,2,7)==true);
        QVERIFY(example2->inOneLine(5,4,2,7)==false);
        QVERIFY(example2->inThreeLine(5,4,2,7)==true);
    }
    void case4(){
        map[5][6]=2;
        map[2][6]=3;
        example3=new PlayScene(300,1,1,0,map);
        example3->timer->stop();
        QVERIFY(example3->inThreeLine(5,4,2,7)==true);
        QVERIFY(example3->inTwoLine(5,4,2,7)==false);
        QVERIFY(example3->inOneLine(5,4,2,7)==false);
    }
    void case5(){
        map[3][6]=2;
        example7=new PlayScene(300,1,1,0,map);
        example7->timer->stop();
        QVERIFY(example2->inTwoLine(5,6,3,6)==true);
        QVERIFY(example2->inOneLine(5,6,3,6)==true);
        QVERIFY(example2->inThreeLine(5,6,3,6)==true);
    }
    void case6(){
        map[4][4]=2;
        map[6][4]=2;
        example8=new PlayScene(300,1,1,0,map);
        example8->timer->stop();
        QVERIFY(example8->inOneLine(5,4,2,7)==false);
        QVERIFY(example8->inTwoLine(5,4,2,7)==false);
        QVERIFY(example8->inThreeLine(5,4,2,7)==false);
    }
    void case7(){
        example4=new PlayScene(300,1,1,0,map);
        example4->timer->stop();
        connect(example4,&PlayScene::scene_Close,[=](){
            closeFlag=true;
        });
        QTest::mouseClick(example4->back, Qt::LeftButton);
        QTest::qWait(500);
        QVERIFY(closeFlag==true);
    }
    void case8(){
        example5=new DoubleScene;
        QTest::keyEvent(QTest::Click,example5, Qt::Key_S, Qt::ControlModifier);
        QTest::keyEvent(QTest::Click,example5, Qt::Key_1, Qt::ControlModifier);
        QVERIFY(example5->boy->x==2);
        QVERIFY(example5->girl->y==COLUMN_COUNT-3);
    }

signals:
};

#endif // TEST_H
//QTEST_MAIN(Test);


//#include "playscene.h"
//#include "ui_playscene.h"
//#include"protagonist1.h"
//#include<QWidget>
//#include<QTimer>
//#include<QEvent>
//#include <QKeyEvent>
//#include <QDebug>
//#include <QPainter>
//#include<QPixmap>
//#include<QPropertyAnimation>
//#include<QRandomGenerator>
//#include<QMainWindow>


//PlayScene::PlayScene(QWidget *parent)
//    : QMainWindow(parent)
//    , ui(new Ui::PlayScene)
//{
//    //设置主mainwindow
//    ui->setupUi(this);
//    this->setFixedSize(1700,1450);
//    timer = new QTimer(this);
//    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
//    timer->start(5);
////    keyflag=0;
////    keypressflag=false;
//    //创建角色
////    boy=new Protagonist1(":/Image/protagonist1.png");
//    boy=new Protagonist1(":/Image/5.png");
//    initial();
//    //设置图层和主widget
//    windows = new QWidget();
//    gridLayout = new QGridLayout;
//    draw2=new Draw;
//    draw=new Draw;


//    for(int i = 0;i < ROW_COUNT;++i){
//        for(int j = 0; j<COLUMN_COUNT;j++){
//            if(i==0||i==ROW_COUNT-1||i==1||i==ROW_COUNT-2||j==0||j==COLUMN_COUNT-1||j==1||j==COLUMN_COUNT-2){map[i][j]=0;}
//            else{map[i][j]=PixmapData[i][j];}
//        }
//    }
//    setCentralWidget(windows);
//    for(int i = 0; i < ROW_COUNT; ++i)
//            for(int j = 0; j < COLUMN_COUNT; ++j) {
//                if(i==0||i==ROW_COUNT-1||j==0||j==COLUMN_COUNT-1){image[i][j]=createImageButton(QString(":/Image/wall.png"),QString(":/Image/wall.png"));}
//                else if(i==1||i==ROW_COUNT-2||j==1||j==COLUMN_COUNT-2){image[i][j]=createImageButton(QString(":/Image/blank.png"),QString(":/Image/blank.png"));}
//                else{
//                    image[i][j] = createImageButton(
//                              QString(":/Image/%1.png").arg(PixmapData[i][j]),
//                              QString(":/Image/%1.png").arg(PixmapData[i][j]+26));
//                }
//                gridLayout->addWidget(image[i][j], i, j, Qt::AlignCenter);


//    }
//    windows->resize(1700,1450);
//    gridLayout->addWidget(boy,boy->x,boy->y);
//    gridLayout->setAlignment(Qt::AlignCenter); // 居中布局



//    gridLayout->addWidget(draw,0,0,13,13);
//    gridLayout->setContentsMargins(0,0,0,0);
//    gridLayout->setSpacing(10);
//    gridLayout->setMargin(0);
//    windows->setLayout(gridLayout);
////    windows->setStyleSheet("background-image: url(:/Image/background1.png);");

//    //将激活信号和处理函数相连
//    connect(this,&PlayScene::activiate,this,&PlayScene::judge);
//    //设置画笔参数
//    linePen.setColor(Qt::red);
//    linePen.setWidth(10);
//    //初始不画
////    oneFlag=false;
////    twoFlag=false;
////    threeFlag=false;
//}



//ImageButton *PlayScene::createImageButton(const QString &str1,
//                                           const QString &str2)
//{
//    // 加载两张图片
//    QPixmap img1, img2;
//    img1.load(str1);
//    img2.load(str2);
//    ImageButton *button = new ImageButton;
//    // 设置大小和图片
////    button->setGeometry(0, 0, 0, 0);
//    button->setFixedSize(80, 80);
//    button->setButtonIcon(QIcon(img1), QIcon(img2));
//    button->setIconSize(QSize(button->width(),button->height()));
//    button->setStyleSheet("border:1px rgba(237, 241, 255, 100);"
//                          "border-radius:8px;"
//                          "padding:0px;"
//                          "border-style: outset;");
//    return button;
//}

//PlayScene::~PlayScene()
//{
//    delete ui;
//}
////实现人物移动及激活信号
//void PlayScene::keyPressEvent(QKeyEvent *event){
//    switch(event->key())
//    {
//    case Qt::Key_W:
////        keypressflag = true;
////        keyflag = 1;
//        if(boy->x==1){break;}
//        if(map[boy->x-1][boy->y]>0){
//            emit activiate(boy->x-1,boy->y);
//        }
//        else{
//            boy->x=boy->x-1;
//            changePlace();
//        }
//        return;

//    case Qt::Key_S:
////        keypressflag = true;
////        keyflag = 2;
//        if(boy->x==ROW_COUNT-2){break;}
//        if(map[boy->x+1][boy->y]>0){
//            emit activiate(boy->x+1,boy->y);
//        }
//        else{
//            boy->x=boy->x+1;
//            changePlace();
//        }
//        return;

//    case Qt::Key_A:
////        keypressflag = true;
////        keyflag = 3;
//        if(boy->y==1){break;}
//        if(map[boy->x][boy->y-1]>0){
//            emit activiate(boy->x,boy->y-1);
//        }
//        else{
//            boy->y=boy->y-1;
//            changePlace();
//        }
//        return;

//    case Qt::Key_D:
////        keypressflag = true;
////        keyflag = 4;
//        if(boy->y==ROW_COUNT-2){break;}
//        if(map[boy->x][boy->y+1]>0){
//            emit activiate(boy->x,boy->y+1);
//        }
//        else{
//            boy->y=boy->y+1;
//            changePlace();
//        }
//        return;
//    }
//}



////void PlayScene::keyReleaseEvent(QKeyEvent *event){
////    QWidget::keyPressEvent(event);
////    switch(event->key())
////       {
////       case Qt::Key_W:
////           keypressflag = false;
////           return;

////       case Qt::Key_S:
////           keypressflag = false;
////           return;

////       case Qt::Key_A:
////           keypressflag = false;
////           return;

////       case Qt::Key_D:
////           keypressflag = false;
////           return;
////       }

////}
//void PlayScene::paintEvent(QPaintEvent *event){
//    //打印背景图
//    QPainter painter(this);
//    QPixmap pix ;
//    pix.load(":/Image/background1.png");
//    pix=pix.scaled(this->width(),this->height());
//    painter.drawPixmap(0,0,pix.width(),pix.height(),pix);


////    drawOneLine(painter);

//    //打印主界面
////    for(int i=0;i<ROW_COUNT;++i){
////        for(int j=0;j<COLUMN_COUNT;++j)
////        {
////            painter.drawPixmap(200+j*IMAGE_WIDHT,200+i*IMAGE_HEIGHT,IMAGE_WIDHT,IMAGE_HEIGHT,
////                                    QPixmap(QString(":/Image/%1.png").arg(PixmapData[i][j])));
////        }
////        //  游戏结束
////        if(lab_data == 100 ){
////        // emit Win();
////            painter.drawPixmap(10*10,10*10,300,300, QPixmap(":/img/win.jpeg"));
////            update();
////            if( win ==true){
////                painter.drawPixmap(10*10,10*10,300,300, QPixmap(":/img/over.jpeg"));
////                update();
////            }
////        }
////    }
//    //控制人物移动
////    if(keypressflag){
////        switch(keyflag){
////            case 1:

////                painter.drawPixmap(boy->x,boy->y,boy->pix);
////                update();
////                return;
////            case 2:

////                painter.drawPixmap(boy->x,boy->y,boy->pix);
////                update();
////                return;
////            case 3:

////                painter.drawPixmap(boy->x,boy->y,boy->pix);
////                update();
////                return;
////            case 4:

////                painter.drawPixmap(boy->x,boy->y,boy->pix);
////                update();
////                return;
////        }
////    }
////    else{
////        painter.drawPixmap(boy->x,boy->y,boy->pix);
////        update();
////    }
//}




//void PlayScene::initial(){

//     showGameArea=false;
//     //生成的数据必须成对,可以先生成一半，后一半通过前一半得到
//     QVector<int>*Exist=new QVector<int>(ROW_COUNT/2*COLUMN_COUNT,0);
//     for(int i=0;i<ROW_COUNT/2;++i){
//         for(int j=0;j<COLUMN_COUNT;++j){
//             if(i==0||i==ROW_COUNT-1||i==1||i==ROW_COUNT-2||j==0||j==COLUMN_COUNT-1||j==1||j==COLUMN_COUNT-2){PixmapData[i][j]=0;continue;}
//             int type=QRandomGenerator::global()->generate()%26+1;
//             //先生成前一半
//             PixmapData[i][j]=type;

////             生成后一半
//             while(true)
//             {
//                 //生成后一半的随机数
//                 int tempIndex=QRandomGenerator::global()->generate()%(ROW_COUNT/2*COLUMN_COUNT)+
//                         ROW_COUNT/2*COLUMN_COUNT;
//                 //判断是否出现过 没有出现，则赋值
//                 if(tempIndex/ROW_COUNT==0||tempIndex/ROW_COUNT==ROW_COUNT-1||tempIndex%ROW_COUNT==0||tempIndex%ROW_COUNT==COLUMN_COUNT-1||tempIndex/ROW_COUNT==1||tempIndex/ROW_COUNT==ROW_COUNT-2||tempIndex%ROW_COUNT==1||tempIndex%ROW_COUNT==COLUMN_COUNT-2){PixmapData[tempIndex/ROW_COUNT][tempIndex%ROW_COUNT]=0;continue;}
//                 if((*Exist)[tempIndex-ROW_COUNT/2*COLUMN_COUNT]==0)
//                 {
//                     PixmapData[tempIndex/ROW_COUNT][tempIndex%ROW_COUNT]=type;

//                     (*Exist)[tempIndex-ROW_COUNT/2*COLUMN_COUNT]=1;
//                     break;
//                 }
//             }
//         }
//    }

////     isEmpty=new QVector<QVector<bool>>(ROW_COUNT,QVector<bool>(COLUMN_COUNT,false));
////     collisionCount=0;
////     firstCollisionX=-1;
////     firstCollisionY=-1;
// }

//void PlayScene::changePlace(){
//    gridLayout->removeWidget(boy);
//    gridLayout->addWidget(boy,boy->x,boy->y);
//}
//void PlayScene::flushState(int x,int y){
//    gridLayout->removeWidget(image[x][y]);
//    gridLayout->addWidget(image[x][y],x,y);
//}
////判断激活情况
//void PlayScene::judge(int x, int y){
//    static bool times=false;

//    if(!times){
//        image[x][y]->changeIcon();
//        flushState(x,y);
//        times=true;
//        first_xy[0]=x;
//        first_xy[1]=y;
//    }
//    else {
//        if(first_xy[0]==x&&first_xy[1]==y){image[x][y]->changeIcon();flushState(x,y);times=false;}
//        else if(map[x][y]!=map[first_xy[0]][first_xy[1]]){
//            image[x][y]->changeIcon();
//            flushState(x,y);
//            QTimer *timer=new QTimer;
//            timer->start(500);
//            connect(timer,&QTimer::timeout,[=](){
//                image[x][y]->changeIcon();
//                image[first_xy[0]][first_xy[1]]->changeIcon();
//                flushState(x,y);
//                flushState(first_xy[0],first_xy[1]);
//                timer->stop();
//                times=false;
//            });
//        }
//        else{
//            if(inOneLine(x,y,first_xy[0],first_xy[1])){
//                draw->oneLineData[0]=x;
//                draw->oneLineData[1]=y;
//                draw->oneLineData[2]=first_xy[0];
//                draw->oneLineData[3]=first_xy[1];
//                draw->oneFlag=true;
//                draw->update();
//                image[x][y]->changeIcon();
//                QTimer *timer=new QTimer;
//                timer->start(500);
//                connect(timer,&QTimer::timeout,[=](){
//                    draw->oneFlag=false;
//                    draw->update();
//                    image[x][y]->clearIcon();
//                    image[first_xy[0]][first_xy[1]]->clearIcon();
//                    timer->stop();
//                });
//                map[x][y]=0;
//                map[first_xy[0]][first_xy[1]]=0;

//                times=false;

//            }
//            else if(inTwoLine(x,y,first_xy[0],first_xy[1])){
//                draw->twoLineData[0]=x;
//                draw->twoLineData[1]=y;
//                draw->twoLineData[4]=first_xy[0];
//                draw->twoLineData[5]=first_xy[1];
//                draw->twoFlag=true;
//                draw->update();
//                image[x][y]->changeIcon();
//                QTimer *timer=new QTimer;
//                timer->start(500);
//                connect(timer,&QTimer::timeout,[=](){
//                    draw->twoFlag=false;
//                    draw->update();
//                    image[x][y]->clearIcon();
//                    image[first_xy[0]][first_xy[1]]->clearIcon();
//                    timer->stop();
//                });
//                map[x][y]=0;
//                map[first_xy[0]][first_xy[1]]=0;
//            }
//            else if(inThreeLine(x,y,first_xy[0],first_xy[1])){
//                draw->threeLineData[0]=x;
//                draw->threeLineData[1]=y;
//                draw->threeLineData[6]=first_xy[0];
//                draw->threeLineData[7]=first_xy[1];
//                draw->threeFlag=true;
//                draw->update();
//                image[x][y]->changeIcon();
//                QTimer *timer=new QTimer;
//                timer->start(500);
//                connect(timer,&QTimer::timeout,[=](){
//                    draw->threeFlag=false;
//                    draw->update();
//                    image[x][y]->clearIcon();
//                    image[first_xy[0]][first_xy[1]]->clearIcon();
//                    timer->stop();
//                });
//                map[x][y]=0;
//                map[first_xy[0]][first_xy[1]]=0;
//            }
//            else{
//                image[x][y]->changeIcon();
//                QTimer *timer=new QTimer;
//                timer->start(500);
//                connect(timer,&QTimer::timeout,[=](){
//                    image[x][y]->changeIcon();
//                    image[first_xy[0]][first_xy[1]]->changeIcon();
//                    timer->stop();
//                    times=false;
//                });
//            }
//            times=false;
//        }
//    }
//}
//bool PlayScene::inOneLine(int x,int y,int first_x,int first_y){
//    bool empty=true;
//    if(x==first_x){
//        for(int i=minItem(y,first_y)+1;i<maxItem(y,first_y);i++){
//            if(map[x][i]>0){empty=false;break;}
//        }
//        if(empty){
//            //绘制一条线

//            return true;
//        }
//        else{return false;}
//    }
//    else if(y==first_y){
//        for(int i=minItem(x,first_x)+1;i<maxItem(x,first_x);i++){
//            if(map[i][y]>0){empty=false;break;}
//        }
//        if(empty){

//            return true;
//        }
//        else{return false;}
//    }
//    else{return false;}
//}
//bool PlayScene::inTwoLine(int x,int y,int first_x,int first_y){
//    bool flag1=inOneLine(x,y,x,first_y)&&inOneLine(x,first_y,first_x,first_y);
//    bool flag2=inOneLine(x,y,first_x,y)&&inOneLine(first_x,y,first_x,first_y);

//    if( flag1 && map[x][first_y]==0) {
//        //画两条线
//        draw->twoLineData[2]=x;
//        draw->twoLineData[3]=first_y;
//        draw->threeLineData[4]=x;
//        draw->threeLineData[5]=first_y;
//        return true;
//    }
//    else if( flag2 && map[first_x][y]==0 ){
//        draw->twoLineData[2]=first_x;
//        draw->twoLineData[3]=y;
//        draw->threeLineData[4]=first_x;
//        draw->threeLineData[5]=y;
//        return true;
//    }
//    else{return false;}
//}
//bool PlayScene::inThreeLine(int x, int y, int first_x, int first_y){
//    bool flag=false;
//    //固定行
//    for(int i=1;i<COLUMN_COUNT-1;i++)
//    {
//        if(i==y){
//            continue;
//        }
//        if(map[x][i]==0){
//            flag=inOneLine(x,i,x,y)&&inTwoLine(x,i,first_x,first_y);
//            draw->threeLineData[2]=x;
//            draw->threeLineData[3]=i;
//        }
//        if(flag){
//            //画三条线

//            return true;
//        }
//    }
//    //固定列
//    for(int i=1;i<ROW_COUNT-1;i++)
//    {
//        if(i==x){
//            continue;
//        }
//        if(map[i][y]==0){
//            flag=inOneLine(i,y,x,y)&&inTwoLine(i,y,first_x,first_y);
//            draw->threeLineData[2]=i;
//            draw->threeLineData[3]=y;
//        }
//        if(flag)
//            //画三条线

//            return true;
//    }
//    return false;
//}
//int PlayScene::minItem(int x, int y){
//    return (x>y)?y:x;
//}
//int PlayScene::maxItem(int x, int y){
//    return (x>y)?x:y;
//}
////void PlayScene::drawOneLine(QPainter &painter){
////    if(oneFlag){
////        painter.drawLine(image[drawOne[0]][drawOne[1]]->geometry().center(),image[drawOne[2]][drawOne[3]]->geometry().center());
////    }
////}

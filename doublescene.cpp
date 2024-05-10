#include "doublescene.h"
#include "ui_doublescene.h"
#include"protagonist1.h"
#include<QWidget>
#include<QTimer>
#include<QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QPainter>
#include<QPixmap>
#include<QPropertyAnimation>
#include<QRandomGenerator>
#include<QMainWindow>
#include<QStatusBar>

int DoubleScene:: i=300;
int DoubleScene:: j=0;
int DoubleScene:: k=0;
QTime DoubleScene::leftTime(0,5,0);



DoubleScene::DoubleScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DoubleScene)
{
    //设置主mainwindow
    map=new int *[ROW_COUNT];
    for(int i=0;i<ROW_COUNT;i++){
        map[i]=new int [COLUMN_COUNT];
    }
    image=new ImageButton **[ROW_COUNT];
    for(int i=0;i<ROW_COUNT;i++){
        image[i]=new ImageButton*[COLUMN_COUNT];
        for(int j=0;j<COLUMN_COUNT;j++){
            image[i][j]=new ImageButton;
        }
    }

    PixmapData=new int *[ROW_COUNT];
    for(int i=0;i<ROW_COUNT;i++){
        PixmapData[i]=new int [COLUMN_COUNT];
    }

    dizzy1flag=false;
    dizzy2flag=false;
    freeze1Flag=false;
    freeze2Flag=false;

    this->setWindowTitle("原神连连看");
    this->setWindowIcon(QIcon(":/Image/icon.png"));
    this->setFixedSize(1700,1450);

    timer=new QTimer;
    timer->start(1000);
    //创建角色
    boy=new Protagonist1(":/Image/protagonist1.png",1,1);
    girl=new Protagonist2(":/Image/protagonist2.png",ROW_COUNT-2,COLUMN_COUNT-2);
    initial();
    pix.load(":/Image/background3.png");

    //设置图层和主widget
    windows = new QWidget();
    gridLayout = new QGridLayout;
    draw2=new Draw(Qt::red);
    draw=new Draw(Qt::red);
    drawHint=new Draw(Qt::blue);
    endScene=new EndGame;
    for(int i = 0;i < ROW_COUNT;++i){
        for(int j = 0; j<COLUMN_COUNT;j++){
            if(i==0||i==ROW_COUNT-1||i==1||i==ROW_COUNT-2||j==0||j==COLUMN_COUNT-1||j==1||j==COLUMN_COUNT-2){map[i][j]=0;}
            else{map[i][j]=PixmapData[i][j];}
        }
    }
    setCentralWidget(windows);
    for(int i = 0; i < ROW_COUNT; ++i)
            for(int j = 0; j < COLUMN_COUNT; ++j) {
                if(i==0||i==ROW_COUNT-1||j==0||j==COLUMN_COUNT-1){image[i][j]=createImageButton(QString(":/Image/wall.png"),QString(":/Image/wall.png"));}
                else if(i==1||i==ROW_COUNT-2||j==1||j==COLUMN_COUNT-2){image[i][j]=createImageButton(QString(":/Image/blank.png"),QString(":/Image/blank.png"));}
                else{
                    image[i][j] = createImageButton(
                              QString(":/Image/%1.png").arg(PixmapData[i][j]),
                              QString(":/Image/%1.png").arg(PixmapData[i][j]+26));
                }
                gridLayout->addWidget(image[i][j], i, j, Qt::AlignCenter);


    }
    windows->resize(1700,1450);
    gridLayout->addWidget(boy,boy->x,boy->y);
    gridLayout->addWidget(girl,girl->x,girl->y);
    gridLayout->setAlignment(Qt::AlignCenter); // 居中布局



    gridLayout->addWidget(draw,0,0,ROW_COUNT-1,COLUMN_COUNT-1);
    gridLayout->addWidget(draw2,0,0,ROW_COUNT-1,COLUMN_COUNT-1);
    gridLayout->addWidget(drawHint,0,0,ROW_COUNT-1,COLUMN_COUNT-1);
    gridLayout->setContentsMargins(0,0,0,0);
    gridLayout->setSpacing(10);
    gridLayout->setMargin(0);
    windows->setLayout(gridLayout);


    //将激活信号和处理函数相连
    connect(this,&DoubleScene::activiate,this,&DoubleScene::judge);
    connect(this,&DoubleScene::activiate2,this,&DoubleScene::judge2);
    //设置画笔参数
    linePen.setColor(Qt::red);
    linePen.setWidth(10);

    //设置倒计时
    j=0;
    k=0;
    i=300;
    QTime zero(0,0,0);
    progressBar=new QProgressBar;

    progressBar->setMinimum(0);
    progressBar->setMaximum(i);
    label=new QLabel;
    label->setText("剩余时间："+leftTime.toString("mm:ss"));
    progressBar->setRange(0,i);
    progressBar->setValue(i);
    QApplication::processEvents();
    QToolBar *toolbar=new QToolBar(this);
    addToolBar(Qt::BottomToolBarArea,toolbar);
    connect(timer,&QTimer::timeout,[=](){

        --i;
        leftTime=leftTime.addSecs(-1);
        label->setText("剩余时间："+leftTime.toString("mm:ss"));
        int h=leftTime.hour();
        int m=leftTime.minute();
        int s=leftTime.second();
        limitTime=3600*h+m*60+s;
        progressBar->setValue(3600*h+60*m+s);
        progressBar->update();
        if(i==0||!checkRemain()){
            this->close();

            endScene=new EndGame;
            if(j>k){
                endScene->information->setText("角色1胜利，是否再来一局");
            }
            else if(j<k){
                endScene->information->setText("角色2胜利，是否再来一局");
            }
            else{endScene->information->setText("平局，是否再来一局");}
            endScene->show();
            connect(endScene,&EndGame::choose,[=](){
                emit choose();
            });
            timer->stop();
            timer->deleteLater();
        }
    });
    QString styleSheet = "QLabel { font-size: 30px;color: green; }";
    label->setStyleSheet(styleSheet);
    statusBar()->addWidget(progressBar);
    statusBar()->addWidget(label);
    //设计得分

    score=new QLabel;
    score2=new QLabel;
    score->setText("角色1得分："+QString::number(j));
    score2->setText("角色2得分："+QString::number(k));
    QString style = "QLabel { font-size: 30px;color: red }";
    score->setStyleSheet(style);
    score2->setStyleSheet(style);
    toolbar->addWidget(score);
    toolbar->addSeparator();
    toolbar->addWidget(score2);
    connect(this,&DoubleScene::scoreChange,[=](){
        j+=10;
        score->setText("角色1得分："+QString::number(j));
    });
    connect(this,&DoubleScene::scoreChange2,[=](){
        k+=10;
        score2->setText("角色2得分："+QString::number(k));
    });
    save =new QPushButton("保存游戏",this);
    back=new QPushButton("退出游戏",this);
    pause=new QPushButton("暂停游戏",this);

    QString style2 = "QPushButton {  background-image: url(':/Image/buttonbackground.png');background-position: center; border: none;color:blue;font-size: 30px }";
    back->setStyleSheet(style2);
    pause->setStyleSheet(style2);
    save->setStyleSheet(style2);
    pause->resize(220,60);
    back->resize(220,60);
    save->resize(220,60);
    back->move(0,0);
    pause->move(0,70);
    save->move(0,140);
    save->hide();
    continueFlag=true;

    connect(pause,&QPushButton::clicked,[=](){
        if(continueFlag){
            pause->setText("继续游戏");
            save->show();
            timer->stop();
            freeze1Flag=true;
            freeze2Flag=true;
            continueFlag=false;
        }
        else{
            pause->setText("暂停游戏");
            save->hide();
            timer->start();
            freeze1Flag=false;
            freeze2Flag=false;
            continueFlag=true;
        }

    });
    connect(back,&QPushButton::clicked,[=](){
        this->close();
        emit choose();
        timer->stop();
        timer->deleteLater();
    });
    saveMode=2;
    connect(save,&QPushButton::clicked,[=](){
            QMessageBox tmp;
                tmp.setText("已保存！");
                tmp.exec();

                std::ofstream save("C:\\Users\\86191\\Qt creater\\QLink\\saveGame.txt", std::ios::out);
                save<< saveMode <<" "
                    <<ROW_COUNT<<" "
                    <<COLUMN_COUNT<<" "
                    <<characterNumber<<" "
                    << limitTime << " "
                    << boy->x << " "
                    << boy->y<< " "
                    << j <<" "
                    << girl->x << " "
                    << girl->y<< " "
                    << k<< std::endl;
                for(int i = 0; i < ROW_COUNT;++i)
                    for(int j = 0; j < COLUMN_COUNT; ++j)
                        save<< map[i][j] << " ";

                save.close();
                this->close();
                emit start();
    });


    //设置buff图片
    buff[0]=createImageButton(":/Image/+1s.png",":/Image/+1s.png");
    buff[1]=createImageButton(":/Image/shuffle.png",":/Image/shuffle.png");
    buff[2]=createImageButton(":/Image/hint.png",":/Image/hint.png");
    buff[3]=createImageButton(":/Image/dizzy.png",":/Image/dizzy.png");
    buff[4]=createImageButton(":/Image/freeze.png",":/Image/freeze.png");

    //随机生成buff
    setBuff();
    connect(this,&DoubleScene::buffEmit,this,&DoubleScene::buffStart);
    thisBuff=new ImageButton;
    buffRow=0;
    buffColumn=0;
    //初始不用提示
    hintFlag=false;
    connect(this,&DoubleScene::hintUpdate,[=](){
        drawHint->oneFlag=false;
        drawHint->twoFlag=false;
        drawHint->threeFlag=false;
        drawHint->update();
        QTimer *ss=new QTimer;
        ss->start(100);
        connect(ss,&QTimer::timeout,[=](){
            if(hintFlag){hint();}
            ss->stop();
        });

    });

    //初始不运行鼠标事件
    mouseIsActive=false;





}
DoubleScene::DoubleScene(int ii,int x1,int y1,int jj,int x2,int y2,int kk,int **mapp){
    //设置主mainwindow
//     ui->setupUi(this);
    map=new int *[ROW_COUNT];
    for(int i=0;i<ROW_COUNT;i++){
        map[i]=new int [COLUMN_COUNT];
    }
    image=new ImageButton **[ROW_COUNT];
    for(int i=0;i<ROW_COUNT;i++){
        image[i]=new ImageButton*[COLUMN_COUNT];
        for(int j=0;j<COLUMN_COUNT;j++){
            image[i][j]=new ImageButton;
        }
    }

    PixmapData=new int *[ROW_COUNT];
    for(int i=0;i<ROW_COUNT;i++){
        PixmapData[i]=new int [COLUMN_COUNT];
    }
    dizzy1flag=false;
    dizzy2flag=false;
    freeze1Flag=false;
    freeze2Flag=false;

    this->setWindowTitle("原神连连看");
    this->setWindowIcon(QIcon(":/Image/icon.png"));
    this->setFixedSize(1700,1450);

    timer=new QTimer;
    timer->start(1000);
    //创建角色
    boy=new Protagonist1(":/Image/protagonist1.png",x1,y1);
    girl=new Protagonist2(":/Image/protagonist2.png",x2,y2);
    initial();
    pix.load(":/Image/background3.png");
    //设置buff图片
    buff[0]=createImageButton(":/Image/+1s.png",":/Image/+1s.png");
    buff[1]=createImageButton(":/Image/shuffle.png",":/Image/shuffle.png");
    buff[2]=createImageButton(":/Image/hint.png",":/Image/hint.png");
    buff[3]=createImageButton(":/Image/dizzy.png",":/Image/dizzy.png");
    buff[4]=createImageButton(":/Image/freeze.png",":/Image/freeze.png");
    //设置图层和主widget
    windows = new QWidget;
    gridLayout = new QGridLayout;
    draw2=new Draw(Qt::red);
    draw=new Draw(Qt::red);
    drawHint=new Draw(Qt::blue);
    endScene=new EndGame;
    buffFlag=false;
    for(int i = 0;i < ROW_COUNT;++i){
        for(int j = 0; j<COLUMN_COUNT;j++){
            if(i==0||i==ROW_COUNT-1||j==0||j==COLUMN_COUNT-1){map[i][j]=0;}
            else{map[i][j]=mapp[i][j];}
        }
    }
    setCentralWidget(windows);
    for(int i = 0; i < ROW_COUNT; ++i)
            for(int j = 0; j < COLUMN_COUNT; ++j) {
                if(i==0||i==ROW_COUNT-1||j==0||j==COLUMN_COUNT-1){image[i][j]=createImageButton(QString(":/Image/wall.png"),QString(":/Image/wall.png"));}
                else if(map[i][j]==0){image[i][j]=createImageButton(QString(":/Image/blank.png"),QString(":/Image/blank.png"));}
                else if(map[i][j]>0){
                    image[i][j] = createImageButton(
                              QString(":/Image/%1.png").arg(mapp[i][j]),
                              QString(":/Image/%1.png").arg(mapp[i][j]+26));

                }
                else{
                    image[i][j]=createImageButton(QString(":/Image/blank.png"),QString(":/Image/blank.png"));
                    gridLayout->addWidget(image[i][j], i, j, Qt::AlignCenter);
                    thisBuff=new ImageButton;
                    thisBuff=createImageButton(buff[-1-map[i][j]]->normalPath,buff[-1-map[i][j]]->activePath);
                    gridLayout->addWidget(thisBuff,i,j);
                    buffFlag=true;
                    continue;
                }
                gridLayout->addWidget(image[i][j], i, j, Qt::AlignCenter);


    }
    windows->resize(1700,1450);
    gridLayout->addWidget(boy,boy->x,boy->y);
    gridLayout->addWidget(girl,girl->x,girl->y);
    gridLayout->setAlignment(Qt::AlignCenter); // 居中布局



    gridLayout->addWidget(draw,0,0,ROW_COUNT-1,COLUMN_COUNT-1);
    gridLayout->addWidget(draw2,0,0,ROW_COUNT-1,COLUMN_COUNT-1);
    gridLayout->addWidget(drawHint,0,0,ROW_COUNT-1,COLUMN_COUNT-1);
    gridLayout->setContentsMargins(0,0,0,0);
    gridLayout->setSpacing(10);
    gridLayout->setMargin(0);
    windows->setLayout(gridLayout);
//    windows->setStyleSheet("background-image: url(:/Image/background1.png);");

    //将激活信号和处理函数相连
    connect(this,&DoubleScene::activiate,this,&DoubleScene::judge);
    connect(this,&DoubleScene::activiate2,this,&DoubleScene::judge2);
    //设置画笔参数
    linePen.setColor(Qt::red);
    linePen.setWidth(10);

    //设置倒计时
    j=jj;
    k=kk;
    i=ii;
    QTime zero(0,0,0);
    progressBar=new QProgressBar;

    progressBar->setMinimum(0);
    progressBar->setMaximum(300);
    label=new QLabel;
    label->setText("剩余时间："+leftTime.toString("mm:ss"));
    progressBar->setRange(0,300);
    progressBar->setValue(i);
    QApplication::processEvents();
    QToolBar *toolbar=new QToolBar(this);
    addToolBar(Qt::BottomToolBarArea,toolbar);
    connect(timer,&QTimer::timeout,[=](){

        --i;
        leftTime=leftTime.addSecs(-1);
        label->setText("剩余时间："+leftTime.toString("mm:ss"));
        int h=leftTime.hour();
        int m=leftTime.minute();
        int s=leftTime.second();
        limitTime=3600*h+m*60+s;
        progressBar->setValue(3600*h+60*m+s);
        progressBar->update();
        if(leftTime==zero){timer->stop();}
        if(i==0||!checkRemain()){
            this->close();

            endScene=new EndGame;
            if(j>k){
                endScene->information->setText("角色1胜利，是否再来一局");
            }
            else if(j<k){
                endScene->information->setText("角色2胜利，是否再来一局");
            }
            else{endScene->information->setText("平局，是否再来一局");}
            endScene->show();
            connect(endScene,&EndGame::choose,[=](){
                emit choose();
            });
            timer->stop();
            timer->deleteLater();
            if(score>score2){}
        }
    });
    QString styleSheet = "QLabel { font-size: 30px;color: green; }";
    label->setStyleSheet(styleSheet);
    statusBar()->addWidget(progressBar);
    statusBar()->addWidget(label);
    //设计得分

    score=new QLabel;
    score2=new QLabel;
    score->setText("角色1得分："+QString::number(j));
    score2->setText("角色2得分："+QString::number(k));
    QString style = "QLabel { font-size: 30px;color: red }";
    score->setStyleSheet(style);
    score2->setStyleSheet(style);
    toolbar->addWidget(score);
    toolbar->addSeparator();
    toolbar->addWidget(score2);
    connect(this,&DoubleScene::scoreChange,[=](){
        j+=10;
        score->setText("角色1得分："+QString::number(j));
    });
    connect(this,&DoubleScene::scoreChange2,[=](){
        k+=10;
        score2->setText("角色2得分："+QString::number(k));
    });
    save =new QPushButton("保存游戏",this);
    back=new QPushButton("退出游戏",this);
    pause=new QPushButton("暂停游戏",this);

    QString style2 = "QPushButton {  background-image: url(':/Image/buttonbackground.png');background-position: center; border: none;color:blue;font-size: 30px }";
    back->setStyleSheet(style2);
    pause->setStyleSheet(style2);
    save->setStyleSheet(style2);
    pause->resize(220,60);
    back->resize(220,60);
    save->resize(220,60);
    back->move(0,0);
    pause->move(0,70);
    save->move(0,140);
    save->hide();
    continueFlag=true;

    connect(pause,&QPushButton::clicked,[=](){
        if(continueFlag){
            pause->setText("继续游戏");
            save->show();
            timer->stop();
            freeze1Flag=true;
            freeze2Flag=true;
            continueFlag=false;
        }
        else{
            pause->setText("暂停游戏");
            save->hide();
            timer->start();
            freeze1Flag=false;
            freeze2Flag=false;
            continueFlag=true;
        }

    });
    connect(back,&QPushButton::clicked,[=](){
        this->close();
        emit choose();
        timer->stop();
        timer->deleteLater();
    });
    saveMode=2;
    connect(save,&QPushButton::clicked,[=](){
            QMessageBox tmp;
                tmp.setText("已保存！");
                tmp.exec();

                std::ofstream save("C:\\Users\\86191\\Qt creater\\QLink\\saveGame.txt", std::ios::out);
                save<< saveMode <<" "
                    <<ROW_COUNT<<" "
                    <<COLUMN_COUNT<<" "
                    <<characterNumber<<" "
                    <<limitTime << " "
                    << boy->x << " "
                    << boy->y<< " "
                    << j<< std::endl;
                save<< girl->x << " "
                    << girl->y<< " "
                    << k<< std::endl;
                for(int i = 0; i < ROW_COUNT;++i)
                    for(int j = 0; j < COLUMN_COUNT; ++j)
                        save<< map[i][j] << " ";

                save.close();
                this->close();
                emit start();
    });




    //随机生成buff
    setBuff();
    connect(this,&DoubleScene::buffEmit,this,&DoubleScene::buffStart);
    if(!buffFlag){thisBuff=new ImageButton;}
    buffRow=0;
    buffColumn=0;
    //初始不用提示
    hintFlag=false;
    connect(this,&DoubleScene::hintUpdate,[=](){
        drawHint->oneFlag=false;
        drawHint->twoFlag=false;
        drawHint->threeFlag=false;
        drawHint->update();
        QTimer *ss=new QTimer;
        ss->start(100);
        connect(ss,&QTimer::timeout,[=](){
            if(hintFlag){hint();}
            ss->stop();
        });

    });

    //初始不运行鼠标事件
    mouseIsActive=false;
}

bool DoubleScene::corner(int x,int y){
    if((map[x-1][y]==0||map[x+1][y]==0||map[x][y-1]==0||map[x][y+1]==0)&&map[x][y]>0){return true;}
    return false;
}

bool DoubleScene::checkRemain(){
    std::vector<int>x;
    std::vector<int>y;
    for(int i=2;i<ROW_COUNT-2;i++){
        for(int j=2;j<COLUMN_COUNT-2;j++){
            if(corner(i,j)){
                x.push_back(i);
                y.push_back(j);
            }
        }
    }
    std::vector<int>::iterator i = x.begin();
    std::vector<int>::iterator j = y.begin();

    for( ;i!=x.end();(++i,++j)){
        std::vector<int>::iterator m=i+1;
        std::vector<int>::iterator n=j+1;

        for(;m!=x.end();(++m,++n)){
            if(oneCheck(*i,*j,*m,*n)&&(map[*i][*j]==map[*m][*n])){
                return true;
            }
            else if(twoCheck(*i,*j,*m,*n)&&(map[*i][*j]==map[*m][*n])){
                return true;
            }
            else if(threeCheck(*i,*j,*m,*n)&&(map[*i][*j]==map[*m][*n])){
                        return true;
            }

        }
    }
    return false;
}
void DoubleScene::hint(){
    bool end=false;
    std::vector<int>x;
    std::vector<int>y;
    for(int i=2;i<ROW_COUNT-2;i++){
        for(int j=2;j<COLUMN_COUNT-2;j++){
            if(corner(i,j)){
                x.push_back(i);
                y.push_back(j);
            }
        }
    }
    std::vector<int>::iterator i = x.begin();
    std::vector<int>::iterator j = y.begin();
    for( ;i!=x.end();(++i,++j)){
        std::vector<int>::iterator m=i+1;
        std::vector<int>::iterator n=j+1;

        for(;m!=x.end();(++m,++n)){
            if(inOneLine(*i,*j,*m,*n)&&(map[*i][*j]==map[*m][*n])){

                drawHint->oneLineData[0]=*i;
                drawHint->oneLineData[1]=*j;
                drawHint->oneLineData[2]=*m;
                drawHint->oneLineData[3]=*n;
                drawHint->oneFlag=true;
                drawHint->update();
//                while(true){
//                    if(!drawHint->oneFlag){drawHint->update();return;}
//                }
                end=true;
                break;
            }
            else if(inTwoLine(*i,*j,*m,*n)&&(map[*i][*j]==map[*m][*n])){

                drawHint->twoLineData[0]=*i;
                drawHint->twoLineData[1]=*j;
                drawHint->twoLineData[4]=*m;
                drawHint->twoLineData[5]=*n;
                drawHint->twoFlag=true;
                drawHint->update();
//                while(true){
//                    if(!drawHint->twoFlag){drawHint->update();return;}
//                }
                end=true;
                break;
            }
            else if(inThreeLine(*i,*j,*m,*n)&&(map[*i][*j]==map[*m][*n])){

                drawHint->threeLineData[0]=*i;
                drawHint->threeLineData[1]=*j;
                drawHint->threeLineData[6]=*m;
                drawHint->threeLineData[7]=*n;
                drawHint->threeFlag=true;
                drawHint->update();
//                while(true){
//                    if(!drawHint->threeFlag){drawHint->update();return;}

//                }
                end=true;
                break;
            }

        }
        if(end){break;}
    }

}
void DoubleScene::setBuff(){
    int randomTime = (QRandomGenerator::global()->generate()%5+30)*1000;
    QTimer *gap=new QTimer;
    gap->start(randomTime);
    connect(gap,&QTimer::timeout,[=](){
        if(thisBuff!=nullptr){gridLayout->removeWidget(thisBuff);delete thisBuff;thisBuff=nullptr;}
        map[buffRow][buffColumn]=0;
    if(i!=0){
        thisBuff=new ImageButton;
        int randomBuff = QRandomGenerator::global()->generate()%5;

        //找随机空位置
        buffRow=QRandomGenerator::global()->generate()%(ROW_COUNT-2)+1;
        buffColumn=QRandomGenerator::global()->generate()%(COLUMN_COUNT-2)+1;

        while(map[buffRow][buffColumn]!=0){
            buffRow=QRandomGenerator::global()->generate()%(ROW_COUNT-2)+1;
            buffColumn=QRandomGenerator::global()->generate()%(COLUMN_COUNT-2)+1;
        }
        thisBuff=createImageButton(buff[randomBuff]->normalPath,buff[randomBuff]->activePath);
             gridLayout->addWidget(thisBuff,buffRow,buffColumn);
             map[buffRow][buffColumn]=-(randomBuff+1);

    }
    if(i==0){
        gap->stop();
        gap->deleteLater();}
    });

}



ImageButton *DoubleScene::createImageButton(const QString &str1,
                                           const QString &str2)
{
    // 加载两张图片

    QPixmap img1, img2;
    img1.load(str1);
    img2.load(str2);
    ImageButton *button = new ImageButton;
    button->normalPath=str1;
    button->activePath=str2;
    // 设置大小和图片
//    button->setGeometry(0, 0, 0, 0);
    button->setFixedSize(80, 80);
    button->setButtonIcon(QIcon(img1), QIcon(img2));
    button->setIconSize(QSize(button->width(),button->height()));
    button->setStyleSheet("border:1px rgba(237, 241, 255, 100);"
                          "border-radius:8px;"
                          "padding:0px;"
                          "border-style: outset;");
    return button;
}

void DoubleScene::buffStart(int x, int y){
    if(map[x][y]==-1){
        gridLayout->removeWidget(thisBuff);
        delete thisBuff;
        thisBuff=nullptr;
        i=i+30;
        leftTime=leftTime.addSecs(30);
        label->setText("剩余时间："+leftTime.toString("mm:ss"));
        progressBar->setValue(i);
        map[x][y]=0;
    }
    else if(map[x][y]==-2){
        shuffle();
        gridLayout->update();
        gridLayout->removeWidget(thisBuff);
        delete thisBuff;
        thisBuff=nullptr;
        map[x][y]=0;

    }
    else if (map[x][y]==-3){
        QTimer *tenmin=new QTimer;
        tenmin->start(10000);
        hintFlag=true;
        connect(tenmin,&QTimer::timeout,[=](){
            hintFlag=false;
            drawHint->oneFlag=false;
            drawHint->twoFlag=false;
            drawHint->threeFlag=false;
            drawHint->update();
            tenmin->stop();
            tenmin->deleteLater();
        });
        hint();
        gridLayout->removeWidget(thisBuff);
        delete thisBuff;
        thisBuff=nullptr;
        map[x][y]=0;
    }
    else if(map[x][y]==-4){
        QTimer *tenMin=new QTimer;
        tenMin->start(10000);
        if(who){
            dizzy2flag=true;
        }
        else{dizzy1flag=true;}
        connect(tenMin,&QTimer::timeout,[=](){
            dizzy2flag=false;
            dizzy1flag=false;
            tenMin->stop();
            tenMin->deleteLater();
        });
        gridLayout->removeWidget(thisBuff);
        delete thisBuff;
        thisBuff=nullptr;
        map[x][y]=0;
    }
    else{
        QTimer*threeMin=new QTimer;
        threeMin->start(3000);
        QTimer *three=new QTimer;
        three->start(200);
        connect(three,&QTimer::timeout,[=](){
            if(who2){
                freeze2Flag=true;
                qDebug()<<"2";
            }
            else{freeze1Flag=true;qDebug()<<"1";}
            three->stop();
            three->deleteLater();
        });

        connect(threeMin,&QTimer::timeout,[=](){
            freeze1Flag=false;
            freeze2Flag=false;
            threeMin->stop();
            threeMin->deleteLater();
        });
                gridLayout->removeWidget(thisBuff);
                delete thisBuff;
                thisBuff=nullptr;
                map[x][y]=0;
    }
}

void DoubleScene::shuffle(){
    for(int i = 2; i < ROW_COUNT-2; ++i)
         for(int j = 2; j < COLUMN_COUNT-2; ++j) {
             if(map[i][j]>0) {
                 std::srand((unsigned)time(NULL));
                 int x=rand()%(ROW_COUNT-4)+2;
                 int y=rand()%(COLUMN_COUNT-4)+2;
                 while(map[x][y]==0){
                     x=rand()%(ROW_COUNT-4)+2;
                     y=rand()%(COLUMN_COUNT-4)+2;
                 }
                 image[i][j]->exchangeIcon(image[x][y]);
                 image[i][j]->flushIcon();
                 image[x][y]->flushIcon();

                 int tmp1 = map[x][y];
                 map[x][y] = map[i][j];
                 map[i][j] = tmp1;
             }
         }

}
DoubleScene::~DoubleScene()
{
    delete ui;
    delete this;
}

void DoubleScene::mousePressEvent(QMouseEvent*ev){
    if(mouseIsActive){
        int xx,yy;
        if(ev->y()<153||ev->y()>1223||ev->x()<315||ev->x()>1385){return;}
        else {
            xx=(ev->y()-58)/90;
            yy=(ev->x()-220)/90;
            qDebug()<<xx<<yy;
        }
        if(map[xx][yy]==0){boy->x=xx;boy->y=yy;changePlace();}
        else if(!corner(xx,yy)){
            return ;
        }
        else{
            judge(xx,yy);
            if(map[xx-1][yy]==0){boy->x=xx-1;boy->y=yy;changePlace();}
            else if(map[xx+1][yy]==0){boy->x=xx+1;boy->y=yy;changePlace();}
            else if(map[xx][yy-1]==0){boy->x=xx;boy->y=yy-1;changePlace();}
            else{boy->x=xx;boy->y=yy+1;changePlace();}
        }
    }
}
//实现人物移动及激活信号
void DoubleScene::keyPressEvent(QKeyEvent *event){

    switch(event->key())
    {
    case Qt::Key_W:
        if(!freeze1Flag){
        if(dizzy1flag){
            if(boy->x==ROW_COUNT-2){break;}
            if(map[boy->x+1][boy->y]>0){
                emit activiate(boy->x+1,boy->y);
            }
            else if(map[boy->x+1][boy->y]<0){
                emit buffEmit(boy->x+1,boy->y);
                who=true;
                who2=true;
                boy->x=boy->x+1;
                changePlace();
             }
            else{
                boy->x=boy->x+1;
                changePlace();
            }
            return;
        }
        else{
            if(boy->x==1){break;}
            if(map[boy->x-1][boy->y]>0){
            emit activiate(boy->x-1,boy->y);
            }
            else if(map[boy->x-1][boy->y]<0){
                emit buffEmit(boy->x-1,boy->y);
                who=true;
                who2=true;
                boy->x=boy->x-1;
                changePlace();

            }
            else{
                boy->x=boy->x-1;
                changePlace();
            }
            return;
        }
        }

    case Qt::Key_S:
        if(!freeze1Flag){
        if(dizzy1flag){
            if(boy->x==1){break;}
            if(map[boy->x-1][boy->y]>0){
            emit activiate(boy->x-1,boy->y);
            }
            else if(map[boy->x-1][boy->y]<0){
                emit buffEmit(boy->x-1,boy->y);
                who=true;
                who2=true;
                boy->x=boy->x-1;
                changePlace();

            }
            else{
                boy->x=boy->x-1;
                changePlace();
            }
            return;
        }
        else{
            if(boy->x==ROW_COUNT-2){break;}
            if(map[boy->x+1][boy->y]>0){
                emit activiate(boy->x+1,boy->y);
            }
            else if(map[boy->x+1][boy->y]<0){
                emit buffEmit(boy->x+1,boy->y);
                who=true;
                who2=true;
                boy->x=boy->x+1;
                changePlace();
            }
            else{
                boy->x=boy->x+1;
                changePlace();
            }
            return;
        }
        }
    case Qt::Key_A:
        if(!freeze1Flag){
        if(dizzy1flag){
            if(boy->y==COLUMN_COUNT-2){break;}
            if(map[boy->x][boy->y+1]>0){
                emit activiate(boy->x,boy->y+1);
            }
            else if(map[boy->x][boy->y+1]<0){
                emit buffEmit(boy->x,boy->y+1);
                who=true;
                who2=true;
                boy->y=boy->y+1;
                changePlace();
            }
            else{
                boy->y=boy->y+1;
                changePlace();
            }
            return;
        }
        else{
            if(boy->y==1){break;}
            if(map[boy->x][boy->y-1]>0){
                emit activiate(boy->x,boy->y-1);
            }
            else if(map[boy->x][boy->y-1]<0){
                emit buffEmit(boy->x,boy->y-1);
                who=true;
                who2=true;
                boy->y=boy->y-1;
                changePlace();
            }
            else{
                boy->y=boy->y-1;
                changePlace();
            }
            return;
        }
        }

    case Qt::Key_D:
    if(!freeze1Flag){
        if(dizzy1flag){
            if(boy->y==1){break;}
            if(map[boy->x][boy->y-1]>0){
                emit activiate(boy->x,boy->y-1);
            }
            else if(map[boy->x][boy->y-1]<0){
                emit buffEmit(boy->x,boy->y-1);
                who=true;
                who2=true;
                boy->y=boy->y-1;
                changePlace();
            }
            else{
                boy->y=boy->y-1;
                changePlace();
            }
            return;
        }
        else{
            if(boy->y==COLUMN_COUNT-2){break;}
            if(map[boy->x][boy->y+1]>0){
                emit activiate(boy->x,boy->y+1);
            }
            else if(map[boy->x][boy->y+1]<0){
                emit buffEmit(boy->x,boy->y+1);
                who=true;
                who2=true;
                boy->y=boy->y+1;
                changePlace();
            }
            else{
                boy->y=boy->y+1;
                changePlace();
            }
            return;
        }
     }
    case Qt::Key_5:
     if(!freeze2Flag){
        if(dizzy2flag){
            if(girl->x==ROW_COUNT-2){break;}
            if(map[girl->x+1][girl->y]>0){
                emit activiate2(girl->x+1,girl->y);
            }
            else if(map[girl->x+1][girl->y]<0){
                emit buffEmit(girl->x+1,girl->y);
                who=false;
                who2=false;
                girl->x=girl->x+1;
                changePlace();
             }
            else{
                girl->x=girl->x+1;
                changePlace();
            }
            return;

        }
        else{
            if(girl->x==1){break;}
            if(map[girl->x-1][girl->y]>0){
                emit activiate2(girl->x-1,girl->y);
            }
            else if(map[girl->x-1][girl->y]<0){
                emit buffEmit(girl->x-1,girl->y);
                who=false;
                who2=false;
                girl->x=girl->x-1;
                changePlace();

            }
            else{
                girl->x=girl->x-1;
                changePlace();
            }
            return;
        }
    }
    case Qt::Key_2:
    if(!freeze2Flag){
        if(dizzy2flag){
            if(girl->x==1){break;}
            if(map[girl->x-1][girl->y]>0){
                emit activiate2(girl->x-1,girl->y);
            }
            else if(map[girl->x-1][girl->y]<0){
                emit buffEmit(girl->x-1,girl->y);
                who=false;
                who2=false;
                girl->x=girl->x-1;
                changePlace();

            }
            else{
                girl->x=girl->x-1;
                changePlace();
            }
            return;
        }
        else{
            if(girl->x==ROW_COUNT-2){break;}
            if(map[girl->x+1][girl->y]>0){
                emit activiate2(girl->x+1,girl->y);
            }
            else if(map[girl->x+1][girl->y]<0){
                emit buffEmit(girl->x+1,girl->y);
                who=false;
                who2=false;
                girl->x=girl->x+1;
                changePlace();
            }
            else{
                girl->x=girl->x+1;
                changePlace();
            }
            return;
        }
    }
    case Qt::Key_1:
    if(!freeze2Flag){
        if(dizzy2flag){
            if(girl->y==COLUMN_COUNT-2){break;}
            if(map[girl->x][girl->y+1]>0){
                emit activiate2(girl->x,girl->y+1);
            }
            else if(map[girl->x][girl->y+1]<0){
                emit buffEmit(girl->x,girl->y+1);
                who=false;
                who2=false;
                girl->y=girl->y+1;
                changePlace();
            }
            else{
                girl->y=girl->y+1;
                changePlace();
            }
            return;
        }
        else{
            if(girl->y==1){break;}
            if(map[girl->x][girl->y-1]>0){
                emit activiate2(girl->x,girl->y-1);
            }
            else if(map[girl->x][girl->y-1]<0){
                emit buffEmit(girl->x,girl->y-1);
                who=false;
                who2=false;
                girl->y=girl->y-1;
                changePlace();
            }
            else{
                girl->y=girl->y-1;
                changePlace();
            }
            return;
        }
    }
    case Qt::Key_3:
    if(!freeze2Flag){
        if(dizzy2flag){
            if(girl->y==1){break;}
            if(map[girl->x][girl->y-1]>0){
                emit activiate2(girl->x,girl->y-1);
            }
            else if(map[girl->x][girl->y-1]<0){
                emit buffEmit(girl->x,girl->y-1);
                who=false;
                who2=false;
                girl->y=girl->y-1;
                changePlace();
            }
            else{
                girl->y=girl->y-1;
                changePlace();
            }
            return;
        }
        else{
            if(girl->y==COLUMN_COUNT-2){break;}
            if(map[girl->x][girl->y+1]>0){
                emit activiate2(girl->x,girl->y+1);
            }
            else if(map[girl->x][girl->y+1]<0){
                emit buffEmit(girl->x,girl->y+1);
                who=false;
                who2=false;
                girl->y=girl->y+1;
                changePlace();
            }
            else{
                girl->y=girl->y+1;
                changePlace();
            }
            return;
        }
    }

}
}

void DoubleScene::paintEvent(QPaintEvent *event){
    //打印背景图
    QPainter painter(this);
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix.width(),pix.height(),pix);
}




void DoubleScene::initial(){

    //生成的数据必须成对,可以先生成一半，后一半通过前一半得到
    QVector<int>*Exist=new QVector<int>(ROW_COUNT/2*COLUMN_COUNT,0);
    for(int i=0;i<ROW_COUNT/2;++i){
        for(int j=0;j<COLUMN_COUNT;++j){
            if(i==0||i==ROW_COUNT-1||i==1||i==ROW_COUNT-2||j==0||j==COLUMN_COUNT-1||j==1||j==COLUMN_COUNT-2){PixmapData[i][j]=0;continue;}
            else{
                int type=QRandomGenerator::global()->generate()%characterNumber+1;
            //先生成前一半
                PixmapData[i][j]=type;

            //生成后一半
               while(true)
               {
                   //生成后一半的随机数
                   int tempIndex=QRandomGenerator::global()->generate()%(ROW_COUNT*COLUMN_COUNT/2)+
                        ROW_COUNT*COLUMN_COUNT/2;
                   //判断是否出现过 没有出现，则赋值
                   if(tempIndex/COLUMN_COUNT==0||tempIndex/COLUMN_COUNT==ROW_COUNT-1||tempIndex%COLUMN_COUNT==0||tempIndex%COLUMN_COUNT==COLUMN_COUNT-1||tempIndex/COLUMN_COUNT==1||tempIndex/COLUMN_COUNT==ROW_COUNT-2||tempIndex%COLUMN_COUNT==1||tempIndex%COLUMN_COUNT==COLUMN_COUNT-2){PixmapData[tempIndex/COLUMN_COUNT][tempIndex%COLUMN_COUNT]=0;}
                   else if((*Exist)[tempIndex-ROW_COUNT/2*COLUMN_COUNT]==0)
                   {
                       PixmapData[tempIndex/COLUMN_COUNT][tempIndex%COLUMN_COUNT]=type;
                       (*Exist)[tempIndex-ROW_COUNT/2*COLUMN_COUNT]=1;
                       break;
                   }
               }

            }

        }
   }
 }

void DoubleScene::changePlace(){
    gridLayout->removeWidget(boy);
    gridLayout->addWidget(boy,boy->x,boy->y);
    gridLayout->removeWidget(girl);
    gridLayout->addWidget(girl,girl->x,girl->y);

}
void DoubleScene::flushState(int x,int y){
    gridLayout->removeWidget(image[x][y]);
    gridLayout->addWidget(image[x][y],x,y);
}
//判断激活情况
void DoubleScene::judge(int x, int y){
    static bool times=false;

    if(!times){
        image[x][y]->changeIcon();
//        flushState(x,y);
        times=true;
        QTimer *timer=new QTimer;
        timer->start(100);
        connect(timer,&QTimer::timeout,[=](){
            first_xy[0]=x;
            first_xy[1]=y;
            timer->stop();
            timer->deleteLater();
        });

    }
    else {
        if(first_xy[0]==x&&first_xy[1]==y){image[x][y]->changeIcon();/*flushState(x,y);*/times=false;}
        else if(map[x][y]!=map[first_xy[0]][first_xy[1]]){
            image[x][y]->changeIcon();
            QTimer *timer=new QTimer;
            timer->start(100);
            connect(timer,&QTimer::timeout,[=](){
                image[x][y]->changeIcon();
                image[first_xy[0]][first_xy[1]]->changeIcon();
                timer->stop();
                times=false;
                timer->deleteLater();
            });
        }
        else{
            if(inOneLine(x,y,first_xy[0],first_xy[1])){
                map[x][y]=0;
                map[first_xy[0]][first_xy[1]]=0;
                emit hintUpdate();
                times=false;
                draw->oneLineData[0]=x;
                draw->oneLineData[1]=y;
                draw->oneLineData[2]=first_xy[0];
                draw->oneLineData[3]=first_xy[1];
                draw->oneFlag=true;
                draw->update();
                image[x][y]->changeIcon();
                QTimer *timer=new QTimer;
                timer->start(100);
                connect(timer,&QTimer::timeout,[=](){
                    draw->oneFlag=false;
                    draw->update();
                    image[x][y]->clearIcon();
                    image[first_xy[0]][first_xy[1]]->clearIcon();
                    timer->stop();
                    timer->deleteLater();
                });


                times=false;

                emit scoreChange();

            }
            else if(inTwoLine(x,y,first_xy[0],first_xy[1])){
                map[x][y]=0;
                map[first_xy[0]][first_xy[1]]=0;
                emit hintUpdate();
                times=false;
                draw->twoLineData[0]=x;
                draw->twoLineData[1]=y;
                draw->twoLineData[4]=first_xy[0];
                draw->twoLineData[5]=first_xy[1];
                draw->twoFlag=true;
                draw->update();
                image[x][y]->changeIcon();
                QTimer *timer=new QTimer;
                timer->start(100);
                connect(timer,&QTimer::timeout,[=](){
                    draw->twoFlag=false;
                    draw->update();
                    image[x][y]->clearIcon();
                    image[first_xy[0]][first_xy[1]]->clearIcon();
                    timer->stop();
                    timer->deleteLater();
                });


                emit scoreChange();

            }
            else if(inThreeLine(x,y,first_xy[0],first_xy[1])){
                map[x][y]=0;
                map[first_xy[0]][first_xy[1]]=0;
                emit hintUpdate();
                times=false;
                draw->threeLineData[0]=x;
                draw->threeLineData[1]=y;
                draw->threeLineData[6]=first_xy[0];
                draw->threeLineData[7]=first_xy[1];
                draw->threeFlag=true;
                draw->update();
                image[x][y]->changeIcon();
                QTimer *timer=new QTimer;
                timer->start(100);
                connect(timer,&QTimer::timeout,[=](){
                    draw->threeFlag=false;
                    draw->update();
                    image[x][y]->clearIcon();
                    image[first_xy[0]][first_xy[1]]->clearIcon();
                    timer->stop();
                    timer->deleteLater();
                });


                emit scoreChange();

            }
            else{
                image[x][y]->changeIcon();
                QTimer *timer=new QTimer;
                timer->start(100);
                connect(timer,&QTimer::timeout,[=](){
                    image[x][y]->changeIcon();
                    image[first_xy[0]][first_xy[1]]->changeIcon();
                    timer->stop();
                    timer->deleteLater();

                });
                times=false;
            }
            times=false;

        }
    }

}
void DoubleScene::judge2(int x, int y){
    static bool times2=false;

    if(!times2){
        image[x][y]->changeIcon();
        times2=true;
        QTimer *timer=new QTimer;
        timer->start(100);
        connect(timer,&QTimer::timeout,[=](){
            first_xy2[0]=x;
            first_xy2[1]=y;
            timer->stop();
            timer->deleteLater();
        });

    }
    else {
        if(first_xy2[0]==x&&first_xy2[1]==y){image[x][y]->changeIcon();/*flushState(x,y);*/times2=false;}
        else if(map[x][y]!=map[first_xy2[0]][first_xy2[1]]){
            image[x][y]->changeIcon();
            QTimer *timer=new QTimer;
            timer->start(100);
            connect(timer,&QTimer::timeout,[=](){
                image[x][y]->changeIcon();
                image[first_xy2[0]][first_xy2[1]]->changeIcon();
                timer->stop();
                times2=false;
                timer->deleteLater();
            });
        }
        else{
            if(inOneLine2(x,y,first_xy2[0],first_xy2[1])){
                map[x][y]=0;
                map[first_xy2[0]][first_xy2[1]]=0;
                emit hintUpdate();
                times2=false;
                draw2->oneLineData[0]=x;
                draw2->oneLineData[1]=y;
                draw2->oneLineData[2]=first_xy2[0];
                draw2->oneLineData[3]=first_xy2[1];
                draw2->oneFlag=true;
                draw2->update();
                image[x][y]->changeIcon();
                QTimer *timer=new QTimer;
                timer->start(100);
                connect(timer,&QTimer::timeout,[=](){
                    draw2->oneFlag=false;
                    draw2->update();
                    image[x][y]->clearIcon();
                    image[first_xy2[0]][first_xy2[1]]->clearIcon();
                    timer->stop();
                    timer->deleteLater();
                });


                times2=false;

                emit scoreChange2();

            }
            else if(inTwoLine2(x,y,first_xy2[0],first_xy2[1])){
                map[x][y]=0;
                map[first_xy2[0]][first_xy2[1]]=0;
                emit hintUpdate();
                times2=false;
                draw2->twoLineData[0]=x;
                draw2->twoLineData[1]=y;
                draw2->twoLineData[4]=first_xy2[0];
                draw2->twoLineData[5]=first_xy2[1];
                draw2->twoFlag=true;
                draw2->update();
                image[x][y]->changeIcon();
                QTimer *timer=new QTimer;
                timer->start(100);
                connect(timer,&QTimer::timeout,[=](){
                    draw2->twoFlag=false;
                    draw2->update();
                    image[x][y]->clearIcon();
                    image[first_xy2[0]][first_xy2[1]]->clearIcon();
//                    flushState(x,y);
//                    flushState(first_xy[0],first_xy[1]);
                    timer->stop();
                    timer->deleteLater();
                });


                emit scoreChange2();

            }
            else if(inThreeLine2(x,y,first_xy2[0],first_xy2[1])){
                map[x][y]=0;
                map[first_xy2[0]][first_xy2[1]]=0;
                emit hintUpdate();
                times2=false;
                draw2->threeLineData[0]=x;
                draw2->threeLineData[1]=y;
                draw2->threeLineData[6]=first_xy2[0];
                draw2->threeLineData[7]=first_xy2[1];
                draw2->threeFlag=true;
                draw2->update();
                image[x][y]->changeIcon();
                QTimer *timer=new QTimer;
                timer->start(100);
                connect(timer,&QTimer::timeout,[=](){
                    draw2->threeFlag=false;
                    draw2->update();
                    image[x][y]->clearIcon();
                    image[first_xy2[0]][first_xy2[1]]->clearIcon();
                    timer->stop();
                    timer->deleteLater();
                });


                emit scoreChange2();

            }
            else{
                image[x][y]->changeIcon();
                QTimer *timer=new QTimer;
                timer->start(100);
                connect(timer,&QTimer::timeout,[=](){
                    image[x][y]->changeIcon();
                    image[first_xy2[0]][first_xy2[1]]->changeIcon();
                    timer->stop();
                    timer->deleteLater();

                });
                times2=false;
            }
            times2=false;

        }
    }

}
bool DoubleScene::inOneLine(int x,int y,int first_x,int first_y){
    bool empty=true;
    if(x==first_x){
        for(int i=minItem(y,first_y)+1;i<maxItem(y,first_y);i++){
            if(map[x][i]>0){empty=false;break;}
        }
        if(empty){
            //绘制一条线

            return true;
        }

    }
    else if(y==first_y){
        for(int i=minItem(x,first_x)+1;i<maxItem(x,first_x);i++){
            if(map[i][y]>0){empty=false;break;}
        }
        if(empty){

            return true;
        }

    }
    else{return false;}
    return false;
}
bool DoubleScene::inOneLine2(int x,int y,int first_x,int first_y){
    bool empty=true;
    if(x==first_x){
        for(int i=minItem(y,first_y)+1;i<maxItem(y,first_y);i++){
            if(map[x][i]>0){empty=false;break;}
        }
        if(empty){
            //绘制一条线

            return true;
        }

    }
    else if(y==first_y){
        for(int i=minItem(x,first_x)+1;i<maxItem(x,first_x);i++){
            if(map[i][y]>0){empty=false;break;}
        }
        if(empty){

            return true;
        }

    }
    else{return false;}
    return false;
}
bool DoubleScene::inTwoLine(int x,int y,int first_x,int first_y){
    bool flag1=inOneLine(x,y,x,first_y)&&inOneLine(x,first_y,first_x,first_y);
    bool flag2=inOneLine(x,y,first_x,y)&&inOneLine(first_x,y,first_x,first_y);


    if( flag1 && map[x][first_y]==0) {
        //画两条线
        draw->twoLineData[2]=x;
        draw->twoLineData[3]=first_y;
        draw->threeLineData[4]=x;
        draw->threeLineData[5]=first_y;
        if(hintFlag==true){
            drawHint->twoLineData[2]=x;
            drawHint->twoLineData[3]=first_y;
            drawHint->threeLineData[4]=x;
            drawHint->threeLineData[5]=first_y;
        }
        return true;
    }
    else if( flag2 && map[first_x][y]==0 ){
        draw->twoLineData[2]=first_x;
        draw->twoLineData[3]=y;
        draw->threeLineData[4]=first_x;
        draw->threeLineData[5]=y;
        if(hintFlag==true){
            drawHint->twoLineData[2]=first_x;
            drawHint->twoLineData[3]=y;
            drawHint->threeLineData[4]=first_x;
            drawHint->threeLineData[5]=y;
        }
        return true;
    }
    else{return false;}
}
bool DoubleScene::inTwoLine2(int x,int y,int first_x,int first_y){
    bool flag1=inOneLine2(x,y,x,first_y)&&inOneLine2(x,first_y,first_x,first_y);
    bool flag2=inOneLine2(x,y,first_x,y)&&inOneLine2(first_x,y,first_x,first_y);


    if( flag1 && map[x][first_y]==0) {
        //画两条线
        draw2->twoLineData[2]=x;
        draw2->twoLineData[3]=first_y;
        draw2->threeLineData[4]=x;
        draw2->threeLineData[5]=first_y;
        if(hintFlag==true){
            drawHint->twoLineData[2]=x;
            drawHint->twoLineData[3]=first_y;
            drawHint->threeLineData[4]=x;
            drawHint->threeLineData[5]=first_y;
        }
        return true;
    }
    else if( flag2 && map[first_x][y]==0 ){
        draw2->twoLineData[2]=first_x;
        draw2->twoLineData[3]=y;
        draw2->threeLineData[4]=first_x;
        draw2->threeLineData[5]=y;
        if(hintFlag==true){
            drawHint->twoLineData[2]=first_x;
            drawHint->twoLineData[3]=y;
            drawHint->threeLineData[4]=first_x;
            drawHint->threeLineData[5]=y;
        }
        return true;
    }
    else{return false;}
}
bool DoubleScene::inThreeLine(int x, int y, int first_x, int first_y){
    bool flag=false;
    //固定行
    for(int i=1;i<COLUMN_COUNT-1;i++)
    {
        if(i==y){
            continue;
        }
        if(map[x][i]==0){
            flag=inOneLine(x,i,x,y)&&inTwoLine(x,i,first_x,first_y);
            draw->threeLineData[2]=x;
            draw->threeLineData[3]=i;
            if(hintFlag){
                drawHint->threeLineData[2]=x;
                drawHint->threeLineData[3]=i;
            }
        }
        if(flag){
            //画三条线

            return true;
        }
    }
    //固定列
    for(int i=1;i<ROW_COUNT-1;i++)
    {
        if(i==x){
            continue;
        }
        if(map[i][y]==0){
            flag=inOneLine(i,y,x,y)&&inTwoLine(i,y,first_x,first_y);
            draw->threeLineData[2]=i;
            draw->threeLineData[3]=y;
            if(hintFlag==true){
                drawHint->threeLineData[2]=i;
                drawHint->threeLineData[3]=y;
            }
        }
        if(flag)
            //画三条线

            return true;
    }
    return false;
}
bool DoubleScene::inThreeLine2(int x, int y, int first_x, int first_y){
    bool flag=false;
    //固定行
    for(int i=1;i<COLUMN_COUNT-1;i++)
    {
        if(i==y){
            continue;
        }
        if(map[x][i]==0){
            flag=inOneLine2(x,i,x,y)&&inTwoLine2(x,i,first_x,first_y);
            draw2->threeLineData[2]=x;
            draw2->threeLineData[3]=i;
            if(hintFlag){
                drawHint->threeLineData[2]=x;
                drawHint->threeLineData[3]=i;
            }
        }
        if(flag){
            //画三条线

            return true;
        }
    }
    //固定列
    for(int i=1;i<ROW_COUNT-1;i++)
    {
        if(i==x){
            continue;
        }
        if(map[i][y]==0){
            flag=inOneLine2(i,y,x,y)&&inTwoLine2(i,y,first_x,first_y);
            draw2->threeLineData[2]=i;
            draw2->threeLineData[3]=y;
            if(hintFlag==true){
                drawHint->threeLineData[2]=i;
                drawHint->threeLineData[3]=y;
            }
        }
        if(flag)
            //画三条线

            return true;
    }
    return false;
}
int DoubleScene::minItem(int x, int y){
    return (x>y)?y:x;
}
int DoubleScene::maxItem(int x, int y){
    return (x>y)?x:y;
}
bool DoubleScene::oneCheck(int x, int y, int first_x, int first_y){
    bool empty=true;
    if(x==first_x){
        for(int i=minItem(y,first_y)+1;i<maxItem(y,first_y);i++){
            if(map[x][i]>0){empty=false;break;}
        }
        if(empty){
            return true;
        }

    }
    else if(y==first_y){
        for(int i=minItem(x,first_x)+1;i<maxItem(x,first_x);i++){
            if(map[i][y]>0){empty=false;break;}
        }
        if(empty){
            return true;
        }

    }
    else{return false;}
    return false;
}
bool DoubleScene::twoCheck(int x, int y, int first_x, int first_y){
    bool flag1=oneCheck(x,y,x,first_y)&&oneCheck(x,first_y,first_x,first_y);
    bool flag2=oneCheck(x,y,first_x,y)&&oneCheck(first_x,y,first_x,first_y);


    if( flag1 && map[x][first_y]==0) {
        return true;
    }
    else if( flag2 && map[first_x][y]==0 ){
        return true;
    }
    else{return false;}
}
bool DoubleScene::threeCheck(int x, int y, int first_x, int first_y){
    bool flag=false;
    //固定行
    for(int i=1;i<COLUMN_COUNT-1;i++)
    {
        if(i==y){
            continue;
        }
        if(map[x][i]==0){
            flag=oneCheck(x,i,x,y)&&twoCheck(x,i,first_x,first_y);
        }
        if(flag){
            return true;
        }
    }
    //固定列
    for(int i=1;i<ROW_COUNT-1;i++)
    {
        if(i==x){
            continue;
        }
        if(map[i][y]==0){
            flag=oneCheck(i,y,x,y)&&twoCheck(i,y,first_x,first_y);
        }
        if(flag){
            return true;
        }
    }
    return false;
}

#include "startscene.h"
#include "ui_startscene.h"
#include<QMessageBox>
int ROW_COUNT=8;
int COLUMN_COUNT=8;
int characterNumber=10;
StartScene::StartScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartScene)
{
    //设置背景图片与按钮
    ui->setupUi(this);
    this->setWindowTitle("原神连连看");
    this->setWindowIcon(QIcon(":/Image/icon.png"));
    this->setFixedSize(1000,700);
    pix.load(":/Image/background2.png");
    ui->pushButton->resize(300,60);
    ui->pushButton->move(350,300);
    ui->pushButton_2->resize(300,60);
    ui->pushButton_2->move(350,400);
    ui->pushButton_3->resize(300,60);
    ui->pushButton_3->move(350,500);
    QString styleSheet = "QPushButton {  background-image: url(':/Image/background2.png');background-position: center; border: none;color:blue;font-size: 30px }";

    ui->pushButton->setStyleSheet(styleSheet);
    ui->pushButton_2->setStyleSheet(styleSheet);
    ui->pushButton_3->setStyleSheet(styleSheet);
    //设置“退出游戏”
    connect(ui->pushButton_3,&QPushButton::clicked,[=](){
        this->close();
    });
    //设置“开始游戏”
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        a=new ChooseMode;
        this->close();
        a->show();
        connect(a,&ChooseMode::start,[=](){
            a->close();
            this->show();
        });
    });
    //设置“载入游戏”
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        QMessageBox tmp;
            tmp.setText("已载入");
            tmp.exec();

            std::ifstream load("C:\\Users\\86191\\Qt creater\\QLink\\saveGame.txt", std::ios::in);
            load >>saveMode
                 >>ROW_COUNT
                 >>COLUMN_COUNT
                 >>characterNumber;

            map=new int *[ROW_COUNT];
            for(int i=0;i<ROW_COUNT;i++){
                map[i]=new int [COLUMN_COUNT];
            }
            map2=new int *[ROW_COUNT];
            for(int i=0;i<ROW_COUNT;i++){
                map2[i]=new int [COLUMN_COUNT];
            }
            if(saveMode==1){
                load >> i
                     >> x1
                     >> y1
                     >> j;
                qDebug()<<i<<x1<<y1<<j;
                for(int i = 0; i < ROW_COUNT;++i){
                        for(int j = 0; j < COLUMN_COUNT; ++j){
                            load >>map[i][j];
                        }
                }
                 load.close();
                PlayScene *a=new PlayScene(i,x1,y1,j,map);
                a->show();
            }
           else if(saveMode==2){
                    load >> i
                         >> x1
                         >> y1
                         >> j
                         >> x2
                         >> y2
                         >> k;
                    qDebug()<<i<<x1<<y1<<j<<x2<<y2<<k;
                    for(int i = 0; i < ROW_COUNT;++i){
                            for(int j = 0; j < COLUMN_COUNT; ++j){
                                load >>map[i][j];
                            }
                    }

                     load.close();
                     DoubleScene *b=new DoubleScene(i,x1,y1,j,x2,y2,k,map);
                     b->show();
                }


    });

//    musicPlayer = new QMediaPlayer(this);
//    // 设置全景音乐文件的路径
//    QString musicFilePath = "C:\\Users\\86191\\Desktop\\花玲-_-喵酱油-_-宴宁-_-Kinsen-让风告诉你.mp3";
//    // 设置音频文件
//    musicPlayer->setMedia(QUrl::fromLocalFile(musicFilePath));
//    // 开始播放音频
//    musicPlayer->play();
}

void StartScene::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix.width(),pix.height(),pix);
}
StartScene::~StartScene()
{
    delete ui;
}

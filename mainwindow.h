#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include<QTimer>
#include"protagonist1.h"
#include<QPainter>
#include"mythread.h"
#include"imagebutton.h"
#include<QGridLayout>
#include<QMainWindow>
#include"draw.h"
#include<QProgressBar>
#include<QLabel>
#include"timebar.h"
#include<QToolBar>
#include<QPushButton>
#include"endgame.h"
#include<QMessageBox>
#include<fstream>
#include<QMediaPlayer>
#include<QSound>

extern const int IMAGE_WIDH;
extern const int IMAGE_HEIGHT;

//行数和列数
extern int ROW_COUNT;
extern int COLUMN_COUNT;
extern int characterNumber;
QT_BEGIN_NAMESPACE
namespace Ui { class PlayScene; }
QT_END_NAMESPACE

class PlayScene : public QMainWindow
{
    Q_OBJECT

public:

    PlayScene(QWidget *parent = nullptr);
    PlayScene(int ii,int x1,int y1,int jj,int **map);
    ~PlayScene();
    void keyPressEvent(QKeyEvent *event);
//    void keyReleaseEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event) ;
    void initial();//初始化地图
    void judge(int x,int y);
    void flushState(int x,int y);
    bool inOneLine(int x,int y,int first_x,int first_y);//可用一条线连接
    bool inTwoLine(int x,int y,int first_x,int first_y);//可用两条线连接
    bool inThreeLine(int x,int y,int first_x,int first_y);//可用三条线连接
    int maxItem(int x,int y);
    int minItem(int x,int y);
//    void drawOneLine(QPainter &painter);
    void setBuff();//放置buff
    void buffStart(int x,int y);//触发buff
    bool corner(int x,int y);//是否周围有空地
    void changePlace();//人物移动
    void shuffle();
    void hint();
    bool checkRemain();
    void mousePressEvent(QMouseEvent*ev);
    bool oneCheck(int x,int y,int first_x,int first_y);
    bool twoCheck(int x,int y,int first_x,int first_y);
    bool threeCheck(int x,int y,int first_x,int first_y);
    void closeEvent(QCloseEvent *event){
        emit scene_Close();
    }



    static int j;
    static int i;//进度条值
    static QTime leftTime;//时间值
    int **map;//地图
    ImageButton ***image;// 存储二态图片的按钮
    QWidget *windows;    // 主widget
    QGridLayout *gridLayout;    // 主布局
    ImageButton *createImageButton(const QString &str1,const QString &str2);


    int **PixmapData;   //二维数组，用于记录图片的类型
     int first_xy[2];

//实现画画的功能
     Draw *draw;
     Draw *draw2;
     Draw *drawHint;
     QPen linePen;
     bool hintFlag;
//负责记录时间变化
    QLabel *score;//记录分数
    QLabel *label;//记录时间
    QProgressBar *progressBar;//时间进度条
    QPushButton *back;//返回按钮
    QPushButton *pause;
    QPushButton *save;
    ImageButton *buff[6];//道具
    ImageButton *thisBuff;//正在画面中的道具
    int buffRow;//道具出现的位行
    int buffColumn;//道具出现的列
    bool mouseIsActive;//鼠标事件开始标志
    EndGame *endScene;
    Protagonist1 *boy;
    QTimer *timer;
    bool continueFlag;
    bool freeze;
    int saveMode;//保存的模式
    int limitTime;//保存的剩余时间
    bool buffFlag;//是否载入的游戏中有buff
    QMediaPlayer *musicPlayer;
    QPixmap pix ;





private:
    Ui::PlayScene *ui;
signals:
    void activiate(int x,int y);
    void scoreChange();
    void buffEmit(int x,int y);
    void hintUpdate();
    void overFlag();
    void choose();
    void start();
    void scene_Close();
};


#endif // MAINWINDOW_H

//#ifndef PLAYSCENE_H
//#define PLAYSCENE_H

//#include <QWidget>
//#include<QTimer>
//#include"protagonist1.h"
//#include<QPainter>
//#include"mythread.h"
//#include"imagebutton.h"
//#include<QGridLayout>
//#include<QMainWindow>
//#include"draw.h"
//const int IMAGE_WIDHT=80;
//const int IMAGE_HEIGHT=80;

////行数和列数
//const int ROW_COUNT=14;
//const int COLUMN_COUNT=14;
//QT_BEGIN_NAMESPACE
//namespace Ui { class PlayScene; }
//QT_END_NAMESPACE

//class PlayScene : public QMainWindow
//{
//    Q_OBJECT

//public:
//    Protagonist1 *boy;
//    QTimer *timer;
//    bool keypressflag;
//    int keyflag;
//    PlayScene(QWidget *parent = nullptr);
//    ~PlayScene();
//    void keyPressEvent(QKeyEvent *event);
////    void keyReleaseEvent(QKeyEvent *event);
//    void paintEvent(QPaintEvent *event) ;
//    void initial();
//    void judge(int x,int y);
//    void flushState(int x,int y);
//    bool inOneLine(int x,int y,int first_x,int first_y);
//    bool inTwoLine(int x,int y,int first_x,int first_y);
//    bool inThreeLine(int x,int y,int first_x,int first_y);
//    int maxItem(int x,int y);
//    int minItem(int x,int y);
////    void drawOneLine(QPainter &painter);


//    int map[ROW_COUNT][COLUMN_COUNT];
//    ImageButton *image[ROW_COUNT][COLUMN_COUNT];// 存储二态图片的按钮
//    QWidget *windows;    // 主widget
//    QGridLayout *gridLayout;    // 主布局
//    ImageButton *createImageButton(const QString &str1,const QString &str2);
//    bool showGameArea = false;
//    void changePlace();
////    QVector<QVector<bool>>* isEmpty;
////    int collisionCount;     //鼠标点击次数
////    int firstCollisionX;    //点击时的x坐标
////    int firstCollisionY;    //点击时的Y坐标
//    int PixmapData[ROW_COUNT][COLUMN_COUNT];   //二维数组，用于记录图片的类型
////    int lab_data = 0;       //lad的信号数字显示
////    bool win =false;
//     int first_xy[2];
//     Draw *draw;
//     Draw *draw2;
//     QPen linePen;

////     bool oneFlag;
////     bool twoFlag;
////     bool threeFlag;
////     int drawOne[4];//x y x y

//private:
//    Ui::PlayScene *ui;
//signals:
//    void activiate(int x,int y);

//};
//#endif // PLAYSCENE_H

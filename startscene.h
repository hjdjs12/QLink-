#ifndef STARTSCENE_H
#define STARTSCENE_H

#include <QMainWindow>
#include<QWidget>
#include"choosemode.h"
#include"doublescene.h"
#include<fstream>
#include<QMediaPlayer>


namespace Ui {
class StartScene;
}

class StartScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartScene(QWidget *parent = nullptr);
    ~StartScene();
    void paintEvent(QPaintEvent *event) ;
    ChooseMode *a;
    int saveMode;
    int i;//时间
    int j;//得分
    int k;//得分2
    //第一个角色的位置
    int x1;
    int y1;
    //第二个角色的位置
    int x2;
    int y2;
    int **map;
    int **map2;
    QMediaPlayer* musicPlayer;
    QPixmap pix;



private:
    Ui::StartScene *ui;
};

#endif // STARTSCENE_H

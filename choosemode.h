#ifndef CHOOSEMODE_H
#define CHOOSEMODE_H

#include <QMainWindow>
#include <QPushButton>
#include<QPainter>
#include<QLabel>
#include"mainwindow.h"
#include<QWidget>
#include"doublescene.h"
#include<QSpinBox>

namespace Ui {
class ChooseMode;
}

class ChooseMode : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChooseMode(QWidget *parent = nullptr);
    ~ChooseMode();
    QPushButton *singleOne;
    QPushButton *doubleTwo;
    QLabel *information;
    void paintEvent(QPaintEvent*ev);
    PlayScene *w;
    DoubleScene *q;
    //设置行列数
    QSpinBox *row;
    QSpinBox *column;
    QLabel *rst;
    QLabel *cst;
    QSpinBox *charcal;
    QLabel *charcalst;
    QPixmap pix;



private:
    Ui::ChooseMode *ui;
signals:
    void start();
};

#endif // CHOOSEMODE_H

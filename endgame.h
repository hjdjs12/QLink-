#ifndef ENDGAME_H
#define ENDGAME_H

#include <QMainWindow>
#include<QWidget>
#include<QPainter>
#include<QPushButton>
#include<QLabel>
#include<QDebug>


class EndGame : public QMainWindow
{
    Q_OBJECT
public:
    explicit EndGame(QWidget *parent = nullptr);
    ~EndGame(){};
     void paintEvent(QPaintEvent*event);
    QPushButton *yes;
    QPushButton *no;
    QLabel *information;
    QPixmap pix;


signals:
     void choose();
};

#endif // ENDGAME_H

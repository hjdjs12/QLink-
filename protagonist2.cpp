#include "protagonist2.h"
#include<QDebug>
#include<QPixmap>
#include<QPainter>
#include<QKeyEvent>
Protagonist2::Protagonist2(QString path)
{
    setDown(false);
    setFocusPolicy(Qt::NoFocus);
    pix.load(path);
    pix=pix.scaled(80,80);
    this->setFixedSize(80, 80);
    this->setIcon(pix);
    this->setIconSize(QSize(this->width(),this->height()));
    this->setStyleSheet("border:1px rgba(237, 241, 255, 100);"
                          "border-radius:8px;"
                          "padding:0px;"
                          "border-style: outset;");

}
Protagonist2::Protagonist2(QString path,int xx,int yy)
{
    setDown(false);
    setFocusPolicy(Qt::NoFocus);
    pix.load(path);
    x=xx;
    y=yy;
    pix=pix.scaled(80,80);
    this->setFixedSize(80, 80);
    this->setIcon(pix);
    this->setIconSize(QSize(this->width(),this->height()));
    this->setStyleSheet("border:1px rgba(237, 241, 255, 100);"
                          "border-radius:8px;"
                          "padding:0px;"
                          "border-style: outset;");

}

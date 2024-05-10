#ifndef DRAW_H
#define DRAW_H
#include<QPainter>
#include <QWidget>
class Draw : public QWidget
{
    Q_OBJECT
public:
    Draw(QColor b,QWidget *parent = nullptr) : QWidget(parent) {
        oneFlag=false;
        twoFlag=false;
        threeFlag=false;
        a=b;
    };
    void paintEvent(QPaintEvent *event) override {
            Q_UNUSED(event);
            linePen.setColor(a);
            linePen.setWidth(10);
            QPainter painter(this);
            painter.setPen(linePen);


            // 在这里绘制你想要的图形
            drawOneLine(painter);
            drawTwoLine(painter);
            drawThreeLine(painter);
        }
    void drawOneLine(QPainter &painter);
    void drawTwoLine(QPainter &painter);
    void drawThreeLine(QPainter &painter);
    bool oneFlag;
    bool twoFlag;
    bool threeFlag;
    int oneLineData[4];
    int twoLineData[6];
    int threeLineData[8];
    QPen linePen;
    QColor a;
signals:

};

#endif // DRAW_H

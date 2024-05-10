#ifndef PROTAGONIST1_H
#define PROTAGONIST1_H

#include <QWidget>
#include<QToolButton>

class Protagonist1 : public QToolButton
{
    Q_OBJECT
public:
    Protagonist1(QString path);
    Protagonist1(QString path,int x,int y);
    QPixmap pix;
    int x;
    int y;

signals:

};

#endif // PROTAGONIST1_H

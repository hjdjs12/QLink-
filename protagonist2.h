#ifndef PROTAGONIST2_H
#define PROTAGONIST2_H

#include <QObject>
#include <QWidget>
#include<QToolButton>

class Protagonist2 : public QToolButton
{
    Q_OBJECT
public:
    Protagonist2(QString path);
    Protagonist2(QString path,int xx,int yy);
    QPixmap pix;
    int x;
    int y;
};

#endif // PROTAGONIST2_H

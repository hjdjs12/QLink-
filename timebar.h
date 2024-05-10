#ifndef TIMEBAR_H
#define TIMEBAR_H

#include <QWidget>
#include<QTimer>
#include<QTime>
namespace Ui {
class TimeBar;
}

class TimeBar : public QWidget
{
    Q_OBJECT

public:
    explicit TimeBar(QWidget *parent = nullptr);
    ~TimeBar();
    QTimer *timer;

private:
    Ui::TimeBar *ui;
};

#endif // TIMEBAR_H

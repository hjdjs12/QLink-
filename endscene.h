#ifndef ENDSCENE_H
#define ENDSCENE_H
#include <QMainWindow>
#include<QWidget>
#include<QPainter>
#include<QPushButton>
#include<QLabel>
#include<QDebug>
//#include"choosemode.h"
namespace Ui {
class EndScene;
}

class EndScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit EndScene(QWidget *parent = nullptr);
    ~EndScene();
    void paintEvent(QPaintEvent*event);



    QPushButton *yes;
    QPushButton *no;
    QLabel *information;
//    ChooseMode *b;

private:
    Ui::EndScene *ui;
signals:
    void game();
    void choose();
};
#endif // ENDSCENE_H

#include "endscene.h"
#include "ui_endscene.h"

EndScene::EndScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EndScene)
{
    ui->setupUi(this);
    this->setFixedSize(1000,500);
    information=new QLabel();
    information->setParent(this);
    yes=new QPushButton("Yes",this);
    no=new QPushButton("No",this);
    yes->resize(150,50);
    no->resize(150,50);
    QString style1 = "QPushButton {  color:green;font-size: 30px }";
    yes->setStyleSheet(style1);
    no->setStyleSheet(style1);
    yes->move(300,300);
    no->move(530,300);
    QString style2 = "QLabel {  color:white;font-size: 40px }";
    information->setStyleSheet(style2);
    information->setText("游戏结束，是否再来一局？");
    information->move(300,-150);
    connect(yes,&QPushButton::clicked,[=](){
//       this->close();
        emit choose();

    });
    connect(no,&QPushButton::clicked,[=](){
        this->close();
    });




}

void EndScene::paintEvent(QPaintEvent *event){
        QPainter painter(this);
        QPixmap pix;
        pix.load(":/Image/background5.png");
        pix=pix.scaled(this->width(),this->height());
        painter.drawPixmap(0,0,pix.width(),pix.height(),pix);

}

EndScene::~EndScene()
{
    delete ui;
}

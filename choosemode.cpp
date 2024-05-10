#include "choosemode.h"
#include "ui_choosemode.h"

ChooseMode::ChooseMode(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChooseMode)
{

    ui->setupUi(this);
    this->setWindowTitle("原神连连看");
    this->setWindowIcon(QIcon(":/Image/icon.png"));
    this->setFixedSize(1200,600);

    pix.load(":/Image/background6.png");//加载图片

    //设置单人模式和双人模式的按钮
    singleOne=new QPushButton("单人模式",this);
    doubleTwo=new QPushButton("双人模式",this);
    singleOne->resize(150,50);
    doubleTwo->resize(150,50);
    QString style1 = "QPushButton {  color:green;font-size: 30px ;;}";
    singleOne->setStyleSheet(style1);
    doubleTwo->setStyleSheet(style1);
    singleOne->move(450,400);
    doubleTwo->move(650,400);

    //设置单双人选择界面的文字介绍
    QString style2 = "QLabel {  color:yellow;font-size: 40px;}";
    information=new QLabel();
    information->setParent(this);
    information->setStyleSheet(style2);
    information->setText("请选择关卡类型");
    information->move(470,-150);

    //设置调节行列大小的Spinbox
    QFont font;
    font.setPointSize(16); // 设置字体大小为16
    row=new QSpinBox(this);
    row->setRange(8,14);
    row->setSingleStep(2);
    row->move(430,200);
    row->resize(150,30);
    row->setFont(font);
    row->setStyleSheet("QSpinBox { background-color: yellow; }");

    column=new QSpinBox(this);
    column->setRange(8,16);
    column->setSingleStep(2);
    column->move(770,200);
    column->resize(150,30);
    column->setFont(font);
    column->setStyleSheet("QSpinBox{background-color:yellow;}");


    //显示调节行列的内容
    rst=new QLabel(this);
    rst->resize(150,30);
    QString style3 = "QLabel {  color:yellow;font-size: 30px }";
    rst->setStyleSheet(style3);
    rst->setText("请设置行数");
    rst->move(280,200);

    cst=new QLabel(this);
    cst->resize(150,30);
    cst->setStyleSheet(style3);
    cst->setText("请设置列数");
    cst->move(620,200);

    ROW_COUNT=row->value();
    COLUMN_COUNT=column->value();
    connect(row, QOverload<int>::of(&QSpinBox::valueChanged), [=]() {
        ROW_COUNT = row->value();
    });
    connect(column, QOverload<int>::of(&QSpinBox::valueChanged), [=]() {
        COLUMN_COUNT = column->value();
    });

    //设置调节图案数量的Spinbox
    charcal=new QSpinBox(this);
    charcal->setRange(10,26);
    charcal->setSingleStep(1);
    charcal->move(640,300);
    charcal->resize(150,30);
    charcal->setFont(font);
    charcal->setStyleSheet("QSpinBox { background-color: yellow; }");

    //显示调节图案数量的内容
    charcalst=new QLabel(this);
    charcalst->resize(190,30);
    charcalst->setStyleSheet(style3);
    charcalst->setText("请设置图案数");
    charcalst->move(450,300);
    characterNumber=charcal->value();
    connect(charcal, QOverload<int>::of(&QSpinBox::valueChanged), [=]() {
        characterNumber = charcal->value();
    });


    connect(singleOne,&QPushButton::clicked,[=](){
       this->hide();
       w=new PlayScene;
       w->i=300;
       w->leftTime.setHMS(0,5,0);
       w->j=0;
       w->show();
       connect(w,&PlayScene::choose,[=](){
//           w->close();
//           delete w;
           this->show();
       });
       connect(w,&PlayScene::start,[=](){
           emit start();
           this->close();
       });
    });
    connect(doubleTwo,&QPushButton::clicked,[=](){
       this->hide();
       q=new DoubleScene;
       q->i=300;
       q->leftTime.setHMS(0,5,0);
       q->j=0;
       q->show();
       connect(q,&DoubleScene::choose,[=](){
//           w->close();
//           delete w;
           this->show();
       });
       connect(q,&DoubleScene::start,[=](){
           emit start();
           this->close();
       });
    });




}

void ChooseMode::paintEvent(QPaintEvent *event){
        QPainter painter(this);
        pix=pix.scaled(this->width(),this->height());
        painter.drawPixmap(0,0,pix.width(),pix.height(),pix);

}

ChooseMode::~ChooseMode()
{
    delete ui;
}

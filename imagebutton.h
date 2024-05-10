#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H
#include <QToolButton>
#include <QIcon>
#include <QWidget>
class ImageButton:public QToolButton
{
    Q_OBJECT

private:
    QIcon normalState;    // 普通状态
    QIcon activeState;    // 激活状态
    QIcon clearState;    // 空白状态
    bool currentIcon;    //当前为普通态还是激活态


public:
    QString normalPath;
    QString activePath;
    ImageButton();
    ~ImageButton(){}
    // 切换激活态和普通态
    void changeIcon();
    // 初始设置按钮
    void setButtonIcon(QIcon normal, QIcon active);
    // 消除图片后清空按钮
    void clearIcon();
    void exchangeIcon(ImageButton *);
    void flushIcon();
};

#endif // IMAGEBUTTON_H


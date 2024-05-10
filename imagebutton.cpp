#include "imagebutton.h"

ImageButton::ImageButton()
{
    setDown(false);
    setFocusPolicy(Qt::NoFocus);
    // 空白图片
    QPixmap map(":/Image/blank.png");
    clearState = QIcon(map);
}
//两种状态切换
void ImageButton::changeIcon() {
    if(currentIcon) {
        setIcon(normalState);
        currentIcon = 0;
    } else {
        setIcon(activeState);
        currentIcon = 1;
    }
}
//初始化图像
void ImageButton::setButtonIcon(QIcon normal, QIcon active)
{
    normalState = normal;
    activeState = active;
    setIcon(normal);
    currentIcon = 0;
}

//设置成空白控件
void ImageButton::clearIcon() {
    setIcon(clearState);
}

void ImageButton::exchangeIcon(ImageButton *m)
{
    QIcon tmp1 = activeState;
    QIcon tmp2 = normalState;
    activeState = m->activeState;
    normalState = m->normalState;
    m->activeState = tmp1;
    m->normalState = tmp2;
}

void ImageButton::flushIcon()
{
    setIcon(normalState);
}

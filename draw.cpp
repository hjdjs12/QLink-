#include "draw.h"
void Draw::drawOneLine(QPainter &painter){
    if(oneFlag){
        int first_x=(oneLineData[0]+1)*80+oneLineData[0]*10-40;
        int first_y=(oneLineData[1]+1)*80+oneLineData[1]*10-40;
        int second_x=(oneLineData[2]+1)*80+oneLineData[2]*10-40;
        int second_y=(oneLineData[3]+1)*80+oneLineData[3]*10-40;
        painter.drawLine(first_y,first_x,second_y,second_x);
    }
}
void Draw::drawTwoLine(QPainter &painter){
    if(twoFlag){
        int first_x=(twoLineData[0]+1)*80+twoLineData[0]*10-40;
        int first_y=(twoLineData[1]+1)*80+twoLineData[1]*10-40;
        int second_x=(twoLineData[2]+1)*80+twoLineData[2]*10-40;
        int second_y=(twoLineData[3]+1)*80+twoLineData[3]*10-40;
        int third_x=(twoLineData[4]+1)*80+twoLineData[4]*10-40;
        int third_y=(twoLineData[5]+1)*80+twoLineData[5]*10-40;
        painter.drawLine(first_y,first_x,second_y,second_x);
        painter.drawLine(second_y,second_x,third_y,third_x);
    }
}
void Draw::drawThreeLine(QPainter &painter){
    if(threeFlag){
        int first_x=(threeLineData[0]+1)*80+threeLineData[0]*10-40;
        int first_y=(threeLineData[1]+1)*80+threeLineData[1]*10-40;
        int second_x=(threeLineData[2]+1)*80+threeLineData[2]*10-40;
        int second_y=(threeLineData[3]+1)*80+threeLineData[3]*10-40;
        int third_x=(threeLineData[4]+1)*80+threeLineData[4]*10-40;
        int third_y=(threeLineData[5]+1)*80+threeLineData[5]*10-40;
        int fourth_x=(threeLineData[6]+1)*80+threeLineData[6]*10-40;
        int fourth_y=(threeLineData[7]+1)*80+threeLineData[7]*10-40;
        painter.drawLine(first_y,first_x,second_y,second_x);
        painter.drawLine(second_y,second_x,third_y,third_x);
        painter.drawLine(third_y,third_x,fourth_y,fourth_x);
    }
}

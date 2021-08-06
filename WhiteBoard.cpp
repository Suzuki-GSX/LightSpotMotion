#include "WhiteBoard.h"
#include <QDebug>
WhiteBoard::WhiteBoard(QWidget *parent) : QWidget(parent)
{

}

void WhiteBoard::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    int remainder_5;//画布除5的余数  白板的边长需要是5的倍数
    if(this->width()>this->height())//画布区域宽比长大 选小的边为白板的边长
    {
        remainder_5 = this->height()%5;//画布高除5的余数
        BoartLength = this->height()-remainder_5;
    }
    else
    {
        remainder_5 = this->width()%5;//画布宽除5的余数
        BoartLength = this->width()-remainder_5;
    }
    mult_500 = (float)BoartLength/500.0;//白板长度是500的几倍(一位小数)
    num_5 = BoartLength/5;//边长 = num_5 * 5
    originX = (int)((this->width()-BoartLength)/2);//原点X
    originY = (int)((this->height()-BoartLength)/2);//原点Y
    float SpotSize = (int)(mult_500*13.0);//点大小
    QBrush brush=painter.brush();
    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(originX, originY,BoartLength,BoartLength);//画白色板子

    painter.setPen(Qt::gray);
    for(qint8 i=0;i<=5;i++)//画网格
    {
        painter.drawText(originX+(i*num_5),originY+BoartLength,QString("%1").arg((int)(i*10)));//画X轴坐标数值
        painter.drawLine(originX+(i*num_5),originY,originX+(i*num_5),originY+BoartLength);//画竖线
        painter.drawText(originX,((5-i)*num_5)+originY,QString("%1").arg((int)(i*10)));//画Y轴坐标数值
        painter.drawLine(originX,(i*num_5)+originY,originX+BoartLength,(i*num_5)+originY);//画横线
    }

    brush.setColor(Qt::red);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);//绘画实时激光点
    quint16 RedSpotX = (quint16)(((float)SpotCoorX*mult_500)+originX);
    quint16 RedSpotY = (quint16)((BoartLength-((float)SpotCoorY*mult_500))+originY);
    if(originX>=8) RedSpotX -= 8;
    if(originY>=8) RedSpotY -= 8;
    painter.drawEllipse(RedSpotX,RedSpotY,SpotSize,SpotSize);
    painter.setPen(Qt::gray);//绘画实时激光点
    painter.drawText(RedSpotX-5,RedSpotY,QStringLiteral("激光点"));

    float spotX,spotY;//点显示的坐标
    float Radius;//第三题半径
    bool T1flag = false;//T1斜率 flag
    switch (spotState) {/////////////////////////////////////////////////////////
    case T1Slope://T1斜率
        T1flag = true;
    case T1Text: //通过LineEdit输入坐标改变
    case T1Confirm://第一题确定
        painter.setBrush(Qt::yellow);//黄色
        spotX = (((float)T1SpotX*mult_500)+originX-8);
        spotY = ((BoartLength-((float)T1SpotY*mult_500))+originY-8);
        painter.drawEllipse(spotX,spotY,SpotSize,SpotSize);//
        painter.setPen(Qt::gray);
        painter.drawText(spotX,spotY,QStringLiteral("目标点"));
        if(T1flag)
            painter.drawLine(RedSpotX+(SpotSize/2),RedSpotY+(SpotSize/2),spotX+(SpotSize/2),spotY+(SpotSize/2));//画距离线
        break;
    case T1Motion: //第一题点跟随鼠标移动
        painter.setBrush(Qt::yellow);//黄色
        painter.drawEllipse(mouseMoveX-8,mouseMoveY-8,SpotSize,SpotSize);//
        painter.setPen(Qt::gray);
        painter.drawText(mouseMoveX-8,mouseMoveY-8,QStringLiteral("目标点"));
        T1SpotX = (quint16)((float)(mouseMoveX-originX)/mult_500);
        T1SpotY = (quint16)((float)(BoartLength-(mouseMoveY-originY))/mult_500);
        emit dataUpdate();//数据更新信号
        break;
////第二题///////////////////////////////////////////////////////////////第二题
    case T2Spot1Motion://第二题起点1点跟随鼠标移动
        painter.setBrush(Qt::blue);//蓝色
        painter.drawEllipse(mouseMoveX-8,mouseMoveY-8,SpotSize,SpotSize);//
        painter.setPen(Qt::gray);
        painter.drawText(mouseMoveX-8,mouseMoveY-8,QStringLiteral("起点"));
        T2Spot1X = (quint16)((float)(mouseMoveX-originX)/mult_500);
        T2Spot1Y = (quint16)((float)(BoartLength-(mouseMoveY-originY))/mult_500);
        emit dataUpdate();//数据更新信号
        painter.setBrush(Qt::green);//绿色终点
        spotX = (((float)T2Spot2X*mult_500)+originX-8);
        spotY = ((BoartLength-((float)T2Spot2Y*mult_500))+originY-8);
        painter.drawEllipse(spotX,spotY,SpotSize,SpotSize);
        painter.setPen(Qt::gray);
        painter.drawText(spotX,spotY,QStringLiteral("终点"));
        break;
    case T2Spot2Motion://第二题终点2点跟随鼠标移动
        painter.setBrush(Qt::green);//蓝色
        painter.drawEllipse(mouseMoveX-8,mouseMoveY-8,SpotSize,SpotSize);//
        painter.setPen(Qt::gray);
        painter.drawText(mouseMoveX-8,mouseMoveY-8,QStringLiteral("终点"));
        T2Spot2X = (quint16)((float)(mouseMoveX-originX)/mult_500);
        T2Spot2Y = (quint16)((float)(BoartLength-(mouseMoveY-originY))/mult_500);
        emit dataUpdate();//数据更新信号
        painter.setBrush(Qt::blue);//蓝色起点
        spotX = (((float)T2Spot1X*mult_500)+originX-8);
        spotY = ((BoartLength-((float)T2Spot1Y*mult_500))+originY-8);
        painter.drawEllipse(spotX,spotY,SpotSize,SpotSize);
        painter.setPen(Qt::gray);
        painter.drawText(spotX,spotY,QStringLiteral("起点"));
        break;
    case T2Text://第二题通过LineEdit输入坐标改变
        painter.setBrush(Qt::blue);//蓝色起点
        spotX = (((float)T2Spot1X*mult_500)+originX-8);
        spotY = ((BoartLength-((float)T2Spot1Y*mult_500))+originY-8);
        painter.drawEllipse(spotX,spotY,SpotSize,SpotSize);
        painter.setPen(Qt::gray);
        painter.drawText(spotX,spotY,QStringLiteral("起点"));

        painter.setBrush(Qt::green);//绿色终点
        spotX = (((float)T2Spot2X*mult_500)+originX-8);
        spotY = ((BoartLength-((float)T2Spot2Y*mult_500))+originY-8);
        painter.drawEllipse(spotX,spotY,SpotSize,SpotSize);
        painter.setPen(Qt::gray);
        painter.drawText(spotX,spotY,QStringLiteral("终点"));
        break;
////T3画圆////////////////////////////////////////////////T3画圆
    case T3Text:
    case T3Confirm:
        painter.setBrush(QColor("#ff9500"));//橙色圆心
        spotX = (((float)T3CircleSpotX*mult_500)+originX);
        spotY = ((BoartLength-((float)T3CircleSpotY*mult_500))+originY);
        painter.drawEllipse(spotX-4,spotY-4,8,8);
        painter.setPen(Qt::gray);
        painter.drawText(spotX,spotY,QStringLiteral("圆心"));

        Radius = (float)T3Radius*mult_500;
        painter.setBrush(Qt::NoBrush);//橙色圆心
        painter.setPen(QColor("#ff9500"));//橙色圆
        painter.drawEllipse(spotX-Radius,spotY-Radius,Radius*2,Radius*2);
        break;
    case T3Motion:
        painter.setBrush(QColor("#ff9500"));//橙色圆心
        painter.drawEllipse(mouseMoveX-4,mouseMoveY-4,8,8);
        painter.setPen(Qt::gray);
        painter.drawText(mouseMoveX,mouseMoveY,QStringLiteral("圆心"));
        T3CircleSpotX = (quint16)((float)(mouseMoveX-originX)/mult_500);
        T3CircleSpotY = (quint16)((float)(BoartLength-(mouseMoveY-originY))/mult_500);
        emit dataUpdate();//数据更新信号
        Radius = (float)T3Radius*mult_500;
        painter.setBrush(Qt::NoBrush);//橙色圆心
        painter.setPen(QColor("#ff9500"));//橙色圆
        painter.drawEllipse((float)mouseMoveX-Radius,(float)mouseMoveY-Radius,Radius*2,Radius*2);
        break;
    default:  break;
    }
}

void WhiteBoard::mouseMoveEvent(QMouseEvent *event)//鼠标移动事件
{
    mouseMoveX = event->x();
    mouseMoveY = event->y();
    if(spotState == T3Motion)
    {
        float r = T3Radius*mult_500;
        float minX = originX+r;
        float maxX = originX+BoartLength-r;
        float minY = originY+r;
        float maxY = originY+BoartLength-r;
        if((mouseMoveX<minX)||(mouseMoveX>maxX)||
           (mouseMoveY<minY)||(mouseMoveY>maxY))
            return;
    }
    if(mouseMoveX<originX) mouseMoveX = originX;
    if(mouseMoveY<originY) mouseMoveY = originY;
    if(mouseMoveX>originX+BoartLength) mouseMoveX = originX+BoartLength;
    if(mouseMoveY>originY+BoartLength) mouseMoveY = originY+BoartLength;

    this->update();//更新 重绘
}

void WhiteBoard::mouseReleaseEvent(QMouseEvent* event)//鼠标点击事件
{
    mouseClickX = event->x();
    mouseClickY = event->y();
    if((mouseClickX<originX)|(mouseClickY<originY)
        |(mouseClickX>originX+BoartLength)
        |(mouseClickY>originY+BoartLength)) return;
    this->setMouseTracking(false);
    float  r,minX,maxX,minY,maxY;
    switch (spotState) {//第一题的目标点
    case T1Motion://第一题确定
        spotState = T1Confirm;
        T1SpotX = (quint16)((float)(mouseClickX-originX)/mult_500);
        T1SpotY = (quint16)((float)(BoartLength-(mouseClickY-originY))/mult_500);
        emit dataUpdate();
        break;
    case T2Spot1Motion://第二题起点1确定
        spotState = T2Spot1Confirm;
        T2Spot1X = (quint16)((float)(mouseClickX-originX)/mult_500);
        T2Spot1Y = (quint16)((float)(BoartLength-(mouseClickY-originY))/mult_500);
        emit dataUpdate();
        break;
    case T2Spot2Motion://第二题终点2确定
        spotState = T2Spot2Confirm;
        T2Spot2X = (quint16)((float)(mouseClickX-originX)/mult_500);
        T2Spot2Y = (quint16)((float)(BoartLength-(mouseClickY-originY))/mult_500);
        emit dataUpdate();
        break;
    case T3Motion://第三题圆心确定
        spotState = T3Confirm;
        r = T3Radius*mult_500;
        minX = originX+r;
        maxX = originX+BoartLength-r;
        minY = originY+r;
        maxY = originY+BoartLength-r;
        if((mouseClickX<minX))
            T3CircleSpotX = (quint16)(r/mult_500);
        else if((mouseClickX>maxX))
            T3CircleSpotX = (quint16)((float)(BoartLength-r)/mult_500);
        else
            T3CircleSpotX = (quint16)((float)(mouseClickX-originX)/mult_500);

        if((mouseClickY<minY))
            T3CircleSpotY = (quint16)((float)BoartLength-r/mult_500);
        else if((mouseClickY>maxY))
            T3CircleSpotY = (quint16)(r/mult_500);
        else
            T3CircleSpotY = (quint16)((float)(BoartLength-(mouseClickY-originY))/mult_500);
        emit dataUpdate();
        break;
    default: return;
    }
    this->update();//更新 重绘
}



















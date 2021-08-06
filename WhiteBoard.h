#ifndef WHITEBOARD_H
#define WHITEBOARD_H
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
class WhiteBoard : public QWidget
{
    Q_OBJECT
public:
    WhiteBoard(QWidget *parent=nullptr);
    virtual void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    int mouseMoveX,mouseMoveY;//鼠标移动坐标
    int mouseClickX,mouseClickY;//鼠标点击坐标

    quint16 BoartLength=0;//白板边长
    qint16 SpotCoorX=0, SpotCoorY=0;//光点坐标
    float mult_500;//白板实际长度是50的几倍(一位小数)
    quint8 num_5;//边长有几个5
    int originX=0,originY=0;//界面白板原点 左上角
    enum SpotState{No, T1Text, T1Motion, T1Slope, T1Confirm,
                   T2Text, T2Spot1Motion, T2Spot2Motion, T2Spot1Confirm, T2Spot2Confirm,
                   T3Text, T3Motion, T3Confirm,
                    Debug, Calibration};//不显示  正在移动选坐标   已经确定点
    SpotState spotState=No;//T1的目标点状态
    quint16 T1SpotX=300,T1SpotY=300;//T1目标点坐标
    quint16 T2Spot1X=50,T2Spot1Y=50;//T2目标点1坐标
    quint16 T2Spot2X=300,T2Spot2Y=300;//T2目标点2坐标
    quint16 T3CircleSpotX=200,T3CircleSpotY=200, T3Radius=100;//T3圆点坐标 半径
signals:
    void dataUpdate();//数据更新
};


#endif // WHITEBOARD_H





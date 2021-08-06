#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "ui_MainWindow.h"
#include "WhiteBoard.h"
#include <stdio.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void DataUpdate();//数据更新槽函数
    void on_tabWidget_currentChanged(int index);//题目改变
    void on_StartBtn_clicked(bool checked);//开始运行
    void on_OriginBtn_clicked();//回原点
    void on_SpeedScrollBar_valueChanged(int value);//速度值改变
    void timerOut();//定时实践到
/*串口*****/
    void serialPortReadData();//串口数据接收
    void on_SendBtn_clicked();//数据发送
    void on_ReceiveHexCheckBox_stateChanged(int arg1);//接收数据显示框十六进制显示改变
    void on_OpenBtn_clicked();//打开串口
    void on_BaudComboBox_currentIndexChanged(const QString &arg1);//波特率改变
    void on_StopBitComboBox_currentIndexChanged(int index);//停止位改变
    void on_DataBitComboBox_currentIndexChanged(int index);//数据位改变
    void on_CheckComboBox_currentIndexChanged(int index);//校验位改变
    void on_RefreshBtn_clicked();//刷新
    void on_ReceiveClearBtn_clicked();//清除接收
/*串口*****/
/*T1*****/
    void on_T1ConfirmBtn_clicked();//确定
    void on_T1SetSpotBtn_clicked();//设点
    void on_T1SlopeRadioBtn_clicked(bool checked);//斜率
    void on_T1AimsRadioBtn_clicked(bool checked);//目标点
    void on_T1AimsXLineEdit_textChanged(const QString &arg1);//X
    void on_T1AimsYLineEdit_textChanged(const QString &arg1);//Y
    void on_T1SlopeLineEdit_textChanged(const QString &arg1);//斜率输入
    void on_T1DistanceLineEdit_textChanged(const QString &arg1);//距离输入
//*T1*****/
/*T2*****/
    void on_T2SetSpot1Btn_clicked();//确定
    void on_T2SetSpot2Btn_clicked();//设点1
    void on_T2X1LineEdit_textChanged(const QString &arg1);//设点2
    void on_T2Y1LineEdit_textChanged(const QString &arg1);//点1 X改变
    void on_T2X2LineEdit_textChanged(const QString &arg1);//点1 Y改变
    void on_T2Y2LineEdit_textEdited(const QString &arg1);//点2 X改变
    void on_T2ConfirmBtn_clicked();//点2 Y改变

/*T2*****/
/*T3*****/
    void on_T3SetCircleSpotBtn_clicked();//确定
    void on_T3XLineEdit_textChanged(const QString &arg1);//设圆心
    void on_T3YLineEdit_textChanged(const QString &arg1);//X
    void on_T3RadiusLineEdit_textChanged(const QString &arg1);//Y
    void on_T3ConfirmBtn_clicked();//半径
/*T3*****/
/*DebugTab*****/
    void on_DebugUpBtn_clicked();//上
    void on_DebugDownBtn_clicked();//下
    void on_DebugLeftBtn_clicked();//左
    void on_DebugRightBtn_clicked();//右
/*DebugTab*****/
/*CalibrationTab*****/
    void on_CalibrationUpBtn_clicked();//上
    void on_CalibrationDownBtn_clicked();//下
    void on_CalibrationLeftBtn_clicked();//左
    void on_CalibrationRightBtn_clicked();//右
/*CalibrationTab*****/



    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    WhiteBoard *whiteBoard;
    QTimer *timer;
/*串口*****/
    QSerialPort *serialPort;
    void SerialPortInit();//串口初始化
    void SerialPortParametersSetting(bool set);//串口各参数ComBox使能设置
    void SerialPortError(QSerialPort::SerialPortError error);//错误槽函数
/*串口*****/
    quint16 spotCoorX=0,spotCoorY=0;//现实白板中光点的坐标0-500 mm
/*T1*****/
    void T1SetWidgetEnable(bool state);//T1各控件使能操作
    void T1SpopeCale(int k, int d);
/*T1*****/

};
#endif // MAINWINDOW_H

























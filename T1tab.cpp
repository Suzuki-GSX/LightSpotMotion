#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "WhiteBoard.h"
#include <qmath.h>
#include <math.h>
#include <stdio.h>

void MainWindow::on_T1ConfirmBtn_clicked()//确定
{
    if(!serialPort->isOpen())//串口未打开
    {
        QMessageBox::warning(this,QStringLiteral("串口未打开"),
                                QStringLiteral("数据发送失败，请先打开串口再试。"));
        return;
    }
    ui->StartBtn->setEnabled(true);//开始按键使能
    char sendData[12];
    sprintf(sendData,"1 %03d %03d\r\n",whiteBoard->T1SpotX,whiteBoard->T1SpotY);
    serialPort->write(sendData);//发送数据
}

void MainWindow::on_T1SetSpotBtn_clicked()//设点
{
    if(whiteBoard->spotState != WhiteBoard::T1Motion)
    {
        whiteBoard->spotState = WhiteBoard::T1Motion;
        whiteBoard->setMouseTracking(true);//鼠标使能
        ui->T1SetSpotBtn->setText(QStringLiteral("取消"));
        ui->T1AimsXLineEdit->setReadOnly(true);
        ui->T1AimsYLineEdit->setReadOnly(true);
        ui->T1AimsRadioBtn->setEnabled(false);
        ui->T1SlopeRadioBtn->setEnabled(false);
    }
    else
    {
        whiteBoard->spotState = WhiteBoard::T1Text;//通过LineEdit输入改变坐标
        whiteBoard->setMouseTracking(false);//鼠标失能
        ui->T1SetSpotBtn->setText(QStringLiteral("设点"));
        ui->T1AimsXLineEdit->setReadOnly(false);
        ui->T1AimsYLineEdit->setReadOnly(false);
        ui->T1AimsRadioBtn->setEnabled(true);
        ui->T1SlopeRadioBtn->setEnabled(true);
        whiteBoard->update();
    }

}

void MainWindow::on_T1SlopeRadioBtn_clicked(bool checked)//斜率
{
    if(checked)
    {
        T1SetWidgetEnable(false);
        whiteBoard->spotState=WhiteBoard::T1Slope;
        T1SpopeCale(ui->T1SlopeLineEdit->text().toInt(),ui->T1DistanceLineEdit->text().toInt());
    }
}

void MainWindow::on_T1AimsRadioBtn_clicked(bool checked)//目标点
{
    if(checked)
    {
        T1SetWidgetEnable(true);
        whiteBoard->spotState=WhiteBoard::T1Text;
        whiteBoard->T1SpotX=(quint16)(ui->T1AimsXLineEdit->text().toInt());
        whiteBoard->T1SpotY=(quint16)(ui->T1AimsYLineEdit->text().toInt());
        whiteBoard->update();
    }
}

void MainWindow::T1SetWidgetEnable(bool state)//各控件使能操作
{
    ui->T1SlopeLineEdit->setEnabled(!state);
    ui->T1SlopeLabel->setEnabled(!state);
    ui->T1DistanceLineEdit->setEnabled(!state);
    ui->T1DistanceLabel->setEnabled(!state);

    ui->T1SetSpotBtn->setEnabled(state);
    ui->T1AimsXLineEdit->setEnabled(state);
    ui->T1AimsYLineEdit->setEnabled(state);
    ui->T1AimsXLabel->setEnabled(state);
    ui->T1AimsYLabel->setEnabled(state);
}

void MainWindow::on_T1AimsXLineEdit_textChanged(const QString &arg1)//X
{
    if(arg1.isNull()||arg1.isEmpty()) return;
    int a = arg1.toInt();
    if(a<0||a>500) return;
    whiteBoard->T1SpotX=(quint16)a;
    whiteBoard->update();
}

void MainWindow::on_T1AimsYLineEdit_textChanged(const QString &arg1)//Y
{
    if(arg1.isNull()||arg1.isEmpty()) return;
    int a = arg1.toInt();
    if(a<0||a>500) return;
    whiteBoard->T1SpotY=(quint16)a;
    whiteBoard->update();
}

void MainWindow::on_T1SlopeLineEdit_textChanged(const QString &arg1)//斜率输入
{
    bool isOk=false;
    int k = arg1.toInt(&isOk,10);
    if(!isOk||k<0) return;
    int d = ui->T1DistanceLineEdit->text().toInt(&isOk,10);
    if(!isOk) return;
    T1SpopeCale(k,d);
}

void MainWindow::on_T1DistanceLineEdit_textChanged(const QString &arg1)//距离输入
{
    bool isOk=false;
    int d = arg1.toInt(&isOk,10);
    if(!isOk||d<0) return;
    int k = ui->T1SlopeLineEdit->text().toInt();
    if(!isOk) return;
    T1SpopeCale(k,d);
}

void MainWindow::T1SpopeCale(int k, int d)
{
    whiteBoard->T1SpotX = (quint16)sqrt((d*d)/((k*k)+1));
    whiteBoard->T1SpotY = whiteBoard->T1SpotX * k;
    whiteBoard->update();
}












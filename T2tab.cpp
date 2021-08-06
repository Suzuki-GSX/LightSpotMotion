#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "WhiteBoard.h"


void MainWindow::on_T2ConfirmBtn_clicked()//确定
{
    if(!serialPort->isOpen())//串口未打开
    {
        QMessageBox::warning(this,QStringLiteral("串口未打开"),
                                QStringLiteral("数据发送失败，请先打开串口再试。"));
        return;
    }
    ui->StartBtn->setEnabled(true);//开始按键使能
    char sendData[19];
    sprintf(sendData,"2 %03d %03d %03d %03d\r\n",
            whiteBoard->T2Spot1X,whiteBoard->T2Spot1Y,
            whiteBoard->T2Spot2X,whiteBoard->T2Spot2Y);
    serialPort->write(sendData);//发送数据
}

void MainWindow::on_T2SetSpot1Btn_clicked()//设点1
{
    if(whiteBoard->spotState != WhiteBoard::T2Spot1Motion)//设点1
    {
        whiteBoard->spotState = WhiteBoard::T2Spot1Motion;
        ui->T2SetSpot1Btn->setText(QStringLiteral("取消"));
        whiteBoard->setMouseTracking(true);//鼠标使能
        ui->T2X1LineEdit->setReadOnly(true);//X1只读
        ui->T2Y1LineEdit->setReadOnly(true);//Y1只读
        ui->T2X2LineEdit->setReadOnly(true);//X2只读
        ui->T2Y2LineEdit->setReadOnly(true);//Y2只读
        ui->T2SetSpot2Btn->setEnabled(false);//设点2失能
        ui->T2ConfirmBtn->setEnabled(false);//确定按键失能
    }
    else //取消设点1
    {
        whiteBoard->spotState = WhiteBoard::T2Text;
        ui->T2SetSpot1Btn->setText(QStringLiteral("设起点1"));
        whiteBoard->setMouseTracking(false);//鼠标失能
        ui->T2X1LineEdit->setReadOnly(false);//X1可写
        ui->T2Y1LineEdit->setReadOnly(false);//Y1可写
        ui->T2X2LineEdit->setReadOnly(false);//X2可写
        ui->T2Y2LineEdit->setReadOnly(false);//Y2可写
        ui->T2SetSpot2Btn->setEnabled(true);//设点2使能
        ui->T2ConfirmBtn->setEnabled(true);//确定按键使能
    }
    whiteBoard->update();
}

void MainWindow::on_T2SetSpot2Btn_clicked()//设点2
{
    if(whiteBoard->spotState != WhiteBoard::T2Spot2Motion)//设点1
    {
        whiteBoard->spotState = WhiteBoard::T2Spot2Motion;
        ui->T2SetSpot2Btn->setText(QStringLiteral("取消"));
        whiteBoard->setMouseTracking(true);//鼠标使能
        ui->T2X1LineEdit->setReadOnly(true);//X1只读
        ui->T2Y1LineEdit->setReadOnly(true);//Y1只读
        ui->T2X2LineEdit->setReadOnly(true);//X2只读
        ui->T2Y2LineEdit->setReadOnly(true);//Y2只读
        ui->T2SetSpot1Btn->setEnabled(false);//设点2失能
        ui->T2ConfirmBtn->setEnabled(false);//确定按键失能
    }
    else //取消设点1
    {
        whiteBoard->spotState = WhiteBoard::T2Text;
        ui->T2SetSpot2Btn->setText(QStringLiteral("设终点2"));
        whiteBoard->setMouseTracking(false);//鼠标失能
        ui->T2X1LineEdit->setReadOnly(false);//X1只读
        ui->T2Y1LineEdit->setReadOnly(false);//Y1只读
        ui->T2X2LineEdit->setReadOnly(false);//X2只读
        ui->T2Y2LineEdit->setReadOnly(false);//Y2只读
        ui->T2SetSpot1Btn->setEnabled(true);//设点2使能
        ui->T2ConfirmBtn->setEnabled(true);//确定按键使能
    }
    whiteBoard->update();
}

void MainWindow::on_T2X1LineEdit_textChanged(const QString &arg1)//点1 X改变
{
    if(arg1.isNull()||arg1.isEmpty()) return;
    int a = arg1.toInt();
    if(a<0||a>500) return;
    whiteBoard->T2Spot1X=(quint16)a;
    whiteBoard->update();
}

void MainWindow::on_T2Y1LineEdit_textChanged(const QString &arg1)//点1 Y改变
{
    if(arg1.isNull()||arg1.isEmpty()) return;
    int a = arg1.toInt();
    if(a<0||a>500) return;
    whiteBoard->T2Spot1Y=(quint16)a;
    whiteBoard->update();
}

void MainWindow::on_T2X2LineEdit_textChanged(const QString &arg1)//点2 X改变
{
    if(arg1.isNull()||arg1.isEmpty()) return;
    int a = arg1.toInt();
    if(a<0||a>500) return;
    whiteBoard->T2Spot2X=(quint16)a;
    whiteBoard->update();
}

void MainWindow::on_T2Y2LineEdit_textEdited(const QString &arg1)//点2 Y改变
{
    if(arg1.isNull()||arg1.isEmpty()) return;
    int a = arg1.toInt();
    if(a<0||a>500) return;
    whiteBoard->T2Spot2Y=(quint16)a;
    whiteBoard->update();
}


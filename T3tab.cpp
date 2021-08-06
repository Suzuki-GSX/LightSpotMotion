#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "WhiteBoard.h"

void MainWindow::on_T3ConfirmBtn_clicked()//确定
{
    if(!serialPort->isOpen())//串口未打开
    {
        QMessageBox::warning(this,QStringLiteral("串口未打开"),
                                QStringLiteral("数据发送失败，请先打开串口再试。"));
        return;
    }
    ui->StartBtn->setEnabled(true);//开始按键使能
    char sendData[15];
    sprintf(sendData,"1 %03d %03d %03d\r\n", whiteBoard->T3CircleSpotX,
            whiteBoard->T3CircleSpotX,whiteBoard->T3Radius);
    serialPort->write(sendData);//发送数据
}

void MainWindow::on_T3SetCircleSpotBtn_clicked()//设圆心
{
    if(whiteBoard->spotState != WhiteBoard::T3Motion)
    {
        whiteBoard->spotState = WhiteBoard::T3Motion;
        ui->T3SetCircleSpotBtn->setText(QStringLiteral("取消"));
        whiteBoard->setMouseTracking(true);//鼠标使能
        ui->T3XLineEdit->setReadOnly(true);//X只读
        ui->T3YLineEdit->setReadOnly(true);//X只读
        ui->T2ConfirmBtn->setEnabled(false);//确定按键失能
    }
    else
    {
        whiteBoard->spotState = WhiteBoard::T3Text;
        ui->T3SetCircleSpotBtn->setText(QStringLiteral("设圆心"));
        whiteBoard->setMouseTracking(false);//鼠标失能
        ui->T3XLineEdit->setReadOnly(false);//X可写
        ui->T3YLineEdit->setReadOnly(false);//X可写
        ui->T2ConfirmBtn->setEnabled(true);//确定按键使能
    }
    whiteBoard->update();
}

void MainWindow::on_T3XLineEdit_textChanged(const QString &arg1)//X
{
    if(arg1.isNull()||arg1.isEmpty()) return;
    int x = arg1.toInt();
    if(x<0||x>500)
    {
        ui->T3XLineEdit->setText(QString("%1").arg(whiteBoard->T3CircleSpotX));
        return;
    }
    whiteBoard->T3CircleSpotX=(quint16)x;
    whiteBoard->update();
}

void MainWindow::on_T3YLineEdit_textChanged(const QString &arg1)//Y
{
    if(arg1.isNull()||arg1.isEmpty()) return;
    int y = arg1.toInt();
    if(y<0||y>500)
    {
        ui->T3YLineEdit->setText(QString("%1").arg(whiteBoard->T3CircleSpotY));
        return;
    }
    whiteBoard->T3CircleSpotY=(quint16)y;
    whiteBoard->update();
}

void MainWindow::on_T3RadiusLineEdit_textChanged(const QString &arg1)//半径
{
    if(arg1.isNull()||arg1.isEmpty()) return;
    int r = arg1.toInt();
    if(r<0||r>250)
    {
        ui->T3RadiusLineEdit->setText(QString("%1").arg(whiteBoard->T3Radius));
        return;
    }
    whiteBoard->T3Radius=(quint16)r;
    whiteBoard->update();
}









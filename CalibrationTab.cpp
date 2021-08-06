#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "WhiteBoard.h"

char Cdat[9];
void MainWindow::on_CalibrationUpBtn_clicked()//上
{
    if(!serialPort->isOpen()) return;
    sprintf(Cdat,"4 1 %03d", ui->CalibrationDistantLineEdit->text().toInt());
    serialPort->write(Cdat);
    qDebug() << Cdat;
}

void MainWindow::on_CalibrationDownBtn_clicked()//下
{
    if(!serialPort->isOpen()) return;
    sprintf(Cdat,"4 2 %03d", ui->CalibrationDistantLineEdit->text().toInt());
    serialPort->write(Cdat);
}

void MainWindow::on_CalibrationLeftBtn_clicked()//左
{
    if(!serialPort->isOpen()) return;
    sprintf(Cdat,"4 3 %03d", ui->CalibrationDistantLineEdit->text().toInt());
    serialPort->write(Cdat);
}

void MainWindow::on_CalibrationRightBtn_clicked()//右
{
    if(!serialPort->isOpen()) return;
    sprintf(Cdat,"4 4 %03d", ui->CalibrationDistantLineEdit->text().toInt());
    serialPort->write(Cdat);
}

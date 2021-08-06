#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "WhiteBoard.h"
char Ddat[9];
void MainWindow::on_DebugUpBtn_clicked()//上
{
    if(!serialPort->isOpen()) return;
    sprintf(Ddat,"5 1 %03d", ui->DebugDistantLineEdit->text().toInt());
    serialPort->write(Ddat);
    qDebug() << Ddat;
}

void MainWindow::on_DebugDownBtn_clicked()//下
{
    if(!serialPort->isOpen()) return;
    sprintf(Ddat,"5 2 %03d", ui->DebugDistantLineEdit->text().toInt());
    serialPort->write(Ddat);
}

void MainWindow::on_DebugLeftBtn_clicked()//左
{
    if(!serialPort->isOpen()) return;
    sprintf(Ddat,"5 3 %03d", ui->DebugDistantLineEdit->text().toInt());
    serialPort->write(Ddat);
}

void MainWindow::on_DebugRightBtn_clicked()//右
{
    if(!serialPort->isOpen()) return;
    sprintf(Ddat,"5 4 %03d", ui->DebugDistantLineEdit->text().toInt());
    serialPort->write(Ddat);
}

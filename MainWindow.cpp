#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont font = this->font();
    font.setPixelSize(13);
    font.setFamily(QStringLiteral("宋体"));
    this->setFont(font);//设置字体

    whiteBoard = new WhiteBoard(this);//添加白板
    QGridLayout *BoartLayout = new QGridLayout(this);
    BoartLayout->addWidget(whiteBoard);
    ui->BoardWidget->setLayout(BoartLayout);
    connect(whiteBoard,&WhiteBoard::dataUpdate,this,&MainWindow::DataUpdate);
    SerialPortInit();//串口初始化
    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer,&QTimer::timeout, this,&MainWindow::timerOut);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DataUpdate()//数据更新
{
    switch (whiteBoard->spotState) {//第一题的目标点
    case WhiteBoard::T1Motion: //第一题点跟随鼠标移动
        ui->T1AimsXLineEdit->setText(QString("%1").arg(whiteBoard->T1SpotX));
        ui->T1AimsYLineEdit->setText(QString("%1").arg(whiteBoard->T1SpotY));
        break;
    break;
    case WhiteBoard::T1Confirm://第一题确定
        whiteBoard->spotState = WhiteBoard::T1Text;//通过LineEdit输入改变坐标
        ui->T1SetSpotBtn->setText(QStringLiteral("设点"));
        ui->T1AimsXLineEdit->setReadOnly(false);
        ui->T1AimsYLineEdit->setReadOnly(false);
        ui->T1AimsRadioBtn->setEnabled(true);
        ui->T1SlopeRadioBtn->setEnabled(true);
        break;
    case WhiteBoard::T2Spot1Motion://第二题起点1点跟随鼠标移动
        ui->T2X1LineEdit->setText(QString("%1").arg(whiteBoard->T2Spot1X));
        ui->T2Y1LineEdit->setText(QString("%1").arg(whiteBoard->T2Spot1Y));
        break;
    case WhiteBoard::T2Spot2Motion://第二题起点1点跟随鼠标移动
        ui->T2X2LineEdit->setText(QString("%1").arg(whiteBoard->T2Spot2X));
        ui->T2Y2LineEdit->setText(QString("%1").arg(whiteBoard->T2Spot2Y));
         break;
    case WhiteBoard::T2Spot1Confirm://第二题起点1确定
        whiteBoard->spotState = WhiteBoard::T2Text;
        ui->T2SetSpot1Btn->setText(QStringLiteral("设起点1"));
        ui->T2X1LineEdit->setReadOnly(false);//X1可写
        ui->T2Y1LineEdit->setReadOnly(false);//Y1可写
        ui->T2X2LineEdit->setReadOnly(false);//X2可写
        ui->T2Y2LineEdit->setReadOnly(false);//Y2可写
        ui->T2SetSpot2Btn->setEnabled(true);//设点2使能
        ui->T2ConfirmBtn->setEnabled(true);//确定按键使能
        break;
    case WhiteBoard::T2Spot2Confirm://第二题起点1确定
        whiteBoard->spotState = WhiteBoard::T2Text;
        ui->T2SetSpot2Btn->setText(QStringLiteral("设终点2"));
        ui->T2X1LineEdit->setReadOnly(false);//X1可写
        ui->T2Y1LineEdit->setReadOnly(false);//Y1可写
        ui->T2X2LineEdit->setReadOnly(false);//X2可写
        ui->T2Y2LineEdit->setReadOnly(false);//Y2可写
        ui->T2SetSpot1Btn->setEnabled(true);//设点2使能
        ui->T2ConfirmBtn->setEnabled(true);//确定按键使能
        break;
    case WhiteBoard::T3Motion://第三题移动
        ui->T3XLineEdit->setText(QString("%1").arg(whiteBoard->T3CircleSpotX));
        ui->T3YLineEdit->setText(QString("%1").arg(whiteBoard->T3CircleSpotY));
        break;
    case WhiteBoard::T3Confirm://第三题起点1确定
        whiteBoard->spotState = WhiteBoard::T3Text;
        ui->T3SetCircleSpotBtn->setText(QStringLiteral("设圆心"));
        ui->T3XLineEdit->setReadOnly(false);//X只读
        ui->T3YLineEdit->setReadOnly(false);//X只读
        ui->T3ConfirmBtn->setEnabled(true);//确定按键使能
        whiteBoard->update();
        break;
    default:   break;
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)//题目改变
{
    ui->StartBtn->setEnabled(false);//开始按键失能
    switch (index) {
    case 0: whiteBoard->spotState=WhiteBoard::T1Text;
        if(serialPort->isOpen()) serialPort->write("11\r\n"); break;
    case 1: whiteBoard->spotState=WhiteBoard::T2Text;
        if(serialPort->isOpen()) serialPort->write("22\r\n");break;
    case 2: whiteBoard->spotState=WhiteBoard::T3Text;
        if(serialPort->isOpen()) serialPort->write("33\r\n");break;
    case 3: whiteBoard->spotState=WhiteBoard::Calibration;
        if(serialPort->isOpen()) serialPort->write("44\r\n");break;
    case 4: whiteBoard->spotState=WhiteBoard::Debug;
        if(serialPort->isOpen()) serialPort->write("55\r\n");break;
    default: whiteBoard->spotState=WhiteBoard::No;break;
    }
    whiteBoard->update();
}

void MainWindow::on_StartBtn_clicked(bool checked)
{
    if(!serialPort->isOpen())//串口未打开
    {
        QMessageBox::warning(this,QStringLiteral("串口未打开"),
                                QStringLiteral("数据发送失败，请先打开串口再试。"));
        ui->StartBtn->setChecked(!checked);
        return;
    }
    if(checked)//开始运行
    {
        serialPort->write("77\r\n");
        ui->StartBtn->setText(QStringLiteral("停止"));
        ui->OriginBtn->setEnabled(false);//回原点使能
        ui->tabWidget->setEnabled(false);//选题页使能
    }
    else//停止运行
    {
        serialPort->write("88\r\n");
        ui->StartBtn->setText(QStringLiteral("开始"));
        ui->OriginBtn->setEnabled(true);//回原点使能
        ui->tabWidget->setEnabled(true);//选题页使能
    }
}

void MainWindow::on_OriginBtn_clicked()//回原点
{
    if(serialPort->isOpen()) serialPort->write("99\r\n");
}

void MainWindow::on_SpeedScrollBar_valueChanged(int value)//速度值改变
{
    if((!serialPort->isOpen())||timer->isActive()) return;
    timer->start(800);
}

void MainWindow::timerOut()
{
    char dat[7];
    sprintf(dat,"6 %03d\r\n",ui->SpeedScrollBar->value());
    serialPort->write(dat);
}

void MainWindow::on_pushButton_clicked()//说明导出到文档
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        tr("Save File"),"",
        tr("Text Files(*.txt)"));

    if (fileName != "") {
        QFile file(fileName );
        if (!file.open(QIODevice::WriteOnly)){
             QMessageBox::critical(this,tr("Error"),
                                   tr("Save Error!"));
        }
        else {
            QTextStream stream(&file);
            stream << ui->textBrowser->toPlainText();
            stream.flush();
            file.close();
        }
    }
}

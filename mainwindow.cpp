#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pSerialPort(NULL)
    , isOpen(false)
{
    ui->setupUi(this);

    //初始化UI串口配置信息
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        ui->comboBox_Com->addItem(info.portName());
    }

    ui->comboBox_Com->setCurrentIndex(0);
    ui->comboBox_BoundRate->setCurrentIndex(7);
    ui->comboBox_DataBits->setCurrentIndex(3);
    ui->comboBox_ParityBits->setCurrentIndex(0);
    ui->comboBox_StopBits->setCurrentIndex(0);

    pSerialPort = new QSerialPort(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_OnOff_clicked()
{
    if(isOpen == false){
        pSerialPort->setPortName(ui->comboBox_Com->currentText());
        if(pSerialPort->open(QIODevice::ReadWrite)){
            ui->pushButton_OnOff->setText("关闭");
            ui->label_ComState->setText("打开");
            isOpen = true;
            switch (ui->comboBox_BoundRate->currentIndex()) {
            case 0:
                pSerialPort->setBaudRate(QSerialPort::Baud1200);
                break;
            case 1:
                pSerialPort->setBaudRate(QSerialPort::Baud2400);
                break;
            case 2:
                pSerialPort->setBaudRate(QSerialPort::Baud4800);
                break;
            case 3:
                pSerialPort->setBaudRate(QSerialPort::Baud9600);
                break;
            case 4:
                pSerialPort->setBaudRate(QSerialPort::Baud19200);
                break;
            case 5:
                pSerialPort->setBaudRate(QSerialPort::Baud38400);
                break;
            case 6:
                pSerialPort->setBaudRate(QSerialPort::Baud57600);
                break;
            case 7:
                pSerialPort->setBaudRate(QSerialPort::Baud115200);
                break;
            default:
                qDebug() << "set baud rate error";
                return;
                break;
            }

            switch (ui->comboBox_DataBits->currentIndex()) {
            case 0:
                pSerialPort->setDataBits(QSerialPort::Data5);
                break;
            case 1:
                pSerialPort->setDataBits(QSerialPort::Data6);
                break;
            case 2:
                pSerialPort->setDataBits(QSerialPort::Data7);
                break;
            case 3:
                pSerialPort->setDataBits(QSerialPort::Data8);
                break;
            default:
                qDebug() << "set data bits error";
                return;
                break;
            }

            switch (ui->comboBox_ParityBits->currentIndex()) {
            case 0:
                pSerialPort->setParity(QSerialPort::NoParity);
                break;
            case 1:
                pSerialPort->setParity(QSerialPort::EvenParity);
                break;
            case 2:
                pSerialPort->setParity(QSerialPort::OddParity);
                break;
            case 3:
                pSerialPort->setParity(QSerialPort::SpaceParity);
                break;
            case 4:
                pSerialPort->setParity(QSerialPort::MarkParity);
                break;
            default:
                qDebug() << "set parity error";
                return;
                break;
            }

            switch (ui->comboBox_StopBits->currentIndex()) {
            case 0:
                pSerialPort->setStopBits(QSerialPort::OneStop);
                break;
            case 1:
                pSerialPort->setStopBits(QSerialPort::OneAndHalfStop);
                break;
            case 2:
                pSerialPort->setStopBits(QSerialPort::TwoStop);
                break;
            default:
                qDebug() << "set stop bits error";
                return;
                break;
            }

            connect(pSerialPort, &QSerialPort::readyRead, this, &MainWindow::recv);
        }
    }else{
        pSerialPort->close();
        ui->pushButton_OnOff->setText("打开");
        ui->label_ComState->setText("关闭");
        isOpen = false;
        disconnect(pSerialPort, &QSerialPort::readyRead, this, &MainWindow::recv);
    }
}

void MainWindow::recv()
{
    recvBuff.append(pSerialPort->readAll());
    //接收到一个完整的数据帧
    if(checkData()){
        ui->textBrowser->append(QString("[recv] %1").arg(recvBuff.data()));
        parseData();
        recvBuff.clear();
    }
}

void MainWindow::on_pushButton_Clear_clicked()
{
    ui->textBrowser->clear();
}

bool MainWindow::checkData()
{
    return false;
}

void MainWindow::parseData()
{

}

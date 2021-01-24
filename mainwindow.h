#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtSerialPort/QtSerialPort"
#include "QThread"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_OnOff_clicked();
    void on_pushButton_Clear_clicked();
    void recv();

private:
    Ui::MainWindow *ui;
    QSerialPort *pSerialPort;
    bool isOpen;
    QByteArray recvBuff;

    bool checkData();
    void parseData();
};
#endif // MAINWINDOW_H

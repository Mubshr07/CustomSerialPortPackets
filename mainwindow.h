#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include "qdebug.h"

#include <QDateTime>

#include <QObject>
#include <QFile>
#include <QIODevice>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>
#include <QTimer>
#include <QElapsedTimer>
#include <qmath.h>
#include <QDateTime>
#include <QKeyEvent>
#include <QCryptographicHash>
#include <QIcon>
#include <QFileDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <qserialportglobal.h>

#include <QStringList>
#include <QThread>
#include <QMutexLocker>


#include <random>
#include <QRandomGenerator>
#include <cstdlib>
#include <random>
#include <cstdint>
#include <iostream>
#include <time.h>
#include <iostream>


#include <qbitarray.h>


#include "PortSettings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void rxNewSerialPortConfig(QString portName);

    void onSerialReadyData();
    void onTimerSingleShotElapsed();


private slots:
    void on_pbClear_clicked();
    void on_pbStart_clicked();
    void on_pbClose_clicked();
    void on_openButton_clicked();

    void on_pbSettings_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timerSingleShot;
    QSerialPort m_serialPort;

    QVector<double> m_xs;
    QVector<double> m_ys;

    PortSettings *portSettingObj;

    int m_xLength;
    bool toggleOpenSerial = false;


    QByteArray receivedBytes;
    int receiveIndex = 0;

    QMutex mlocker;

    void processSerialData();
    void processSerialSinglePacket(QByteArray ba);
    int indexOfHeader = 0, currentPacketType = 0;
    QByteArray singlePacket;

    void serialSendTheseBytes(QByteArray ba);
    //---------------------- [0-1]=Header,   [last(5)]=footer

    QByteArray serialRx, serialData;
    QByteArray serialBytesTxhandShake = QByteArray::fromHex("EA920011000000000000000000BB").toUpper();
    QByteArray serialBytesTxSelfTestSupplyVoltages = QByteArray::fromHex("EA920101000000000000000000BB").toUpper();
    QByteArray serialBytesTxSelfTestInsulationResistance = QByteArray::fromHex("EA920200000000000000000000BB").toUpper();

    QByteArray serialBytesTxResistanceTest = QByteArray::fromHex("EA920300000000000000000000BB").toUpper();  //  [2]=PacketID
    QByteArray serialBytesTxPolarityTest = QByteArray::fromHex("EA920400000000000000000000BB").toUpper();  //  [2]=PacketID, [3]=ChID, [4]=Ch.Status
    QByteArray serialBytesTxInsulationResistanceTest = QByteArray::fromHex("EA920300000000000000000000BB").toUpper(); //  [2]=PacketID, [3]=ChID, [4]=Ch.Status
    QByteArray serialBytesTxLaunchControlTest = QByteArray::fromHex("EA920300000000000000000000BB").toUpper(); //  [2]=PacketID, [3]=Simulation.Time,

    float randomNumberGeneratorFloat(double min, double max);






};
#endif // MAINWINDOW_H

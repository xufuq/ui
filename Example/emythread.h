#ifndef EMYTHREAD_H
#define EMYTHREAD_H

#include <QWidget>
#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QGridLayout>

class EMyThread : public QThread
{
    Q_OBJECT
public:
    explicit EMyThread(QWidget *parent = nullptr);


signals:
    void setsenddata(QByteArray);

public slots:
    void searchport();
    void openport();
    void closeport();
    void receivemessage();
public:


    QLabel *PortText;
    QLabel *Port;
    QLabel *Baud;
    QLabel *NumBit;
    QLabel *CheckBit;
    QLabel *StopBit;

    QPushButton *SearchPort;
    QPushButton *OpenPort;
    QPushButton *ClosePort;
    QComboBox   *port;
    QComboBox   *baud;
    QComboBox   *numbit;
    QComboBox   *checkbit;
    QComboBox   *stopbit;

    EMyThread *mythread;

    //蓝牙相关
    QTextEdit *Showbuf;
    QSerialPort *MySerialPort;
    QTimer *timer;
    QString NowTime;
    bool isopen=false;
    bool WithTime;
    QByteArray showdata;

    int pattern_select;
    int color_bit_select;
    int image_count;
protected:

};

#endif // EMYTHREAD_H

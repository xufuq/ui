#ifndef USART_H
#define USART_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QCheckBox>
#include <QTextBrowser>
#include <QString>
#include <QList>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtCore>

class Usart : public QWidget
{
    Q_OBJECT
public:
    explicit Usart(QWidget *parent = nullptr);

signals:

private:
    QLabel    *TopText;
    QPushButton *SearchPort;
    QPushButton *OpenPort;
    QPushButton *ClosePort;
    QLabel    *Port;
    QLabel    *Baud;
    QLabel    *NumBit;
    QLabel    *CheckBit;
    QLabel    *StopBit;
    QLabel    *ReceiveText;
    QLabel    *TextText;
    QComboBox *port;
    QComboBox *baud;
    QComboBox *numbit;
    QComboBox *checkbit;
    QComboBox *stopbit;


    QRadioButton *ascii;
    QRadioButton *hex;
    QRadioButton *To_10;
    QCheckBox    *changeline;
    QCheckBox    *displayoutput;
    QCheckBox    *displaytime;

    QPushButton  *Retry;

    QTextBrowser *TextIn;
    QTextEdit    *Textout;
    QPushButton  *TextSend;
    QComboBox    *TextMemory;

    QVBoxLayout *MainLeft;
    QVBoxLayout *MainRight;
    QGridLayout *LeftTop;
    QGridLayout *LeftCerten;
    QGridLayout *LeftBottom;
    QHBoxLayout *RightSend;


    //蓝牙相关
    QSerialPort *MySerialPort;
    QTimer *timer;
    QString NowTime;
    bool isopen=false;
    bool ishex;
    bool WithTime;

public slots:
    void searchport();
    void openport();
    void closeport();
    void sendmessage();
    void receivemessage();
    void timeupdate();
    void receivedelete();

};

#endif // USART_H

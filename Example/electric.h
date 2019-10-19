#ifndef ELECTRIC_H
#define ELECTRIC_H
#include "emythread.h"
#include "echart.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QList>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtCore>
#include <QPainter>
#include <QPen>
#include <QPalette>      //设置背景颜色等
#include <QTextEdit>
#include <QLineEdit>
#include <QVector>


class Electric : public QWidget
{
    Q_OBJECT
public:
    explicit Electric(QWidget *parent = nullptr);
    EMyThread *mythread;
    ~Electric();

signals:

private:
    QHBoxLayout *TopLayout;
    QHBoxLayout *BottomLayout;
    QGridLayout *BotLeftLayout;
    QGridLayout *BotRightLayout;
    QHBoxLayout *BotRRightLayout;
    QGridLayout *BotCertenLayout;

    QCheckBox *port0,*port1,*port2,*port3,*port4,*port5,*port6,*port7,*port8,*port9,*port10,*port11,*port12,*port13,*port14,*port15;
    QLineEdit *portnum0, *portnum1,*portnum2,*portnum3,*portnum4,*portnum5,*portnum6,*portnum7,*portnum8,*portnum9,*portnum10,*portnum11,*portnum12,*portnum13,*portnum14,*portnum15;
    QVector<QCheckBox *> port_collect;
    QVector<QLineEdit *> portnum_collect;

    QPushButton *MemClear;
    QPushButton *Pause;
    bool send_bit;



    //画图相关
    Echart *echart;

public slots:   
    void datashow(QByteArray);
    void bit_change();


};

#endif // ELECTRIC_H

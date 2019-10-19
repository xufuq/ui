#ifndef CAMERA_H
#define CAMERA_H

#include "emythread.h"
#include "epoint.h"
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
#include <QRadioButton>
#include <QTimer>

/*
* 两个任务
* 显示灰度图像
* 显示二值图像
*/

class Camera : public QWidget
{
    Q_OBJECT
public:
    explicit Camera(QWidget *parent = nullptr);

    ~Camera();
    EMyThread *mythread;

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

    QRadioButton *One_bit;
    QRadioButton *eight_bit;
    QRadioButton *ei_to_one;
    QLabel       *middle_label;
    QLineEdit    *middle_num;
    bool send_bit;

    EPoint    *epoint;
    QTimer *time_break;
signals:

public slots:
    void datashow(QByteArray data1);
    void time_out();
};

#endif // CAMERA_H

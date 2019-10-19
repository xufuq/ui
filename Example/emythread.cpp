#include "emythread.h"
#include <QDebug>

EMyThread::EMyThread(QWidget *parent) : QThread(parent)
{

    PortText = new QLabel(tr("串口设置"));
    PortText->setFixedSize(60,20);
    SearchPort=new QPushButton(tr("搜索串口"));
    SearchPort->setFixedSize(60,20);
    OpenPort=new QPushButton(tr("打开串口"));
    OpenPort->setFixedSize(60,20);
    ClosePort=new QPushButton(tr("关闭串口"));
    ClosePort->setFixedSize(60,20);
    Port=new QLabel(tr("串口"));
    Port->setFixedSize(60,20);
    Baud=new QLabel(tr("波特率"));
    Baud->setFixedSize(60,20);
    NumBit=new QLabel(tr("数据位"));
    NumBit->setFixedSize(60,20);
    CheckBit=new QLabel(tr("校验位"));
    CheckBit->setFixedSize(60,20);
    StopBit =new QLabel(tr("停止位"));
    StopBit->setFixedSize(60,20);
    port=new QComboBox();
    port->setFixedSize(60,20);
    baud=new QComboBox();
    baud->setFixedSize(60,20);
    baud->insertItem(0,tr("115200"));
    baud->insertItem(1,tr("57600"));
    baud->insertItem(2,tr("38400"));
    baud->insertItem(3,tr("19200"));
    baud->insertItem(4,tr("9600"));
    numbit=new QComboBox();
    numbit->setFixedSize(60,20);
    numbit->insertItem(0,tr("8"));
    numbit->insertItem(1,tr("7"));
    numbit->insertItem(2,tr("6"));
    numbit->insertItem(3,tr("5"));
    checkbit=new QComboBox();
    checkbit->setFixedSize(60,20);
    checkbit->insertItem(0,tr("None"));
    checkbit->insertItem(1,tr("Even"));
    checkbit->insertItem(2,tr("Odd"));
    checkbit->insertItem(3,tr("Mark"));
    checkbit->insertItem(4,tr("Space"));
    stopbit =new QComboBox();
    stopbit->setFixedSize(60,20);
    stopbit->insertItem(0,tr("1"));
    stopbit->insertItem(1,tr("1.5"));
    stopbit->insertItem(2,tr("2"));

    Showbuf=new QTextEdit();
    Showbuf->setMaximumHeight(100);
//    Showbuf->setMaximumWidth(300);

    MySerialPort = new QSerialPort();

    connect(SearchPort,SIGNAL(clicked()),this,SLOT(searchport()));
    connect(OpenPort,SIGNAL(clicked()),this,SLOT(openport()));
    connect(ClosePort,SIGNAL(clicked()),this,SLOT(closeport()));
    connect(MySerialPort,SIGNAL(readyRead()),this,SLOT(receivemessage()));

    color_bit_select=1;
    image_count=0;

}

void EMyThread::searchport()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Name : " << info.portName();
        Showbuf->append("port:  "+info.portName());
        port->addItem(info.portName());
    }
}

void EMyThread::openport()
{
    QString comname=port->currentText();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        if(info.portName()==comname)
            MySerialPort->setPortName(info.systemLocation());
    }
    qint32 nowbaudindex=baud->currentIndex();

    switch (nowbaudindex) {
    case 4:
        MySerialPort->setBaudRate(QSerialPort::Baud9600,QSerialPort::AllDirections);
        break;
    case 3:
        MySerialPort->setBaudRate(QSerialPort::Baud19200,QSerialPort::AllDirections);
        break;
    case 2:
        MySerialPort->setBaudRate(QSerialPort::Baud38400,QSerialPort::AllDirections);
        break;
    case 1:
        MySerialPort->setBaudRate(QSerialPort::Baud57600,QSerialPort::AllDirections);
        break;
    case 0:
        MySerialPort->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);
        break;
    default:
        break;
    }

    qint32 databit=numbit->currentIndex();
    switch (databit) {
    case 0:
        MySerialPort->setDataBits(QSerialPort::Data8);
        break;
    case 1:
        MySerialPort->setDataBits(QSerialPort::Data7);
        break;
    case 2:
        MySerialPort->setDataBits(QSerialPort::Data6);
        break;
    case 3:
        MySerialPort->setDataBits(QSerialPort::Data5);
        break;
    default:
        break;
    }

    qint32 parity_index=checkbit->currentIndex();
    switch (parity_index) {
    case 0:
        MySerialPort->setParity(QSerialPort::NoParity);
        break;
    case 1:
        MySerialPort->setParity(QSerialPort::OddParity);
        break;
    case 2:
        MySerialPort->setParity(QSerialPort::EvenParity);
        break;
    default:
        MySerialPort->setParity(QSerialPort::UnknownParity);
        break;
    }

    qint32 stopbit_index=stopbit->currentIndex();
    switch (stopbit_index) {
    case 0:
        MySerialPort->setStopBits(QSerialPort::OneStop);
        break;
    case 1:
        MySerialPort->setStopBits(QSerialPort::OneAndHalfStop);
        break;
    case 2:
        MySerialPort->setStopBits(QSerialPort::TwoStop);
        break;
    default:
        MySerialPort->setStopBits(QSerialPort::UnknownStopBits);
        break;
    }

    MySerialPort->setFlowControl(QSerialPort::NoFlowControl);

    bool com=MySerialPort->open(QIODevice::ReadWrite);//打开串口并选择读写模式
    if(com)
    {
        //timer->start(1000);
        isopen=true;
        Showbuf->append("port:  "+comname+"  已打开");
    }
    else
    {
        isopen=false;
        Showbuf->append("串口打开失败");
    }
}

void EMyThread::closeport()
{
    if(MySerialPort->isOpen())
    {
        //timer->stop();
        MySerialPort->close();
        isopen=false;
        port->clear();
        Showbuf->append("串口已关闭");
    }
}

void EMyThread::receivemessage()
{
    if(pattern_select==1)
    {
        showdata.append(MySerialPort->readAll());//有可能由于接受数据不完整而导致【】访问溢出，先判断数据大小，如果不符合直接舍弃

        if(showdata[1]!=37||showdata[0]!=255)
        {
            showdata.clear();
        }

        if(showdata.size()==36)
        {
            if((showdata[0]==255)&&(showdata[1]==37)&&(showdata[34]==37)&&(showdata[35]==255))
            {
                image_count++;
                Showbuf->append("接受第"+QString::number(image_count,10)+"组数据");
                emit setsenddata(showdata);
            }
        }

        if(showdata.size()>=36)
        {
            showdata.clear();
        }
    }
    else if(pattern_select==2)
    {
        showdata.append(MySerialPort->readAll());//有可能由于接受数据不完整而导致【】访问溢出，先判断数据大小，如果不符合直接舍弃
        if(showdata[1]!=37||showdata[0]!=255)
        {
            showdata.clear();
        }

        if(color_bit_select==255)
        {
            if(showdata.size()==showdata[2]*showdata[3]*100+38)
            {
                if((showdata[0]==255)&&(showdata[1]==37)&&(showdata[showdata[2]*showdata[3]*100+36]==37)&&(showdata[showdata[2]*showdata[3]*100+37]==255))
                {
                    image_count++;
                    Showbuf->append("接受第"+QString::number(image_count,10)+"张灰度图像");
                    emit setsenddata(showdata);
                }
            }

            if(showdata.size()>=showdata[2]*showdata[3]*100+38)
            {
                showdata.clear();
            }
        }
        else if(color_bit_select==1)
        {
            if(showdata.size()==showdata[2]*showdata[3]*100/8+38)
            {
                if((showdata[0]==255)&&(showdata[1]==37)&&(showdata[showdata[2]*showdata[3]*100/8+36]==37)&&(showdata[showdata[2]*showdata[3]*100/8+37]==255))
                {
                    image_count++;
                    Showbuf->append("接受第"+QString::number(image_count,10)+"张二值图像");
                    emit setsenddata(showdata);
                }
            }

            if(showdata.size()>=showdata[2]*showdata[3]*100/8+38)
            {
                showdata.clear();
            }
        }
    }
}



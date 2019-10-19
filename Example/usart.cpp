#include "usart.h"
#include <QDebug>


Usart::Usart(QWidget *parent) : QWidget(parent)
{

    MainLeft=new QVBoxLayout();

    LeftTop =new QGridLayout();
    TopText=new QLabel(tr("串口设置"));
    TopText->setFixedSize(60,20);
    QLabel *TopText1=new QLabel(tr("  "));
    SearchPort =new QPushButton(tr("搜索串口"));
    SearchPort->setFixedSize(60,20);
    OpenPort   =new QPushButton(tr("打开串口"));
    OpenPort->setFixedSize(60,20);
    ClosePort  =new QPushButton(tr("关闭串口"));
    ClosePort->setFixedSize(60,20);
    Port   =new QLabel(tr("端 口"));
    Port->setFixedSize(60,20);
    port   =new QComboBox();
    port->setFixedSize(60,20);
    Baud   =new QLabel(tr("波特率"));
    Baud->setFixedSize(60,20);
    baud   =new QComboBox();
    baud->setFixedSize(60,20);
    baud->insertItem(0,tr("115200"));
    baud->insertItem(1,tr("57600"));
    baud->insertItem(2,tr("38400"));
    baud->insertItem(3,tr("19200"));
    baud->insertItem(4,tr("9600"));
    NumBit =new QLabel(tr("数据位"));
    NumBit->setFixedSize(60,20);
    numbit =new QComboBox();
    numbit->setFixedSize(60,20);
    numbit->insertItem(0,tr("8"));
    numbit->insertItem(1,tr("7"));
    numbit->insertItem(2,tr("6"));
    numbit->insertItem(3,tr("5"));
    CheckBit=new QLabel(tr("校验位"));
    CheckBit->setFixedSize(60,20);
    checkbit=new QComboBox();
    checkbit->setFixedSize(60,20);
    checkbit->insertItem(0,tr("None"));
    checkbit->insertItem(1,tr("Even"));
    checkbit->insertItem(2,tr("Odd"));
    checkbit->insertItem(3,tr("Mark"));
    checkbit->insertItem(4,tr("Space"));
    StopBit =new QLabel(tr("停止位"));
    StopBit->setFixedSize(60,20);
    stopbit =new QComboBox();
    stopbit->setFixedSize(60,20);
    stopbit->insertItem(0,tr("1"));
    stopbit->insertItem(1,tr("1.5"));
    stopbit->insertItem(2,tr("2"));
    LeftTop->addWidget(TopText,0,0);
    LeftTop->addWidget(SearchPort,0,1);
    LeftTop->addWidget(OpenPort,1,0);
    LeftTop->addWidget(ClosePort,1,1);
    LeftTop->addWidget(Port,2,0);
    LeftTop->addWidget(port,2,1);
    LeftTop->addWidget(Baud,3,0);
    LeftTop->addWidget(baud,3,1);
    LeftTop->addWidget(NumBit,4,0);
    LeftTop->addWidget(numbit,4,1);
    LeftTop->addWidget(CheckBit,5,0);
    LeftTop->addWidget(checkbit,5,1);
    LeftTop->addWidget(StopBit,6,0);
    LeftTop->addWidget(stopbit,6,1);

    LeftCerten   =new QGridLayout();
    ReceiveText  =new QLabel(tr("接收设置"));
    ReceiveText->setFixedSize(60,20);
    ascii        =new QRadioButton(tr("ASCII"));
    ascii->setFixedSize(60,20);
    hex          =new QRadioButton(tr("hex"));
    hex->setFixedSize(60,20);
    To_10        =new QRadioButton(tr("To_10"));
    To_10->setFixedSize(60,20);
    changeline   =new QCheckBox(tr("自动换行"));
    displayoutput=new QCheckBox(tr("显示发送"));
    displaytime  =new QCheckBox(tr("显示时间"));
    LeftCerten->addWidget(ReceiveText,0,0);
    LeftCerten->addWidget(ascii,1,1);
    LeftCerten->addWidget(hex,2,1);
    LeftCerten->addWidget(To_10,3,1);
    LeftCerten->addWidget(changeline,1,0);
    LeftCerten->addWidget(displayoutput,2,0);
    LeftCerten->addWidget(displaytime,3,0);


    LeftBottom=new QGridLayout();
    Retry=new QPushButton(tr("清空接受区"));
    LeftBottom->addWidget(Retry,0,0);

    QLabel *mainleftextra=new QLabel(tr("   "));
    QVBoxLayout *MainLeft1  =new QVBoxLayout();

    MainLeft1->addLayout(LeftTop);
    MainLeft1->addLayout(LeftCerten);
    MainLeft1->addLayout(LeftBottom);
    MainLeft1->setSizeConstraint(QLayout::SetFixedSize);
    MainLeft->addLayout(MainLeft1);
    MainLeft->addWidget(mainleftextra);
    MainLeft->addWidget(TopText1);


    MainRight =new QVBoxLayout();
    RightSend =new QHBoxLayout();
    TextIn  =new QTextBrowser();
    Textout   =new QTextEdit();
    TextMemory=new QComboBox();
    TextSend  =new QPushButton(tr("发送"));
    RightSend->addWidget(Textout);
    RightSend->addWidget(TextSend);

    MainRight->addWidget(TextIn);
    MainRight->addLayout(RightSend);
    MainRight->addWidget(TextMemory);
    MainRight->setStretchFactor(TextIn,10);
    MainRight->setStretchFactor(RightSend,2);
    MainRight->setStretchFactor(TextMemory,1);

    QGridLayout *mainLayout=new QGridLayout(this);
    mainLayout->setMargin(10);
    mainLayout->setSpacing(6);
    mainLayout->addLayout(MainLeft,0,0);
    mainLayout->addLayout(MainRight,0,1);


    //蓝牙相关
    MySerialPort = new QSerialPort();
    timer=new QTimer();

    connect(SearchPort,SIGNAL(clicked()),this,SLOT(searchport()));
    connect(OpenPort,SIGNAL(clicked()),this,SLOT(openport()));
    connect(ClosePort,SIGNAL(clicked()),this,SLOT(closeport()));
    connect(TextSend,SIGNAL(clicked()),this,SLOT(sendmessage()));
    connect(timer,SIGNAL(timeout()),this,SLOT(timeupdate()));
    connect(MySerialPort,SIGNAL(readyRead()),this,SLOT(receivemessage()));
    connect(Retry,SIGNAL(clicked(bool)),this,SLOT(receivedelete()));
}


void Usart::searchport()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Name : " << info.portName();
        TextIn->append("port:  "+info.portName());
        port->addItem(info.portName());
    }
}

void Usart::openport()
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
        timer->start(1000);
        isopen=true;
        TextIn->append("port:  "+comname+"  已打开");
    }
    else
    {
        isopen=false;
        TextIn->append("串口打开失败");
    }
}

void Usart::closeport()
{
    if(MySerialPort->isOpen())
    {
        timer->stop();
        MySerialPort->close();
        isopen=false;
        port->clear();
        TextIn->append("串口已关闭");
    }
}

void Usart::sendmessage()
{
    if(isopen==true)
    {
        if(!Textout->toPlainText().isEmpty())
        {
            ishex=hex->isChecked();
            QString sendstr=Textout->toPlainText();
            QByteArray sdata;
            if(ishex)
            {
                sdata.append(sendstr).toHex();
            }
            else
            {
                sdata.append(sendstr);
            }
            MySerialPort->write(sdata,sdata.length());
            TextMemory->addItem(sendstr);

            if(displayoutput->isChecked())
            {
                if(displaytime->isChecked())
                    TextIn->append(NowTime+"  "+sendstr+"  发送成功");
                else
                    TextIn->append(sendstr+"   发送成功");
            }
        }
    }
    else
    {
        if(displaytime->isChecked())
            TextIn->append(NowTime+"   发送失败");
        else
            TextIn->append("   发送失败");
    }
}

void Usart::receivemessage()
{

    QByteArray showdata;
    bool ok;
    showdata=MySerialPort->readAll();//如何顺序接受无间隔多路信号

    int showData;
    QString show="";
    ishex =hex->isChecked();
    if(hex->isChecked())
    {
        showData=showdata.toHex().toInt(&ok,16);
        show+=QString::number(showData,16);
    }

    else if(ascii->isChecked())
    {
        show+=QString(showdata);
    }
    else
    {
        showData=showdata.toHex().toInt(&ok,16);
        show+=QString::number(showData,10);

    }

    if(changeline->isChecked())
    {
        if(displaytime->isChecked())
            TextIn->append(NowTime+"   "+show);
        else
            TextIn->append("   "+show);
    }
    else
    {
        if(displaytime->isChecked())
            TextIn->setText(TextIn->toPlainText()+ NowTime+"   "+show);
        else
            TextIn->setText(TextIn->toPlainText()+"   "+show);
    }


}


void Usart::timeupdate()
{
    QDateTime time=QDateTime::currentDateTime();
    NowTime=time.toString("yyyy-MM-dd hh:mm:ss dddd");
}

void Usart::receivedelete()
{
    TextIn->setText("");
}

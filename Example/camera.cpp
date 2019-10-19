#include "camera.h"

Camera::Camera(QWidget *parent) : QWidget(parent)
{




    port0=new QCheckBox(tr("port0")),port1=new QCheckBox(tr("port1")),port2=new QCheckBox(tr("port2")),port3=new QCheckBox(tr("port3"));
    port4=new QCheckBox(tr("port4")),port5=new QCheckBox(tr("port5")),port6=new QCheckBox(tr("port6")),port7=new QCheckBox(tr("port7"));
    port8=new QCheckBox(tr("port8")),port9=new QCheckBox(tr("port9")),port10=new QCheckBox(tr("port10")),port11=new QCheckBox(tr("port11"));
    port12=new QCheckBox(tr("port12")),port13=new QCheckBox(tr("port13")),port14=new QCheckBox(tr("port14")),port15=new QCheckBox(tr("port15"));
    portnum0=new QLineEdit(),portnum1=new QLineEdit(),portnum2=new QLineEdit(),portnum3=new QLineEdit();
    portnum4=new QLineEdit(),portnum5=new QLineEdit(),portnum6=new QLineEdit(),portnum7=new QLineEdit();
    portnum8=new QLineEdit(),portnum9=new QLineEdit(),portnum10=new QLineEdit(),portnum11=new QLineEdit();
    portnum12=new QLineEdit(),portnum13=new QLineEdit(),portnum14=new QLineEdit(),portnum15=new QLineEdit();

    port_collect=QVector<QCheckBox *> {port0,port1,port2,port3,port4,port5,port6,port7,port8,port9,port10,port11,port12,port13,port14,port15};
    portnum_collect=QVector<QLineEdit *> {portnum0,portnum1,portnum2,portnum3,portnum4,portnum5,portnum6,portnum7,portnum8,portnum9,portnum10,portnum11,portnum12,portnum13,portnum14,portnum15};
    BotLeftLayout=new QGridLayout();

    for(int i=0;i<16;i++)
    {
        port_collect[i]->setFixedSize(55,20);
        portnum_collect[i]->setMaximumWidth(40);
        BotLeftLayout->addWidget(port_collect[i],(i/4),2*(i%4));
        BotLeftLayout->addWidget(portnum_collect[i],(i/4),2*(i%4)+1);
    }

    BotRightLayout=new QGridLayout();
    BotRRightLayout=new QHBoxLayout();
    mythread=new EMyThread();

    One_bit  =new QRadioButton(tr("二值图"));
    eight_bit=new QRadioButton(tr("灰度图"));
    ei_to_one=new QRadioButton(tr("灰度转二值"));
    middle_label=new QLabel(tr("转换阈值≥"));
    middle_num=new QLineEdit;
    middle_num->setMaximumWidth(60);
    One_bit->setMaximumWidth(60);
    eight_bit->setMaximumWidth(60);

    BotRightLayout->addWidget(mythread->PortText,0,0);
    BotRightLayout->addWidget(mythread->SearchPort,0,1);
    BotRightLayout->addWidget(One_bit,0,2);
    BotRightLayout->addWidget(eight_bit,0,3);
    BotRightLayout->addWidget(mythread->OpenPort,1,0);
    BotRightLayout->addWidget(mythread->ClosePort,1,1);
    BotRightLayout->addWidget(mythread->Port,2,0);
    BotRightLayout->addWidget(mythread->port,2,1);
    BotRightLayout->addWidget(mythread->Baud,3,0);
    BotRightLayout->addWidget(mythread->baud,3,1);
    BotRightLayout->addWidget(ei_to_one,1,2);
    BotRightLayout->addWidget(middle_label,2,2);
    BotRightLayout->addWidget(middle_num,2,3);
    BotRRightLayout->addWidget(mythread->Showbuf);



    BottomLayout =new QHBoxLayout();
    BottomLayout->addLayout(BotLeftLayout);
    BottomLayout->addLayout(BotRightLayout);
    BottomLayout->addLayout(BotRRightLayout);

    epoint=new EPoint();
    TopLayout    = new QHBoxLayout();
    TopLayout->addWidget(epoint);

    QVBoxLayout *MainLayout=new QVBoxLayout(this);
    MainLayout->setMargin(10);
    MainLayout->setSpacing(6);
    MainLayout->addLayout(TopLayout);
    MainLayout->addLayout(BottomLayout);

    mythread->start();
    time_break=new QTimer(this);
    connect(time_break,&QTimer::timeout,this,&time_out);
    time_break->start(1000);
    connect(mythread,SIGNAL(setsenddata(QByteArray)),this,SLOT(datashow(QByteArray)),Qt::QueuedConnection);
    connect(mythread,SIGNAL(setsenddata(QByteArray)),epoint,SLOT(toUpdate(QByteArray)),Qt::QueuedConnection);

}

Camera::~Camera()
{
    delete mythread;
}


void Camera::datashow(QByteArray data1)
{
    int data_show[16];
    for(int i=0;i<16;i++)
    {
        data_show[i]=data1[2*i+4]*256+(unsigned)(data1[2*i+5]&0xff);
        portnum_collect[i]->setText(QString::number(data_show[i],10));
    }
}


void Camera::time_out()
{
    if(One_bit->isChecked())
    {
        epoint->color_bit_select=1;
        mythread->color_bit_select=1;
    }
    else if(eight_bit->isChecked())
    {
        epoint->color_bit_select=255;
        mythread->color_bit_select=255;
    }
    else if(ei_to_one->isChecked())
    {
        bool ok;
        epoint->color_bit_select=81;
        epoint->middle_num=middle_num->text().toInt(&ok);
        qDebug()<<epoint->middle_num<<endl;
        mythread->color_bit_select=255;
    }
}

#include "electric.h"

Electric::Electric(QWidget *parent) : QWidget(parent)
{
    mythread=new EMyThread();
    echart=new Echart();
    send_bit=true;

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
    BotRightLayout->addWidget(mythread->PortText,0,0);
    BotRightLayout->addWidget(mythread->SearchPort,0,1);
    BotRightLayout->addWidget(mythread->OpenPort,1,0);
    BotRightLayout->addWidget(mythread->ClosePort,1,1);
    BotRightLayout->addWidget(mythread->Port,2,0);
    BotRightLayout->addWidget(mythread->port,2,1);
    BotRightLayout->addWidget(mythread->Baud,3,0);
    BotRightLayout->addWidget(mythread->baud,3,1);
    BotRightLayout->addWidget(mythread->NumBit,1,3);
    BotRightLayout->addWidget(mythread->numbit,1,4);
    BotRightLayout->addWidget(mythread->CheckBit,2,3);
    BotRightLayout->addWidget(mythread->checkbit,2,4);
    BotRightLayout->addWidget(mythread->StopBit,3,3);
    BotRightLayout->addWidget(mythread->stopbit,3,4);
    BotRRightLayout->addWidget(mythread->Showbuf);

    MemClear=new QPushButton(tr("Clear"));
    Pause  =new QPushButton(tr("pause"));
    BotRightLayout->addWidget(MemClear,0,3);
    BotRightLayout->addWidget(Pause,0,4);
    MemClear->setMaximumWidth(60);
    Pause->setMaximumWidth(60);

    BottomLayout =new QHBoxLayout();
    BottomLayout->addLayout(BotLeftLayout);
    BottomLayout->addLayout(BotRightLayout);
    BottomLayout->addLayout(BotRRightLayout);

    TopLayout  = new QHBoxLayout();
    TopLayout->addWidget(echart);
    mythread->start();

    QVBoxLayout *MainLayout=new QVBoxLayout(this);
    MainLayout->setMargin(10);
    MainLayout->setSpacing(6);
    MainLayout->addLayout(TopLayout);
    MainLayout->addLayout(BottomLayout);

    connect(mythread,SIGNAL(setsenddata(QByteArray)),this,SLOT(datashow(QByteArray)),Qt::QueuedConnection);
    connect(MemClear,SIGNAL(clicked(bool)),echart,SLOT(allclear()));
    connect(Pause,SIGNAL(clicked(bool)),this,SLOT(bit_change()));
}


void Electric::datashow(QByteArray data)
{
    if(send_bit)
    {
        int data_show[16];
        for(int i=0;i<16;i++)
        {
            data_show[i]=data[2*i+2]*256+(unsigned)(data[2*i+3]&0xff);
            portnum_collect[i]->setText(QString::number(data_show[i],10));
        }

        echart->draw(100,0,1);
        for(int i=0;i<16;i++)
            echart->draw(i,data_show[i],port_collect[i]->isChecked());


    }

}

Electric::~Electric()
{
    delete mythread;
}

void Electric::bit_change()
{
    send_bit=!send_bit;
    echart->move_flag=!echart->move_flag;
}

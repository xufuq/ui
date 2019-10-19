#include "epoint.h"

EPoint::EPoint(QWidget *parent) : QWidget(parent)
{
    QPalette pal(palette());
    Back_ground=QPixmap(":/image/1.jpg");
    Back_ground=Back_ground.scaled(1000,494);
    pal.setBrush(backgroundRole(),Back_ground);

    setAutoFillBackground(true);
    setPalette(pal);
    Picture=new QPixmap();

    for(int i=0;i<256;i++)
    {
        vcolorTable.append(qRgb(i,i,i));
    }
    for(int i=0;i<76800;i++)
    {
        imagedata[i]=0;
    }

    //setFixedSize(924,654);
    setFixedSize(1000,494);
    color_bit_select=1;
    middle_num=0;

}

//更新显示图像
void EPoint::paintEvent(QPaintEvent *event)
{
    qimage=PK8bitGrayToQim(imagedata,image_width,image_height);//生成指定大小的图像数据
    QPainter *p=new QPainter(this);
    p->drawImage(this->width()/2-qimage.width()/2,this->height()/2-qimage.height()/2,qimage);//在显示器中央显示图像

}

//把不同格式的图像转换成指定大小的图像
QImage EPoint::PK8bitGrayToQim(uchar *pBuffer, const int &bufwidth, const int &bufheight)
{

    QImage image=QImage(pBuffer,bufwidth,bufheight,QImage::Format_Indexed8);
    image.setColorTable(vcolorTable);
    image=image.scaled(640,480);
    return image;
}

//更新图像数据以及大小数据
void EPoint::toUpdate(QByteArray qbytearrar)
{
    image_height=qbytearrar[2]*10;
    image_width=qbytearrar[3]*10;
    if(color_bit_select==255)
    {
        for(int i=0;i<image_height*image_width;i++)
        {
            imagedata[i]=qbytearrar[i+36];
        }
    }

    else if(color_bit_select==1)
    {
        qDebug()<<11<<endl;
        for(uint i=0;i<image_height*image_width/8;i++)
        {
            uint ii=256;
            for(uint j=0;j<8;j++)
            {
                if((qbytearrar[i+36]%ii)/(ii/2)==1)
                    imagedata[8*i+j]=255;
                else
                    imagedata[8*i+j]=0;
                ii/=2;
            }
        }
    }
    else if(color_bit_select==81)
    {

        for(int i=0;i<image_height*image_width;i++)
        {
            imagedata[i]=qbytearrar[i+36]/middle_num;
        }
    }

    update();
}

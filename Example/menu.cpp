#include "menu.h"


Menu::Menu(QWidget *parent) : QWidget(parent)
{
    list=new QComboBox();
    list->insertItem(0,QObject::tr("串口调试助手"));
    list->insertItem(1,QObject::tr("示波器模式"));
    list->insertItem(2,QObject::tr("图像显示模式"));

    about=new QPushButton(tr("关于"));
    contact=new QPushButton(tr("联系我们"));
    cost =new QPushButton(tr("友情赞助"));
    word   =new QLabel(tr("由于作者水平有限，欢迎使用者指出此上位机缺陷与不足"));
    connect(about,SIGNAL(clicked()),this,SLOT(showAbout()));
    connect(contact,SIGNAL(clicked()),this,SLOT(showContact()));
    connect(cost,SIGNAL(clicked()),this,SLOT(showCost()));
    QHBoxLayout *TopLayout=new QHBoxLayout();
    QLabel *Topextra =new QLabel(tr("     "));
    QLabel *Topextra2=new QLabel(tr("     "));
    QLabel *Topextra3=new QLabel(tr("     "));
    TopLayout->addWidget(list);
    TopLayout->addWidget(about);
    TopLayout->addWidget(contact);
    TopLayout->addWidget(cost);
    TopLayout->addWidget(word);
    TopLayout->setSizeConstraint(QLayout::SetMinimumSize);

    QHBoxLayout *TOP=new QHBoxLayout(this);
    TOP->addLayout(TopLayout);
    TOP->addWidget(Topextra);
    TOP->addWidget(Topextra2);
    TOP->addWidget(Topextra3);

    pixmap=QPixmap(":/image/cost.jpg");
    cost_picture=new QLabel();
    pixmap=pixmap.scaled(200,200);


}


void Menu::showAbout()
{
    QMessageBox::about(this,tr("关于"),tr("JLU V1.0"));
}
void Menu::showContact()
{
    QMessageBox::about(this,tr("联系我们"),tr("作者：许富强   邮箱:17843124829@163.com"));
}


void Menu::showCost()
{
    QMessageBox::about(this,tr("友情赞助"),tr("支付宝赞助，感谢您的赞助"));
    cost_picture->resize(200,200);
    cost_picture->setPixmap(pixmap);
    cost_picture->move(800,400);
    cost_picture->setWindowTitle(tr("赞助"));
    cost_picture->show();

}

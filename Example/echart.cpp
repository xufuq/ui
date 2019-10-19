#include "echart.h"
#include <QDebug>


Echart::Echart(QWidget *parent) : QWidget(parent)
{

    int penwidth=2;
    xyshow=new QLabel();
    x_move=0;
    move_flag=false;

    xGrid=0;
    line  =new QLineSeries;
    line0 =new QLineSeries();
    line1 =new QLineSeries();
    line2 =new QLineSeries();
    line3 =new QLineSeries();
    line4 =new QLineSeries();
    line5 =new QLineSeries();
    line6 =new QLineSeries();
    line7 =new QLineSeries();
    line8 =new QLineSeries();
    line9 =new QLineSeries();
    line10=new QLineSeries();
    line11=new QLineSeries();
    line12=new QLineSeries();
    line13=new QLineSeries();
    line14=new QLineSeries();
    line15=new QLineSeries();
    data_collect=QVector<QVector<QPointF>> {data0,data1,data2,data3,data4,data5,data6,data7,data8,data9,data10,data11,data12,data13,data14,data15};
    line_collect=QVector<QLineSeries *>    {line0,line1,line2,line3,line4,line5,line6,line7,line8,line9,line10,line11,line12,line13,line14,line15};

    pen.setWidth(penwidth);
    pen.setColor(QColor(255,0,0));
    line->setPen(pen);
    pen0.setWidth(penwidth);
    pen0.setColor(QColor(0,255,0));
    line0->setPen(pen0);
    pen1.setWidth(penwidth);
    pen1.setColor(QColor(0,0,255));
    line1->setPen(pen1);
    pen2.setWidth(penwidth);
    pen2.setColor(QColor(255,0,0));
    line2->setPen(pen2);
    pen3.setWidth(penwidth);
    pen3.setColor(QColor(255,0,255));
    line3->setPen(pen3);
    pen4.setWidth(penwidth);
    pen4.setColor(QColor(0,255,255));
    line4->setPen(pen4);
    pen5.setWidth(penwidth);
    pen5.setColor(QColor(0,0,0));
    line5->setPen(pen5);
    pen6.setWidth(penwidth);
    pen6.setColor(QColor(217,217,25));
    line6->setPen(pen6);
    pen7.setWidth(penwidth);
    pen7.setColor(QColor(25,100,60));
    line7->setPen(pen7);
    pen8.setWidth(penwidth);
    pen8.setColor(QColor(200,60,80));
    line8->setPen(pen8);
    pen9.setWidth(penwidth);
    pen9.setColor(QColor(60,200,200));
    line9->setPen(pen9);
    pen10.setWidth(penwidth);
    pen10.setColor(QColor(255,90,200));
    line10->setPen(pen10);
    pen11.setWidth(penwidth);
    pen11.setColor(QColor(160,144,160));
    line11->setPen(pen11);
    pen12.setWidth(penwidth);
    pen12.setColor(QColor(35,35,142));
    line12->setPen(pen12);
    pen13.setWidth(penwidth);
    pen13.setColor(QColor(80,100,80));
    line13->setPen(pen13);
    pen14.setWidth(penwidth);
    pen14.setColor(QColor(150,80,150));
    line14->setPen(pen14);
    pen15.setWidth(penwidth);
    pen15.setColor(QColor(133,99,99));
    line15->setPen(pen15);

    mainwindow=new QHBoxLayout(this);


    line->replace(dataa);
    MyChart=new QChart();

    MyChart->addSeries(line);
    for(int i=0;i<16;i++)
    {
        MyChart->addSeries(line_collect[i]);
    }

    MyChart->createDefaultAxes();
    drawXGrid(0,1750);
    drawYGrid(-350,350);
    YEnd=350;
    //MyChart->setBackgroundBrush(QBrush("black"));


    MyChartView =new QChartView(MyChart);
    //MyChartView->setFixedSize(1750,700);
    MyChartView->setBackgroundBrush(QBrush("black"));

    mainwindow->addWidget(MyChartView);

    for(int i=0;i<16;i++)
    {
        connect(line_collect[i],&QLineSeries::hovered, this, &Echart::slotPointHoverd);
    }


}

void Echart::draw(int rank,int num,bool ischecked)
{
    MyChart->createDefaultAxes();
    if(rank==100)
    {
        xGrid+=5;
        if(xGrid>XEnd)
            drawXGrid(xGrid-1750,xGrid);
        else
            drawXGrid(0,XEnd);
    }
    else
    {
        drawXGrid(XEnd-1750,XEnd);
    }
    if(ischecked)
    {
        if(num>YEnd)
            drawYGrid(-num-10,num+10);
        else if(num<-YEnd)
            drawYGrid(num-10,-num+10);
        else
            drawYGrid(-YEnd,YEnd);
    }
    else
    {
        drawYGrid(-YEnd,YEnd);
    }

    if(rank<=15)
    {
//        if(data_collect[rank].count()<350)
//            data_collect[rank].append(QPointF(xGrid,num));
//        else
//        {
//            data_collect[rank].pop_front();
//            data_collect[rank].push_back(QPointF(xGrid,num));
//        }

//        if(ischecked)
//        {
//            line_collect[rank]->replace(data_collect[rank]);

//        }
//        else
//        {
//            data_collect[rank].pop_back();
//            data_collect[rank].push_back(QPointF(xGrid,0));
//            line_collect[rank]->replace(data_collect[rank]);
//        }

        data_collect[rank].append(QPointF(xGrid,num));
        if(ischecked)
        {
            line_collect[rank]->replace(data_collect[rank]);

        }
        else
        {
            data_collect[rank].pop_back();
            data_collect[rank].push_back(QPointF(xGrid,0));
            line_collect[rank]->replace(data_collect[rank]);
        }
    }




}


void Echart::drawXGrid(int xStart,int xEnd)
{
    XStart=xStart,XEnd=xEnd;
    MyChart->axisX()->setRange(xStart,xEnd);
    QValueAxis *axisx=new QValueAxis();
    axisx->setRange(xStart,xEnd);
    axisx->setGridLineVisible(true);
    axisx->setTickCount(36);
    axisx->setMinorTickCount(1);
    MyChart->setAxisX(axisx);
}

void Echart::drawYGrid(int yStart,int yEnd)
{
    YEnd=yEnd;
    MyChart->axisY()->setRange(yStart,yEnd);
    QValueAxis *axisy=new QValueAxis();
    axisy->setRange(yStart,yEnd);
    axisy->setGridLineVisible(true);
    axisy->setTickCount(21);
    axisy->setMinorTickCount(1);
    MyChart->setAxisY(axisy);
}

void Echart::mousePressEvent(QMouseEvent *event)
{

    if(move_flag)
    {
        x_move=event->x()-(XStart+XEnd)/2;
        MyChart->createDefaultAxes();
        drawXGrid(XStart-x_move,XEnd-x_move);
        if(XStart<0)
            drawXGrid(0,1750);
        else if(XEnd>xGrid)
            drawXGrid(xGrid-1750,xGrid);
        drawYGrid(-YEnd,YEnd);

        for(int rank=0;rank<16;rank++)
        {
            line_collect[rank]->replace(data_collect[rank]);
        }
    }
}


void Echart::slotPointHoverd(const QPointF &point, bool state)
{
    if(state)
    {
        xyshow->setText(tr("(")+QString::asprintf("%1.0f",point.x())+tr(",")+QString::asprintf("%1.0f",point.y())+tr(")"));
        QPoint curPos = mapFromGlobal(QCursor::pos());
        xyshow->move(curPos.x(), curPos.y()+80);
        xyshow->setWindowFlags(Qt::FramelessWindowHint);
        xyshow->show();
    }
//    else
//        xyshow->hide();

}


void Echart::allclear()
{
    for(int i=0;i<16;i++)
    {
        data_collect[i].clear();
        line_collect[i]->replace(data_collect[i]);
    }
    MyChart->createDefaultAxes();
    drawXGrid(0,1750);
    drawYGrid(-350,350);
    YEnd=350;
    xGrid=0;

}

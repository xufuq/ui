#ifndef ECHART_H
#define ECHART_H

#include <QWidget>
#include <QAreaSeries>
#include <QBarSeries>
#include <QChart>
#include <QChartView>
#include <QValueAxis>
#include <QLineSeries>
#include <QChartGlobal>
#include <QHBoxLayout>
#include <QVector>
#include <QRubberBand>
#include <QMouseEvent>
#include <QLineEdit>
#include <QLabel>


QT_CHARTS_USE_NAMESPACE

class Echart : public QWidget
{
    Q_OBJECT
public:
    explicit Echart(QWidget *parent = nullptr);
    void draw(int rank, int num,bool ischecked);
    void drawXGrid(int xStart, int xEnd);
    void drawYGrid(int yStart, int yEnd);
    void mousePressEvent(QMouseEvent *event);

    bool move_flag;
private:
    QChart      *MyChart;
    QChartView  *MyChartView;
    QLineSeries *line;
    QLineSeries *line0, *line1, *line2, *line3,
                *line4, *line5, *line6, *line7,
                *line8, *line9, *line10,*line11,
                *line12,*line13,*line14,*line15;

    QPen        pen0, pen1, pen2, pen3,pen,
                pen4, pen5, pen6, pen7,
                pen8, pen9, pen10,pen11,
                pen12,pen13,pen14,pen15;

    QVector<QPointF> data0, data1, data2, data3,
                     data4, data5, data6, data7,
                     data8, data9, data10,data11,
                     data12,data13,data14,data15,
                     dataa;
    QPointF EarlyPoint;
    QPointF LaterPoint;
    int xGrid,XStart,XEnd,YEnd;
    int x_move;

    QHBoxLayout *mainwindow;
    QLabel *xyshow;
    QVector<QVector<QPointF>> data_collect;
    QVector<QLineSeries *>    line_collect;
signals:

public slots:
    void slotPointHoverd(const QPointF &point, bool state);
    void allclear();
};

#endif // ECHART_H

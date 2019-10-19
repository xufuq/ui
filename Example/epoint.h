#ifndef EPOINT_H
#define EPOINT_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QPalette>      //设置背景颜色等
#include <QDebug>

class EPoint : public QWidget
{
    Q_OBJECT
public:
    explicit EPoint(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    QImage PK8bitGrayToQim(uchar *pBuffer, const int &bufwidth, const int &bufheight);
    int color_bit_select;
    int middle_num;

signals:

private:
    QPixmap  *Picture;
    QPixmap  Back_ground;
    QImage   qimage;
    QVector<QRgb> vcolorTable;
    uchar imagedata[76800];
    int image_width,image_height;

public slots:
    void toUpdate(QByteArray qbytearrar);
};

#endif // EPOINT_H

//添加的头文件
#include <QStackedWidget>
#include <QPushButton>
#include "usart.h"
#include "camera.h"
#include "electric.h"
class Content : public QFrame
{
    Q_OBJECT
public:
    Content(QWidget *parent=0);
    QStackedWidget *stack;

    Usart    *usart;
    Electric *electric;
    Camera   *camera;
public slots:
    void set_pattern(int x);
};


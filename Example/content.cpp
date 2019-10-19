#include "content.h"

Content::Content(QWidget *parent)
    :QFrame(parent)
{
    stack =new QStackedWidget(this);
    stack->setFrameStyle(QFrame::Panel|QFrame::Raised);
    usart =new Usart();
    electric=new Electric();
    camera=new Camera();

    //堆栈，放置三种状态
    stack->addWidget(usart);
    stack->addWidget(electric);
    stack->addWidget(camera);



    QVBoxLayout *RightLayout =new QVBoxLayout(this);
    RightLayout->setMargin(10);
    RightLayout->setSpacing(6);
    RightLayout->addWidget(stack); //添加元素

}
void Content::set_pattern(int x)
{
    electric->mythread->pattern_select=x;
    camera->mythread->pattern_select=x;
}

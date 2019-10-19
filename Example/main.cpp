#include "content.h"
#include "menu.h"
#include "windows.h"
#include <QApplication>
#include <QTextCodec>
#include <QSplitter>
#include <QListWidget>
#include <QComboBox>
#include <QPixmap>
#include <QSplashScreen>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/image/Qt.png");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();

    QSplitter *splitterMain =new QSplitter(Qt::Vertical,0);//新建水平分割窗口
    splitterMain->setOpaqueResize(false);

    Menu *menu=new Menu(splitterMain);
    Content *content =new Content(splitterMain); //都在分割窗口上作为基类，所以可以分割显示
    QObject::connect(menu->list,SIGNAL(currentIndexChanged(int)),content->stack,SLOT(setCurrentIndex(int)));
    QObject::connect(menu->list,SIGNAL(currentIndexChanged(int)),content,SLOT(set_pattern(int)));
    splitterMain->setWindowTitle(QObject::tr("三合一上位机"));
    splitterMain->setMinimumSize(splitterMain->minimumSize());
    splitterMain->setMaximumSize(splitterMain->maximumSize());
    splitterMain->show();
    splitterMain->move((a.desktop()->width()-splitterMain->width())/2,(a.desktop()->height()-splitterMain->height())/2);
    splash.finish(splitterMain);
    return a.exec();
}



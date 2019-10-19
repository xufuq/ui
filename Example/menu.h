#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QPixmap>

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = nullptr);

    QPushButton *about;
    QPushButton *contact;
    QLabel      *word;
    QComboBox   *list;
    QPushButton *cost;
    QPixmap pixmap;
    QLabel  *cost_picture;

signals:

private slots:
    void showAbout();
    void showContact();
    void showCost();
};

#endif // MENU_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>
#include <QLabel>
#include <QImage>
#include <QDebug>
#include <QPixmap>
#include "mythread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void changePicture_1(QImage *image);
    void changePicture_2(QImage *image);

private slots:
    void on_pushButtonStart_clicked();

    void on_pushButtonStop_clicked();

    void on_pushButtonEnd_clicked();

private:
    Ui::Widget *ui;
    MyThread *thread;
    MyThread *thread_2;
    int pictureWidth;
    int pictureHeight;
    bool isPause;
    bool isStart;
    void freshButton();
    void showPicture(QLabel* label, QImage *image);
};
#endif // WIDGET_H

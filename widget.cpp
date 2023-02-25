#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    isPause = false;
    isStart = false;

    pictureWidth = ui->pictureLabel_1->width();
    pictureHeight = ui->pictureLabel_1->height();

    thread = nullptr;
    thread_2 = nullptr;

    freshButton();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changePicture_1(QImage *image)
{
    showPicture(ui->pictureLabel_1, image);
}

void Widget::changePicture_2(QImage *image)
{
    showPicture(ui->pictureLabel_2, image);
}

void Widget::showPicture(QLabel* label, QImage *image)
{
    QPixmap pixmap = QPixmap::fromImage(*image);
    QPixmap fitpixmap = pixmap.scaled(pictureWidth, pictureHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    if(thread != nullptr && thread_2 != nullptr) {
        label->setPixmap(fitpixmap);
    }
}

void Widget::on_pushButtonStart_clicked()
{
    if(isPause) {
        thread->resumeThread();
        thread_2->resumeThread();
    }
    if(thread)
    {
        thread->close();
        thread->deleteLater();
    }
    if(thread_2)
    {
        thread_2->close();
        thread_2->deleteLater();
    }
    thread = new MyThread;
    thread_2 = new MyThread;

    connect(thread, SIGNAL(curImage(QImage*)), this, SLOT(changePicture_1(QImage*)));
    connect(thread_2, SIGNAL(curImage(QImage*)), this, SLOT(changePicture_2(QImage*)));

    thread->start();
    thread_2->start();
    isPause = false;
    isStart = true;
    freshButton();
}


void Widget::on_pushButtonStop_clicked()
{
    if(!isStart) {
        return;
    }
    if(isPause) {
        qDebug() << "thread resume";
        thread->resumeThread();
        thread_2->resumeThread();
        isPause = false;
    } else {
        qDebug() << "thread pause";
        thread->pauseThread();
        thread_2->pauseThread();
        isPause = true;
    }
    freshButton();
}


void Widget::on_pushButtonEnd_clicked()
{
    if(!isStart) {
        return;
    }
    ui->pictureLabel_1->clear();
    ui->pictureLabel_2->clear();
    if(isPause) {
        thread->resumeThread();
        thread_2->resumeThread();
    }
    thread->close();
    thread_2->close();
    thread->deleteLater();
    thread_2->deleteLater();
    thread = nullptr;
    thread_2 = nullptr;
    isPause = false;
    isStart = false;
    freshButton();
}

void Widget::freshButton()
{
    if(!isStart) {
        ui->pushButtonEnd->setEnabled(false);
        ui->pushButtonStop->setEnabled(false);
    } else {
        ui->pushButtonEnd->setEnabled(true);
        ui->pushButtonStop->setEnabled(true);
    }
    if(!isPause) {
        ui->pushButtonStop->setText("暂停");
    } else {
        ui->pushButtonStop->setText("继续");
    }
}

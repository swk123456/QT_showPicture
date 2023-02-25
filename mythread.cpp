#include "mythread.h"

MyThread::MyThread()
{
    stop = false;
    pause = false;
    pictureID = 1;
}

MyThread::~MyThread()
{
    if(this->pauseLock.tryLock()) {
        //this->pauseLock.unlock();
    }
}

void MyThread::close()
{
    stop = true;
    quit();
    wait();
    qDebug() << "thread stop";
}

void MyThread::pauseThread()
{
    qDebug() << "pauseThread";
    this->pauseLock.lock();
    pause = true;
}

void MyThread::resumeThread()
{
    qDebug() << "resumeThread";
    this->pauseLock.unlock();
    pause = false;
}

void MyThread::run()
{
    qDebug() << "thread start";
    while(true)
    {
        if(!stop)
        {
            //线程锁在业务开始与结束
            pauseLock.lock();

            QImage *img = new QImage;
            QString filePath(FILE_PATH + QString::number(pictureID) + QString(".png"));
            qDebug() << filePath;
            img->load(filePath);

            pictureID++;
            if(pictureID == 11) {
                pictureID = 1;
            }

            emit curImage(img);

            pauseLock.unlock();
            sleep(1);
        }
        else
        {
            break;
        }
    }
}

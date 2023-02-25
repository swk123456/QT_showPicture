#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QImage>
#include <QDebug>
#include <QCoreApplication>
#include <QMutex>
#include <QReadWriteLock>
#include "config_file.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread();
    ~MyThread();

    void close();
    void pauseThread();
    void resumeThread();

signals:
    void curImage(QImage *image);

protected:
    void run();

private:
    volatile bool stop;
    bool pause;
    QMutex pauseLock;
    int pictureID;
};

#endif // MYTHREAD_H

//#ifndef WORKTHREAD_H
//#define WORKTHREAD_H

#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H
#include <QThread>
class  Camerathread : public QThread
{
    Q_OBJECT
public:
    Camerathread();

signals:
    void show(const QString &name);


protected:
     void run();
};

#endif // WORKTHREAD_H

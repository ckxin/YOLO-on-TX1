#ifndef GRABTHREAD_H
#define GRABTHREAD_H

#include <QThread>
class  GrabThread : public QThread
{
    Q_OBJECT
public:
     GrabThread();

signals:
    void Grab(const QString &name);


protected:
     void run();
};



#endif // GRABTHREAD_H


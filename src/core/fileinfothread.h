#ifndef FILEINFOTHREAD_H
#define FILEINFOTHREAD_H
#include <QThread>

class FileInfoThread : public QThread
{

public:
    FileInfoThread();
    void run();

};

#endif // FILEINFOTHREAD_H

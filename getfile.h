#ifndef GETFILE_H
#define GETFILE_H
#include<QWidget>
#include <QObject>
#include<qdebug.h>
#include<QImage>
#include<QObject>

class getfile:public QObject
{
    Q_OBJECT
public:
    getfile();
public slots:
    void getsavefileName(QImage*);
    void getloadfileName(QImage*);

};

#endif // GETFILE_H

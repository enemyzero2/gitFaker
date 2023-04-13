#include <QApplication>
#include <iostream>
#include<QWidget>//窗口
#include <QIcon>//图标设置
#include <QPushButton>
#include <point.h>
#include <mainwindow.h>
#include<circle.h>
#include<color.h>
#include<colordialog.h>
int main(int argc,char*argv[]){
    QApplication a(argc,argv);
    MainWindow w;
    w.setWindowTitle("图形编辑系统");
    w.setWindowIcon(QIcon("D:/photo/xiubi.jpg"));
    w.setMinimumSize(1920,1080);
    w.show();
    a.exec();
    return 0;
}

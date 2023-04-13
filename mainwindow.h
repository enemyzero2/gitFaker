#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <point.h>
#include<circle.h>
#include <rect.h>
#include<triangle.h>
#include<color.h>
#include<colordialog.h>
#include<returnlast.h>
#include<QMenu>
#include<QAction>
#include<QMenuBar>
#include<QFileDialog>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // 绘图区域的像素点
    QImage m_image;
    // 当前操作的绘图形状
    enum ShapeType {
        ShapePoint,
        ShapeCircle,
        ShapeRect,
        ShapeTriangle
    } m_shapeType;
    Point *startPoint;
    Point *endPoint;
    Point *thirdPoint;
    d_circle *x ;
    n_Rect* rect;
    Triangle* triangle;
    ColorDialog *colorDialog;
    ReturnLast *returnlast;
    QMenuBar *menubar;
    QMenu *pmenu;
    QMenu *pmenu2;
    QAction *paction;
    QAction *paction2;
    QAction *paction3;
    QAction *paction4;
private:
    bool eventFilter(QObject *obj, QEvent *event) override;
private slots:
    void pushButton_clicked_Point();
    void pushButton_clicked_Circle();
    void pushButton_clicked_Rect();
    void pushButton_clicked_Triangle();
    void pushButton_clicked_clearImage();
    void paintEvent(QPaintEvent *event) override;
    void clearImage();
    void updateimage(QPixmap);
    void saveimage();
    void loadimage();

};

#endif // MAINWINDOW_H

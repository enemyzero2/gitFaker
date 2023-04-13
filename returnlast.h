#ifndef RETURNLAST_H
#define RETURNLAST_H
#include<QWidget>
#include<QPixmap>
#include<QStack>
#include<QPoint>
#include<QPushButton>
#include<QImage>

class ReturnLast :public QWidget
{
    Q_OBJECT
public:
    ReturnLast(QWidget *paRent =nullptr);
private:
    QPixmap m_pixmap;
    QStack<QPixmap> m_undoStack;
    QStack<QPixmap> m_redoStack;
    QPoint m_previousPosition;
private slots:
    void undo();
    void redo();
public:
    void savePixmap(QImage*);
signals:
    QPixmap imageChanged(QPixmap);
};

#endif // RETURNLAST_H

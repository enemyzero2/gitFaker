#include "returnlast.h"
#include<QHBoxLayout>
#include<QEvent>
#include<QDebug>
ReturnLast::ReturnLast(QWidget *parent)
{
installEventFilter(this);

m_undoStack.clear();
m_redoStack.clear();

QPushButton *undoButton=new QPushButton(tr("Undo"));
QPushButton *redoButton=new QPushButton(tr("Redo"));
auto *buttonLayout=new QHBoxLayout;
buttonLayout->addWidget(undoButton);
buttonLayout->addWidget(redoButton);
QVBoxLayout *mainLayout = new QVBoxLayout(this);
mainLayout->addLayout(buttonLayout);
setLayout(mainLayout);


}
void ReturnLast::undo()
{
    if (m_undoStack.isEmpty()) {
       return;
    }
    else{
    QPixmap lastPixmap = m_undoStack.pop();
    m_redoStack.push(lastPixmap);
    QPixmap currentPixmap = m_undoStack.top();
    qDebug() << "valueChanged signal emitted";
    emit imageChanged(currentPixmap);
    }
}

void ReturnLast::redo()
{
    if (m_redoStack.isEmpty()) {
        return;
    }
    else {
    QPixmap lastPixmap = m_redoStack.pop();
    m_undoStack.push(lastPixmap);
    QPixmap currentPixmap = m_undoStack.top();
    emit imageChanged(currentPixmap);}

}
// 保存当前界面图片
void ReturnLast::savePixmap(QImage* m_image)
{
    m_redoStack.clear(); // 清空重做栈
    QPixmap currentPixmap = QPixmap::fromImage(*m_image); // 获取当前界面图片
    m_undoStack.push(currentPixmap); // 存入撤销栈
    qDebug() << "pixmap emitted";
}
QPixmap imageChanged(QPixmap a){
    return a;
}

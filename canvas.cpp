#include <QWidget>
class Canvas : public QWidget
{
public:
    Canvas(QWidget *parent = nullptr) : QWidget(parent)
    {
        setMinimumSize(400, 300);
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);

        // 在右侧画布区域绘制所需的图形
        painter.setPen(QPen(Qt::black, 1));
        painter.drawLine(0, 0, width(), height());
    }
};

#ifndef COLOR_H
#define COLOR_H
#include<QtWidgets>
#include<QSpinBox>
#include<QtDebug>
#include <QObject>
#include<QWidget>
class ColorWidget : public QWidget {
    Q_OBJECT
signals:
    void colorchanged();
public:
    ColorWidget(QWidget *parent=nullptr);
    int red() const { return rSpinBox->value(); }
    int green() const { return gSpinBox->value(); }
    int blue() const { return bSpinBox->value(); }

public:
    QSpinBox *rSpinBox;
    QSpinBox *gSpinBox;
    QSpinBox *bSpinBox;
};

#endif // COLOR_H


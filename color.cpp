#include<QApplication>
#include "color.h"
ColorWidget::ColorWidget(QWidget *parent) : QWidget(parent) {
    rSpinBox = new QSpinBox;
    rSpinBox->setRange(0, 255);

    gSpinBox = new QSpinBox;
    gSpinBox->setRange(0, 255);

    bSpinBox = new QSpinBox;
    bSpinBox->setRange(0, 255);

    auto layout = new QHBoxLayout(this);
    layout->addWidget(new QLabel("R:"));
    layout->addWidget(rSpinBox);
    layout->addWidget(new QLabel("G:"));
    layout->addWidget(gSpinBox);
    layout->addWidget(new QLabel("B:"));
    layout->addWidget(bSpinBox);
   //connect(rSpinBox, SIGNAL(valueChanged(int)), this, SLOT(emitchanged()));
    //connect(gSpinBox, SIGNAL(valueChanged(int)), this, SLOT(emitchanged()));
    //connect(bSpinBox, SIGNAL(valueChanged(int)), this, SLOT(emitchanged()));
}

#ifndef COLORDIALOG_H
#define COLORDIALOG_H
#include<QWidget>
#include <QObject>
#include<color.h>
#include<qdebug.h>

class ColorDialog : public QDialog {
    Q_OBJECT
public:
    friend ColorWidget;
    ColorDialog(QWidget *parent = nullptr) : QDialog(parent) {
        colorWidget = new ColorWidget;

        previewWidget = new QWidget;
        previewWidget->setFixedSize(40, 40);
        previewWidget->setAutoFillBackground(true);
        updatePreview();

        auto layout = new QVBoxLayout(this);
        layout->addWidget(colorWidget);
        layout->addWidget(new QLabel("Preview:"));
        layout->addWidget(previewWidget);

        auto okButton = new QPushButton("OK");
        auto cancelButton = new QPushButton("Cancel");
        auto buttonLayout = new QHBoxLayout;
        buttonLayout->addStretch();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);
        layout->addLayout(buttonLayout);

        connect(colorWidget->rSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
        connect(colorWidget->gSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
        connect(colorWidget->bSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
        connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
        connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
        update();
    }

    QColor color() const { return currentColor; }

private:
    ColorWidget *colorWidget;
    QWidget *previewWidget;
    QColor currentColor;
public slots:
    Q_SLOT void updatePreview() {
        currentColor = QColor(colorWidget->red(), colorWidget->green(), colorWidget->blue());
        previewWidget->setPalette(QPalette(currentColor));
        //qDebug() << "valueChanged signal emitted";
        previewWidget->update();
        update();
    }
};

#endif // COLORDIALOG_H

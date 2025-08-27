#include "ViewWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include "qmessagebox.h"
#include "qnamespace.h"
#include "qpalette.h"

ViewWidget::ViewWidget(QWidget* parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    label = new QLabel("PDF渲染窗口");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    label->close();

    scrollArea = new QScrollArea(this);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFixedSize(1000, 600);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->close();
    
    changeFlip("left-right");
}

void ViewWidget::changeImage(const QImage& image) {
    if(image.isNull()){
        label->setText("无法渲染页面");
        return;
    }
    label->setPixmap(QPixmap::fromImage(image));
}

void ViewWidget::loadScrollArea(QList<QImage> imageCache){
    if(imageCache.empty()){
        return;
    }
    scrollWidget = new QWidget();
    scrollLayout = new QVBoxLayout(scrollWidget);
    for(auto image : imageCache){
        QLabel* label = new QLabel();
        label->setPixmap(QPixmap::fromImage(image));
        label->setScaledContents(true);
        scrollLayout->addWidget(label);
    }
    scrollArea->setWidget(scrollWidget);
    
}

void ViewWidget::changeFlip(QString flip){
    if(flip == "left-right"){
        scrollArea->close();
        label->show();
    }else if(flip == "scroll"){
        label->close();
        scrollArea->show();
    }
    this->flip = flip;
}
#include "ViewWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include "qgraphicsitem.h"
#include "qgraphicsview.h"
#include "qmessagebox.h"
#include "qnamespace.h"
#include "qpalette.h"
#include "qpixmap.h"

ViewWidget::ViewWidget(QWidget* parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing, true);
    view->setRenderHint(QPainter::TextAntialiasing, true);
    view->setRenderHint(QPainter::SmoothPixmapTransform, true);
    view->setAlignment(Qt::AlignCenter);
    view->setBackgroundRole(QPalette::Dark);
    pixmapItem = nullptr;
    layout->addWidget(view);
    setMinimumSize(200, 200);
    setAutoFillBackground(true);

    scrollView = new QGraphicsView();
    scrollView->setRenderHint(QPainter::Antialiasing, true);
    scrollView->setRenderHint(QPainter::TextAntialiasing, true);
    scrollView->setRenderHint(QPainter::SmoothPixmapTransform, true);
    scrollView->setAlignment(Qt::AlignCenter);
    scrollView->setBackgroundRole(QPalette::Dark);
    scrollView->close();
    scrollScene = nullptr;

    changeFlip("left-right");
}

void ViewWidget::changeImage(const QImage& image) {
    scene->clear();
    if (image.isNull()) {
        pixmapItem = nullptr;
        return;
    }
    QPixmap pixmap = QPixmap::fromImage(image);
    pixmapItem = scene->addPixmap(pixmap);
    pixmapItem->setTransformationMode(Qt::SmoothTransformation);
    scene->setSceneRect(pixmap.rect());
    view->fitInView(pixmapItem, Qt::KeepAspectRatio);
}

void ViewWidget::loadScrollArea(QList<QImage> imageCache){
    if(imageCache.empty()){
        return;
    }
    if(scrollScene!= nullptr)
    {
        scrollView->setScene(nullptr);
        delete scrollScene;
    }
    scrollScene = new QGraphicsScene(this);
    int height = 0;
    for(auto image : imageCache){
        QPixmap pixmap = QPixmap::fromImage(image.scaled(scrollView->width(),scrollView->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
        QGraphicsPixmapItem* item = scrollScene->addPixmap(pixmap);
        item->setPos(0,height); 
        height += pixmap.height();
    }
    scrollView->setScene(scrollScene);
}

void ViewWidget::changeFlip(QString flip){
    if(flip != "left-right" && flip != "scroll"){
        QMessageBox::warning(this, "Error", "Invalid flip value");
        return;
    }
    if(flip == this->flip){
        return;
    }
    if(flip == "left-right" && this->flip == "scroll"){
        layout->removeWidget(scrollView);
        layout->addWidget(view);
        scrollView->close();
        view->show();
    }else if(flip == "scroll" && this->flip == "left-right"){
        layout->removeWidget(view);
        layout->addWidget(scrollView);
        view->close();
        scrollView->show();
    }
    this->flip = flip;
}
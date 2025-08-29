#pragma once

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QImage>
#include <QPixmap>
#include "qboxlayout.h"
#include "qgraphicsview.h"
#include "qobject.h"
#include "qscrollarea.h"
#include "qtmetamacros.h"
#include "QScrollArea"
#include "qwidget.h"
#include <QString>
#include <memory>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class ViewWidget : public QWidget {
    Q_OBJECT

public:
    ViewWidget(QWidget* parent = nullptr);
public slots:
    void changeImage(const QImage& image);
    void loadScrollArea(QList<QImage> imageCache);
    void changeFlip(QString flip);
private:
    QGraphicsView* view;
    QGraphicsScene* scene;
    QGraphicsPixmapItem* pixmapItem;
    QVBoxLayout* layout;

    QGraphicsView* scrollView;
    QGraphicsScene* scrollScene;
    QVBoxLayout* scrollLayout;

    QString flip = "left-right";
};
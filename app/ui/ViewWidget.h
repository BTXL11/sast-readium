#pragma once

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QImage>
#include <QPixmap>
#include "qboxlayout.h"
#include "qscrollarea.h"
#include "qtmetamacros.h"
#include "QScrollArea"
#include "qwidget.h"
#include <QString>
#include <memory>

class ViewWidget : public QWidget {
    Q_OBJECT

public:
    ViewWidget(QWidget* parent = nullptr);
public slots:
    void changeImage(const QImage& image);
    void loadScrollArea(QList<QImage> imageCache);
    void changeFlip(QString flip);
private:
    QLabel* label;
    QVBoxLayout* layout;
    QVBoxLayout* scrollLayout;
    QWidget* scrollWidget;
    QScrollArea* scrollArea;
    QString flip = "left-right";
};
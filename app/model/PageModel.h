#pragma once

#include <QObject>
#include <QSharedPointer>
#include "RenderModel.h"
#include "qimage.h"
#include <QList>
#include <QMessageBox>

class PageModel : public QObject {
    Q_OBJECT

public:
    PageModel(int totalPages = 1, QObject* parent = nullptr);
    PageModel(RenderModel* renderModel, QObject* parent = nullptr);

    int currentPage() const;
    int totalPages() const;

    void setCurrentPage(int pageNum);
    QImage pageAt(int pageNum) const;
    void nextPage();
    void prevPage();

    ~PageModel(){};
public slots:
    void updateInfo(Poppler::Document* document);
    void updateImageCache(QList<QImage> imageCache) { _ImageCache = imageCache; }

signals:
    void pageUpdate(int currentPage);
    //void pageUpdate(QImage image);

private:
    int _totalPages;
    int _currentPage;
    RenderModel* _renderModel;
    QList<QImage> _ImageCache;
};
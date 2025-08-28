#include "DocumentModel.h"
#include "RenderModel.h"
#include "qimage.h"
#include <QList>

DocumentModel::DocumentModel(RenderModel* _renderModel): renderModel(_renderModel) {
    qDebug() << "DocumentModel created";
}

bool DocumentModel::isNULL() { return false; }

bool DocumentModel::openFromFile(const QString& filePath) {
    if (filePath.isEmpty() || !QFile::exists(filePath)) {
        qWarning() << "Invalid file path:" << filePath;
        return false;
    }

    auto _document = Poppler::Document::load(filePath);
    if (!_document) {
        qDebug() << "Failed to load document:" << filePath;
        return false;
    }
    if(document){
        document.release();
    }
    document = std::move(_document);
    currentFilePath = filePath;
    qDebug() << "Opened successfully:" << filePath;

    renderModel->setDocument(document.get());
    QList<QImage> imageCache;
    for(int i=0;i<document->numPages();i++){
        imageCache.append(renderModel->renderPage(i,432.0,432.0,-1,-1,-1,-1));
    }
    emit renderAllPagesDone(imageCache);

    return true;
}

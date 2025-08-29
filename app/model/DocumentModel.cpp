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
    document->setRenderHint(Poppler::Document::Antialiasing, true);
    document->setRenderHint(Poppler::Document::TextAntialiasing, true);
    document->setRenderHint(Poppler::Document::TextHinting, true);
    document->setRenderHint(Poppler::Document::TextSlightHinting, true);
    currentFilePath = filePath;
    qDebug() << "Opened successfully:" << filePath;

    renderModel->setDocument(document.get());
    renderModel->renderAllPages(288.0,288.0,-1,-1,-1,-1);

    return true;
}

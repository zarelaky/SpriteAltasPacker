#ifndef IMAGEPREVIEWWIDGET_H
#define IMAGEPREVIEWWIDGET_H

#include <QDockWidget>
#include <QLabel>
class ZoomableImageWidget;
class ImagePreviewWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit ImagePreviewWidget();
    ~ImagePreviewWidget();
    
signals:


    
public slots:
    void setImage(const QString& imageFullPath);
private:
    ZoomableImageWidget* _img;
};

#endif // IMAGEPREVIEWWIDGET_H

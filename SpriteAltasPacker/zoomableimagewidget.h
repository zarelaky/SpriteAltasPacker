#ifndef ZOOMABLEIMAGEWIDGET_H
#define ZOOMABLEIMAGEWIDGET_H

#include <QWidget>

class ZoomableImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZoomableImageWidget(QWidget *parent = 0);

    void setPixmap(const QString& imagePath);
protected:

    virtual void paintEvent(QPaintEvent *);
signals:
    
public slots:

private:
    QPixmap _img;
};

#endif // ZOOMABLEIMAGEWIDGET_H

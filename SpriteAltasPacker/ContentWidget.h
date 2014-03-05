#pragma once

#include <QImage>
#include <QPaintEvent>
#include <QWidget>
#include <QResizeEvent>
#include <imagelistmodel.h>
#include <3rdparties/rbp/MaxRectsBinPack.h>


class ImagePlaceInfo
{
public:
    rbp::Rect           rc;
    bool                rotated;
    TrimmedImageInfo*   tii;
};

class ContentWidget : public QWidget
{
    Q_OBJECT
    typedef QMap<QString,ImagePlaceInfo*> ImagePlaceInfoMap;
    typedef QMapIterator<QString,ImagePlaceInfo*> ImagePlaceInfoMapIterator;
public:
    ContentWidget(QWidget* parent = NULL);
	~ContentWidget();
	virtual void paintEvent(QPaintEvent* e);
	virtual void resizeEvent(QResizeEvent* e);
    void SetImageListModel(ImageListModel* ilm);
public slots:
    void SetCanvasSize(int w, int h);
    void SetHeuristic(rbp::MaxRectsBinPack::FreeRectChoiceHeuristic heuristic);
    void setCanvasSize(const QSize& sz);
public slots:

    void imageListChanged();

protected:
	void rerender();
    void updateImagePlaceInfos();
private:
	QImage _canvas;	
    QBrush* _bkgndBrush;
    ImageListModel* _ilm;
    rbp::MaxRectsBinPack    _rbp;
    rbp::MaxRectsBinPack::FreeRectChoiceHeuristic    _heuristic;
    ImagePlaceInfoMap _ipis;
};

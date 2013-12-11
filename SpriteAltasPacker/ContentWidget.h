#pragma once

#include <QImage>
#include <QPaintEvent>
#include <QWidget>
#include <QResizeEvent>

class ContentWidget : public QWidget
{
	Q_OBJECT;
public:
	ContentWidget(QWidget* parent = NULL);
	~ContentWidget();
	virtual void paintEvent(QPaintEvent* e);
	virtual void resizeEvent(QResizeEvent* e);
protected:
	void rerender();
private:
	QImage _canvas;	

};

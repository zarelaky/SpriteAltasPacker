#pragma once

#include <QDockWidget>
class ImageListModel;
namespace Ui
{
    class PropertiesDockWidget;
}

class PropertiesWidget : public QDockWidget
{
	Q_OBJECT
public:
    PropertiesWidget(QWidget* parent, ImageListModel* ilm);
	~PropertiesWidget();
public slots:
    void formatIndexChange(int);
    void trimedChanged(int);
    void rotatedChanged(int);
    void interSpaceChanged(int);
    void widthTextChange(QString);
    void heightTextChange(QString);
    void savePath();
private:
    Ui::PropertiesDockWidget* _ui;
    ImageListModel* _ilm;
};


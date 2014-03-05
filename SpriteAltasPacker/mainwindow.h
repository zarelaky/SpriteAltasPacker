#pragma once
#include <QMainWindow>
#include <imagelistmodel.h>

namespace Ui
{
    class MainWindow;
}


class PropertiesWidget;
class FilesWidget;
class ImagePreviewWidget;
class LogWidget;

class MainWindow : public QMainWindow 
{
    Q_OBJECT
public:
	MainWindow();
	~MainWindow();

public slots:
    void menuActionTriggered(QAction* act);
private:
    Ui::MainWindow*     _ui;
    PropertiesWidget*   propertiesWidget;
    FilesWidget*        filesWidget;
    ImagePreviewWidget* imgPreviewWidget;
    LogWidget*          logWidget;
    ImageListModel      _ilm;

};

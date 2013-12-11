#pragma once
#include <QDockWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileInfo>
#include <QTreeWidgetItem>

namespace Ui
{
    class FilesDockWidget;
}
class FilesWidget : public QDockWidget
{
	Q_OBJECT;
public:
	FilesWidget(QWidget* parent);
	~FilesWidget();

    void dragEnterEvent(QDragEnterEvent* evt);
    void dropEvent(QDropEvent* e);
protected:
    void addToTree(const QString& file);
    void addDir(const QFileInfo& fi, QTreeWidgetItem* parent= NULL);
    void addFile(const QFileInfo& fi, QTreeWidgetItem* parent = NULL);
private:
    Ui::FilesDockWidget* _ui;    
};

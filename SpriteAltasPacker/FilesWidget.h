#pragma once
#include <QDockWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileInfo>
#include <QTreeWidgetItem>
#include <QMenu>
#include <imagelistmodel.h>
namespace Ui
{
    class FilesDockWidget;
}
class FilesWidget : public QDockWidget
{
    Q_OBJECT
public:
    FilesWidget(QWidget* parent, ImageListModel& ilm);
	~FilesWidget();

    void dragEnterEvent(QDragEnterEvent* evt);
    void dropEvent(QDropEvent* e);
    QList<QString> fileList();
    void removeFileInList(QTreeWidgetItem* d);
protected:
    void addToTree(const QString& file);
    void addFolder(const QFileInfo& fi, QTreeWidgetItem* parent= NULL);
    void addFile(const QFileInfo& fi, QTreeWidgetItem* parent = NULL);
    bool checkFileType(const QFileInfo& fi);
protected:
    virtual void contextMenuEvent(QContextMenuEvent *);
protected slots:
    void onAddFile();
    void onAddFolder();
    void onDeleteFile();
    void onRename();
    void treeCurrentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*);
signals:
    void selectImageChanged(const QString& imgpath);

private:
    Ui::FilesDockWidget* _ui;
    QMenu* treeContextMenu;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *);
private:
    ImageListModel& _ilm;
};

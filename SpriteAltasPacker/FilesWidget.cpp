#include <QMessageBox>
#include <QUrl>
#include <QMimeData>
#include <QString>
#include <QDir>

#include "FilesWidget.h"
#include "ui_filesview.h"

FilesWidget::FilesWidget(QWidget* p)
	: QDockWidget(p)
{
    _ui = new Ui::FilesDockWidget();
	_ui->setupUi(this);
    setAcceptDrops(true);
}

FilesWidget::~FilesWidget()
{
}

void FilesWidget::dragEnterEvent(QDragEnterEvent* evt)
{
    if (evt->mimeData()->hasUrls()) {
        evt->acceptProposedAction();
    }
} 
void FilesWidget::dropEvent(QDropEvent* evt)
{
    if (evt->mimeData()->hasUrls()) {
        foreach(QUrl url, evt->mimeData()->urls()) {
            if (url.isLocalFile()){
                QMessageBox::information(NULL, "info", url.toLocalFile());
                addToTree(url.toLocalFile());
            }
        }
    }
}

void FilesWidget::addToTree(const QString& file)
{
    QFileInfo fi(file);
    if (fi.isDir()){
        QMessageBox::information(NULL, "info", "bbb");
        addDir(fi);
        return;
    }
    addFile(fi);
    QMessageBox::information(NULL, "info", "aaa");

    _ui->treeWidget->expandAll();
}

void FilesWidget::addDir(const QFileInfo& fi, QTreeWidgetItem* p)
{
    QTreeWidget* tw = _ui->treeWidget;
    QTreeWidgetItem* item = NULL;
    if (NULL == p) {
        item = new QTreeWidgetItem(tw);
        tw->addTopLevelItem(item);
    } else {
        item = new QTreeWidgetItem(p);
    }
    item->setText(0, fi.fileName());

    QDir dir(fi.absoluteFilePath());

    QFileInfoList fil = dir.entryInfoList(QDir::AllEntries|QDir::Readable|QDir::NoDotAndDotDot);
    typedef QListIterator<QFileInfo> QFileInfoListIterator;
    QFileInfoListIterator i(fil);
  //  QMessageBox::information(this, "", QString("%1 %2").arg(dir.dirName()).arg(fil.size()));  
    while (i.hasNext()){
        QFileInfo inf = i.next();        
       if (inf.isDir()) {
           addDir(inf, item);
       } else if (inf.isFile()) {
           addFile(inf, item);
       }
    }
    
}

void FilesWidget::addFile(const QFileInfo& fi, QTreeWidgetItem* p)
{
    QTreeWidget* tw = _ui->treeWidget;
    QTreeWidgetItem* item = NULL;
    int level = 0;
    if (NULL == p) {
        item = new QTreeWidgetItem(tw);
        tw->addTopLevelItem(item);    
    } else {
    //    level  = 1;
        item = new QTreeWidgetItem(p);
    }
    item->setText(level, fi.fileName());

}

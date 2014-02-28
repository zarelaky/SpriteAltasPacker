#include <QMessageBox>
#include <QUrl>
#include <QMimeData>
#include <QString>
#include <QDir>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include "FilesWidget.h"
#include "ui_filesview.h"
#include "renamedialog.h"
#include <QDebug>

const char* supports[] = {
    "bmp",
    "jpg",
    "png",
    NULL
};

FilesWidget::FilesWidget(QWidget* p)
	: QDockWidget(p)
{
    _ui = new Ui::FilesDockWidget();
	_ui->setupUi(this);
    setAcceptDrops(true);

    treeContextMenu = new QMenu();
    QAction* act = treeContextMenu->addAction("Add File");
    connect(act, SIGNAL(triggered()), SLOT(onAddFile()));

    act = treeContextMenu->addAction("Add Folder");
    connect(act, SIGNAL(triggered()), SLOT(onAddFolder()));
    act = treeContextMenu->addAction("Delete");
    connect(act, SIGNAL(triggered()), SLOT(onDeleteFile()));
    act = treeContextMenu->addAction("Rename");
    connect(act, SIGNAL(triggered()), SLOT(onRename()));

    connect(_ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), SLOT(treeCurrentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));

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
               // QMessageBox::information(NULL, "info", url.toLocalFile());
                addToTree(url.toLocalFile());
            }
        }
    }
}


bool FilesWidget::checkFileType(const QFileInfo &fi)
{
    if(!fi.isFile()) {
        return false;
    }
    const char* *p = supports;
    while (*p) {
        if (0 == fi.suffix().compare(*p, Qt::CaseInsensitive)) {
            return true;
        }
        ++p;
    }
    return false;
}



void FilesWidget::addToTree(const QString& file)
{
    QFileInfo fi(file);
    if (fi.isDir()){
        //QMessageBox::information(NULL, "info", "bbb");
        addFolder(fi);
        return;
    }
    addFile(fi);
   // QMessageBox::information(NULL, "info", "aaa");

    _ui->treeWidget->expandAll();
}

void FilesWidget::addFolder(const QFileInfo& fi, QTreeWidgetItem* p)
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
    item->setData(1, Qt::DisplayRole, fi.absoluteFilePath());
    item->setData(0, Qt::UserRole, 0);
    QDir dir(fi.absoluteFilePath());

    QFileInfoList fil = dir.entryInfoList(QDir::AllEntries|QDir::Readable|QDir::NoDotAndDotDot);
    typedef QListIterator<QFileInfo> QFileInfoListIterator;
    QFileInfoListIterator i(fil);
  //  QMessageBox::information(this, "", QString("%1 %2").arg(dir.dirName()).arg(fil.size()));  
    while (i.hasNext()){
        QFileInfo inf = i.next();        
       if (inf.isDir()) {
           addFolder(inf, item);
       } else if (inf.isFile()) {
           addFile(inf, item);
       }
    }
    
}

void FilesWidget::addFile(const QFileInfo& fi, QTreeWidgetItem* p)
{
    if (!checkFileType(fi)) {
        return;
    }
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
    item->setData(0, Qt::UserRole, 1);
    item->setData(1, Qt::DisplayRole, fi.absoluteFilePath());
}

void FilesWidget::onAddFile() {
    QString s = QFileDialog::getOpenFileName(this, tr(""), "", "Images (*.jpg *.png *.bmp)");
    if (!s.isEmpty()) {
        addFile(QFileInfo(s));
    }

}

void FilesWidget::onAddFolder()
{
    QString s = QFileDialog::getExistingDirectory(this, tr(""));
    if (!s.isEmpty()) {
        addFolder(QFileInfo(s));
    }
}

void FilesWidget::onDeleteFile()
{
    QTreeWidget* tw = _ui->treeWidget;
    QTreeWidgetItem* ti = tw->currentItem();
    if (ti) {
        if (ti->parent()) {
            QList<QTreeWidgetItem*> children = ti->takeChildren();
            QListIterator<QTreeWidgetItem*> i(children);
            while (i.hasNext()) {
                delete i.next();
            }
            ti->parent()->removeChild(ti);
        } else {
            tw->takeTopLevelItem(tw->indexOfTopLevelItem(ti));

        }
        delete ti;
    }
}
void FilesWidget::onRename()
{
    QTreeWidget* tw = _ui->treeWidget;
    QTreeWidgetItem* i = tw->currentItem();
    if (i) {
        QVariant v = i->data(0, Qt::DisplayRole);
        RenameDialog dlg;
        dlg.setEditText(v.toString());
        dlg.show();
        if (QDialog::Accepted == dlg.exec()) {
            i->setData(0, Qt::DisplayRole, dlg.editText());
        }

    }
}

void FilesWidget::contextMenuEvent(QContextMenuEvent * evt)
{
    QTreeWidgetItem* item = _ui->treeWidget->itemAt(_ui->treeWidget->viewport()->mapFromGlobal(evt->globalPos()));
    if (item){

        treeContextMenu->popup(evt->globalPos());
    }
}

void FilesWidget::treeCurrentItemChanged(QTreeWidgetItem* cur, QTreeWidgetItem* pre) {
    if (!cur) {
        return;
    }

    Q_UNUSED(pre);
    QString path = cur->data(1, Qt::DisplayRole).toString();
    QVariant fileType = cur->data(0, Qt::UserRole);
    if (fileType.toInt() == 0) {
        path.clear();
    }
    emit selectImageChanged(path);
}


void FilesWidget::keyPressEvent(QKeyEvent * evt) {
    if (evt->key() == Qt::Key_Delete) {
        onDeleteFile();
    } else if (evt->key() == Qt::Key_F2) {
        onRename();
    }
}

#include <QScrollArea>
#include "mainwindow.h"
#include "FilesWidget.h"
#include "PropertiesWidget.h"
#include "ContentWidget.h"
#include "ui_mainwindow.h"
#include "AboutWidget.h"
#include "imagepreviewwidget.h"
#include "logwidget.h"

MainWindow::MainWindow()
{
    _ui = new Ui::MainWindow();
    _ui->setupUi(this);


    QWidget* p = _ui->centralwidget;

    _ui->scrollAreaWidgetContents->SetImageListModel(&_ilm);
    connect(_ui->menubar, SIGNAL(triggered(QAction*)), SLOT(menuActionTriggered(QAction*)));

    propertiesWidget    = new PropertiesWidget(p,&_ilm);
    filesWidget         = new FilesWidget(p, _ilm);
    imgPreviewWidget    = new ImagePreviewWidget();


    addDockWidget(Qt::LeftDockWidgetArea, propertiesWidget);
    propertiesWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, filesWidget);
    filesWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
    addDockWidget(Qt::RightDockWidgetArea, imgPreviewWidget);
    imgPreviewWidget->setAllowedAreas(Qt::AllDockWidgetAreas);

    logWidget = new LogWidget();
    addDockWidget(Qt::BottomDockWidgetArea, logWidget);

    connect(filesWidget, SIGNAL(selectImageChanged(const QString)), imgPreviewWidget, SLOT(setImage(const QString)));
    connect(&_ilm, SIGNAL(imageListChanged()), _ui->scrollAreaWidgetContents, SLOT(imageListChanged()));
    connect(&_ilm, SIGNAL(canvasSizeChanged(const QSize&)), _ui->scrollAreaWidgetContents, SLOT(setCanvasSize(const QSize&)));


    _ilm.setCanvasHeight(1024);
    _ilm.setCanvasWidth(1024);
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::menuActionTriggered(QAction* act)
{
    if ( _ui->action_About == act) {
		AboutWidget * about = new AboutWidget(this);
		about->setModal(true);	
		about->show();
    }
    else if (_ui->actionExit == act)
    {
        this->close();
    } else if (_ui->actionFileView == act) {
        filesWidget->show();
    } else if (_ui->actionPropertiesView == act) {
        propertiesWidget->show();
    } else if (_ui->actionImagePreview == act) {
        imgPreviewWidget->show();
    } else if (_ui->actionLogView == act) {
        logWidget->show();
    }

}


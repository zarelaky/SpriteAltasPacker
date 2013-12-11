#include <QScrollArea>
#include "mainwindow.h"
#include "FilesWidget.h"
#include "PropertiesWidget.h"
#include "ContentWidget.h"
#include "ui_mainwindow.h"
#include "AboutWidget.h"


MainWindow::MainWindow()
{
    _ui = new Ui::MainWindow();
    _ui->setupUi(this);


    QWidget* p = _ui->centralwidget;

    _ui->scrollAreaWidgetContents->setFixedSize(2048, 2048);
    connect(_ui->menubar, SIGNAL(triggered(QAction*)), SLOT(menuActionTriggered(QAction*)));

	PropertiesWidget* propertiesWidget = new PropertiesWidget(p);
	FilesWidget*	filesWidget = new FilesWidget(p);
	addDockWidget(Qt::LeftDockWidgetArea, propertiesWidget);
	addDockWidget(Qt::RightDockWidgetArea, filesWidget);


}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::menuActionTriggered(QAction* act)
{
	if ( 0 == act->objectName().compare("action_About")) {
		AboutWidget * about = new AboutWidget(this);
		about->setModal(true);	
		about->show();
    }
    else if (0 == act->objectName().compare("actionExit"))
    {
        this->close();
    }
}

#pragma once
#include <QMainWindow>
namespace Ui
{
    class MainWindow;
}
class MainWindow : public QMainWindow 
{
    Q_OBJECT;
public:
	MainWindow();
	~MainWindow();

public slots:
    void menuActionTriggered(QAction* act);
private:
    Ui::MainWindow* _ui;
};

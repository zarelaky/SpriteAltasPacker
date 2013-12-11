#pragma once
#include <QDialog>

namespace Ui
{
    class About;
}

class AboutWidget : public QDialog 
{
	Q_OBJECT
public:
	AboutWidget(QWidget* parent = NULL);
	~AboutWidget();
private:
    Ui::About* _ui;
};

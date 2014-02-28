#include "renamedialog.h"
#include "ui_renamedialog.h"

RenameDialog::RenameDialog()
{
    _ui = new Ui::RenameDialogUI();
    _ui->setupUi(this);
    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

}

RenameDialog::~RenameDialog()
{

}

void RenameDialog::setEditText(const QString &txt)
{
    _ui->lineEdit->setText(txt);
}

QString RenameDialog::editText() const
{
    return _ui->lineEdit->text();
}

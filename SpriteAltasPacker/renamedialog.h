#ifndef RENAMEDIALOG_H
#define RENAMEDIALOG_H
#include <QDialog>
namespace Ui
{
    class RenameDialogUI;
}
class RenameDialog: public QDialog
{
    Q_OBJECT
public:
    RenameDialog();
    virtual ~RenameDialog();
    void setEditText(const QString& txt);
    QString editText() const ;

private:
    Ui::RenameDialogUI* _ui;
};

#endif // RENAMEDIALOG_H

#ifndef SAVEPANELDIALOG_H
#define SAVEPANELDIALOG_H

#include <QDialog>

namespace Ui {
class SavePanelDialog;
}

class SavePanelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SavePanelDialog(QWidget *parent = nullptr, QString text = "");
    ~SavePanelDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SavePanelDialog *ui;
    QString curText;
};

#endif // SAVEPANELDIALOG_H

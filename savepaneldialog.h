#ifndef SAVEPANELDIALOG_H
#define SAVEPANELDIALOG_H

#include <QDialog>
#include <QRegExpValidator>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QFileSystemModel>
#include <QPrinter>

namespace Ui {
class SavePanelDialog;
}

class SavePanelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SavePanelDialog(QWidget *parent = nullptr, QString text = "");
    ~SavePanelDialog();

    void convertIntoText();
    void convertIntoPDF();

private slots:
    void on_buttonBox_accepted();

    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::SavePanelDialog *ui;
    QString curText;
    QFileSystemModel* directory;
    QString prefix = "";
};

#endif // SAVEPANELDIALOG_H

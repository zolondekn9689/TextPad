#include "savepaneldialog.h"
#include "ui_savepaneldialog.h"
#include <QRegExpValidator>
#include <QFile>
#include <QDebug>

SavePanelDialog::SavePanelDialog(QWidget *parent, QString text) :
    QDialog(parent),
    ui(new Ui::SavePanelDialog)
{
    ui->setupUi(this);
    curText = text;

    // Reg Ex in string to use for regex expression.
    QString lettersAllowed = "^[a-zA-Z]+[a-zA-Z0-9]*$";
    QRegExp reg(lettersAllowed);

    //Validator to validator input.
    QRegExpValidator* validator = new QRegExpValidator(this);
    validator->setRegExp(reg);

    ui->lineEdit->setValidator(validator);
}

SavePanelDialog::~SavePanelDialog()
{
    delete ui;
}

void SavePanelDialog::on_buttonBox_accepted()
{
    //Have a file name.
   // QString prefix = "C:/Users";
    QString filename = ui->lineEdit->text() + "." + ui->comboBox->currentText();

    //Create a file.
    QFile file(filename);

    //Write file.
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        qWarning() << "Failed to write to file " << filename << "\n";
        return;
    }

    QTextStream out(&file);

    out << curText;
    file.flush();

    file.close();

}

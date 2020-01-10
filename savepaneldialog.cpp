#include "savepaneldialog.h"
#include "ui_savepaneldialog.h"
#include <QTextDocument>

SavePanelDialog::SavePanelDialog(QWidget *parent, QString text) :
    QDialog(parent),
    ui(new Ui::SavePanelDialog)
{
    ui->setupUi(this);

    //Text from the string.
    curText = text;

    // Reg Ex in string to use for regex expression.
    QString lettersAllowed = "^[a-zA-Z]+[a-zA-Z0-9]*$";
    QRegExp reg(lettersAllowed);

    //Validator to validator input.
    QRegExpValidator* validator = new QRegExpValidator(this);
    validator->setRegExp(reg);

    //Set the line edit to be validated so user can't just enter anything.
    ui->lineEdit->setValidator(validator);

    //Set the directory. So it can be used during the button event.
    QString dir = "C:/";
    directory = new QFileSystemModel(this);
    directory->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    directory->setRootPath(dir);

    //Set the model to the directory.
    ui->treeView->setModel(directory);

    //Hide Size Column: Nothing is shown as these are directories.
    ui->treeView->hideColumn(1);

    //Resize the headers in the tree as you go deeper into the hierachy.
    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);


}

SavePanelDialog::~SavePanelDialog()
{
    delete ui;
}

void SavePanelDialog::on_buttonBox_accepted()
{
    //Catch for an empty edit input.
    if (ui->lineEdit->text().isEmpty())
    {
        QMessageBox* box = new QMessageBox(this);
        box->setWindowTitle("Saving Error");
        box->setText("Failed to save file!");
        box->setModal(true);
        box->exec();
        return;
    }

    switch (ui->comboBox->currentIndex())
    {
    case 0:
        convertIntoText();
        break;
    case 1:
        convertIntoPDF();
        break;
    }

}

void SavePanelDialog::convertIntoText() {
    //The name of the file with extension that will be saved.
     QString filename = ui->lineEdit->text() + "." + ui->comboBox->currentText();

    //Have a file name.
     QFile file;


    //Check to see if prefix is empty.
    if (!prefix.isEmpty())
    {
        //Create a file.
        file.setFileName(prefix + "/" + filename);
    } else {
        //Set file name.
        file.setFileName(filename);
    }

    //Write file.
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        qWarning() << "Failed to create and write to " << filename << "\n";
        return;
    }

    //Put the file into a text stream.
    QTextStream out(&file);

    // Save the text stream into the file.
    out << curText;

    //Clear the stream.
    file.flush();

    //Close the file
    file.close();
}
void SavePanelDialog::convertIntoPDF()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    //printer.setPaperSize(QPrinter::A4);
    QTextDocument document(curText);

    QString filename = "";



    //Check to see if prefix is empty.
    if (prefix.isEmpty())
    {
        //Create a file.
        filename = ui->lineEdit->text() + ".pdf";
        printer.setOutputFileName(filename);
    } else {
        //Set file name.
        filename = prefix + "/" + ui->lineEdit->text() + ".pdf";
        printer.setOutputFileName(filename);
    }

    qDebug() << filename;
    qDebug() << prefix;

    document.setPlainText(curText);
    document.print(&printer);



}

void SavePanelDialog::on_treeView_clicked(const QModelIndex &index)
{
    prefix = directory->fileInfo(index).absoluteFilePath();
}

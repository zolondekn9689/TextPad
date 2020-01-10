#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "savepaneldialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    systemPreferences = Preferences::getInstance();
    //updateTabSpace();
    updateFontSize();
    ui->plainTextEdit->setTabStopDistance(8);
    ui->plainTextEdit->setWordWrapMode(QTextOption::WordWrap);
}




MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateTabSpace(int spaces)
{
    //Take care of case where spaces are below these.
    if (spaces > 0 && spaces < 99)
    {
        systemPreferences->setTabWidth(spaces);
        ui->plainTextEdit->setTabStopDistance(spaces);
    } else {
        ui->plainTextEdit->setTabStopDistance(systemPreferences->getTabWidth());
    }
}

/**Below 0 means
 * @brief MainWindow::updateFontSize
 * @param fontSize
 */
void MainWindow::updateFontSize(int fontSize)
{
    QFont font = ui->plainTextEdit->font();

    // Update automatically in this case.
    if (fontSize < 1)
    {
        //Font size does not get used.
        font.setPointSize(systemPreferences->getFontSize());
    } else {

        //Update manually. This means that font size gets use.
        font.setPointSize(fontSize);
    }

}

/**Set tab distances.
 * @brief MainWindow::on_actionSet_Tab_Spaces_triggered
 */
void MainWindow::on_actionSet_Tab_Spaces_triggered()
{
    //TODO LATER TRICKY
}


/**New Button is used.
 * @brief MainWindow::on_actionNew_triggered
 */
void MainWindow::on_actionNew_triggered()
{
    MainWindow* window = new MainWindow(this);
    window->show();
    //on_actionClear_All_triggered();
}

/**Button for clearing everything.
 * @brief MainWindow::on_actionClear_All_triggered
 */
void MainWindow::on_actionClear_All_triggered()
{
    ui->plainTextEdit->clear();
}



/**Save As. The only operation that is used currently.
 * @brief MainWindow::on_actionSave_As_triggered
 */
void MainWindow::on_actionSave_As_triggered()
{
    // Launch the saving panel.
    SavePanelDialog* panel = new SavePanelDialog(this, ui->plainTextEdit->toPlainText());
    panel->setModal(true);
    panel->exec();
}

/**Undo action.
 * @brief MainWindow::on_actionUndo_triggered
 */
void MainWindow::on_actionUndo_triggered()
{
    //Used to undo
    ui->plainTextEdit->undo();
}

void MainWindow::on_actionCopy_triggered()
{
    //Copies the selected text.
    ui->plainTextEdit->copy();
}


/**For pasting.
 * @brief MainWindow::on_actionPaste_triggered
 */
void MainWindow::on_actionPaste_triggered()
{
    //Pastes the seperate text.
    ui->plainTextEdit->paste();
}

/**Method and slot for cutting text.
 * @brief MainWindow::on_actionCut_triggered
 */
void MainWindow::on_actionCut_triggered()
{
    ui->plainTextEdit->cut();
}

void MainWindow::on_actionDelete_triggered()
{
    ui->plainTextEdit->cut();
    QApplication::clipboard()->clear();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->plainTextEdit->redo();
}

void MainWindow::on_actionFind_triggered()
{

    ui->plainTextEdit->find("Hello");
}

void MainWindow::on_actionPrint_2_triggered()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle("Printer Document");

    if (ui->plainTextEdit->textCursor().hasSelection())
    {

        dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);

    }


    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }
}

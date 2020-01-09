#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "savepaneldialog.h"


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



/**On Save.
 * @brief MainWindow::on_actionSave_triggered
 */
void MainWindow::on_actionSave_triggered()
{
    // Launch the saving panel.
    SavePanelDialog* panel = new SavePanelDialog(this, ui->plainTextEdit->toPlainText());
    panel->setModal(true);
    panel->exec();
}

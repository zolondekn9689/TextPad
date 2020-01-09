#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QHBoxLayout>
#include <QSpinBox>
#include "preferences.h"
#include <QTextCursor>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void updateTabSpace(int spaces = -1);

    void updateFontSize(int fontSize = -1);

    ~MainWindow();

private slots:
    void on_actionSet_Tab_Spaces_triggered();

    void on_actionNew_triggered();

    void on_actionClear_All_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    Preferences* systemPreferences;





};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Reference source: https://stackoverflow.com/questions/26162336/qt-any-guideline-on-how-to-implement-navigation-between-ui-forms

#include <QMainWindow>
#include "dialog.h"
#include "form.h"
#include "subwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dialog_selected();
    void on_form_selected();
    void on_subWindow_selected();

private:
    Ui::MainWindow *ui;

    Dialog *m_dialog;
    Form *m_form;
    SubWindow *m_subWindow;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include "userinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool connectDB(const QString &address);
    void disconnectDB();

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase m_database;
};
#endif // MAINWINDOW_H

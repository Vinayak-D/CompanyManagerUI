#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "setupcompanywindow.h"

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
    void on_companyButton_clicked();

private:
    Ui::MainWindow *ui;
    setupcompanywindow *companywindow;
};
#endif // MAINWINDOW_H

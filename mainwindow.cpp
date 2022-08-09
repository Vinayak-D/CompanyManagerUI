#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    qApp->quit();
    delete ui;
}

//the object name is companyButton, default is pushButton (on_pushButton_clicked), check mainwindow.ui
void MainWindow::on_companyButton_clicked(){
    QString companyName = ui->companyLineEdit->text();
    //this refers to mainwindow
    this->close();
    companywindow = new setupcompanywindow(this, companyName);
    companywindow->show();
}


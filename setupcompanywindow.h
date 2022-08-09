#ifndef SETUPCOMPANYWINDOW_H
#define SETUPCOMPANYWINDOW_H
#include <QDialog>
#include "src/company.h"
#include "editcompanywindow.h"
using namespace std;
#include <sstream>

namespace Ui {
class setupcompanywindow;
}

class setupcompanywindow : public QDialog
{
    Q_OBJECT

public:
    explicit setupcompanywindow(QWidget *parent = nullptr, QString text = "company");
    ~setupcompanywindow();

private slots:
    void on_setLeaderButton_clicked();
    void continueCompanySetup();
    void on_continueButton_clicked();
    vector<string> parseEmployeeInputs(string s);
    void on_NextButton_clicked();

private:
    Ui::setupcompanywindow *ui;
    editcompanywindow *companyeditwin;
    company Company;
};

#endif // SETUPCOMPANYWINDOW_H

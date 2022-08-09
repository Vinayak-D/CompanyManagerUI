#ifndef EDITCOMPANYWINDOW_H
#define EDITCOMPANYWINDOW_H
#include "src/company.h"
#include <QDialog>
#include <sstream>

namespace Ui {
class editcompanywindow;
}

class editcompanywindow : public QDialog
{
    Q_OBJECT

public:
    explicit editcompanywindow(QWidget *parent = nullptr, company Company = company());
    ~editcompanywindow();

private slots:
    void on_UpdateCompanyButton_clicked();
    void updateCompanyDisplay();
    //vector<string> parseEmployeeInputs(string s);
    void on_HireButton_clicked();
    vector<vector<string>> parseEmployeeHireInputs(string s, string p);
    void on_EmployeeSearchButton_clicked();
    void on_replaceEmployeeRadioButton_toggled(bool checked);
    void disableRadioButtons();
    void on_EmployeeReplaceButton_clicked();
    void on_fireEmployeeRadioButton_toggled(bool checked);
    void on_firePromoteAllRadioButton_toggled(bool checked);
    void on_FirePromoteAllButton_clicked();
    void on_firePromoteOneRadioButton_toggled(bool checked);
    void on_EmployeeFindBossButton_clicked();
    void on_EmployeeChangeBossButton_clicked();
    void on_EmployeeESearchButton_clicked();
    void on_EmployeeEditButton_clicked();

private:
    Ui::editcompanywindow *ui;
    company Companycopy;
};

#endif // EDITCOMPANYWINDOW_H

#include "editcompanywindow.h"
#include "ui_editcompanywindow.h"

editcompanywindow::editcompanywindow(QWidget *parent, company Company) :QDialog(parent), ui(new Ui::editcompanywindow){
    //copy the object, and any changes in this class will be on Companycopy
    Companycopy = Company;
    ui->setupUi(this);
    ui->companyNameLabel->setText(QString::fromStdString(Company.getName()));
    updateCompanyDisplay();
    ui->hirePromptLabel->hide();
    ui->EmployeeReplaceButton->setEnabled(false);
    disableRadioButtons();
    ui->employeeSearchPrompt->hide();
    ui->newEmployeeNameLineEdit->setEnabled(false);
    ui->newEmployeePhoneLineEdit->setEnabled(false);
    ui->fireOptionPrompt->hide();
    ui->FirePromoteAllButton->hide();
    ui->employeeReportsToLabel->hide();
    ui->employeeNewBossLineEdit->setEnabled(false);
    ui->employeePromoteSearchPrompt->hide();
    ui->employeeESearchPrompt->hide();
    ui->employeeNewNameLineEdit->setEnabled(false);
    ui->employeeNewPhoneLineEdit->setEnabled(false);
    ui->EmployeeEditButton->setEnabled(false);
}

editcompanywindow::~editcompanywindow(){
    delete ui;
}

void editcompanywindow::on_UpdateCompanyButton_clicked(){
    updateCompanyDisplay();
}

void editcompanywindow::updateCompanyDisplay(){
    //method to print tree (will change later)
    vector<bool> flag(1, true);
    ui->CompanyDisplay->setText(QString::fromStdString(Companycopy.returnEmployees(Companycopy.returnLeader(), flag, 0, true)));
    Companycopy.resetEmployeeString();
}

void editcompanywindow::on_HireButton_clicked()
{
    ui->hirePromptLabel->hide();
    vector<vector<string>> newEmployees;
    //process new employee(s) names and numbers
    string employeeNames = ui->employeeNameLineEdit->text().toStdString();
    string employeePhone = ui->employeePhoneLineEdit->text().toStdString();
    newEmployees = parseEmployeeHireInputs(employeeNames, employeePhone);
    //find employee reporting to and process
    string employeesReportTo = ui->employeeReportLineEdit->text().toStdString();
    Companycopy.findNode(Companycopy.returnLeader(), employeesReportTo);
    //hire person under node and update prompt
    if (Companycopy.returnFoundNode() == nullptr){
        ui->hirePromptLabel->setText("Employee not found!");
        employeesReportTo.clear();
    }
    else if (Companycopy.returnFoundNode()->returnEmp() == employeesReportTo){
        if (newEmployees[0].size() == newEmployees[1].size()){
            Companycopy.addChildren(Companycopy.returnFoundNode(),newEmployees[0],newEmployees[1]);
            updateCompanyDisplay();
            ui->hirePromptLabel->setText(QString::fromStdString("Hired: " + employeeNames + " under " +  Companycopy.returnFoundNode()->returnEmp()));
            ui->employeeNameLineEdit->clear();
            ui->employeePhoneLineEdit->clear();
            ui->employeeReportLineEdit->clear();
            Companycopy.resetFoundNode();
        }
        else {
            ui->hirePromptLabel->setText("Extra name(s) and/or phone numbers!");
        }
    }
    ui->hirePromptLabel->show();
}

vector<vector<string>> editcompanywindow::parseEmployeeHireInputs(string s, string p){
    //vector of vectors containing names and phone numbers
    vector<vector<string>> result;
    //parse the names
    vector<string> names;
    stringstream ss(s);
    while(ss.good()) {
        string substr;
        getline(ss,substr,',');
        names.push_back(substr);
    }
    //parse the phone numbers
    vector<string> phoneNumbers;
    stringstream ss2(p);
    while(ss2.good()) {
        string substr2;
        getline(ss2,substr2,',');
        phoneNumbers.push_back(substr2);
    }
    //result[0] = names, result[1] = phoneNumbers
    result.push_back(names);
    result.push_back(phoneNumbers);
    return result;
}

void editcompanywindow::on_EmployeeSearchButton_clicked()
{
    //search employee
    ui->EmployeeSearchButton->setEnabled(false);
    string employeeName = ui->employeeSearchLineEdit->text().toStdString();
    Companycopy.findNode(Companycopy.returnLeader(), employeeName);

    //if searched employee is the ceo and does not match input, it means it did not find the employee
    if (Companycopy.returnFoundNode() == nullptr){
        ui->EmployeeSearchButton->setEnabled(true);
        ui->employeeSearchPrompt->setText("Employee not found!");
        ui->employeeSearchPrompt->show();
    }
    else if (employeeName == Companycopy.returnLeader()->returnEmp()){
        ui->firePromoteOneRadioButton->setEnabled(true);
        ui->replaceEmployeeRadioButton->setEnabled(true);
    }
    else if (Companycopy.returnFoundNode()->returnChildren().size() == 0){
        ui->replaceEmployeeRadioButton->setEnabled(true);
        ui->fireEmployeeRadioButton->setEnabled(true);
    }
    else if (Companycopy.returnFoundNode()->returnChildren().size() == 1){
        ui->replaceEmployeeRadioButton->setEnabled(true);
        ui->firePromoteAllRadioButton->setEnabled(true);
    }
    else{
        ui->replaceEmployeeRadioButton->setEnabled(true);
        ui->firePromoteOneRadioButton->setEnabled(true);
        ui->firePromoteAllRadioButton->setEnabled(true);
    }
}

void editcompanywindow::on_replaceEmployeeRadioButton_toggled(bool checked)
{
    if (checked){
        disableRadioButtons();
        ui->fireOptionPrompt->setText("Details of the new employee");
        ui->fireOptionPrompt->show();
        ui->newEmployeeNameLineEdit->setEnabled(true);
        ui->EmployeeReplaceButton->setEnabled(true);
        ui->newEmployeePhoneLineEdit->setEnabled(true);
    }
}

void editcompanywindow::disableRadioButtons(){
    ui->fireEmployeeRadioButton->setEnabled(false);
    ui->firePromoteAllRadioButton->setEnabled(false);
    ui->firePromoteOneRadioButton->setEnabled(false);
    ui->replaceEmployeeRadioButton->setEnabled(false);
}

void editcompanywindow::on_EmployeeReplaceButton_clicked(){
    string employeeModName = ui->newEmployeeNameLineEdit->text().toStdString();
    string employeeModPhone = ui->newEmployeePhoneLineEdit->text().toStdString();
    Companycopy.returnFoundNode()->editEmpDetails(employeeModName, employeeModPhone);
    updateCompanyDisplay();
    ui->EmployeeSearchButton->setEnabled(true);
    ui->replaceEmployeeRadioButton->setAutoExclusive(false);
    ui->replaceEmployeeRadioButton->setChecked(false);
    ui->FirePromoteAllButton->setEnabled(false);
    ui->EmployeeReplaceButton->setEnabled(false);
    ui->employeeSearchLineEdit->clear();
    ui->newEmployeeNameLineEdit->clear();
    ui->newEmployeePhoneLineEdit->clear();
    ui->employeeSearchPrompt->hide();
    employeeModName.clear();
    employeeModPhone.clear();
    disableRadioButtons();
    Companycopy.resetFoundNode();
}


void editcompanywindow::on_fireEmployeeRadioButton_toggled(bool checked){
    if(checked){
        disableRadioButtons();
        ui->FirePromoteAllButton->setEnabled(true);
        ui->FirePromoteAllButton->show();
    }
}

void editcompanywindow::on_firePromoteAllRadioButton_toggled(bool checked){
    if(checked){
        disableRadioButtons();
        ui->FirePromoteAllButton->setEnabled(true);
        ui->FirePromoteAllButton->show();
    }
}

void editcompanywindow::on_FirePromoteAllButton_clicked(){
    if (ui->newEmployeeNameLineEdit->isEnabled() == false){
        Companycopy.deleteNode(Companycopy.returnLeader(), Companycopy.returnFoundNode(),"all");
    }
    else{
        bool match = false;
        string employeeModName = ui->newEmployeeNameLineEdit->text().toStdString();
        vector<treeNode*> _children = Companycopy.returnFoundNode()->returnChildren();
        unsigned int ct = 0;
        while(ct < _children.size()){
            if (_children[ct]->returnEmp() == employeeModName){
                match = true;
                ct = 100000;
            }
            else{
                ct+=1;
            }
        }
        if (match){
            Companycopy.deleteNode(Companycopy.returnLeader(), Companycopy.returnFoundNode(),employeeModName);
        }
        else{
            Companycopy.deleteNode(Companycopy.returnLeader(), Companycopy.returnFoundNode(),_children[0]->returnEmp());
        }
    }
    //update and reset tab
    updateCompanyDisplay();
    ui->newEmployeeNameLineEdit->clear();
    ui->employeeSearchLineEdit->clear();
    ui->EmployeeSearchButton->setEnabled(true);
    ui->fireEmployeeRadioButton->setAutoExclusive(false);
    ui->fireEmployeeRadioButton->setChecked(false);
    ui->firePromoteAllRadioButton->setAutoExclusive(false);
    ui->firePromoteAllRadioButton->setChecked(false);
    ui->firePromoteOneRadioButton->setAutoExclusive(false);
    ui->firePromoteOneRadioButton->setChecked(false);
    ui->FirePromoteAllButton->setEnabled(false);
    ui->EmployeeReplaceButton->setEnabled(false);
    Companycopy.resetFoundNode();
}


void editcompanywindow::on_firePromoteOneRadioButton_toggled(bool checked)
{
    if(checked){
        disableRadioButtons();
        vector<treeNode*> _children = Companycopy.returnFoundNode()->returnChildren();
        string options;
        for (unsigned int i = 0; i < _children.size(); i++){
            options += _children[i]->returnEmp() + ", ";
        }
        ui->fireOptionPrompt->setText("Choose one employee to promote from: " + QString::fromStdString(options));
        ui->fireOptionPrompt->show();
        ui->newEmployeeNameLineEdit->setEnabled(true);
        ui->FirePromoteAllButton->setEnabled(true);
        ui->FirePromoteAllButton->show();
    }
}

void editcompanywindow::on_EmployeeFindBossButton_clicked()
{
    string employeePromoteName = ui->employeePromoteSearchLineEdit->text().toStdString();
    Companycopy.findNode(Companycopy.returnLeader(), employeePromoteName);
    if (Companycopy.returnFoundNode() == nullptr || Companycopy.returnFoundNode() == Companycopy.returnLeader() ){
        ui->employeePromoteSearchPrompt->setText("Employee not found, or cannot change the CEO's position!");
        ui->employeePromoteSearchPrompt->setEnabled(true);
        ui->employeePromoteSearchPrompt->show();
    }
    else{
        ui->employeePromoteSearchPrompt->setText("Employee reports to: " + QString::fromStdString(Companycopy.returnFoundNode()->returnParent()->returnEmp()));
        ui->employeePromoteSearchPrompt->show();
        ui->EmployeeFindBossButton->setEnabled(false);
        ui->employeeNewBossLineEdit->setEnabled(true);
    }
}

void editcompanywindow::on_EmployeeChangeBossButton_clicked()
{
    string employeeNewBoss = ui->employeeNewBossLineEdit->text().toStdString();
    if (!employeeNewBoss.empty()){
        Companycopy.changeParent(Companycopy.returnLeader(), Companycopy.returnFoundNode(), employeeNewBoss);
        updateCompanyDisplay();
        ui->employeePromoteSearchLineEdit->clear();
        ui->employeePromoteSearchPrompt->hide();
        ui->EmployeeFindBossButton->setEnabled(true);
        ui->employeeNewBossLineEdit->clear();
        Companycopy.resetFoundNode();
    }
}

void editcompanywindow::on_EmployeeESearchButton_clicked()
{
    //search employee
    ui->EmployeeESearchButton->setEnabled(false);
    string employeeName = ui->employeeESearchLineEdit->text().toStdString();
    Companycopy.findNode(Companycopy.returnLeader(), employeeName);
    //if searched employee is the ceo and does not match input, it means it did not find the employee
    if (Companycopy.returnFoundNode() == nullptr){
        ui->EmployeeESearchButton->setEnabled(true);
        ui->employeeESearchPrompt->setText("Employee not found!");
        ui->employeeESearchPrompt->show();
    }
    else{
        ui->EmployeeESearchButton->setEnabled(false);
        ui->employeeESearchPrompt->setText("Found Employee: " + QString::fromStdString(Companycopy.returnFoundNode()->returnEmp()));
        ui->employeeESearchPrompt->show();
        ui->employeeNewNameLineEdit->setText(QString::fromStdString(Companycopy.returnFoundNode()->returnEmp()));
        ui->employeeNewNameLineEdit->setEnabled(true);
        ui->employeeNewPhoneLineEdit->setEnabled(true);
        ui->EmployeeEditButton->setEnabled(true);
    }
}

void editcompanywindow::on_EmployeeEditButton_clicked()
{
    string newName = ui->employeeNewNameLineEdit->text().toStdString();
    string newPhone = ui->employeeNewPhoneLineEdit->text().toStdString();
    if (!newName.empty() && !newPhone.empty()){
        Companycopy.returnFoundNode()->editEmpDetails(newName, newPhone);
        updateCompanyDisplay();
        ui->employeeESearchLineEdit->clear();
        ui->employeeNewNameLineEdit->clear();
        ui->employeeNewPhoneLineEdit->clear();
        ui->employeeESearchPrompt->setText("Done");
        ui->EmployeeESearchButton->setEnabled(true);
        Companycopy.resetFoundNode();
    }
    else{
        ui->employeeESearchPrompt->setText("Name and/or Phone field is empty!");
    }
}


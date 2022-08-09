#include "setupcompanywindow.h"
#include "ui_setupcompanywindow.h"

setupcompanywindow::setupcompanywindow(QWidget *parent, QString text):QDialog(parent),ui(new Ui::setupcompanywindow),Company(text.toStdString()){
    ui->setupUi(this);
    ui->continueButton->hide();
    ui->companyLabelEdit->setText(text);
    ui->employeeNameLineEdit->setEnabled(false);
    ui->employeePhoneLineEdit->setEnabled(false);
    ui->leaderNameLabel->hide();
    ui->promptLabel->hide();
    ui->NextButton->hide();
    ui->NextButton->setEnabled(false);
}

setupcompanywindow::~setupcompanywindow(){
    delete ui;
}

void setupcompanywindow::on_setLeaderButton_clicked(){
    //store leader info
    string leaderName = ui->leaderNameLineEdit->text().toStdString();
    string leaderPhone = ui->leaderPhoneLineEdit->text().toStdString();
    unsigned int numleaderChildren = ui->leaderNCLineEdit->text().toInt();
    //set the root node of Company
    if (!leaderName.empty() && !leaderPhone.empty()){
        Company.setLeader(leaderName,leaderPhone);
        //continue setting up rest of company
        if (numleaderChildren > 0){
            //disable leader setting buttons
            ui->leaderNameLineEdit->setEnabled(false);
            ui->leaderPhoneLineEdit->setEnabled(false);
            ui->leaderNCLineEdit->setEnabled(false);
            ui->setLeaderButton->setEnabled(false);
            ui->promptLabel->hide();
            continueCompanySetup();
        }
        else{
            ui->promptLabel->setText("You must have atleast 1 employee reporting to leader!");
            ui->setLeaderButton->setEnabled(true);
            ui->promptLabel->show();
        }
    }
    else if (leaderName.empty() || leaderPhone.empty()){
        ui->promptLabel->setText("Missing name or phone number");
        ui->promptLabel->show();
    }
}


void setupcompanywindow::continueCompanySetup(){
    //show prompt to add employees
    ui->addEmployeesLabel->show();
    //show the leader name
    ui->leaderNameLabel->setText(QString::fromStdString(Company.returnLeader()->returnEmp()));
    ui->leaderNameLabel->show();
    //enable button and text fields
    ui->employeeNameLabel->show();
    ui->employeePhoneLabel->show();
    ui->employeeNameLineEdit->setEnabled(true);
    ui->employeePhoneLineEdit->setEnabled(true);
    ui->continueButton->show();
}

void setupcompanywindow::on_continueButton_clicked(){
    //store employee children to string
    string employeeNames = ui->employeeNameLineEdit->text().toStdString();
    string employeePhoneNumbers = ui->employeePhoneLineEdit->text().toStdString();
    vector<string> names = parseEmployeeInputs(employeeNames);
    vector<string> numbers = parseEmployeeInputs(employeePhoneNumbers);
    //check if both vectors are same size
    if(names.size() == numbers.size()){
        ui->continueButton->setEnabled(false);
        ui->promptLabel->hide();
        Company.addChildren(Company.returnLeader(), names, numbers);
        ui->NextButton->show();
        ui->NextButton->setEnabled(true);
    }
    else{
        ui->promptLabel->setText("Extra name(s) and/or phone numbers!");
        ui->promptLabel->show();
    }
}

vector<string> setupcompanywindow::parseEmployeeInputs(string s){
    vector<string> result;
    stringstream ss(s);
    while(ss.good()) {
        string substr;
        getline(ss,substr,',');
        result.push_back(substr);
    }
    return result;
}

void setupcompanywindow::on_NextButton_clicked(){
    ui->NextButton->setEnabled(false);
    ui->employeeNameLineEdit->setEnabled(false);
    ui->employeePhoneLineEdit->setEnabled(false);
    this->close();
    companyeditwin = new editcompanywindow(this, Company);
    companyeditwin->show();
}


#include "mainwindow.h"
#include "ui_mainwindow.h"


static double calcVal = 0.0;
static double memoryVal = 0.0;
static double prevMemoryVal = 0.0;
static bool divTrigger = false;
static bool multTrigger = false;
static bool addTrigger = false;
static bool subTrigger = false;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));

    QPushButton *numButtons[10];

    for(int i = 0; i < 10; ++i){
        QString butName = "button_" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(butName);

        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->button_plus, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->button_minus, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->button_multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->button_divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->button_equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));

    connect(ui->button_plus_minus, SIGNAL(released()), this, SLOT(ChangeNumberSign()));

    connect(ui->button_ac, SIGNAL(released()), this, SLOT(ClearButtonPressed()));
    connect(ui->button_m, SIGNAL(released()), this, SLOT(MemoryClearButtonPressed()));
    connect(ui->button_m_plus, SIGNAL(released()), this, SLOT(MemoryAddButtonPressed()));
    connect(ui->button_m_minus, SIGNAL(released()), this, SLOT(MemoryMinusButtonPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();

    if((displayVal.toDouble()== 0) || displayVal.toDouble()== 0.0){
        ui->Display->setText(butVal);
    }else{
        QString newVal = displayVal + butVal;
        double dbNewVal =newVal.toDouble();
        ui->Display->setText(QString::number(dbNewVal, 'g', 16));

    }


}


void MainWindow::MathButtonPressed(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();

    QPushButton *button = (QPushButton *)sender();

    QString butVal = button->text();

    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    }
    else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    }
    else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    }
    else{
        subTrigger = true;
    }


    ui->Display->setText("");

}



void MainWindow::EqualButtonPressed(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();

    double dblDisplayVal = displayVal.toDouble();

    if(addTrigger || subTrigger || multTrigger || divTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        }
        else if(subTrigger){
            solution = calcVal - dblDisplayVal;
        }
        else if(multTrigger){
            solution = calcVal * dblDisplayVal;
        }
        else{
            solution = calcVal / dblDisplayVal;
        }

    }

    ui->Display->setText(QString::number(solution));
    prevMemoryVal = memoryVal;
    memoryVal = solution;

}


void MainWindow::ChangeNumberSign(){
    QString displayVal = ui->Display->text();

    QRegExp reg("[-]?[0-9]*");

    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;

        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}

void MainWindow::ClearButtonPressed(){
    calcVal = 0.0;
    ui->Display->setText(QString::number(calcVal));
}

void MainWindow::MemoryClearButtonPressed(){
    memoryVal = 0.0;
    ui->Display->setText(QString::number(memoryVal));
}

void MainWindow::MemoryAddButtonPressed(){

    double memTotal = prevMemoryVal + memoryVal;
    ui->Display->setText(QString::number(memTotal));


}

void MainWindow::MemoryMinusButtonPressed(){

    double memTotal = memoryVal - prevMemoryVal;
    ui->Display->setText(QString::number(memTotal));


}

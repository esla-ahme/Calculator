#include "mainwindow.h"
#include "ui_mainwindow.h"

double calcValue= 0.0;
bool divTrigger = false;
bool mulTrigger = false;
bool subTrigger = false;
bool addTrigger = false;
double memVal=0.0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->display->setText(QString::number(0.0));
    QPushButton * numBtns[10];
    for (int i=0;i<10;i++) {
        QString btnName = "btn"+QString::number(i);
        numBtns[i]= MainWindow::findChild<QPushButton *>(btnName);
        connect(numBtns[i],SIGNAL(released()),
                this,SLOT(NumPressed()));
    }
    //Math btns connection
    connect(ui->btnAdd,SIGNAL(released()),this,SLOT(MathBtnPressed()));
    connect(ui->btnsub,SIGNAL(released()),this,SLOT(MathBtnPressed()));
    connect(ui->btnMult,SIGNAL(released()),this,SLOT(MathBtnPressed()));
    connect(ui->btnDiv,SIGNAL(released()),this,SLOT(MathBtnPressed()));

    //memory btns connection
    connect(ui->btnMemAdd,SIGNAL(released()),this,SLOT(memControl()));
   connect(ui->btnMemDel,SIGNAL(released()),this,SLOT(memControl()));
   connect(ui->btnMem,SIGNAL(released()),this,SLOT(memControl()));
    //other btns connection
    connect(ui->btnEqual,SIGNAL(released()),this,SLOT(EqualBtn()));
    connect(ui->btnChangeSign,SIGNAL(released()),this,SLOT(ChangeSign()));
    connect(ui->btnAc,SIGNAL(released()),this,SLOT(clear()));




}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed()
{
    QPushButton *btn = (QPushButton *)sender();
    QString btnVal = btn->text();
    QString displayVal = ui->display->text();
    if(displayVal.toDouble()==0 ||
       displayVal.toDouble()==0.0)
    {
        ui->display->setText(btnVal);
    } else
    {
        double tempVal = displayVal.toDouble();
        displayVal = QString::number(tempVal) + btnVal;
        tempVal = displayVal.toDouble();
        ui->display->setText(QString::number(tempVal,'g',12));
    }
}

void MainWindow::MathBtnPressed()
{
    divTrigger = false;
    mulTrigger = false;
    subTrigger = false;
    addTrigger = false;
   QString displayVal= ui ->display->text();
   calcValue = displayVal.toDouble();
    QPushButton *btn = (QPushButton *)sender();
    QString btnVal = btn->text();
    if(QString::compare(btnVal,"/",Qt::CaseInsensitive)==0){
        divTrigger = true;
    } else  if(QString::compare(btnVal,"*",Qt::CaseInsensitive)==0){
        mulTrigger = true;
    } else  if(QString::compare(btnVal,"+",Qt::CaseInsensitive)==0){
        addTrigger = true;
    } else  if(QString::compare(btnVal,"-",Qt::CaseInsensitive)==0){
        subTrigger = true;
    }
    ui->display->setText(QString::number(0.0));
}

void MainWindow::EqualBtn()
{
    double solution = 0.0;
    QString displayVal= ui ->display->text();
    double dbDisplayValue = displayVal.toDouble();
    if(addTrigger || mulTrigger || subTrigger || divTrigger)
    {
        if(addTrigger){
            solution = calcValue + dbDisplayValue;
        } else if(subTrigger){
            solution = calcValue - dbDisplayValue;
        } else if(divTrigger && dbDisplayValue != 0 ){
            solution = calcValue / dbDisplayValue;
        } else if(divTrigger && dbDisplayValue == 0 ){
            solution = qInf();
        }else{
            solution = calcValue * dbDisplayValue;
        }
    }
    ui-> display->setText(QString::number(solution,'g',12));
}

void MainWindow::ChangeSign()
{
     QString displayVal= ui ->display->text();
     QRegExp reg("[-]?[0-9.]*");
     if(reg.exactMatch(displayVal)){
         ui->display->setText(QString::number(-1*displayVal.toDouble()));
     }
}

void MainWindow::clear()
{
     calcValue= 0.0;
     divTrigger = false;
     mulTrigger = false;
     subTrigger = false;
     addTrigger = false;
     ui->display->setText(QString::number(0.0));
}

void MainWindow::memControl()
{
    QString displayVal= ui ->display->text();
    double dbDisplayValue = displayVal.toDouble();
    QPushButton *btn = (QPushButton *)sender();
    QString btnVal = btn->text();
    if(QString::compare(btnVal,"M+",Qt::CaseInsensitive)==0){
        memVal = dbDisplayValue;
    } else  if(QString::compare(btnVal,"M-",Qt::CaseInsensitive)==0){
        memVal = 0;
    } else  if(QString::compare(btnVal,"M",Qt::CaseInsensitive)==0){
           ui->display->setText(QString::number(memVal));
    }
}


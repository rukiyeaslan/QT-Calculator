#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QTextStream>


double calcVal = 0.0;
bool addPressed = false;     //add button
bool subPressed= false;      //subtract button
bool isNegative = false;     //negative input is entered
bool equalPressed = false;   //equal button

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));

    QPushButton *buttons[16];
    for(int i = 0; i<16; i++){
        QString butName = "Button" + QString::number(i);
        buttons[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(buttons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->Add, SIGNAL(released()), this,
                SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this,
                SLOT(MathButtonPressed()));

    connect(ui->Equals, SIGNAL(released()), this,
                SLOT(EqualButtonPressed()));

    connect(ui->Clear, SIGNAL(released()), this,
                SLOT(ClearButtonPressed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_centralwidget_customContextMenuRequested(const QPoint &pos)
{

}

//if a number button is pressed, execute corresponding actions.
void MainWindow::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    double decimalVal;
    QString displayVal;
    if(equalPressed){
          displayVal= 0;
    }
    else{
        displayVal = ui->Display->text();
    }



    //bool isNegative = false;
   if(calcVal == 0 && subPressed){
         isNegative = true;

   }
    if((QString::compare(displayVal, "0", Qt::CaseInsensitive) == 0) || (QString::compare(displayVal,"0.0", Qt::CaseInsensitive) == 0)){

         ui->Display->setText(butVal);

    }
    else{
        QString newVal = displayVal + butVal;
        int size = newVal.size();
        if (size < 10) {
            ui->Display->setText(newVal);
        }

    }
    equalPressed = false;
}

//if math button pressed, make buttons clicked.
void MainWindow::MathButtonPressed(){

    // delete previous math button clicks

     addPressed= false;
    subPressed = false;

    // Store current value in Display
    QString displayVal = ui->Display->text();

    bool ok;

    int hex = displayVal.toInt(&ok, 16);
    calcVal=hex;


    QPushButton *button = (QPushButton *)sender();

    // Get math symbol on the button
    QString butVal = button->text();


    if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addPressed = true;

    } else {
        subPressed = true;
    }


    // Clear display
    ui->Display->setText("");

}
//clear everything
void MainWindow::ClearButtonPressed(){
    ui->Display->setText("");
    subPressed=false;
    addPressed=false;
    calcVal = 0;
}

//calculate the result
void MainWindow::EqualButtonPressed(){

    //new calculation
    double solution = 0.0;
    equalPressed = true;

    // get value in display
    QString displayVal = ui->Display->text();

    bool ok;

    int hex = displayVal.toInt(&ok, 16);

    // Make sure a math button was pressed
    if(addPressed || subPressed){
        if(addPressed && isNegative){

            solution = (-1) * calcVal + hex;
            isNegative = false;
        }else if(subPressed && isNegative ){

            solution = (-1) * calcVal - hex;
            isNegative = false;
        }
        else if(addPressed){

            solution = calcVal + hex;
        } else if(subPressed){

            solution = calcVal - hex;
        }
    }

    // put solution in display

    uint decimal= solution;
    QString hexadecimal;
    hexadecimal.setNum(decimal,16);
    ui->Display->setText(hexadecimal.toUpper());


}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  <math.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnPlusMinus, SIGNAL(clicked()), this, SLOT(btnPlusMinusClicked()));



    digitBTNs = {{Qt::Key_0,ui->btnNum0},
               {Qt::Key_1,ui->btnNum1},
               {Qt::Key_2,ui->btnNum2},
               {Qt::Key_3,ui->btnNum3},
               {Qt::Key_4,ui->btnNum4},
               {Qt::Key_5,ui->btnNum5},
               {Qt::Key_6,ui->btnNum6},
               {Qt::Key_7,ui->btnNum7},
               {Qt::Key_8,ui->btnNum8},
               {Qt::Key_9,ui->btnNum9},
              };

    foreach(auto btn,digitBTNs)
        connect(btn,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

//    connect(ui->btnNum0,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
//    connect(ui->btnNum1,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
//    connect(ui->btnNum2,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
//    connect(ui->btnNum3,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
//    connect(ui->btnNum4,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
//    connect(ui->btnNum5,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
//    connect(ui->btnNum6,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
//    connect(ui->btnNum7,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
//    connect(ui->btnNum8,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
//    connect(ui->btnNum9,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    operatorBTNs ={ {Qt::Key_Plus, ui->btnPlus},
                    {Qt::Key_Minus, ui->btnMinus},
                    {Qt::Key_Asterisk, ui->btnMultipe},
                    {Qt::Key_Slash, ui->btnDivide},
                    {Qt::Key_Percent, ui->btnPercentage},
                  };

    foreach(auto btn, operatorBTNs)
        connect(btn, SIGNAL(clicked()), this, SLOT(btnBinaryOperatorClicked()));


//    connect(ui->btnMultipe,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
//    connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
//    connect(ui->btnMinus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
//    connect(ui->btnDivide,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));

//    connect(ui->btnPercentage,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
      connect(ui->btnInverse,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
      connect(ui->btnSquare,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
      connect(ui->btnSqrt,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation(bool *ok)
{
    ui->statusbar->showMessage("calcuation is in progress");

    double result=0;
    if(operands.size()==2 && opcodes.size()>0)
    {
        //取操作数
        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();

        //取操作符
        QString op = opcodes.front();
        opcodes.pop_front();

        if(op == "+"){
            result = operand1 + operand2;
        } else if(op == "-"){
            result = operand1 - operand2;
        } else if(op == "×"){
            result = operand1 * operand2;
        } else if(op == "÷"){
            result = operand1 / operand2;
        }

        operands.push_back(QString::number(result));

        ui->statusbar->showMessage(QString("calcuation is in progress: operands is %1 ,opcode is %2").arg(operands.size()).arg(opcodes.size()));
    }
    else
        ui->statusbar->showMessage(QString("operands is %1 ,opcode is %2").arg(operands.size()).arg(opcodes.size()));
    return QString::number(result);
}

void MainWindow::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();
    if(digit == "0" && operand == "0")
        digit ="";
    if(operand == "0" && digit !="0")
        operand = "";
    operand += digit;

    ui->display->setText(operand);
    //ui->statusbar->showMessage(qobject_cast<QPushButton *>(sender())->text() + "btn clicked");

}




void MainWindow::on_btnPeriod_clicked()
{

    if(!operand.contains("."))
        operand += qobject_cast<QPushButton *>(sender())->text();
    ui->display->setText(operand);
}


void MainWindow::on_btnDel_clicked()
{

    operand = operand.left(operand.length()-1);
    ui->display->setText(operand);
}


void MainWindow::on_btnClear_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}

void MainWindow::btnBinaryOperatorClicked()
{
    ui->statusbar->showMessage("last operand " + operand);
    QString opcode = qobject_cast<QPushButton *>(sender())->text();


    if(operand != ""){
        operands.push_back(operand);
        operand ="";

        //new1
        QString opcode = qobject_cast<QPushButton *>(sender())->text();
        opcodes.push_back(opcode);
        QString result= calculation();
        ui->display->setText(result);
    }

}

void MainWindow::btnUnaryOperatorClicked()
{
    if(operand != ""){
        double result = operand.toDouble();
        operand = "";

        QString op = qobject_cast<QPushButton*>(sender())->text();

        if(op == "%")
            result /=100.0;
        else if(op =="1/x")
            result =1/result;
        else if(op =="x^2")
            result *=result;
        else if(op =="")
            result =sqrt(result);

        ui->display->setText(QString::number(result));
    }

}

void MainWindow::on_btnEqual_clicked()
{
    if(operand != ""){
        operands.push_back(operand);
        operand ="";
    }

//    QString result= calculation();

//    ui->display->setText(result);

    // 进行计算
       if (operands.size() >= 2 && opcodes.size() > 0) {
           QString result = calculation();
           ui->display->setText(result);

           // 计算完成后重置操作数和操作符
           operands.clear();
           opcodes.clear();
       } else {
           ui->statusbar->showMessage("Invalid input: not enough operands or operators");
           ui->display->setText("0"); // 或者保持显示当前操作数
       }

}

void MainWindow::btnPlusMinusClicked()
{
    if (!operand.isEmpty()) {
            double value = operand.toDouble();
            value = -value;
            operand = QString::number(value);
            ui->display->setText(operand);
        }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    foreach(auto btnKey , digitBTNs.keys())
    {
        if(event->key() == btnKey)
            digitBTNs[btnKey]->animateClick(100);
    }

    foreach(auto btnKey, operatorBTNs.keys()) {
            if (event->key() == btnKey) {
                operatorBTNs[btnKey]->animateClick(100); // 动画点击
                return;
            }
        }



    }
//    if(event->key() == Qt::Key_0)
//        ui->btnNum0->animateClick(100);
//    else if(event->key() == Qt::Key_1)
//        ui->btnNum1->animateClick(100);










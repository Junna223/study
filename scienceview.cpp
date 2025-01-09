#include "scienceview.h"
#include "ui_scienceview.h"
#include <math.h>
#include <QDebug>
#include <QMessageBox>
#include <QtMath>
#include <cmath>

scienceview::scienceview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::scienceview)
{
    ui->setupUi(this);

    // 初始化数字按钮和操作符按钮的连接
    digitBTNs = {
        {Qt::Key_0, ui->btnNum0},
        {Qt::Key_1, ui->btnNum1},
        {Qt::Key_2, ui->btnNum2},
        {Qt::Key_3, ui->btnNum3},
        {Qt::Key_4, ui->btnNum4},
        {Qt::Key_5, ui->btnNum5},
        {Qt::Key_6, ui->btnNum6},
        {Qt::Key_7, ui->btnNum7},
        {Qt::Key_8, ui->btnNum8},
        {Qt::Key_9, ui->btnNum9},
    };

    foreach(auto btn, digitBTNs)
        connect(btn, SIGNAL(clicked()), this, SLOT(btnNumClicked()));

    operatorBTNs = {
        {Qt::Key_Plus, ui->btnPlus},
        {Qt::Key_Minus, ui->btnMinus},
        {Qt::Key_Asterisk, ui->btnMultipe},
        {Qt::Key_Slash, ui->btnDivide},

    };

    foreach(auto btn, operatorBTNs)
    connect(btn, SIGNAL(clicked()), this, SLOT(btnBinaryOperatorClicked()));

    //单目运算符
    connect(ui->btnInverse, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSquare, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSqrt, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnCube, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSin, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSinh, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnCos, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnCosh, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnTan, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnTanh, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnTenToX, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnIndex, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnFactorial, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnLn, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnLog, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));

    connect(ui->btnMS, SIGNAL(clicked()), this, SLOT(on_btnMS_clicked()));
    connect(ui->btnMR, SIGNAL(clicked()), this, SLOT(on_btnMR_clicked()));
    connect(ui->btnMC, SIGNAL(clicked()), this, SLOT(on_btnMC_clicked()));
}


scienceview::~scienceview()
{
    delete ui;
}

QString scienceview::calculation(bool *ok)
{
    //ui->statusbar->showMessage("calculation is in progress");
    double result = 0;

    while (operands.size() >= 2 && !opcodes.isEmpty())
    {
        // 取操作数
        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();

        // 取操作符
        QString op = opcodes.front();
        opcodes.pop_front();

        // 根据操作符进行相应计算
        if (op == "+")
        {
            result = operand1 + operand2;
        }
        else if (op == "-")
        {
            result = operand1 - operand2;
        }
        else if (op == "×")
        {
            result = operand1 * operand2;
        }
        else if (op == "÷")
        {
            if (operand2 == 0)
            {
                //ui->statusbar->showMessage("Error: Division by zero");
                return "Error";
            }
            result = operand1 / operand2;
        }

        // 将本次计算结果压入操作数栈
        operands.push_front(QString::number(result));
    }

    // 如果最后只剩一个操作数且操作符栈为空，直接返回该操作数作为最终结果
    if (operands.size() == 1 && opcodes.isEmpty())
    {
        result = operands.front().toDouble();
    }
    else
    {
        //ui->statusbar->showMessage("Invalid input: not enough operands or operators");
    }

    return QString::number(result);
}

void scienceview::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();
    if (operand == "0" && digit != "0")
        operand = "";
    operand += digit;

    ui->display->setText(operand);
}

void scienceview::btnBinaryOperatorClicked()
{
    QString opcode = qobject_cast<QPushButton *>(sender())->text();

    if (!operand.isEmpty())
    {
        operands.push_back(operand);
        operand = "";
        opcodes.push_back(opcode);

        // 如果已经有两个操作数，则进行计算
        if (operands.size() == 2)
        {
            QString result = calculation();
            ui->display->setText(result);
            operand = result; // 将结果存储为下一个操作数
            operands.clear(); // 清空操作数栈，以便开始新的计算
            opcodes.clear();  // 清空操作符栈
        }
    }
}

void scienceview::btnUnaryOperatorClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = ui->display->text().toDouble();
    double result = 0.0;

    if (clickedOperator == tr("√")) {
        if (operand < 0.0) {

            return;
        }
        result = std::sqrt(operand); // 使用 std::sqrt
    } else if (clickedOperator == tr("x^2")) {
        result = std::pow(operand, 2.0); // 使用 std::pow
    } else if (clickedOperator == tr("x^3")) {
        result = std::pow(operand, 3.0); // 使用 std::pow
    } else if (clickedOperator == tr("1/X")) {
        if (operand == 0.0) {

            return;
        }
        result = 1.0 / operand;
    } else if (clickedOperator == tr("ln")) {
        if (operand < 0.0) {

            return;
        }
        result = std::log(operand); // 使用 std::log
    } else if (clickedOperator == tr("log")) {
        if (operand < 0.0) {

            return;
        }
        result = std::log10(operand); // 使用 std::log10
    } else if (clickedOperator == tr("sin")) {
        result = std::sin(operand * M_PI / 180); // 转换为弧度
    } else if (clickedOperator == tr("sinh")) {
        result = std::sinh(operand); // 使用 std::sinh
    } else if (clickedOperator == tr("cos")) {
        result = std::cos(operand * M_PI / 180); // 转换为弧度
    } else if (clickedOperator == tr("cosh")) {
        result = std::cosh(operand); // 使用 std::cosh
    } else if (clickedOperator == tr("tan")) {
        result = std::tan(operand * M_PI / 180); // 转换为弧度
    } else if (clickedOperator == tr("tanh")) {
        result = std::tanh(operand);
    } else if (clickedOperator == tr("n!")) {
        if (operand < 0.0) {

            return;
        }
        result = std::tgamma(operand + 1); // 使用 std::tgamma
    } else if (clickedOperator == tr("e^x")) {
        result = std::exp(operand); // 使用 std::exp
    } else if (clickedOperator == tr("10^x")) {
        result = std::pow(10,operand); // 使用 std::pow
    } else if (clickedOperator == tr("Int")) {
        result = std::floor(operand); // 使用 std::floor
    } else if (clickedOperator == tr("Not")) {
        // 逻辑非的实现需要自定义，这里假设为按位取反
        result = ~(int)(operand);
    }

    ui->display->setText(QString::number(result));
    //waitingForOperand = true;
}

void scienceview::on_btnPeriod_clicked()
{
    if (!operand.contains("."))
        operand += ".";
    ui->display->setText(operand);
}

void scienceview::on_btnDel_clicked()
{
    operand = operand.left(operand.length() - 1);
    ui->display->setText(operand);
}

void scienceview::on_btnClear_clicked()
{
    operand.clear();
    operands.clear();
    opcodes.clear();
    ui->display->setText("0");
}

void scienceview::on_btnEqual_clicked()
{
    if (!operand.isEmpty())
    {
        operands.push_back(operand);
    }

    if (operands.size() >= 2)
    {
        QString result = calculation();
        ui->display->setText(result);
        operand = result; // 将结果存储为下一个操作数
        operands.clear(); // 清空操作数栈，以便开始新的计算
        opcodes.clear();  // 清空操作符栈
    }
    else
    {
        //ui->statusbar->showMessage("Invalid input: not enough operands or operators");
        ui->display->setText("0");
    }
}

void scienceview::btnPlusMinusClicked()
{
    if (!operand.isEmpty())
    {
        double value = operand.toDouble();
        value = -value;
        operand = QString::number(value);
        ui->display->setText(operand);
    }
}

void scienceview::keyPressEvent(QKeyEvent *event)
{
    foreach (auto btnKey, digitBTNs.keys())
    {
        if (event->key() == btnKey)
            digitBTNs[btnKey]->animateClick(100);
    }

    foreach (auto btnKey, operatorBTNs.keys())
    {
        if (event->key() == btnKey)
        {
            operatorBTNs[btnKey]->animateClick(100);
            return;
        }
    }
}

void scienceview::on_btnMS_clicked()
{
    memoryValue = ui->display->text();
}

void scienceview::on_btnMR_clicked()
{
    if (!operand.isEmpty() || !operands.isEmpty() || !opcodes.isEmpty())
    {
        int choice = QMessageBox::question(this, "Memory Recall", "Do you want to use the memory value as a new operand and continue the current calculation?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (choice == QMessageBox::Yes)
        {
            operand = memoryValue;
            ui->display->setText(operand);
        }
        else if (choice == QMessageBox::No)
        {
            operand.clear();
            operands.clear();
            opcodes.clear();
            ui->display->setText(memoryValue);
        }
        else
        {
            // 用户取消操作，不做任何处理
        }
    }
    else
    {
        ui->display->setText(memoryValue);
    }
}

void scienceview::on_btnMC_clicked()
{
    memoryValue = "";
}


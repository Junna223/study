#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QLabel>
#include <QKeyEvent>
#include <QMap>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString operand;
    QString opcode;
    QStack <QString> operands;
    QStack <QString> opcodes;//操作符
    QMap<int,QPushButton*> digitBTNs;
    QMap<char,QPushButton*> operatorBTNs;

    QString calculation(bool *ok=NULL);


private slots:
    void btnNumClicked();
    void btnBinaryOperatorClicked();
    void btnUnaryOperatorClicked();

    void on_btnPeriod_clicked();

    void on_btnDel_clicked();

    void on_btnClear_clicked();

    void on_btnEqual_clicked();

    void btnPlusMinusClicked();

    virtual void keyPressEvent(QKeyEvent *event);
    void on_pushButton_18_clicked();

    void on_btnPlusMinus_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

#ifndef SCIENCEVIEW_H
#define SCIENCEVIEW_H

#include <QWidget>
#include <QStack>
#include <QLabel>
#include <QKeyEvent>
#include <QMap>
#include <QPushButton>

namespace Ui {
class scienceview;
}

class scienceview : public QWidget
{
    Q_OBJECT

public:
    explicit scienceview(QWidget *parent = nullptr);
    ~scienceview();

    QString operand;
    QString opcode;
    QStack <QString> operands;
    QStack <QString> opcodes;//操作符
    QMap<int,QPushButton*> digitBTNs;
    QMap<char,QPushButton*> operatorBTNs;

    QString calculation(bool *ok=NULL);

    QString memoryValue;


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

    void on_btnMS_clicked();

    void on_btnMR_clicked();

    void on_btnMC_clicked();

private:
    Ui::scienceview *ui;
};

#endif // SCIENCEVIEW_H

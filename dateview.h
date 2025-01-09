#ifndef DATEVIEW_H
#define DATEVIEW_H

#include <QWidget>
#include <QDateEdit>
#include <QLabel>
#include <QLineEdit>

namespace Ui {
class dateview;
}

class dateview : public QWidget
{
    Q_OBJECT

public:
    explicit dateview(QWidget *parent = nullptr);
    ~dateview();

private slots:
    void calculateDifference();

private:
    Ui::dateview *ui;
//    QDateEdit *startDatePicker;
//    QDateEdit *endDatePicker;
//    QLabel *differenceLabel;
};

#endif // DATEVIEW_H

#include "dateview.h"
#include "ui_dateview.h"

dateview::dateview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dateview)
{
    ui->setupUi(this);

    connect(ui->date1Edit, &QDateEdit::dateChanged, this, &dateview::calculateDifference);
    connect(ui->date2Edit, &QDateEdit::dateChanged, this, &dateview::calculateDifference);
}



dateview::~dateview()
{
    delete ui;
}

void dateview::calculateDifference()
{
    QDate startDate = ui->date1Edit->date();
        QDate endDate = ui->date2Edit->date();
        int days = startDate.daysTo(endDate);

        QString difference;
        if (days < 0) {
            days = -days;
            difference = QString::number(days) + " 天前";
        } else {
            difference = QString::number(days) + " 天后";
        }

        ui->outcome->setText(difference);
}

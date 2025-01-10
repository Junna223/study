#ifndef CURRENCYCONVERSIONVIEW_H
#define CURRENCYCONVERSIONVIEW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class CurrencyConversionView; }
QT_END_NAMESPACE

class CurrencyConversionView : public QWidget
{
    Q_OBJECT

public:
    explicit CurrencyConversionView(QWidget *parent = nullptr);
    ~CurrencyConversionView();

private slots:
    void updateConversion();  // 更新货币转换结果

private:
    Ui::CurrencyConversionView *ui;
};

#endif // CURRENCYCONVERSIONVIEW_H

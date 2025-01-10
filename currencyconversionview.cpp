#include "CurrencyConversionView.h"
#include "ui_CurrencyConversionView.h"
#include <QDoubleValidator>

CurrencyConversionView::CurrencyConversionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrencyConversionView)
{
    ui->setupUi(this);
    //this->setMinimumSize(300, 200);

    // 设置QLineEdit的验证器，确保输入的是数字
    QDoubleValidator *validator = new QDoubleValidator(this);
    ui->lineEdit1->setValidator(validator);
    ui->lineEdit2->setValidator(validator);

    // 连接信号和槽
    connect(ui->comboBox1, &QComboBox::currentTextChanged, this, &CurrencyConversionView::updateConversion);
    connect(ui->comboBox2, &QComboBox::currentTextChanged, this, &CurrencyConversionView::updateConversion);
    connect(ui->lineEdit1, &QLineEdit::textChanged, this, &CurrencyConversionView::updateConversion);
}

CurrencyConversionView::~CurrencyConversionView()
{
    delete ui;
}

void CurrencyConversionView::updateConversion()
{
    bool ok;
    double amount = ui->lineEdit1->text().toDouble(&ok);
    if (!ok || amount <= 0) {
        ui->lineEdit2->clear();
        return;
    }

    QString fromCurrency = ui->comboBox1->currentText();
    QString toCurrency = ui->comboBox2->currentText();

    // 这里我们使用一个静态汇率作为示例
    double exchangeRate = 1.0;  // 默认汇率为1
    if (fromCurrency == "美元" && toCurrency == "人民币") {
        exchangeRate = 6.5;   // 示例汇率：1 USD = 6.5 CNY
    } else if (fromCurrency == "人民币" && toCurrency == "美元") {
        exchangeRate = 1 / 6.5;
    } else if (fromCurrency == "欧元" && toCurrency == "人民币") {
        exchangeRate = 7.8;   // 示例汇率：1 EUR = 7.8 CNY
    } else if (fromCurrency == "人民币" && toCurrency == "欧元") {
        exchangeRate = 1 / 7.8;
    }
    // 添加其他货币对的汇率...

    // 计算转换结果
    double result = amount * exchangeRate;
    ui->lineEdit2->setText(QString::number(result, 'f', 2));
}

#include "interface.h"
#include "../common/common.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
    , currentRootsCount(0)
    , maxRootsCount(0)
    , currentNumberType("real")
{
    setWindowTitle("Работа с полиномами (Real/Complex)");
    setFixedSize(650, 550);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Выбор типа чисел
    QHBoxLayout *typeLayout = new QHBoxLayout();
    QLabel *lblType = new QLabel("Тип чисел:", this);
    radioReal = new QRadioButton("Вещественные", this);
    radioComplex = new QRadioButton("Комплексные", this);
    radioReal->setChecked(true);

    QButtonGroup *numberTypeGroup = new QButtonGroup(this);
    numberTypeGroup->addButton(radioReal);
    numberTypeGroup->addButton(radioComplex);

    typeLayout->addWidget(lblType);
    typeLayout->addWidget(radioReal);
    typeLayout->addWidget(radioComplex);
    typeLayout->addStretch();

    // Степень
    QHBoxLayout *degreeLayout = new QHBoxLayout();
    lblDegree = new QLabel("Степень:", this);
    editDegree = new QLineEdit("0", this);
    editDegree->setFixedWidth(50);
    btnSetDegree = new QPushButton("Установить", this);
    degreeLayout->addWidget(lblDegree);
    degreeLayout->addWidget(editDegree);
    degreeLayout->addWidget(btnSetDegree);
    degreeLayout->addStretch();

    // Коэффициент an
    QHBoxLayout *anLayout = new QHBoxLayout();
    lblAn = new QLabel("an =", this);
    editAnRe = new QLineEdit("1", this);
    editAnRe->setFixedWidth(50);
    QLabel *lblPlus1 = new QLabel("+ i*", this);
    editAnIm = new QLineEdit("0", this);
    editAnIm->setFixedWidth(50);
    btnSetAn = new QPushButton("Установить an", this);
    anLayout->addWidget(lblAn);
    anLayout->addWidget(editAnRe);
    anLayout->addWidget(lblPlus1);
    anLayout->addWidget(editAnIm);
    anLayout->addWidget(btnSetAn);
    anLayout->addStretch();

    // Добавление корня
    QHBoxLayout *rootLayout = new QHBoxLayout();
    lblRoot = new QLabel("Корень =", this);
    editRootRe = new QLineEdit("0", this);
    editRootRe->setFixedWidth(50);
    QLabel *lblPlus2 = new QLabel("+ i*", this);
    editRootIm = new QLineEdit("0", this);
    editRootIm->setFixedWidth(50);
    btnAddRoot = new QPushButton("Добавить корень", this);
    lblRootsCount = new QLabel("Корней: 0/0", this);
    rootLayout->addWidget(lblRoot);
    rootLayout->addWidget(editRootRe);
    rootLayout->addWidget(lblPlus2);
    rootLayout->addWidget(editRootIm);
    rootLayout->addWidget(btnAddRoot);
    rootLayout->addWidget(lblRootsCount);
    rootLayout->addStretch();

    // Изменение корня
    QHBoxLayout *changeRootLayout = new QHBoxLayout();
    lblChangeRoot = new QLabel("Изменить корень с индексом:", this);
    editRootIndex = new QLineEdit("0", this);
    editRootIndex->setFixedWidth(30);
    QLabel *lblOn = new QLabel("на значение:", this);
    editNewRootRe = new QLineEdit("0", this);
    editNewRootRe->setFixedWidth(50);
    QLabel *lblPlus3 = new QLabel("+ i*", this);
    editNewRootIm = new QLineEdit("0", this);
    editNewRootIm->setFixedWidth(50);
    btnChangeRoot = new QPushButton("Изменить", this);
    changeRootLayout->addWidget(lblChangeRoot);
    changeRootLayout->addWidget(editRootIndex);
    changeRootLayout->addWidget(lblOn);
    changeRootLayout->addWidget(editNewRootRe);
    changeRootLayout->addWidget(lblPlus3);
    changeRootLayout->addWidget(editNewRootIm);
    changeRootLayout->addWidget(btnChangeRoot);
    changeRootLayout->addStretch();

    // Размерность
    QHBoxLayout *resizeLayout = new QHBoxLayout();
    lblResize = new QLabel("Новая размерность:", this);
    editNewSize = new QLineEdit("0", this);
    editNewSize->setFixedWidth(50);
    btnResize = new QPushButton("Изменить размерность", this);
    resizeLayout->addWidget(lblResize);
    resizeLayout->addWidget(editNewSize);
    resizeLayout->addWidget(btnResize);
    resizeLayout->addStretch();

    // Вычисление в точке
    QHBoxLayout *pointLayout = new QHBoxLayout();
    lblPoint = new QLabel("Вычислить в точке x =", this);
    editPointRe = new QLineEdit("0", this);
    editPointRe->setFixedWidth(50);
    QLabel *lblPlus4 = new QLabel("+ i*", this);
    editPointIm = new QLineEdit("0", this);
    editPointIm->setFixedWidth(50);
    btnCalculate = new QPushButton("Вычислить", this);
    lblResult = new QLabel("Результат: ", this);
    pointLayout->addWidget(lblPoint);
    pointLayout->addWidget(editPointRe);
    pointLayout->addWidget(lblPlus4);
    pointLayout->addWidget(editPointIm);
    pointLayout->addWidget(btnCalculate);
    pointLayout->addWidget(lblResult);
    pointLayout->addStretch();

    // Информация о полиноме
    QLabel *lblPolynomInfo = new QLabel("Текущий полином:", this);
    textPolynomInfo = new QTextEdit(this);
    textPolynomInfo->setReadOnly(true);
    textPolynomInfo->setPlainText("Полином не инициализирован");

    // Добавляем все в основной layout
    mainLayout->addLayout(typeLayout);
    mainLayout->addLayout(degreeLayout);
    mainLayout->addLayout(anLayout);
    mainLayout->addLayout(rootLayout);
    mainLayout->addLayout(changeRootLayout);
    mainLayout->addLayout(resizeLayout);
    mainLayout->addLayout(pointLayout);
    mainLayout->addWidget(lblPolynomInfo);
    mainLayout->addWidget(textPolynomInfo);

    // Подключаем сигналы
    connect(btnSetDegree, &QPushButton::clicked, this, &TInterface::onSetDegree);
    connect(btnSetAn, &QPushButton::clicked, this, &TInterface::onSetAn);
    connect(btnAddRoot, &QPushButton::clicked, this, &TInterface::onAddRoot);
    connect(btnChangeRoot, &QPushButton::clicked, this, &TInterface::onChangeRoot);
    connect(btnResize, &QPushButton::clicked, this, &TInterface::onResize);
    connect(btnCalculate, &QPushButton::clicked, this, &TInterface::onCalculate);
    connect(radioReal, &QRadioButton::toggled, this, &TInterface::onNumberTypeChanged);
    connect(radioComplex, &QRadioButton::toggled, this, &TInterface::onNumberTypeChanged);

    updateNumberType();
}

TInterface::~TInterface()
{
}

void TInterface::updateRootsDisplay()
{
    lblRootsCount->setText(QString("Корней: %1/%2").arg(currentRootsCount).arg(maxRootsCount));
    btnAddRoot->setEnabled(currentRootsCount < maxRootsCount);
}

void TInterface::updateNumberType()
{
    currentNumberType = radioReal->isChecked() ? "real" : "complex";

    // Скрываем/показываем поля для мнимой части в зависимости от типа чисел
    bool showImaginary = (currentNumberType == "complex");

    editAnIm->setVisible(showImaginary);
    editRootIm->setVisible(showImaginary);
    editNewRootIm->setVisible(showImaginary);
    editPointIm->setVisible(showImaginary);

    // Обновляем подписи
    QList<QLabel*> imaginaryLabels = this->findChildren<QLabel*>(QString(), Qt::FindDirectChildrenOnly);
    for (QLabel* label : imaginaryLabels) {
        if (label->text().contains("i*")) {
            label->setVisible(showImaginary);
        }
    }

    // Сбрасываем состояние
    currentRootsCount = 0;
    maxRootsCount = 0;
    updateRootsDisplay();
}

void TInterface::onNumberTypeChanged()
{
    updateNumberType();
}

void TInterface::onSetDegree()
{
    QString degreeStr = editDegree->text();
    bool ok;
    int degree = degreeStr.toInt(&ok);
    if (!ok || degree < 0) {
        degree = 0;
        editDegree->setText("0");
    }

    maxRootsCount = degree;
    updateRootsDisplay();

    QString msg = currentNumberType + separator + degreeStr + separator + QString::number(RESIZE_POLYNOM_REQUEST);
    qDebug() << "Set degree request:" << msg;
    emit request(msg);
}

void TInterface::onSetAn()
{
    QString reStr = editAnRe->text();
    QString imStr = currentNumberType == "complex" ? editAnIm->text() : "0";
    QString msg = currentNumberType + separator + reStr + separator + imStr + separator + QString::number(ADD_LEAD_COEFFICIENT_REQUEST);
    qDebug() << "Set an request:" << msg;
    emit request(msg);
}

void TInterface::onAddRoot()
{
    if (currentRootsCount >= maxRootsCount) {
        qDebug() << "Нельзя добавить корень: достигнут лимит" << maxRootsCount;
        return;
    }

    QString reStr = editRootRe->text();
    QString imStr = currentNumberType == "complex" ? editRootIm->text() : "0";
    QString msg = currentNumberType + separator + reStr + separator + imStr + separator + QString::number(ADD_ROOT_REQUEST);
    qDebug() << "Add root request:" << msg;
    emit request(msg);

    currentRootsCount++;
    updateRootsDisplay();
}

void TInterface::onChangeRoot()
{
    QString indexStr = editRootIndex->text();
    QString reStr = editNewRootRe->text();
    QString imStr = currentNumberType == "complex" ? editNewRootIm->text() : "0";
    QString msg = currentNumberType + separator + indexStr + separator + reStr + separator + imStr + separator + QString::number(CHANGE_ROOT_REQUEST);
    qDebug() << "Change root request:" << msg;
    emit request(msg);
}

void TInterface::onResize()
{
    QString sizeStr = editNewSize->text();
    bool ok;
    int newSize = sizeStr.toInt(&ok);
    if (!ok || newSize < 0) {
        newSize = 0;
        editNewSize->setText("0");
    }

    maxRootsCount = newSize;
    updateRootsDisplay();

    QString msg = currentNumberType + separator + sizeStr + separator + QString::number(RESIZE_POLYNOM_REQUEST);
    qDebug() << "Resize request:" << msg;
    emit request(msg);
}

void TInterface::onCalculate()
{
    QString reStr = editPointRe->text();
    QString imStr = currentNumberType == "complex" ? editPointIm->text() : "0";
    QString msg = currentNumberType + separator + reStr + separator + imStr + separator + QString::number(VALUE_AT_POINT_REQUEST);
    qDebug() << "Calculate request:" << msg;
    emit request(msg);
}

void TInterface::answer(QString msg)
{
    qDebug() << "Received answer:" << msg;

    QStringList parts = msg.split(separator);
    if (parts.size() < 3) {
        textPolynomInfo->setPlainText("Ошибка: некорректный ответ от сервера: " + msg);
        return;
    }

    QString numberType = parts[0];
    if (numberType != currentNumberType) {
        qDebug() << "Answer for different number type, ignoring";
        return;
    }

    bool ok;
    int answerType = parts[1].toInt(&ok);
    if (!ok) {
        textPolynomInfo->setPlainText("Ошибка: не удалось распознать тип ответа");
        return;
    }

    QString data = parts[2];
    QString form2Data = parts.size() > 3 ? parts[3] : "";

    switch (answerType) {
        case PRINT_POLYNOM_ANSWER:
        case ADD_LEAD_COEFFICIENT_ANSWER:
        case CHANGE_ROOT_ANSWER:
        case ADD_ROOT_ANSWER:
        case RESIZE_POLYNOM_ANSWER:
            if (!form2Data.isEmpty()) {
                textPolynomInfo->setPlainText("Форма 1 (по коэффициентам):\n" + data +
                                            "\n\nФорма 2 (по корням):\n" + form2Data);
            } else {
                textPolynomInfo->setPlainText(data);
            }
            break;

        case VALUE_AT_POINT_ANSWER:
            lblResult->setText("Результат: " + data);
            textPolynomInfo->setPlainText("Значение в точке: " + data);
            break;

        default:
            textPolynomInfo->setPlainText("Неизвестный тип ответа: " + msg);
            break;
    }
}
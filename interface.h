#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QRadioButton;

class TInterface : public QWidget
{
    Q_OBJECT

private:
    // Степень
    QLabel *lblDegree;
    QLineEdit *editDegree;
    QPushButton *btnSetDegree;

    // Коэффициент an
    QLabel *lblAn;
    QLineEdit *editAnRe;
    QLineEdit *editAnIm;
    QPushButton *btnSetAn;

    // Добавление корня
    QLabel *lblRoot;
    QLineEdit *editRootRe;
    QLineEdit *editRootIm;
    QPushButton *btnAddRoot;
    QLabel *lblRootsCount;

    // Изменение корня
    QLabel *lblChangeRoot;
    QLineEdit *editRootIndex;
    QLineEdit *editNewRootRe;
    QLineEdit *editNewRootIm;
    QPushButton *btnChangeRoot;

    // Размерность
    QLabel *lblResize;
    QLineEdit *editNewSize;
    QPushButton *btnResize;

    // Вычисление в точке
    QLabel *lblPoint;
    QLineEdit *editPointRe;
    QLineEdit *editPointIm;
    QPushButton *btnCalculate;
    QLabel *lblResult;

    QTextEdit *textPolynomInfo;

    // Состояние полинома
    int currentRootsCount;
    int maxRootsCount;

    // Выбор типа чисел
    QRadioButton *radioReal;
    QRadioButton *radioComplex;
    QString currentNumberType;

    void updateRootsDisplay();
    void updateNumberType();

public:
    explicit TInterface(QWidget *parent = nullptr);
    ~TInterface();

public slots:
    void answer(QString msg);

    signals:
        void request(QString msg);

private slots:
    void onSetDegree();
    void onSetAn();
    void onAddRoot();
    void onChangeRoot();
    void onResize();
    void onCalculate();
    void onNumberTypeChanged();
};

#endif // INTERFACE_H
#include "application.h"
#include "../common/communicator.h"
#include "polynom.h"
#include "../common/common.h"
#include <QString>
#include <QByteArray>
#include <QDebug>

// Вспомогательная функция для преобразования number в QString
static QString numberToQString(const number& num) {
    double re = num.getRe();
    double im = num.getIm();

    if (im < 0 && re != 0) {
        return QString("%1%2i").arg(re).arg(im);
    } else if (im != 0 && re == 0) {
        return QString("%1i").arg(im);
    } else if (im > 0 && re != 0) {
        return QString("%1+%2i").arg(re).arg(im);
    } else if (im == 0 && re != 0) {
        return QString::number(re);
    } else {
        return "0";
    }
}

TApplication::TApplication(int argc, char *argv[])
    : QCoreApplication(argc,argv)
{
    TCommParams pars = {
        QHostAddress("127.0.0.1"), 10000,
        QHostAddress("127.0.0.1"), 10001
    };
    comm = new TCommunicator(pars, this);

    // Инициализируем полиномы
    polynom_real = new Polynom<number>(0, number(1, 0));
    polynom_complex = new Polynom<number>(0, number(1, 0));

    connect(comm, SIGNAL(recieved(QByteArray)), this, SLOT(recieve(QByteArray)));
}

number TApplication::parseNumberForMode(const QStringList& parts, int startIndex, bool realMode)
{
    if (realMode) {
        if (parts.size() > startIndex) {
            double re = parts[startIndex].toDouble();
            return number(re, 0);
        }
    } else {
        if (parts.size() > startIndex + 1) {
            double re = parts[startIndex].toDouble();
            double im = parts[startIndex + 1].toDouble();
            return number(re, im);
        }
    }
    return number(0, 0);
}

void TApplication::recieve(QByteArray msg)
{
    QString answer;
    QString data = QString(msg);
    QStringList parts = data.split(separator);

    qDebug() << "Received:" << data;

    if (parts.size() < 2) {
        qDebug() << "Not enough parts in message";
        return;
    }

    QString numberType = parts.takeFirst();

    bool ok;
    int requestType = parts.takeLast().toInt(&ok);
    if (!ok) {
        qDebug() << "Invalid request type";
        return;
    }

    if (numberType == "real") {
        handleRealRequest(parts, requestType, answer);
    } else if (numberType == "complex") {
        handleComplexRequest(parts, requestType, answer);
    } else {
        qDebug() << "Unknown number type:" << numberType;
        return;
    }

    if (!answer.isEmpty()) {
        qDebug() << "Sending answer:" << answer;
        comm->send(answer.toUtf8());
    }
}

void TApplication::handleRealRequest(const QStringList& parts, int requestType, QString& answer)
{
    QString result;

    switch (requestType)
    {
        case PRINT_POLYNOM_REQUEST: {
            QString form1 = QString::fromStdString(polynom_real->getForm1());
            QString form2 = QString::fromStdString(polynom_real->getForm2());
            result = "real";
            result.append(separator);
            result.append(QString::number(PRINT_POLYNOM_ANSWER));
            result.append(separator);
            result.append(form1);
            result.append(separator);
            result.append(form2);
            answer = result;
            break;
        }

        case VALUE_AT_POINT_REQUEST: {
            if (parts.size() >= 1) {
                number x = parseNumberForMode(parts, 0, true);
                number value = polynom_real->valueAtPoint(x);
                QString valueStr = numberToQString(value);
                result = "real";
                result.append(separator);
                result.append(QString::number(VALUE_AT_POINT_ANSWER));
                result.append(separator);
                result.append(valueStr);
                answer = result;
            }
            break;
        }

        case ADD_LEAD_COEFFICIENT_REQUEST: {
            if (parts.size() >= 1) {
                number coeff = parseNumberForMode(parts, 0, true);
                polynom_real->setAn(coeff);
                QString form1 = QString::fromStdString(polynom_real->getForm1());
                QString form2 = QString::fromStdString(polynom_real->getForm2());
                result = "real";
                result.append(separator);
                result.append(QString::number(ADD_LEAD_COEFFICIENT_ANSWER));
                result.append(separator);
                result.append(form1);
                result.append(separator);
                result.append(form2);
                answer = result;
            }
            break;
        }

        case ADD_ROOT_REQUEST: {
            if (parts.size() >= 1) {
                number root = parseNumberForMode(parts, 0, true);
                polynom_real->addRoot(root);
                QString form1 = QString::fromStdString(polynom_real->getForm1());
                QString form2 = QString::fromStdString(polynom_real->getForm2());
                result = "real";
                result.append(separator);
                result.append(QString::number(ADD_ROOT_ANSWER));
                result.append(separator);
                result.append(form1);
                result.append(separator);
                result.append(form2);
                answer = result;
            }
            break;
        }

        case RESIZE_POLYNOM_REQUEST: {
            if (parts.size() >= 1) {
                int new_degree = parts[0].toInt();
                polynom_real->resize(new_degree);
                QString form1 = QString::fromStdString(polynom_real->getForm1());
                QString form2 = QString::fromStdString(polynom_real->getForm2());
                result = "real";
                result.append(separator);
                result.append(QString::number(RESIZE_POLYNOM_ANSWER));
                result.append(separator);
                result.append(form1);
                result.append(separator);
                result.append(form2);
                answer = result;
            }
            break;
        }

        case CHANGE_ROOT_REQUEST: {
            if (parts.size() >= 2) {
                int index = parts[0].toInt();
                number new_root = parseNumberForMode(parts, 1, true);
                polynom_real->changeRoot(index, new_root);
                QString form1 = QString::fromStdString(polynom_real->getForm1());
                QString form2 = QString::fromStdString(polynom_real->getForm2());
                result = "real";
                result.append(separator);
                result.append(QString::number(CHANGE_ROOT_ANSWER));
                result.append(separator);
                result.append(form1);
                result.append(separator);
                result.append(form2);
                answer = result;
            }
            break;
        }
    }
}

void TApplication::handleComplexRequest(const QStringList& parts, int requestType, QString& answer)
{
    QString result;

    switch (requestType)
    {
        case PRINT_POLYNOM_REQUEST: {
            QString form1 = QString::fromStdString(polynom_complex->getForm1());
            QString form2 = QString::fromStdString(polynom_complex->getForm2());
            result = "complex";
            result.append(separator);
            result.append(QString::number(PRINT_POLYNOM_ANSWER));
            result.append(separator);
            result.append(form1);
            result.append(separator);
            result.append(form2);
            answer = result;
            break;
        }

        case VALUE_AT_POINT_REQUEST: {
            if (parts.size() >= 2) {
                number x = parseNumberForMode(parts, 0, false);
                number value = polynom_complex->valueAtPoint(x);
                QString valueStr = numberToQString(value);
                result = "complex";
                result.append(separator);
                result.append(QString::number(VALUE_AT_POINT_ANSWER));
                result.append(separator);
                result.append(valueStr);
                answer = result;
            }
            break;
        }

        case ADD_LEAD_COEFFICIENT_REQUEST: {
            if (parts.size() >= 2) {
                number coeff = parseNumberForMode(parts, 0, false);
                polynom_complex->setAn(coeff);
                QString form1 = QString::fromStdString(polynom_complex->getForm1());
                QString form2 = QString::fromStdString(polynom_complex->getForm2());
                result = "complex";
                result.append(separator);
                result.append(QString::number(ADD_LEAD_COEFFICIENT_ANSWER));
                result.append(separator);
                result.append(form1);
                result.append(separator);
                result.append(form2);
                answer = result;
            }
            break;
        }

        case ADD_ROOT_REQUEST: {
            if (parts.size() >= 2) {
                number root = parseNumberForMode(parts, 0, false);
                polynom_complex->addRoot(root);
                QString form1 = QString::fromStdString(polynom_complex->getForm1());
                QString form2 = QString::fromStdString(polynom_complex->getForm2());
                result = "complex";
                result.append(separator);
                result.append(QString::number(ADD_ROOT_ANSWER));
                result.append(separator);
                result.append(form1);
                result.append(separator);
                result.append(form2);
                answer = result;
            }
            break;
        }

        case RESIZE_POLYNOM_REQUEST: {
            if (parts.size() >= 1) {
                int new_degree = parts[0].toInt();
                polynom_complex->resize(new_degree);
                QString form1 = QString::fromStdString(polynom_complex->getForm1());
                QString form2 = QString::fromStdString(polynom_complex->getForm2());
                result = "complex";
                result.append(separator);
                result.append(QString::number(RESIZE_POLYNOM_ANSWER));
                result.append(separator);
                result.append(form1);
                result.append(separator);
                result.append(form2);
                answer = result;
            }
            break;
        }

        case CHANGE_ROOT_REQUEST: {
            if (parts.size() >= 3) {
                int index = parts[0].toInt();
                number new_root = parseNumberForMode(parts, 1, false);
                polynom_complex->changeRoot(index, new_root);
                QString form1 = QString::fromStdString(polynom_complex->getForm1());
                QString form2 = QString::fromStdString(polynom_complex->getForm2());
                result = "complex";
                result.append(separator);
                result.append(QString::number(CHANGE_ROOT_ANSWER));
                result.append(separator);
                result.append(form1);
                result.append(separator);
                result.append(form2);
                answer = result;
            }
            break;
        }
    }
}

TApplication::~TApplication() {
    delete polynom_real;
    delete polynom_complex;
    delete comm;
}

#ifndef SERVER_APPLICATION_H
#define SERVER_APPLICATION_H

#include <QCoreApplication>
#include "../common/communicator.h"
#include "polynom.h"
#include "number.h"

class TApplication : public QCoreApplication
{
    Q_OBJECT

private:
    TCommunicator* comm;
    Polynom<number>* polynom_real;
    Polynom<number>* polynom_complex;

public:
    TApplication(int argc, char *argv[]);
    ~TApplication();

private slots:
    void recieve(QByteArray msg);

private:
    void handleRealRequest(const QStringList& parts, int requestType, QString& answer);
    void handleComplexRequest(const QStringList& parts, int requestType, QString& answer);
    number parseNumberForMode(const QStringList& parts, int startIndex, bool realMode);
};

#endif // SERVER_APPLICATION_H
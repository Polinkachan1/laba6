#ifndef CLIENT_APPLICATION_H
#define CLIENT_APPLICATION_H

#include <QApplication>
#include "../common/communicator.h"
#include "interface.h"

class TApplication : public QApplication
{
    Q_OBJECT

private:
    TCommunicator* comm;
    TInterface* interface;

public:
    TApplication(int argc, char *argv[]);

private slots:
    void fromCommunicator(QByteArray msg);
    void toCommunicator(QString msg);
};

#endif // CLIENT_APPLICATION_H
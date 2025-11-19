#include "application.h"
#include "../common/common.h"
#include <QDebug>

TApplication::TApplication(int argc, char *argv[])
    : QApplication(argc, argv)
{
    TCommParams pars = { QHostAddress::LocalHost, 10001, QHostAddress::LocalHost, 10000 };
    comm = new TCommunicator(pars, this);

    interface = new TInterface();
    interface->show();

    connect(comm, SIGNAL(recieved(QByteArray)), this, SLOT(fromCommunicator(QByteArray)));
    connect(interface, SIGNAL(request(QString)), this, SLOT(toCommunicator(QString)));

    qDebug() << "Клиент запущен";
}

void TApplication::fromCommunicator(QByteArray msg)
{
    qDebug() << "Получено от сервера:" << QString(msg);
    interface->answer(QString(msg));
}

void TApplication::toCommunicator(QString msg)
{
    qDebug() << "Отправлено серверу:" << msg;
    comm->send(msg.toUtf8());
}
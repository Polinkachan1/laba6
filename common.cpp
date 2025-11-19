#include "common.h"

const QChar separator(';');
QString& operator<< (QString& m, const QString& s)
{
    if (!m.isEmpty()) {
        m += separator;
    }
    m += s;
    return m;
}
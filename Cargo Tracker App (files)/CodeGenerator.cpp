#include "CodeGenerator.h"
#include <QString>

QString CodeGenerator::nextCode(ContainerKind kind, const QDate& date){
    const int y=date.year(); const int m=date.month();
    if (y!=m_year || m!=m_month){ m_year=y; m_month=m; m_serial=0; }
    m_serial = qMin(m_serial+1, 9999);
    const QChar typeChar = (kind==ContainerKind::Box? QChar('B'): QChar('C'));
    return QString::number(m_year).rightJustified(4, '0') + "/" + QString::number(m_month).rightJustified(2,'0') + "/" + typeChar + QString::number(m_serial);
}

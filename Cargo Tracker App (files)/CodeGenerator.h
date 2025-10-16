#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include <QObject>
#include <QDate>

enum class ContainerKind{ Box, Cylinder };

class CodeGenerator : public QObject{
    Q_OBJECT
public:
    explicit CodeGenerator(QObject* parent=nullptr): QObject(parent) {}
    QString nextCode(ContainerKind kind, const QDate& date=QDate::currentDate());
private:
    int m_year{0}; int m_month{0}; int m_serial{0};
};

#endif // CODEGENERATOR_H

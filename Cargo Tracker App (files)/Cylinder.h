#ifndef CYLINDER_H
#define CYLINDER_H
#include "Container.h"
#include <QtGlobal>

// The Cylinder class represents a cylindrical container, inheriting from the Container base class.
class Cylinder : public Container {
    Q_OBJECT
    // Q_PROPERTY declares the diameter property, allowing it to be used with Qt's Meta-Object System.
    // The NOTIFY signal ensures that other objects can be notified when the diameter changes.
    Q_PROPERTY(int diameter READ diameter WRITE setDiameter NOTIFY diameterChanged)
public:
    // This is the constructor for the Cylinder class.
    explicit Cylinder(QObject* parent=nullptr): Container(parent) {}

    // A getter method to retrieve the cylinder's diameter.
    int diameter() const {
        return m_diameter;
    }

    // A setter method to set the cylinder's diameter and emit a signal if the value changes.
    void setDiameter(int v){
        if (m_diameter == v)
            return;
        m_diameter = v;
        emit diameterChanged(m_diameter);
    }

    // This override method calculates the volume of the cylinder.
    int volume() const override {
        const double r = m_diameter / 2.0;
        const double v = 3.14159265358979323846 * r * r * height();
        return static_cast<int>(qRound(v));
    }

    // This override method returns the type name of the container as a string.
    QString typeName() const override {
        return "Cylinder";
    }

    // This override method creates a new Cylinder object that is a copy of the current one.
    Container* clone(QObject* parent=nullptr) const override {
        auto* c = new Cylinder(parent);
        c->setCode(code());
        c->setWeight(weight());
        c->setHeight(height());
        c->setDiameter(m_diameter);
        return c;
    }

signals:
    // A signal to notify when the diameter property has changed.
    void diameterChanged(int diameter);

private:
    // A private member variable to store the cylinder's diameter.
    int m_diameter{1};
};

#endif // CYLINDER_H

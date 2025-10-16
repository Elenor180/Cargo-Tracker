#ifndef BOX_H
#define BOX_H
#include "Container.h"

// The Box class represents a rectangular container. It inherits from the Container base class.
class Box : public Container {
    Q_OBJECT
    // Q_PROPERTY macro declares properties for the class, allowing them to be accessible via the Qt Meta-Object System.
    // The NOTIFY signal is emitted when the property's value changes.
    Q_PROPERTY(int length READ length WRITE setLength NOTIFY lengthChanged)
    Q_PROPERTY(int breadth READ breadth WRITE setBreadth NOTIFY breadthChanged)

public:
    // This is the constructor for the Box class.
    explicit Box(QObject* parent=nullptr) : Container(parent) {}

    // A getter method to retrieve the box's length.
    int length() const {
        return m_length;
    }

    // A setter method to set the box's length and emit a signal if the value changes.
    void setLength(int v){
        if (m_length == v)
            return;
        m_length = v;
        emit lengthChanged(m_length);
    }

    // A getter method to retrieve the box's breadth.
    int breadth() const {
        return m_breadth;
    }

    // A setter method to set the box's breadth and emit a signal if the value changes.
    void setBreadth(int v){
        if (m_breadth == v)
            return;
        m_breadth = v;
        emit breadthChanged(m_breadth);
    }

    // This override method calculates the volume of the box.
    int volume() const override {
        return m_length * m_breadth * height();
    }

    // This override method returns the type name of the container as a string.
    QString typeName() const override {
        return "Box";
    }

    // This override method creates a new Box object that is a copy of the current one.
    Container* clone(QObject* parent=nullptr) const override {
        auto* b = new Box(parent);
        b->setCode(code());
        b->setWeight(weight());
        b->setHeight(height());
        b->setLength(m_length);
        b->setBreadth(m_breadth);
        return b;
    }

signals:
    // Signals to notify when the length or breadth properties have changed.
    void lengthChanged(int length);
    void breadthChanged(int breadth);

private:
    // Private member variables to store the box's length and breadth.
    int m_length{1};
    int m_breadth{1};
};

#endif // BOX_H

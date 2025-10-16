#ifndef CONTAINER_H
#define CONTAINER_H

#include <QObject>
#include <QString>

// The Container is an abstract base class that defines the common interface for all types of containers.
class Container : public QObject {
    Q_OBJECT
    // The Q_PROPERTY macro declares properties for the class, enabling them to be used with the Qt Meta-Object System.
    // The NOTIFY signal is emitted when the property's value changes.
    Q_PROPERTY(QString code READ code WRITE setCode NOTIFY codeChanged)
    Q_PROPERTY(int weight READ weight WRITE setWeight NOTIFY weightChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
public:
    // This is the constructor for the Container class.
    explicit Container(QObject* parent=nullptr) : QObject(parent) {}
    // The virtual destructor ensures proper cleanup of derived classes.
    ~Container() override = default;

    // A getter method to retrieve the container's unique code.
    QString code() const { return m_code; }
    // A setter method to set the container's code and emit a signal if the value changes.
    void setCode(const QString& v) {
        if (m_code == v)
            return;
        m_code = v;
        emit codeChanged(m_code);
    }

    // A getter method to retrieve the container's weight.
    int weight() const { return m_weight; }
    // A setter method to set the container's weight and emit a signal if the value changes.
    void setWeight(int v) {
        if (m_weight == v)
            return;
        m_weight = v;
        emit weightChanged(m_weight);
    }

    // A getter method to retrieve the container's height.
    int height() const { return m_height; }
    // A setter method to set the container's height and emit a signal if the value changes.
    void setHeight(int v) {
        if (m_height == v)
            return;
        m_height = v;
        emit heightChanged(m_height);
    }

    // A pure virtual function to calculate the volume of the container. Derived classes must implement this.
    virtual int volume() const = 0;
    // A pure virtual function to get the type name of the container. Derived classes must implement this.
    virtual QString typeName() const = 0;
    // A pure virtual function to create a clone of the container. Derived classes must implement this.
    virtual Container* clone(QObject* parent=nullptr) const = 0;

signals:
    // Signals to notify when the code, weight, or height properties have changed.
    void codeChanged(const QString& code);
    void weightChanged(int weight);
    void heightChanged(int height);

protected:
    // Private member variables to store the container's code, weight, and height.
    QString m_code;
    int m_weight{1};
    int m_height{1};
};

#endif // CONTAINER_H

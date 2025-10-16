#ifndef PALLET_H
#define PALLET_H
#include <QObject>
#include <QVector>
class Container;

// The Pallet class manages a collection of containers.
// It inherits from QObject to take advantage of Qt's parent-child ownership and signal/slot mechanism.
class Pallet : public QObject {
    Q_OBJECT
public:
    // This is the constructor for the Pallet class. It initializes the pallet's number and parent.
    explicit Pallet(int number=0, QObject* parent=nullptr): QObject(parent), m_number(number) {}

    // A getter method to retrieve the pallet's number.
    int number() const {
        return m_number;
    }

    // A setter method to set the pallet's number. It emits a 'changed' signal after updating the value.
    void setNumber(int n){
        m_number = n;
        emit changed();
    }

    // A getter method to return a constant reference to the vector of containers on the pallet.
    const QVector<Container*>& items() const {
        return m_items;
    }

    // This method adds a new container to the pallet. The pallet takes ownership of the container.
    void add(Container* c);

    // This method calculates and returns the total weight of all containers on the pallet.
    int totalWeight() const;

    // This method calculates and returns the total volume of all containers on the pallet.
    int totalVolume() const;

signals:
    // A signal that is emitted whenever a property of the pallet changes, such as its number or contents.
    void changed();

private:
    // The member variable that stores the unique number for the pallet.
    int m_number{0};
    // A vector to store pointers to the containers on the pallet. The pallet owns these containers through the parent-child hierarchy.
    QVector<Container*> m_items;
};

#endif // PALLET_H

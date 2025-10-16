#ifndef MEMENTO_H
#define MEMENTO_H
#include <QVector>
#include <memory>
class Container;

struct UnallocatedListMemento{ QVector<Container*> snapshot; ~UnallocatedListMemento(); };

class Caretaker{
public:
    void save(const QVector<Container*>& list);
    QVector<Container*> restore();
    bool hasBackup() const {
        return static_cast<bool>(m_memento);
    }
private:
    std::unique_ptr<UnallocatedListMemento> m_memento;
};

#endif // MEMENTO_H

#include "Memento.h"
#include "Container.h"

// The destructor for UnallocatedListMemento.
// It is responsible for cleaning up the memory of all cloned Container objects stored in the snapshot.
UnallocatedListMemento::~UnallocatedListMemento(){
    // Iterates through the vector and deletes each Container object.
    for(auto* c: snapshot) {
        delete c;
    }
    // Clears the vector after all objects have been deleted.
    snapshot.clear();
}

// The save method of the Caretaker class.
// It creates a new memento (snapshot) of the current state of the unallocated list.
void Caretaker::save(const QVector<Container*>& list){
    // Creates a new unique pointer to an UnallocatedListMemento object.
    m_memento = std::make_unique<UnallocatedListMemento>();
    // Reserves memory in the snapshot vector to prevent reallocations.
    m_memento->snapshot.reserve(list.size());
    // Iterates through the original list and creates a deep copy (clone) of each container.
    // The clones are then added to the memento's snapshot.
    for(auto* c: list){
        m_memento->snapshot.push_back(c->clone(nullptr));
    }
}

// The restore method of the Caretaker class.
// It returns a copy of the saved state from the memento.
QVector<Container*> Caretaker::restore(){
    QVector<Container*> out;
    // Returns an empty vector if no memento has been saved.
    if(!m_memento) {
        return out;
    }
    // Reserves memory in the output vector.
    out.reserve(m_memento->snapshot.size());
    // Creates a new deep copy of each container from the snapshot.
    // This ensures the restored objects are independent of the memento's data.
    for(auto* c: m_memento->snapshot){
        out.push_back(c->clone(nullptr));
    }
    return out;
}

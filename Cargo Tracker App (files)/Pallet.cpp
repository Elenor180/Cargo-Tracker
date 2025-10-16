#include "Pallet.h"
#include "Container.h"

void Pallet::add(Container* c){
    if(!c)
        return;
    c->setParent(this);
    m_items.push_back(c);
    emit changed();
}
int Pallet::totalWeight() const { int t=0;
    for(auto* c: m_items) t+=c->weight();
    return t;
}
int Pallet::totalVolume() const { int t=0;
    for(auto* c: m_items) t+=c->volume();
    return t;
}

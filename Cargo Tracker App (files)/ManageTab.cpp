#include "ManageTab.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QListView>
#include <QStringListModel>
#include <QMessageBox>
#include "Box.h"
#include "Cylinder.h"
#include "Pallet.h"
#include "CodeGenerator.h"
#include "Memento.h"

// The constructor initializes the class members and sets up the UI and connections.
ManageTab::ManageTab(QWidget* parent): QWidget(parent), m_codes(new CodeGenerator(this)), m_caretaker(new Caretaker()){
    // Calls helper functions to build the UI, connect signals, and refresh the model.
    buildUi();
    wire();
    refreshUnallocatedModel();
}

// The destructor ensures proper memory management by deleting dynamically allocated objects.
ManageTab::~ManageTab(){
    // qDeleteAll is a Qt convenience function that deletes all pointers in a container.
    qDeleteAll(m_unallocated);
    m_unallocated.clear();
    qDeleteAll(m_pallets);
    m_pallets.clear();
    // Deletes the caretaker object, which is responsible for managing backups.
    delete m_caretaker;
    m_caretaker = nullptr;
}

// A public method to check if a restore operation is possible.
bool ManageTab::canRestore() const{
    return m_caretaker && m_caretaker->hasBackup();
}

// This private helper function builds the entire user interface for the tab.
void ManageTab::buildUi(){
    // A main grid layout is created to organize the widgets.
    auto* layout = new QGridLayout(this);

    // Creates a group box for adding 'Box' containers.
    auto* gbBox = new QGroupBox(tr("Box"), this);
    auto* glb = new QGridLayout(gbBox);
    // Initializes spin boxes for box dimensions and weight.
    sbBoxBr = new QSpinBox(gbBox); sbBoxBr->setRange(1,10000);
    sbBoxLen= new QSpinBox(gbBox); sbBoxLen->setRange(1,10000);
    sbBoxHt = new QSpinBox(gbBox); sbBoxHt->setRange(1,10000);
    sbBoxWt = new QSpinBox(gbBox); sbBoxWt->setRange(1,100000);
    btnAddBox= new QPushButton(tr("Add box"), gbBox); btnAddBox->setObjectName("BoxButton");

    // Adds labels, spin boxes, and the button to the box group box layout.
    glb->addWidget(new QLabel("Breadth"),0,0); glb->addWidget(sbBoxBr,0,1);
    glb->addWidget(new QLabel("Length"),1,0);  glb->addWidget(sbBoxLen,1,1);
    glb->addWidget(new QLabel("Height"),2,0);  glb->addWidget(sbBoxHt,2,1);
    glb->addWidget(new QLabel("Weight"),3,0);  glb->addWidget(sbBoxWt,3,1);
    glb->addWidget(btnAddBox,4,0,1,2);

    // Creates a group box for adding 'Cylinder' containers.
    auto* gbCyl = new QGroupBox(tr("Cylinder"), this);
    auto* glc = new QGridLayout(gbCyl);
    // Initializes spin boxes for cylinder dimensions and weight.
    sbCylDia = new QSpinBox(gbCyl); sbCylDia->setRange(1,10000);
    sbCylHt  = new QSpinBox(gbCyl); sbCylHt->setRange(1,10000);
    sbCylWt  = new QSpinBox(gbCyl); sbCylWt->setRange(1,100000);
    btnAddCyl= new QPushButton(tr("Add cylinder"), gbCyl); btnAddCyl->setObjectName("CylinderButton");

    // Adds labels, spin boxes, and the button to the cylinder group box layout.
    glc->addWidget(new QLabel("Diameter"),0,0); glc->addWidget(sbCylDia,0,1);
    glc->addWidget(new QLabel("Height"),1,0);    glc->addWidget(sbCylHt,1,1);
    glc->addWidget(new QLabel("Weight"),2,0);    glc->addWidget(sbCylWt,2,1);
    glc->addWidget(btnAddCyl,4,0,1,2);

    // Creates UI elements for the unallocated list and pallet management.
    lvUnallocated = new QListView(this);
    m_unallocModel = new QStringListModel(this);
    lvUnallocated->setModel(m_unallocModel);

    sbPallet = new QSpinBox(this); sbPallet->setRange(1, 99999);
    btnMove  = new QPushButton(tr("Move to pallet"), this);
    btnBackup= new QPushButton(tr("Backup"), this);
    btnRestore=new QPushButton(tr("Restore"), this); btnRestore->setEnabled(false);

    // Adds all the group boxes and other widgets to the main layout.
    layout->addWidget(gbBox,0,0);
    layout->addWidget(gbCyl,0,1);

    layout->addWidget(new QLabel(tr("List of unallocated containers")),1,0);
    layout->addWidget(lvUnallocated,2,0,3,1);

    layout->addWidget(new QLabel(tr("Choose pallet number and move selected container")),1,1);
    layout->addWidget(sbPallet,2,1);
    layout->addWidget(btnMove,3,1);
    layout->addWidget(btnBackup,4,1);
    layout->addWidget(btnRestore,5,1);

    // Sets the grid layout as the main layout for the widget.
    setLayout(layout);
}

// This private helper function connects signals from UI elements to the appropriate slots.
void ManageTab::wire(){
    connect(btnAddBox, &QPushButton::clicked, this, &ManageTab::addBox);
    connect(btnAddCyl, &QPushButton::clicked, this, &ManageTab::addCylinder);
    connect(btnMove,   &QPushButton::clicked, this, &ManageTab::moveSelectedToPallet);
    connect(btnBackup, &QPushButton::clicked, this, &ManageTab::backupUnallocated);
    connect(btnRestore,&QPushButton::clicked, this, &ManageTab::restoreUnallocated);
}

// This function updates the list view model and the state of the restore button.
void ManageTab::refreshUnallocatedModel(){
    QStringList codes;
    codes.reserve(m_unallocated.size());
    for(auto* c: m_unallocated) {
        codes << c->code();
    }
    m_unallocModel->setStringList(codes);
    btnRestore->setEnabled(canRestore());
}

// Ensures that a pallet with the given number exists, creating a new one if necessary.
void ManageTab::ensurePallet(int number){
    for(auto* p: m_pallets){
        if(p->number() == number) {
            return;
        }
    }
    // Creates a new pallet and adds it to the list.
    auto* p = new Pallet(number, this);
    m_pallets.push_back(p);
    emit dataChanged();
}

// Slot to handle the creation of a new Box container.
void ManageTab::addBox(){
    auto* b = new Box(this);
    b->setCode(m_codes->nextCode(ContainerKind::Box));
    b->setBreadth(sbBoxBr->value());
    b->setLength(sbBoxLen->value());
    b->setHeight(sbBoxHt->value());
    b->setWeight(sbBoxWt->value());
    m_unallocated.push_back(b);
    refreshUnallocatedModel();
}

// Slot to handle the creation of a new Cylinder container.
void ManageTab::addCylinder(){
    auto* c = new Cylinder(this);
    c->setCode(m_codes->nextCode(ContainerKind::Cylinder));
    c->setDiameter(sbCylDia->value());
    c->setHeight(sbCylHt->value());
    c->setWeight(sbCylWt->value());
    m_unallocated.push_back(c);
    refreshUnallocatedModel();
}

// Slot to move a selected container from the unallocated list to a pallet.
void ManageTab::moveSelectedToPallet(){
    const auto idx = lvUnallocated->currentIndex();
    if(!idx.isValid()){
        QMessageBox::warning(this, tr("Move"), tr("Select a container first."));
        return;
    }
    const int row = idx.row();
    // Takes the container from the unallocated list without deleting it.
    auto* c = m_unallocated.takeAt(row);
    c->setParent(nullptr); // Unparents the container before reparenting.
    const int palNum = sbPallet->value();
    ensurePallet(palNum);
    for(auto* p: m_pallets){
        if(p->number() == palNum){
            // Reparents the container to the pallet.
            c->setParent(p);
            p->add(c);
            break;
        }
    }
    refreshUnallocatedModel();
    emit dataChanged();
}

// Slot to back up the current state of unallocated containers using the Memento pattern.
void ManageTab::backupUnallocated(){
    if(m_caretaker){
        m_caretaker->save(m_unallocated);
    }
    refreshUnallocatedModel();
}

// Slot to restore the unallocated containers from the last backup.
void ManageTab::restoreUnallocated(){
    if(!m_caretaker || !m_caretaker->hasBackup())
        return;
    // Deletes the existing unallocated containers before restoring.
    qDeleteAll(m_unallocated);
    m_unallocated.clear();
    // Retrieves the backup from the caretaker.
    m_unallocated = m_caretaker->restore();
    // Reparents the restored containers to this tab.
    for(auto* c: m_unallocated) {
        c->setParent(this);
    }
    refreshUnallocatedModel();
}

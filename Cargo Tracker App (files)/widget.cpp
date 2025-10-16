#include "widget.h"
#include <QSpinBox>
#include <QPushButton>
#include <QListWidget>
#include <QTextEdit>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    box_breadth(new QSpinBox()),
    box_length(new QSpinBox()),
    box_height(new QSpinBox()),
    box_weight(new QSpinBox()),
    cylinder_diameter(new QSpinBox()),
    cylinder_height(new QSpinBox()),
    cylinder_weight(new QSpinBox()),
    buttonAddBox(new QPushButton("Add box")),
    buttonAddCylinder(new QPushButton("Add cylinder")),
    displayUnallocated (new QListWidget),
    palletNumber(new QSpinBox()),
    buttonMoveToPallet(new QPushButton("Move to pallet")),
    buttonBackupRestore(new QPushButton("Backup")),
    buttonPostXML(new QPushButton("Post XML to network")),
    displayPalletXML(new QTextEdit)
{
    // Tab 1 - Containers
    QGroupBox *boxGroup(new QGroupBox("Box"));
    QGridLayout *boxlayout(new QGridLayout);
    boxGroup->setLayout(boxlayout);
    QLabel *labelBBreadth(new QLabel("Breadth"));
    boxlayout->addWidget(labelBBreadth, 0, 0);
    boxlayout->addWidget(box_breadth, 0, 1);
    QLabel *labelBLength(new QLabel("Length"));
    boxlayout->addWidget(labelBLength, 1, 0);
    boxlayout->addWidget(box_length, 1, 1);
    QLabel *labelBHeight(new QLabel("Height"));
    boxlayout->addWidget(labelBHeight, 2, 0);
    boxlayout->addWidget(box_height, 2, 1);
    QLabel *labelBWeight(new QLabel("Weight"));
    boxlayout->addWidget(labelBWeight, 3, 0);
    boxlayout->addWidget(box_weight, 3, 1);
    boxlayout->addWidget(buttonAddBox, 4, 0, 1, 2);
    buttonAddBox->setObjectName("BoxButton");

    QGroupBox *cylinderGroup(new QGroupBox("Cylinder"));
    QGridLayout *cylinderlayout(new QGridLayout);
    cylinderGroup->setLayout(cylinderlayout);
    QLabel *labelCDiameter(new QLabel("Diameter"));
    cylinderlayout->addWidget(labelCDiameter, 0, 0);
    cylinderlayout->addWidget(cylinder_diameter, 0, 1);
    QLabel *labelCHeight(new QLabel("Height"));
    cylinderlayout->addWidget(labelCHeight, 1, 0);
    cylinderlayout->addWidget(cylinder_height, 1, 1);
    QLabel *labelCWeight(new QLabel("Weight"));
    cylinderlayout->addWidget(labelCWeight, 2, 0);
    cylinderlayout->addWidget(cylinder_weight, 2, 1);
    QLabel *labelBlank1(new QLabel);
    cylinderlayout->addWidget(labelBlank1, 3, 0);
    cylinderlayout->addWidget(buttonAddCylinder, 4, 0, 1, 2);
    buttonAddCylinder->setObjectName("CylinderButton");

    QWidget *bottomWidget(new QWidget);
    QGridLayout *bottomLayout(new QGridLayout);
    bottomWidget->setLayout(bottomLayout);
    QLabel *labelListOf(new QLabel("List of unallocated containers"));
    bottomLayout->addWidget(labelListOf, 0, 0);
    QLabel *labelClickOn(new QLabel("Click on item in list, choose a pallet number, and Move the container to that pallet"));
    labelClickOn->setWordWrap(true);
    bottomLayout->addWidget(displayUnallocated, 1, 0, 5, 1);
    bottomLayout->addWidget(labelClickOn, 1, 1);
    bottomLayout->addWidget(palletNumber, 2, 1);
    palletNumber->setMinimum(1);
    bottomLayout->addWidget(buttonMoveToPallet, 3, 1);
    QLabel *labelBlank2(new QLabel);
    cylinderlayout->addWidget(labelBlank2, 4, 1);
    bottomLayout->addWidget(buttonBackupRestore, 5, 1);

    QWidget *containerWidget(new QWidget);
    QGridLayout *tabLayoutContainer(new QGridLayout);
    tabLayoutContainer->addWidget(boxGroup, 0, 0);
    tabLayoutContainer->addWidget(cylinderGroup, 0, 1);
    tabLayoutContainer->addWidget(bottomWidget, 1, 0, 1, 2);
    containerWidget->setLayout(tabLayoutContainer);

    // Tab 2 - Post XML
    QWidget *postWidget(new QWidget);
    QVBoxLayout *postLayout(new QVBoxLayout);
    postWidget->setLayout(postLayout);
    postLayout->addWidget(buttonPostXML);
    postLayout->addWidget(displayPalletXML);

    // setting main widget
    QVBoxLayout *vertical(new QVBoxLayout);
    vertical->addWidget(containerWidget);
    vertical->addWidget(postWidget);
    setLayout(vertical);
}

MainWindow::~MainWindow()
{
};


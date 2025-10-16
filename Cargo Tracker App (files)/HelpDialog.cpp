#include "HelpDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>

HelpDialog::HelpDialog(QWidget* p): QDialog(p){ setWindowTitle("Help");
    auto* lay=new QVBoxLayout(this);
    lay->addWidget(new QLabel("Use the Containers tab to add Boxes/Cylinders and move them to pallets. Use Post XML to send to 127.0.0.1:6164."));
    auto* bb=new QDialogButtonBox(QDialogButtonBox::Close,this);
    connect(bb,&QDialogButtonBox::rejected,this,&QDialog::reject);
    lay->addWidget(bb);
}

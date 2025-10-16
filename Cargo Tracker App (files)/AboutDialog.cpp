#include "AboutDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QIcon>

AboutDialog::AboutDialog(QWidget* p): QDialog(p){ setWindowTitle("About");
    setWindowIcon(QIcon(":/icons/info.png"));
    auto* lay=new QVBoxLayout(this);
    lay->addWidget(new QLabel("<b>Container Client</b><br>Qt6 Widgets Application."));
    auto* bb=new QDialogButtonBox(QDialogButtonBox::Ok,this);
    connect(bb,&QDialogButtonBox::accepted,this,&QDialog::accept);
    lay->addWidget(bb);
}

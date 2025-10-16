#ifndef UI_HELPDIALOG_H
#define UI_HELPDIALOG_H

#include <QDialog>

class HelpDialog : public QDialog {
    Q_OBJECT

public:
    explicit HelpDialog(QWidget *parent = nullptr);
};

#endif // UI_HELPDIALOG_H

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QDialog>

class AboutDialog : public QDialog {
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
};

#endif // UI_ABOUTDIALOG_H

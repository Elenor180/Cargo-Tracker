#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QSpinBox;
class QPushButton;
class QListWidget;
class QTextEdit;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

private:
    QSpinBox *box_breadth, *box_length, *box_height, *box_weight;
    QSpinBox *cylinder_diameter, *cylinder_height, *cylinder_weight;
    QPushButton *buttonAddBox, *buttonAddCylinder;
    QListWidget *displayUnallocated;
    QSpinBox *palletNumber;
    QPushButton *buttonMoveToPallet, *buttonBackupRestore;
    QPushButton *buttonPostXML;
    QTextEdit *displayPalletXML;
};

#endif // WIDGET_H

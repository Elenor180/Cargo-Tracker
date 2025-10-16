#ifndef MANAGETAB_H
#define MANAGETAB_H
#include <QWidget>
#include <QVector>
#include <QMap>

// Forward declarations to minimize dependencies and improve compile times.
class QSpinBox; class QPushButton; class QListView; class QStringListModel; class QGroupBox; class QLabel;
class Container; class Box; class Cylinder; class Pallet; class CodeGenerator; class Caretaker;

// The UIType enum is used to distinguish between different types of containers in the user interface.
enum class UIType { Box, Cylinder };

// The ManageTab class is a custom QWidget that manages the creation,
// allocation, and tracking of containers and pallets.
class ManageTab : public QWidget{
    Q_OBJECT
public:
    // Explicit constructor to prevent implicit type conversions.
    explicit ManageTab(QWidget* parent = nullptr);
    // The destructor is responsible for cleaning up dynamically allocated resources.
    ~ManageTab() override;

    // Public methods for data exposure to other parts of the application.
    const QVector<Pallet*>& pallets() const { return m_pallets; }
    bool hasAnyPallets() const {
        return !m_pallets.isEmpty();
    }
    bool canRestore() const;

signals:
    // This signal is emitted when the data managed by this tab changes.
    void dataChanged();

public slots:
    // Public slots that can be connected to signals from other widgets.
    void backupUnallocated();
    void restoreUnallocated();

private slots:
    // Private slots that handle user interactions within this tab, such as button clicks.
    void addBox();
    void addCylinder();
    void moveSelectedToPallet();

private:
    // Private helper functions for setting up the UI and managing data.
    void buildUi();
    void wire();
    void refreshUnallocatedModel();
    void ensurePallet(int number);

private:
    // UI elements for creating and managing containers.
    QSpinBox *sbBoxLen{}, *sbBoxBr{}, *sbBoxHt{}, *sbBoxWt{};
    QPushButton *btnAddBox{};
    QSpinBox *sbCylDia{}, *sbCylHt{}, *sbCylWt{};
    QPushButton *btnAddCyl{};

    // UI elements for the unallocated containers list and controls.
    QListView* lvUnallocated{};
    QStringListModel* m_unallocModel{};
    QSpinBox* sbPallet{};
    QPushButton* btnMove{};
    QPushButton* btnBackup{};
    QPushButton* btnRestore{};

    // Data members that store and manage the application's state.
    // m_unallocated stores containers not yet assigned to a pallet.
    QVector<Container*> m_unallocated;
    // m_pallets stores all the pallets.
    QVector<Pallet*> m_pallets;
    // m_codes is a utility for generating unique container codes.
    CodeGenerator* m_codes{};
    // m_caretaker is used to manage mementos for the backup and restore functionality.
    Caretaker* m_caretaker{};
};

#endif // MANAGETAB_H

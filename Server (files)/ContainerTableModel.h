#ifndef CONTAINERTABLEMODEL_H
#define CONTAINERTABLEMODEL_H
#include <QAbstractTableModel>
#include <QVector>

// This class is a custom data model for displaying container information in a table view.
// It inherits from QAbstractTableModel, which provides a flexible framework for data representation.
class ContainerTableModel : public QAbstractTableModel{
    Q_OBJECT
public:
    // This is the constructor. It initializes the model with an optional parent QObject.
    explicit ContainerTableModel(QObject* parent=nullptr): QAbstractTableModel(parent) {}

    // This override function returns the number of rows in the table.
    int rowCount(const QModelIndex& parent=QModelIndex()) const override {
        Q_UNUSED(parent);
        return m_rows.size();
    }

    // This override function returns the number of columns in the table.
    int columnCount(const QModelIndex& parent=QModelIndex()) const override {
        Q_UNUSED(parent);
        return 8; // The table has a fixed number of 8 columns.
    }

    // This override function provides data for a given index and role.
    QVariant data(const QModelIndex& index, int role) const override{
        // Checks for a valid index and a display role.
        if(!index.isValid() || role!=Qt::DisplayRole) {
            return {};
        }
        // Returns the data from the internal vector at the specified row and column.
        return m_rows.at(index.row()).at(index.column());
    }

    // This override function provides header data for the table's rows and columns.
    QVariant headerData(int section, Qt::Orientation o, int role) const override{
        // Only handles the display role.
        if(role!=Qt::DisplayRole) {
            return {};
        }
        // If the orientation is horizontal, it provides column headers.
        if(o==Qt::Horizontal){
            static const QStringList h{"Pallet","Type","Code","Height","Weight","Length","Breadth","Diameter"};
            return h.value(section);
        }
        // If the orientation is vertical, it provides row numbers.
        return section+1;
    }

    // This method sets the data for the model and notifies views of the change.
    void setRows(const QVector<QVector<QString>>& rows){
        // Signals the start of a model reset.
        beginResetModel();
        // Replaces the internal data with the new rows.
        m_rows=rows;
        // Signals the end of the model reset.
        endResetModel();
    }
private:
    // A private member variable to store the table data as a vector of string vectors.
    QVector<QVector<QString>> m_rows;
};

#endif // CONTAINERTABLEMODEL_H

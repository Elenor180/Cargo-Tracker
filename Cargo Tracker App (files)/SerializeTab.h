#ifndef SERIALIZETAB_H
#define SERIALIZETAB_H
#include <QWidget>
#include <QVector>

// Forward declarations to minimize dependencies and improve compile times.
class QPlainTextEdit;
class QPushButton;
class QThread;
class Pallet;

// The SerializeTab class is a QWidget that provides a user interface
// for serializing data and sending it to a server.
class SerializeTab : public QWidget{
    Q_OBJECT
public:
    // Explicit constructor to prevent implicit type conversions.
    explicit SerializeTab(QWidget* parent=nullptr);
    // The destructor handles the cleanup of dynamically allocated resources, including the worker thread.
    ~SerializeTab() override;

    // This public method is called from outside the class to initiate the serialization process.
    // It passes a constant reference to a vector of Pallet objects to the worker thread.
    void serializeAndSend(const QVector<Pallet*>& pallets);

signals:
    // This signal is emitted to provide status updates to the main application window's status bar.
    void statusMessage(const QString& msg);

private:
    // Private helper functions to set up the UI and connect signals and slots.
    void buildUi();
    void wire();

private:
    // UI elements for the serialization tab.
    // A plain text editor to display the generated XML.
    QPlainTextEdit* txtXml{};
    // A button to trigger the serialization and send process.
    QPushButton* btnPost{};
    // A separate thread to run the serialization and network operations without blocking the UI.
    QThread* workerThread{};
};

#endif // SERIALIZETAB_H

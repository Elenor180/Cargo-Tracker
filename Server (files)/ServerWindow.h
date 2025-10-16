#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H
#include <QMainWindow>
#include <QVector>
#include <QRegularExpression>

// Forward declarations to reduce compile time dependencies.
class QTcpServer;
class QTcpSocket;
class QTableView;
class ContainerTableModel;

// The ServerWindow class represents the main window for a simple TCP server.
// It is responsible for listening for incoming connections, receiving data, and displaying it.
class ServerWindow : public QMainWindow{
    Q_OBJECT
public:
    // This is the constructor for the ServerWindow.
    explicit ServerWindow(QWidget* parent=nullptr);
    // The destructor ensures that the TCP server and other allocated resources are properly cleaned up.
    ~ServerWindow() override;

private slots:
    // This slot is automatically called by the QTcpServer when a new client connects.
    void onNewConnection();
    // This slot is automatically called by the QTcpSocket when new data is available to be read.
    void onReadyRead();

private:
    // This private helper function parses an XML byte array and populates the table model with the data.
    void parseXmlAndPopulate(const QByteArray& xml);

private:
    // Private member variables for the server's functionality.
    QTcpServer* server{};             // The TCP server object that listens for connections.
    QTcpSocket* current{};            // A pointer to the currently connected client socket.
    QTableView* view{};               // The table view widget for displaying container data.
    ContainerTableModel* model{};     // The custom data model for the table view.
    QRegularExpression codeRx{QRegularExpression(R"(^(20\d{2})/(0[1-9]|1[0-2])/[BC](\d{1,4})$)")}; // A regular expression for validating container codes.
};

#endif // SERVERWINDOW_H

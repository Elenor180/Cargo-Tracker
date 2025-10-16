#include "ServerWindow.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QTableView>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDomDocument>
#include <QRegularExpression>
#include "ContainerTableModel.h"

// The constructor sets up the TCP server and the UI.
ServerWindow::ServerWindow(QWidget* parent)
    : QMainWindow(parent),
    current(nullptr),
    codeRx("^[A-Z0-9]{4}$")   // Example regex: 4 alphanumeric chars
{
    // Creates a new QTcpServer instance.
    server = new QTcpServer(this);

    // Connects the server's newConnection signal to a slot that handles incoming connections.
    connect(server, &QTcpServer::newConnection, this, &ServerWindow::onNewConnection);

    // Attempts to start the server listening on the local host and port 6164.
    if (!server->listen(QHostAddress::LocalHost, 6164)) {
        QMessageBox::critical(this, "Server", "Cannot listen on 6164");
    }

    // Initializes the data model and table view, and sets the table view as the central widget.
    model = new ContainerTableModel(this);
    view = new QTableView(this);
    view->setModel(model);
    setCentralWidget(view);

    // Sets the window title.
    setWindowTitle("Container Server (127.0.0.1:6164)");
}

// The destructor ensures that the current socket is properly cleaned up when the server window is closed.
ServerWindow::~ServerWindow() {
    if (current) {
        current->disconnectFromHost();
        current->deleteLater();
        current = nullptr;
    }
}

// This slot is triggered when a new client connects to the server.
void ServerWindow::onNewConnection() {
    // Disconnects and deletes any previous connection before accepting a new one.
    if (current) {
        current->disconnect(this);
        current->deleteLater();
    }

    // Accepts the new connection.
    current = server->nextPendingConnection();

    // Connects the new socket's readyRead signal to a slot to process incoming data.
    connect(current, &QTcpSocket::readyRead, this, &ServerWindow::onReadyRead);
}

// This slot is triggered when data is available to be read from the socket.
void ServerWindow::onReadyRead() {
    if (!current) return;

    // Reads all available data from the socket.
    QByteArray data = current->readAll();

    // Calls a helper function to parse the XML and populate the table.
    parseXmlAndPopulate(data);
}

// This private helper function parses the received XML data and populates the table model.
void ServerWindow::parseXmlAndPopulate(const QByteArray& xml) {
    QDomDocument doc;

    // Use the new overload that returns a ParseResult (Qt 6.5+).
    QDomDocument::ParseResult result = doc.setContent(xml);

    if (!result) {
        QMessageBox::warning(this, "XML",
                             QString("Parse error %1 at %2:%3")
                                 .arg(result.errorMessage)
                                 .arg(result.errorLine)
                                 .arg(result.errorColumn));
        return;
    }

    // Gets the root element, which should be "pallets".
    auto pallets = doc.documentElement();
    if (pallets.tagName() != "pallets") return;

    QVector<QVector<QString>> rows;
    // Finds all "pallet" elements within the document.
    auto palletNodes = pallets.elementsByTagName("pallet");

    // Iterates through each pallet element.
    for (int i = 0; i < palletNodes.count(); ++i) {
        auto pElem = palletNodes.at(i).toElement();
        const QString pnum = pElem.attribute("number");

        // Gets the child nodes (containers) of the current pallet element.
        auto children = pElem.childNodes();

        // Iterates through each container element.
        for (int j = 0; j < children.count(); ++j) {
            auto e = children.at(j).toElement();
            if (e.isNull()) continue;

            const QString type = e.tagName();

            // Extracts container data from XML text elements.
            QString code = e.firstChildElement("code").text();

            // Validates the container code using a regular expression.
            if (!codeRx.match(code).hasMatch()) {
                code = "****"; // Masks invalid codes.
            }

            QString height   = e.firstChildElement("height").text();
            QString weight   = e.firstChildElement("weight").text();
            QString length   = e.firstChildElement("length").text();
            QString breadth  = e.firstChildElement("breadth").text();
            QString diameter = e.firstChildElement("diameter").text();

            // Adds the extracted data as a new row to the data vector.
            rows.push_back({pnum, type, code, height, weight, length, breadth, diameter});
        }
    }

    // Sets the new data on the table model to refresh the view.
    model->setRows(rows);
}

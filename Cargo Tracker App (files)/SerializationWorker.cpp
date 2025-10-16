#include "SerializationWorker.h"
#include "Pallet.h"
#include "Container.h"
#include "Box.h"
#include "Cylinder.h"
#include <QXmlStreamWriter>
#include <QTcpSocket>

// This private helper function builds an XML string from the provided list of pallets.
QString SerializationWorker::buildXml(const QVector<Pallet*>& pallets) const{
    QString s;
    s.reserve(4096); // Reserves memory to improve performance.

    // QXmlStreamWriter is a Qt class for writing XML in a streaming, forward-only manner.
    QXmlStreamWriter w(&s);
    w.setAutoFormatting(true); // Makes the output XML human-readable with indentation.

    // Writes the XML declaration and the root element for the document.
    w.writeStartDocument();
    w.writeStartElement("pallets");
    // Adds an attribute to the root element with the total number of pallets.
    w.writeAttribute("NumberOfPallets", QString::number(pallets.size()));

    // Iterates through each pallet to write its data.
    for(const auto* p: pallets){
        w.writeStartElement("pallet");
        // Writes attributes for the pallet's total weight, volume, and number.
        w.writeAttribute("weight", QString::number(p->totalWeight()));
        w.writeAttribute("volume", QString::number(p->totalVolume()));
        w.writeAttribute("number", QString::number(p->number()));

        // Iterates through each container on the current pallet.
        for(const auto* c: p->items()){
            // Creates an element with the container's type name (e.g., "Box" or "Cylinder").
            w.writeStartElement(c->typeName());
            // Writes text elements for the common container properties.
            w.writeTextElement("code", c->code());
            w.writeTextElement("height", QString::number(c->height()));
            w.writeTextElement("weight", QString::number(c->weight()));

            // Checks the container's type to write type-specific properties.
            if (c->typeName()=="Box"){
                // Casts the generic Container pointer to a Box pointer to access its properties.
                auto* b = static_cast<const Box*>(c);
                w.writeTextElement("length", QString::number(b->length()));
                w.writeTextElement("breadth", QString::number(b->breadth()));
            } else {
                // Casts the generic Container pointer to a Cylinder pointer.
                auto* cy = static_cast<const Cylinder*>(c);
                w.writeTextElement("diameter", QString::number(cy->diameter()));
            }
            // Closes the current container's XML element.
            w.writeEndElement();
        }
        // Closes the current pallet's XML element.
        w.writeEndElement();
    }
    // Closes the root element and the document.
    w.writeEndElement();
    w.writeEndDocument();
    return s;
}

// This private helper function handles the network communication to send the XML data.
void SerializationWorker::sendToServer(const QString& xml){
    QTcpSocket sock;
    // Attempts to connect to the local host on port 6164.
    sock.connectToHost(QHostAddress::LocalHost, 6164);

    // Waits for the connection to be established. Throws an exception on failure.
    if(!sock.waitForConnected(2000)) {
        throw std::runtime_error("Cannot connect to server");
    }

    // Converts the XML string to UTF-8 encoded byte array.
    QByteArray data = xml.toUtf8();
    sock.write(data);
    sock.flush();
    // Waits for the data to be written to the socket.
    sock.waitForBytesWritten(2000);
    // Disconnects from the host.
    sock.disconnectFromHost();
}

// The main entry point for the worker's task.
void SerializationWorker::doSerializeAndSend(const QVector<Pallet*>& pallets){
    try{
        // Builds the XML string.
        const QString xml = buildXml(pallets);
        // Emits a signal to the main thread with the generated XML.
        emit xmlReady(xml);
        // Sends the XML data to the server.
        sendToServer(xml);
        // Emits a signal to indicate the process finished successfully.
        emit finished("XML posted to 127.0.0.1:6164");
    } catch(const std::exception& e){
        // Catches any exceptions and emits an error signal with the error message.
        emit error(QString::fromUtf8(e.what()));
    }
}

#ifndef SERIALIZATIONWORKER_H
#define SERIALIZATIONWORKER_H

#include <QObject>
#include <QVector>

class Pallet;

// The SerializationWorker class is designed to run in a separate thread.
// Its purpose is to perform the serialization of pallet data into XML and send it to a server,
// preventing the main application's UI from freezing during these long-running operations.
class SerializationWorker : public QObject{
    Q_OBJECT
public:
    // This is the constructor for the SerializationWorker.
    explicit SerializationWorker(QObject* parent = nullptr): QObject(parent) {}

public slots:
    // This public slot is the entry point for the worker's task.
    // It's designed to be called from the main thread to initiate the serialization and sending process.
    void doSerializeAndSend(const QVector<Pallet*>& pallets);

signals:
    // This signal is emitted when the XML string has been successfully built.
    void xmlReady(const QString& xml);
    // This signal is emitted when the entire serialization and sending process is complete.
    void finished(const QString& status);
    // This signal is emitted if an error occurs during the process.
    void error(const QString& message);

private:
    // A private helper function that takes pallet data and builds an XML string from it.
    QString buildXml(const QVector<Pallet*>& pallets) const;
    // A private helper function responsible for sending the generated XML data to a server.
    void sendToServer(const QString& xml);
};

#endif // SERIALIZATIONWORKER_H

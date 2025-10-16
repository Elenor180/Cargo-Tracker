#include "SerializeTab.h"
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QThread>
#include <QMessageBox>
#include "SerializationWorker.h"
#include "Pallet.h"

// This is the constructor for the SerializeTab class. It sets up the UI and connections.
SerializeTab::SerializeTab(QWidget* parent): QWidget(parent){
    buildUi();
    wire();
}

// The destructor ensures proper cleanup of the worker thread to prevent memory leaks and crashes.
SerializeTab::~SerializeTab(){
    // Checks if a worker thread exists before attempting to clean it up.
    if(workerThread){
        workerThread->quit(); // Asks the thread to stop its event loop.
        workerThread->wait(); // Waits for the thread to finish its work.
        delete workerThread;
        workerThread = nullptr;
    }
}

// This private helper function builds the user interface for the tab.
void SerializeTab::buildUi(){
    // Sets up a vertical layout to arrange widgets.
    auto* lay=new QVBoxLayout(this);
    // Creates a button for triggering the XML post operation.
    btnPost=new QPushButton(tr("Post XML to network"), this);
    // Creates a plain text edit widget to display the generated XML.
    txtXml=new QPlainTextEdit(this);
    // Makes the text edit widget read-only to prevent user input.
    txtXml->setReadOnly(true);
    // Adds the button and text editor to the layout.
    lay->addWidget(btnPost);
    lay->addWidget(txtXml);
    // Sets the layout for the widget.
    setLayout(lay);
}

// This private helper function connects signals to slots.
void SerializeTab::wire(){
    // Corrected connect statement with 'this' as the context object.
    // Connects the "Post" button's clicked signal to a lambda function that provides a status message.
    connect(btnPost, &QPushButton::clicked, this, [this]{
        emit statusMessage("Nothing to post: choose via toolbar.");
    });
}

// This public method is called to begin the serialization and network process.
void SerializeTab::serializeAndSend(const QVector<Pallet*>& pallets){
    // Checks if there are any pallets to serialize. If not, it shows a message and returns.
    if(pallets.isEmpty()){
        QMessageBox::information(this, tr("Post XML"), tr("No pallets to serialize."));
        return;
    }
    // If a thread from a previous operation exists, it is cleaned up before a new one is started.
    if(workerThread){
        workerThread->quit();
        workerThread->wait();
        delete workerThread;
        workerThread=nullptr;
    }
    // Creates a new worker thread and a SerializationWorker object.
    workerThread = new QThread(this);
    auto* worker = new SerializationWorker();
    // Moves the worker object to the new thread.
    worker->moveToThread(workerThread);

    // All connect statements with lambdas now have 'this' as the third parameter.
    // Connects the thread's started signal to a lambda that calls the worker's main function.
    connect(workerThread, &QThread::started, this, [worker, pallets]{
        worker->doSerializeAndSend(pallets);
    });
    // Connects signals from the worker to slots in this tab for UI updates.
    connect(worker, &SerializationWorker::xmlReady, this, [this](const QString& xml){
        txtXml->setPlainText(xml);
        emit statusMessage("XML generated.");
    });
    connect(worker, &SerializationWorker::finished, this, [this](const QString& s){
        emit statusMessage(s);
    });
    connect(worker, &SerializationWorker::error, this, [this](const QString& e){
        QMessageBox::critical(this, tr("Error"), e);
        emit statusMessage(e);
    });
    // Connects signals from the worker to the thread's quit slot. This stops the thread when the work is done or an error occurs.
    connect(worker, &SerializationWorker::finished, workerThread, &QThread::quit);
    connect(worker, &SerializationWorker::error, workerThread, &QThread::quit);
    // Connects the thread's finished signal to the worker's deleteLater slot, ensuring the worker is safely deleted.
    connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);

    // Starts the worker thread.
    workerThread->start();
}

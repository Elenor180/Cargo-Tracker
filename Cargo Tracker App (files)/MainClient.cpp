#include "MainClient.h"
#include <QAction>
#include <QCloseEvent>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QTabWidget>
#include "ManageTab.h"
#include "SerializeTab.h"

// Constructor for the MainClient class. It initializes the main application window.
MainClient::MainClient(QWidget* parent) : QMainWindow(parent) {
    // Calls helper functions to set up various UI components.
    setupActions();
    setupMenus();
    setupToolbar();
    setupCentral();
    // Connects signals to slots for interaction.
    wire();
    // Updates the initial state of UI elements.
    updateUi();

    // Sets the window title and initial status bar message.
    setWindowTitle("Container Client");
    statusBar()->showMessage("Ready");
    // Sets the application icon.
    setWindowIcon(QIcon(":/info.png"));
}

// Sets up all QAction objects, which represent user commands.
void MainClient::setupActions(){
    // Creates actions with icons, text, and sets their parent.
    actBackup   = new QAction(QIcon(":/images/backup.png"),  tr("Backup"), this);
    actRestore  = new QAction(QIcon(":/images/restore.png"), tr("Restore"), this);
    actPostXml  = new QAction(QIcon(":/images/xml.png"),      tr("Post XML"), this);
    actExit     = new QAction(QIcon(":/images/exit.png"),    tr("Exit"), this);
    actAbout    = new QAction(QIcon(":/images/info.png"),    tr("About"), this);
    actHelp     = new QAction(QIcon(":/images/help.png"),    tr("Help"), this);

    // Sets tooltips for actions, providing brief descriptions when hovered over.
    actBackup->setToolTip("Backup unallocated containers (in-memory)");
    actRestore->setToolTip("Restore unallocated containers from last backup");
    actPostXml->setToolTip("Serialize pallets to XML and send to server");
}

// Sets up the application's menu bar and its menus.
void MainClient::setupMenus(){
    // Adds a "File" menu and an "Exit" action to it.
    mnuFile = menuBar()->addMenu(tr("&File"));
    mnuFile->addAction(actExit);

    // Adds a "Backup" menu and its related actions.
    mnuBackup = menuBar()->addMenu(tr("&Backup"));
    mnuBackup->addAction(actBackup);
    mnuBackup->addAction(actRestore);

    // Adds a "Post XML" menu and its action.
    mnuPost = menuBar()->addMenu(tr("&Post XML"));
    mnuPost->addAction(actPostXml);

    // Adds a "Help" menu and its related actions.
    mnuHelp = menuBar()->addMenu(tr("&Help"));
    mnuHelp->addAction(actAbout);
    mnuHelp->addAction(actHelp);
}

// Sets up the application's toolbar.
void MainClient::setupToolbar(){
    // Creates a new toolbar and adds actions to it.
    toolbar = addToolBar(tr("Main Toolbar"));
    toolbar->addAction(actBackup);
    toolbar->addAction(actRestore);
    toolbar->addSeparator(); // Adds a visual separator between groups of actions.
    toolbar->addAction(actPostXml);
}

// Sets up the central widget of the main window, which contains the tabbed interface.
void MainClient::setupCentral(){
    // Creates a QTabWidget to hold different application views.
    tabs = new QTabWidget(this);
    // Creates instances of custom tab widgets.
    manage = new ManageTab(this);
    serialize = new SerializeTab(this);

    // Adds the custom tabs to the QTabWidget with icons and titles.
    tabs->addTab(manage, QIcon(":/images/box_icon.ico"), tr("Containers"));
    tabs->addTab(serialize, QIcon(":/images/server_icon.ico"), tr("Post XML"));
    // Sets the tab widget as the central widget of the main window.
    setCentralWidget(tabs);
}

// Connects signals from UI elements to appropriate slots.
void MainClient::wire(){
    // Connects actions to their respective slots.
    connect(actExit,    &QAction::triggered, this, &QWidget::close);
    connect(actAbout,   &QAction::triggered, this, &MainClient::showAbout);
    connect(actHelp,    &QAction::triggered, this, &MainClient::showHelp);
    connect(actBackup,  &QAction::triggered, this, &MainClient::onBackup);
    connect(actRestore, &QAction::triggered, this, &MainClient::onRestore);
    connect(actPostXml, &QAction::triggered, this, &MainClient::onPostXml);

    // Connects the dataChanged signal from ManageTab to MainClient's updateUi slot.
    // This ensures the UI is updated when data in ManageTab changes (e.g., enabling/disabling PostXML).
    connect(manage, &ManageTab::dataChanged, this, &MainClient::updateUi);

    // Connects the statusMessage signal from SerializeTab to the status bar's showMessage slot.
    // A lambda is used to pass a timeout argument to showMessage.
    connect(serialize, &SerializeTab::statusMessage, this,
            [this](const QString &msg) {
                statusBar()->showMessage(msg, 5000); // Message displayed for 5 seconds.
            });
}

// Updates the state of various UI elements based on application data.
void MainClient::updateUi(){
    // Checks if there are any pallets to determine if XML posting should be enabled.
    const bool hasPallets = manage->hasAnyPallets();
    actPostXml->setEnabled(hasPallets);
    // Checks if a restore operation is possible to enable/disable the restore action.
    actRestore->setEnabled(manage->canRestore());
}

// Slot to handle the backup action.
void MainClient::onBackup(){
    // Calls the backup function in the ManageTab.
    manage->backupUnallocated();
    // Updates the UI state after the backup.
    updateUi();
    // Displays a temporary message in the status bar.
    statusBar()->showMessage("Backup complete", 1500);
}

// Slot to handle the restore action.
void MainClient::onRestore(){
    // Calls the restore function in the ManageTab.
    manage->restoreUnallocated();
    // Updates the UI state after the restore.
    updateUi();
    // Displays a temporary message in the status bar.
    statusBar()->showMessage("Restore complete", 1500);
}

// Slot to handle the Post XML action.
void MainClient::onPostXml(){
    // Triggers the serialization and sending process in the SerializeTab, passing the current pallets.
    serialize->serializeAndSend(manage->pallets());
}

// Overrides the default close event handler to ask for user confirmation before exiting.
void MainClient::closeEvent(QCloseEvent* event){
    // Displays a question message box.
    const auto ans = QMessageBox::question(this, tr("Exit"), tr("Are you sure you want to exit?"), QMessageBox::Yes|QMessageBox::No, QMessageBox::No);
    // If the user confirms, accept the event (close the application). Otherwise, ignore it.
    if (ans == QMessageBox::Yes) event->accept();
    else event->ignore();
}

// Slot to display an "About" message box.
void MainClient::showAbout(){
    // Shows an about message box with application information.
    QMessageBox::about(this, tr("About"), tr("<b>Container Client</b><br>Qt6 Widgets app for COS3711A3."));
}

// Slot to display a "Help" message box.
void MainClient::showHelp(){
    // Shows an information message box with instructions.
    QMessageBox::information(this, tr("Help"), tr("Use the Containers tab to create Boxes/Cylinders, move to pallets, and Backup/Restore. Use Post XML to send pallets to the server."));
}

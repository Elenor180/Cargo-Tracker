#ifndef MAINCLIENT_H
#define MAINCLIENT_H

#include <QMainWindow>
// Forward declarations to reduce compile time dependencies.
// This is a good practice to avoid including full header files when only a pointer or reference is needed.
class QAction;
class QMenu;
class QToolBar;
class QTabWidget;
class ManageTab;
class SerializeTab;

// The MainClient class serves as the main application window.
// It inherits from QMainWindow, which provides a framework for building a standard application UI
// with a menu bar, toolbars, and a central widget.
class MainClient : public QMainWindow {
    Q_OBJECT
public:
    // Explicit constructor to prevent implicit type conversions.
    // It initializes the main window with an optional parent widget.
    explicit MainClient(QWidget* parent = nullptr);
    // A virtual destructor is used to ensure proper cleanup of derived class objects.
    ~MainClient() override = default;

protected:
    // This function is an override of the base class's close event handler.
    // It is called when the user attempts to close the window, allowing for custom behavior like a confirmation dialog.
    void closeEvent(QCloseEvent* event) override;

private slots:
    // These are private slots that act as event handlers for user actions.
    // The 'slots' keyword allows them to be connected to signals from other objects.
    void showAbout();
    void showHelp();
    void onBackup();
    void onRestore();
    void onPostXml();

private:
    // These are private helper functions used to set up the different parts of the main window's UI.
    void setupActions();
    void setupMenus();
    void setupToolbar();
    void setupCentral();
    // The 'wire' function connects signals from UI elements to the appropriate slots.
    void wire();
    // This function is for updating the UI state, such as enabling/disabling actions.
    void updateUi();

private:
    // Pointers to QAction objects. QActions are abstract commands that can be added to menus and toolbars.
    QAction *actBackup{}, *actRestore{}, *actPostXml{}, *actExit{}, *actAbout{}, *actHelp{};
    // Pointers to QMenu objects, which are dropdown menus in the menu bar.
    QMenu *mnuFile{}, *mnuBackup{}, *mnuPost{}, *mnuHelp{};
    // A pointer to a QToolBar object, which is a movable panel of controls (actions).
    QToolBar* toolbar{};
    // A pointer to a QTabWidget, a container for organizing multiple pages of widgets.
    QTabWidget* tabs{};
    // Pointers to the custom tabs for managing and serializing data.
    ManageTab* manage{};
    SerializeTab* serialize{};
};

#endif // MAINCLIENT_H

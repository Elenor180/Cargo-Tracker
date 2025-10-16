/*Student Number: 10358994
 *
 *
 * This program is a client-server application for managing and tracking cargo containers.
 * The client side allows users to create, organize, and back up containers on pallets,
 * and then serialize that data into XML to be sent to a server for display.
 *
 * Design Patterns used:
 *
 * Model-View-Controller (MVC)
 * Memento pattern
 * Factory Method
 * Threads
 *
 * Data structures used:
 *
 * QVector
 * QMap
 * QStringList
 * QByteArray
 *
 *
 */

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QPixmap>
#include "MainClient.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("Container Client");
    QApplication::setOrganizationName("UNISA");

    // Load the original pixmap from the resource file
    QPixmap originalPixmap(":/images/splash.png");

    // Resize the pixmap to 500x500 pixels, keeping the aspect ratio
    QPixmap resizedPixmap = originalPixmap.scaled(500, 500, Qt::KeepAspectRatio);

    // Create the splash screen with the resized pixmap
    QSplashScreen splash(resizedPixmap);
    splash.show();
    app.processEvents();

    MainClient w;
    QTimer::singleShot(5000, &splash, &QSplashScreen::close);
    QTimer::singleShot(3000, &w, [&w]{ w.showMaximized(); });


    return app.exec();
}

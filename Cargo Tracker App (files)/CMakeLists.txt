cmake_minimum_required(VERSION 3.16)

project(CargoTrackerApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.ui
        MainClient.h
        MainClient.cpp
        Container.h
        Box.h
        Cylinder.h
        Pallet.h
        Pallet.cpp
        CodeGenerator.h
        CodeGenerator.cpp
        Memento.h
        Memento.cpp
        SerializationWorker.h
        SerializationWorker.cpp
        ManageTab.h
        ManageTab.cpp
        SerializeTab.h
        SerializeTab.cpp
        AboutDialog.h
        AboutDialog.cpp
        HelpDialog.h
        HelpDialog.cpp
)

# Add Qt resources
qt_add_resources(APP_RESOURCES resources.qrc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CargoTrackerApp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${APP_RESOURCES}   # <-- include the resource file
    )
else()
    if(ANDROID)
        add_library(CargoTrackerApp SHARED
            ${PROJECT_SOURCES}
            ${APP_RESOURCES}  # <-- include resources for Android too
        )
    else()
        add_executable(CargoTrackerApp
            ${PROJECT_SOURCES}
            ${APP_RESOURCES}
        )
    endif()
endif()

# Link Widgets + Network
target_link_libraries(CargoTrackerApp PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CargoTrackerApp)
endif()

set_target_properties(CargoTrackerApp PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CargoTrackerApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CargoTrackerApp)
endif()

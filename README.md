#  Cargo-Tracker

[![Language](https://img.shields.io/badge/Language-C++-blue.svg)](https://isocpp.org/)
[![Framework](https://img.shields.io/badge/Framework-Qt%206-green.svg)](https://www.qt.io/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

##  Overview

The **Cargo-Tracker** project is a client-server application designed to manage and track the status, location, and details of shipping cargo and containers. It is built using **C++** and the **Qt 6 Framework** for a robust, cross-platform architecture.

The project maintains a clear separation between the core data management and business logic (the **Server**) and the user interface (the **App**).

##  Features

* **Real-time Status Tracking:** Monitor the current location, status (e.g., 'In Transit', 'Customs', 'Delivered'), and history of individual cargo.
* **Container Management:** Log, retrieve, and update detailed information for all managed shipping containers.
* **Client-Server Architecture:** Utilizes Qt's networking capabilities for secure and scalable data exchange.
* **Cross-Platform GUI:** Built with Qt, allowing the application to run on Windows, macOS, and Linux.
* **Data Persistence:** Manages cargo data using an integrated database system.

---

## Technology Stack

| Component | Technology | Description |
| :--- | :--- | :--- |
| **Main Language** | **C++** | Core language for performance and stability. |
| **Framework** | **Qt 6** | Used for the GUI (`Cargo Tracker App`), networking, and server backend structures. |
| **Build System** | **[...]** | (e.g., **QMake** or **CMake**) for managing project compilation. |
| **Database** | **[...]** | (e.g., SQLite, PostgreSQL, MySQL via QSql) |

---

##  Getting Started

Follow these steps to set up and run the **Cargo-Tracker** application locally.

### Prerequisites

* **Qt 6 SDK** (Installed via Qt Maintenance Tool)
* **Qt Creator IDE** (Recommended for development)
* A compatible C++ Compiler (e.g., MinGW, MSVC, GCC/Clang)
* The `git` command-line tool

### Installation & Setup

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/Elenor180/Cargo-Tracker.git](https://github.com/Elenor180/Cargo-Tracker.git)
    cd Cargo-Tracker
    ```

2.  ** Open in Qt Creator:**
    * Launch **Qt Creator**.
    * Select **File > Open File or Project...**
    * Navigate to and select the top-level project file (`.pro` or `CMakeLists.txt`).
    * Configure your build kit (e.g., Desktop Qt 6.x.x).

### Running the Application

You must launch the server before launching the client.

#### 1. Build the Project

In **Qt Creator**, navigate to **Build > Build Project** (`Ctrl+B` or `Cmd+B`). This will compile both the Server and the App executables.

#### 2. Start the Server (Backend)

Locate the compiled **Server** executable in your build directory (e.g., `build-Cargo-Tracker-Desktop_Qt_.../Server (files)/`).

* Execute the **Server** executable first.
    *(The server should output a message indicating the address and port it is running on.)*

#### 3. Start the Client (App)

Locate the compiled **App** executable in your build directory (e.g., `build-Cargo-Tracker-Desktop_Qt_.../Cargo Tracker App (files)/`).

* Execute the **App** executable.

The client application should now launch its GUI and attempt to connect to the running server.

---

## Contribution

If you would like to contribute, report bugs, or suggest features, please feel free to:

1.  **Open an issue** on the [Issues page](https://github.com/Elenor180/Cargo-Tracker/issues).
2.  Fork the repository and submit a **Pull Request**.

---


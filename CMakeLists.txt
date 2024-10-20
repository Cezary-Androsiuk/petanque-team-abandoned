cmake_minimum_required(VERSION 3.16)

project(PetanqueTeam VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Sql)

qt_standard_project_setup()

qt_add_executable(appPetanqueTeam
    main.cpp
)

qt_add_qml_module(appPetanqueTeam
    URI PetanqueTeam
    VERSION 1.0
    QML_FILES qml/Main.qml
    SOURCES cpp/Initializer.h cpp/Initializer.cpp
    SOURCES cpp/storages/Personalization.h cpp/storages/Personalization.cpp
    SOURCES cpp/storages/Database.h cpp/storages/Database.cpp
    SOURCES cpp/support/Log.h cpp/support/Log.cpp
    SOURCES cpp/Login.h cpp/Login.cpp
    QML_FILES qml/LoginForm.qml
    SOURCES cpp/Backend.h cpp/Backend.cpp
    QML_FILES qml/ApplicationIsAlreadyRunning.qml
    QML_FILES qml/event/Start.qml
    QML_FILES qml/event/Continue.qml
    QML_FILES qml/event/Finish.qml
    SOURCES cpp/Memory.h cpp/Memory.cpp
    SOURCES cpp/objects/Player.h cpp/objects/Player.cpp
    SOURCES cpp/objects/Team.h cpp/objects/Team.cpp
    QML_FILES qml/delegates/TeamDelegate.qml
    QML_FILES qml/delegates/PlayerDelegate.qml
    QML_FILES qml/event/Start/StartEvent.qml
    QML_FILES qml/event/Start/AddTeam.qml
    QML_FILES qml/event/Start/AddPlayer.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appPetanqueTeam PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appPetanqueTeam
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appPetanqueTeam
    PRIVATE Qt6::Quick Qt6::Sql
)

include(GNUInstallDirs)
install(TARGETS appPetanqueTeam
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

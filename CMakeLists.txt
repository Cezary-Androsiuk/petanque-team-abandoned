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
    SOURCES cpp/support/Log.h cpp/support/Log.cpp
    SOURCES cpp/Login.h cpp/Login.cpp
    QML_FILES qml/LoginForm.qml
    SOURCES cpp/Backend.h cpp/Backend.cpp
    QML_FILES qml/ApplicationIsAlreadyRunning.qml
    QML_FILES qml/event/Configure.qml
    QML_FILES qml/event/Continue.qml
    QML_FILES qml/event/Finish.qml
    SOURCES cpp/storages/Memory.h cpp/storages/Memory.cpp
    SOURCES cpp/objects/Player.h cpp/objects/Player.cpp
    SOURCES cpp/objects/Team.h cpp/objects/Team.cpp
    QML_FILES qml/event/Configure/TeamDelegate.qml
    QML_FILES qml/event/Configure/PlayerDelegate.qml
    QML_FILES qml/event/Configure/Event.qml
    QML_FILES qml/event/Configure/Team.qml
    QML_FILES qml/event/Configure/Player.qml
    SOURCES cpp/objects/Event.h cpp/objects/Event.cpp
    SOURCES cpp/objects/Match.h cpp/objects/Match.cpp
    SOURCES cpp/storages/DefaultPersonalizationData.h cpp/storages/DefaultPersonalizationData.cpp
    QML_FILES qml/event/Continue/Selection/SelectionTemplate.qml
    QML_FILES qml/event/Configure/Event/InfoField.qml
    QML_FILES qml/event/Configure/Event/TeamsList.qml
    QML_FILES qml/event/Continue/TripletsMatch.qml
    QML_FILES qml/event/Continue/DubletsMatch.qml
    QML_FILES qml/event/Continue/SingielsMatch.qml
    QML_FILES qml/event/Continue/Selection/GroupSelection.qml
    SOURCES cpp/objects/MatchTeam.h cpp/objects/MatchTeam.cpp
    SOURCES cpp/objects/MatchType/MatchTriplets.h cpp/objects/MatchType/MatchTriplets.cpp
    SOURCES cpp/objects/MatchType/MatchDublets.h cpp/objects/MatchType/MatchDublets.cpp
    SOURCES cpp/objects/MatchType/MatchSingiels.h cpp/objects/MatchType/MatchSingiels.cpp
    QML_FILES qml/Play.qml
    SOURCES cpp/objects/MatchType/MatchTypeBase.h cpp/objects/MatchType/MatchTypeBase.cpp
    SOURCES cpp/support/LogQML.h cpp/support/LogQML.cpp
    QML_FILES qml/event/Continue/SingielsSelection.qml
    QML_FILES qml/event/Continue/DubletsSelection.qml
    QML_FILES qml/event/Continue/TripletsSelection.qml
    QML_FILES qml/event/Continue/Match/MatchTemplate.qml
    QML_FILES qml/event/Continue/Match/TeamsMatch.qml
    QML_FILES qml/event/Continue/Match/GroupsMatch.qml
    SOURCES cpp/objects/MatchType/MatchData/Selection.h cpp/objects/MatchType/MatchData/Selection.cpp
    SOURCES cpp/objects/MatchType/MatchData/MatchPoints.h cpp/objects/MatchType/MatchData/MatchPoints.cpp
    QML_FILES qml/event/Continue/MatchSummary.qml
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

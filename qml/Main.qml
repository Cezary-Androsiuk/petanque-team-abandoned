import QtQuick
import QtQuick.Controls.Material

ApplicationWindow {
    id: rootWindow

    width: 1280
    height: 720
    visible: false

    Material.theme: Material.Dark

    Connections{
        target: Initializer
        function onApplicationIsAlreadyRunning(){
            rootLoader.source = "ApplicationIsAlreadyRunning.qml"
        }

        function onInitialized(){
            rootLoader.source = "LoginForm.qml"
        }
    }

    Connections{
        target: Login
        function onAuthenticated(){
            console.log("onAuthenticated")
        }
    }

    Loader{
        id: rootLoader
        anchors.fill: parent
    }

}

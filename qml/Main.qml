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
        target: Memory
        function onMemoryLoaded(){
            rootLoader.source = "event/Continue.qml"
        }

        function onMemorySaved(){
            console.log("memory saved");
            rootLoader.source = "event/Continue.qml"
        }

        function onMemoryError(message){
            console.log("error occur in memory: " + message)
        }
    }

    Connections{
        target: Login
        function onAuthenticated(){
            console.log("onAuthenticated")

            if(Memory.memoryFileExist())
            {
                console.log("load")
                Memory.load()
            }
            else
            {
                console.log("start")
                rootLoader.source = "event/Configure.qml"
            }

        }
    }

    Loader{
        id: rootLoader
        anchors.fill: parent
    }

}

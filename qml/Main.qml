import QtQuick
import QtQuick.Controls.Material

ApplicationWindow {
    id: rootWindow

    width: 1280
    height: 720
    visible: false

    // onWidthChanged: {
    //     console.log("w:" + width + " h:" + height)
    // }
    // onHeightChanged: {
    //     console.log("w:" + width + " h:" + height)
    // }

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

        function onMemoryLoadError(message){
            console.log("error occur while loading memory: " + message)
        }

        function onMemorySaved(){
            console.log("memory saved");
            rootLoader.source = "event/Continue.qml"
        }

        function onMemorySaveError(message){
            console.log("error occur while saving memory: " + message)
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

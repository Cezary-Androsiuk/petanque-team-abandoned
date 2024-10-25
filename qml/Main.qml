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
        function onMemoryFileNotExist(){
            rootLoader.source = "event/Configure.qml"
        }

        function onMemoryLoaded(){
            rootLoader.source = "event/Continue.qml"
            // rootLoader.source = "event/Configure.qml" // to display person data that was loaded
        }

        function onMemoryLoadError(message){
            console.log("error occur while loading memory: " + message)
        }

        function onMemorySaved(){
            console.log("memory saved");
            Memory.load()
        }

        function onMemorySaveError(message){
            console.log("error occur while saving memory: " + message)
        }
    }

    Connections{
        target: Login
        function onAuthenticated(){
            console.log("onAuthenticated")

            Memory.load()
        }
        function onAuthenticationFailed(){
            console.log("onAuthenticationFailed")
        }
    }

    Loader{
        id: rootLoader
        anchors.fill: parent
    }

}

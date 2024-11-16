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
            Backend.event.goToNextStage() // from Stage None to Configure
            rootLoader.source = "Play.qml"
        }

        function onMemoryLoaded(){
            rootLoader.source = "Play.qml"
        }

        function onMemoryLoadError(message){
            rootLoader.source = ""
            log.e("error occur while loading memory: " + message, this.target.toString() + " onMemoryLoadError")
        }

        // sprawdzić jak przekazywane jest matchTeam i triplets etc do qml i jak umożliwia modyfikację wartości skoro pamiętam, że jest const

        function onMemorySaved(reload){ // not reloading memory, while exiting the app
            // console.log("memory saved");
            if(reload)
                Memory.load()
        }

        function onMemorySaveError(message){
            log.w("error occur while saving memory: " + message)
        }
    }
    
    Connections{
        target: Login
        function onAuthenticated(){
            Memory.load()

        }
        function onAuthenticationFailed(){
            log.e("onAuthenticationFailed")
        }
    }

    Loader{
        id: rootLoader
        anchors.fill: parent
    }

}

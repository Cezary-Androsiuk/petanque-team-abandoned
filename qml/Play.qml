import QtQuick
import QtQuick.Controls.Material

Item {
    id: play
    anchors.fill: parent

    property string loaderSource: {
        console.log("source")
        if(Backend.event.stage === 0) // None
        {
            console.log("none stage was reached");
            "";
        }
        else
        if(Backend.event.stage === 1) // Configure
        {
            "event/Configure.qml";
        }
        else
        if(Backend.event.stage === 2) // Continue
        {
            "event/Continue.qml";
        }
        else
        if(Backend.event.stage === 3) // Finish
        {
            "event/Finish.qml";
        }
    }

    // BusyIndicator{
    //     anchors.centerIn: parent
    //     running: loaderSource === ""
    // }

    Loader{
        id: playLoader
        anchors.fill: parent
        source: loaderSource
    }

}

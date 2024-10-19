import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: startEvent
    anchors.fill: parent

    Rectangle{
        anchors.fill: parent
        color: "red"
        opacity: 0.2
    }



    Button{
        anchors.centerIn: parent
        onClicked: {
            Memory.save();
        }
    }
}

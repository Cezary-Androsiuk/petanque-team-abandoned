import QtQuick
import QtQuick.Controls.Material

Item {
    id: applicationIsAlreadyRunning
    anchors.fill: parent

    Component.onCompleted: {
        rootWindow.minimumWidth = label.width + 50;
        rootWindow.minimumHeight = label.height + 50;
        rootWindow.visible = true
    }

    Label{
        id: label
        anchors.centerIn: parent
        font.bold: true
        font.pixelSize: 26
        text: qsTr("Application is already running!");
        color: Qt.rgba(0.8, 0.3, 0.3)
    }
}

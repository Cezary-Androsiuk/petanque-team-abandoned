import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    Rectangle{
        anchors.fill: parent
        color: "#1c1b1f" // dark theme color
    }

    Button{
        anchors.centerIn: parent
        text: "back"
        onClicked: {
            startStackView.pop()
        }
    }
}

import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: addPlayer
    Rectangle{
        anchors.fill: parent
        color: "#1c1b1f" // dark theme color
    }

    required property var team
    required property var player

    Item{
        id: header
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: 70
        Rectangle{
            anchors.fill: parent
            opacity: 0.2
            color: "Red"
        }

        Button{
            anchors{
                left: parent.left
                leftMargin: 10
                verticalCenter: parent.verticalCenter
            }

            text: "back"

            onClicked: {
                startStackView.pop();
                addPlayer.team.deleteDetachedPlayer();
            }
        }
    }

    Item{
        id: footer
        anchors{
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        height: 70
        Rectangle{
            anchors.fill: parent
            opacity: 0.2
            color: "Red"
        }

        Button{
            anchors.centerIn: parent

            text: "save team"

            onClicked: {
                startStackView.pop();
                addPlayer.team.addPlayerUsingDetachedPlayer();
            }
        }
    }
}

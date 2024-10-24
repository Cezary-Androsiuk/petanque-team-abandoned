import QtQuick 2.15
import QtQuick.Controls.Material

Item{
    id: playerDelegate

    property double defaultHeight: 50
    property var playerObject
    property var parentStackView

    clip: true

    height: defaultHeight

    Loader{
        id: contentLoader
        anchors.fill: parent
        sourceComponent: playerObject !== null ? contentComponent : null
    }

    Component{
        id: contentComponent
        Item{
            Rectangle{
                id: playerInfoBorder
                anchors{
                    fill: parent
                    margins: 2
                }

                color: "transparent"
                border.color: Qt.rgba(1,1,1, 0.5)
                border.width: 1
            }

            Label{
                id: playerInfo
                anchors{
                    left: parent.left
                    top: parent.top
                    leftMargin: 10
                }
                verticalAlignment: Text.AlignVCenter
                height: defaultHeight
                text: playerObject.fname + " " + playerObject.lname +
                      "    [" + playerObject.license + "] ("+ playerObject.age +") " + (playerObject.gender ? "F" : "M") +
                      (playerObject.isTeamLeader ? " 👑" : "")
            }

            Button{
                id: deletePlayerButton
                anchors{
                    right: editPlayerButton.left
                    top: parent.top
                }
                height: defaultHeight
                width: height * 2

                text: "delete"

                onClicked:{
                    var team = playerObject.getParent();
                    team.deletePlayer(playerObject);
                }
            }

            Button{
                id: editPlayerButton
                anchors{
                    top: parent.top
                    right: parent.right
                }
                height: defaultHeight
                width: height * 2

                text: "edit"

                onClicked: {
                    playerDelegate.parentStackView.push(
                                "Player.qml",
                                {
                                    edit: true,
                                    parentStackView: playerDelegate.parentStackView,
                                    player: playerDelegate.playerObject
                                }
                    )
                }
            }
        }

    }


}

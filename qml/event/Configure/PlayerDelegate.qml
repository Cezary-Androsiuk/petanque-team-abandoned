import QtQuick 2.15
import QtQuick.Controls.Material

Item{
    id: playerDelegate

    required property var player
    required property var team
    required property var parentStackView

    clip: true

    function deletePlayer(){
        team.deletePlayer(player);
    }

    function editPlayer(){
        const args = {
            edit: true,
            parentStackView: playerDelegate.parentStackView,
            player: playerDelegate.player,
            team: playerDelegate.team
        }
        playerDelegate.parentStackView.push("Player.qml", args)
    }

    Item{
        anchors.fill: parent

        Rectangle{
            id: playerInfoBorder
            anchors.fill: parent
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
                bottom: parent.bottom
            }
            verticalAlignment: Text.AlignVCenter
            text: player.fname + " " + player.lname +
                  "    [" + player.license + "] ("+ player.ageGroup +") " + (player.gender ? "F" : "M") +
                  (player.isTeamLeader ? " 👑" : "")
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
                playerDelegate.deletePlayer();
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
                playerDelegate.editPlayer();
            }
        }
    }


}

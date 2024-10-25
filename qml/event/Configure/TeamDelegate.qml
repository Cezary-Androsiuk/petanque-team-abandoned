import QtQuick 2.15
import QtQuick.Controls.Material

Item{
    id: teamDelegate

    property double defaultHeight: 50
    property var teamObject
    property var parentStackView

    height: defaultHeight
    clip: true

    property bool extended: false


    Loader{
        id: contentLoader
        // loader is here, not in list delegate, because i have some trouble
        // with passing modelData value
        anchors.fill: parent
        sourceComponent: teamObject !== null ? contentComponent : null
    }

    Component{
        id: contentComponent

        Item{

            Rectangle{
                id: contentBorder
                anchors{
                    fill: parent
                    margins: 2
                }
                color: "transparent"
                border.color: Qt.rgba(1,1,1, 0.5)
                border.width: 1
            }

            Item{
                id: teamInfo
                anchors{
                    top: parent.top
                    left: parent.left
                    right: parent.right
                }
                height: defaultHeight

                Rectangle{
                    id: teamInfoBorder
                    anchors{
                        fill: parent
                        margins: 2
                    }
                    color: "transparent"
                    border.color: Qt.rgba(1,1,1, 0.5)
                    border.width: 1
                }

                Label{
                    anchors{
                        left: parent.left
                        top: parent.top
                        leftMargin: 10
                    }
                    height: defaultHeight
                    text: teamObject.teamName

                    verticalAlignment: Text.AlignVCenter
                }

                Button{
                    id: deleteTeamButton
                    anchors{
                        right: editTeamButton.left
                        top: parent.top
                    }
                    height: defaultHeight
                    width: height * 2

                    text: "delete"

                    onClicked:{
                        Backend.event.deleteTeam(teamObject);
                    }
                }

                Button{
                    id: editTeamButton
                    anchors{
                        top: parent.top
                        right: extendButton.left
                    }
                    height: defaultHeight
                    width: height * 2

                    text: "edit"

                    onClicked: {
                        teamDelegate.parentStackView.push(
                                    "Team.qml",
                                    {
                                        edit: true,
                                        parentStackView: teamDelegate.parentStackView,
                                        team: teamDelegate.teamObject
                                    }
                        )
                    }
                }

                Button{
                    id: extendButton
                    anchors{
                        top: parent.top
                        right: parent.right
                    }
                    height: defaultHeight
                    width: height * 2

                    text: teamDelegate.extended ? "^" : "v"

                    onClicked: {
                        teamDelegate.extended = !teamDelegate.extended

                        teamDelegate.height =
                                teamDelegate.extended ?
                                    defaultHeight * 1.5 + playersInfo.height :
                                    defaultHeight

                    }
                }
            }

            Item{
                id: playersInfo
                anchors{
                    top: teamInfo.bottom
                    left: parent.left
                    right: parent.right
                    leftMargin: parent.width * 0.1
                }
                height: teamObject.players.length * defaultHeight

                Connections{
                    target: teamObject
                    function onPlayersChanged() {
                        // after any change of players, change also height
                        teamDelegate.height = teamDelegate.extended ?
                                    defaultHeight * 1.5 + playersInfo.height :
                                    defaultHeight
                    }
                }

                ListView{
                    anchors.fill: parent

                    boundsBehavior: Flickable.StopAtBounds
                    clip: true
                    model: teamObject.players

                    delegate: PlayerDelegate{
                        defaultHeight: teamDelegate.defaultHeight
                        width: playersInfo.width
                        playerObject: modelData
                        parentStackView: teamDelegate.parentStackView
                    }
                }
            }
        }



    }

}

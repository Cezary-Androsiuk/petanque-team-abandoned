import QtQuick 2.15
import QtQuick.Controls.Material

import "../../delegates"

Item {
    id: addTeam
    Rectangle{
        anchors.fill: parent
        color: "#1c1b1f" // dark theme color
    }

    required property var event
    required property var team

    Item{
        id: playersListField
        anchors{
            top: header.bottom
            left: parent.left
            bottom: footer.top
        }
        width: parent.width * 0.5

        Rectangle{
            anchors.fill: parent
            opacity: 0.2
            color: "Green"
        }

        Rectangle{
            id: scrollViewBorder
            anchors.fill: listLoader
            color: "transparent"
            border.color: Qt.rgba(1,1,1, 0.5)
            border.width: 1
        }

        Loader{
            id: listLoader
            anchors{
                fill: parent
                margins: 30
            }
            // I prefer hiding whole list than changing model to 0
            // seems more natural while closing site
            sourceComponent: team !== null ? listComponent : null
        }

        Component{
            id: listComponent
            ScrollView{
                id: scrollView
                clip: true
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

                ListView{
                    id: listView
                    anchors{
                        fill: parent
                        rightMargin: 20
                        leftMargin: 20
                    }

                    model: team.players
                    boundsBehavior: Flickable.StopAtBounds
                    clip: true

                    footer: Item{
                        width: listView.width
                        height: 50
                        Button{
                            anchors.fill: parent
                            text: qsTr("Add new player")
                            onClicked: {
                                addTeam.team.createDetachedPlayer();
                                startStackView.push(
                                            "AddPlayer.qml",
                                            {
                                                team: addTeam.team,
                                                player: addTeam.team.detachedPlayer
                                            }
                                )
                            }
                        }
                    }

                    delegate: PlayerDelegate{
                        defaultHeight: 50
                        width: listView.width
                        playerObject: modelData
                    }


                }
            }
        }


    }

    Item{
        id: teamInfoField
        anchors{
            top: header.bottom
            left: playersListField.right
            right: parent.right
            bottom: footer.top
        }
        Rectangle{
            anchors.fill: parent
            opacity: 0.2
            color: "Blue"
        }


        TextField{
            id: teamNameTextField
            anchors{
                top: parent.top
            }
            height: 60
            width: 230

            placeholderText: qsTr("Team Name")
            onTextEdited: {
                team.teamName = text
            }
        }

    }





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
                addTeam.event.deleteDetachedTeam();
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
                addTeam.event.addTeamUsingDetachedTeam();
            }
        }
    }
}

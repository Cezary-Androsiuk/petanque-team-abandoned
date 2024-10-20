import QtQuick 2.15
import QtQuick.Controls.Material

Item{
    id: teamDelegate

    property double defaultHeight: 50
    property var teamObject
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
                    anchors{
                        top: parent.top
                        right: parent.right
                    }
                    height: defaultHeight
                    width: height * 2

                    text: teamDelegate.extended ? "^" : "v"

                    onClicked: {
                        teamDelegate.height =
                                teamDelegate.extended ?
                                    defaultHeight :
                                    teamDelegate.height + playersInfo.height

                        teamDelegate.extended = !teamDelegate.extended
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
                height: teamObject.getPlayersCount() * defaultHeight

                ListView{
                    anchors.fill: parent

                    boundsBehavior: Flickable.StopAtBounds
                    clip: true
                    model: teamObject.players

                    delegate: PlayerDelegate{
                        defaultHeight: teamDelegate.defaultHeight
                        width: playersInfo.width
                        playerObject: modelData
                    }
                }
            }
        }



    }

}

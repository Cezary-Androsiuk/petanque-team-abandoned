import QtQuick 2.15
import QtQuick.Controls.Material

Item{
    id: teamDelegate

    property double defaultHeight: 50
    property var object
    height: defaultHeight
    clip: true

    property bool extended: false

    Item{
        id: teamInfo
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: defaultHeight

        Label{
            anchors{
                left: parent.left
                top: parent.top
                leftMargin: 10
            }
            height: defaultHeight
            text: object.teamName

            horizontalAlignment: Text.AlignLeft
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
        height: object.playersCount * defaultHeight

        ListView{
            anchors.fill: parent

            boundsBehavior: Flickable.StopAtBounds
            clip: true
            model: object.players

            delegate: PlayerDelegate{
                defaultHeight: teamDelegate.defaultHeight
                width: playersInfo.width
                object: modelData
            }
        }
    }


}

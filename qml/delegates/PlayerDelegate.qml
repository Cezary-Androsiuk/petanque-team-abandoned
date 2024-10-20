import QtQuick 2.15
import QtQuick.Controls.Material

Item{
    id: playerDelegate

    property double defaultHeight: 50
    property var playerObject
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
                text: playerObject.fname + " " + playerObject.lname
            }
        }

    }


}

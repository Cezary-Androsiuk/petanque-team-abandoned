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
            Label{
                anchors{
                    left: parent.left
                    top: parent.top
                    leftMargin: 10
                }
                height: defaultHeight
                text: playerObject.fname + " " + playerObject.lname
            }
        }

    }


}

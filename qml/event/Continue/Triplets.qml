import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: selection
    anchors.fill: parent

    Component.onCompleted: {
        console.log("height: " + height)
    }

    Item{
        anchors{
            fill: parent
            margins: 30
        }
        clip: true

        Rectangle{
            id: selectionFlickableBorder
            anchors.fill: parent
            color: "transparent"
            border.color: Qt.rgba(1,1,1, 0.5)
            border.width: 1
        }

        Flickable{
            id: selectionFlickable
            anchors.fill: parent
            contentWidth: parent.width
            contentHeight: selectionField.height
            boundsBehavior: Flickable.StopAtBounds

            ScrollBar.vertical: ScrollBar{
                policy: ScrollBar.AsNeeded
            }

            Item{
                id: selectionField
                width: parent.width - 40
                x: 20
                y: 10
                height: 890

                Column{
                    id: col
                    anchors.fill: parent
                    spacing: 10
                    Rectangle{
                        width: parent.width
                        height: 100
                        opacity: 0.3
                        color: "red"
                    }
                    Rectangle{
                        width: parent.width
                        height: 100
                        opacity: 0.3
                        color: "green"
                    }
                    Rectangle{
                        width: parent.width
                        height: 100
                        opacity: 0.3
                        color: "blue"
                    }
                    Rectangle{
                        width: parent.width
                        height: 100
                        opacity: 0.3
                        color: "red"
                    }
                    Rectangle{
                        width: parent.width
                        height: 100
                        opacity: 0.3
                        color: "green"
                    }
                    Rectangle{
                        width: parent.width
                        height: 100
                        opacity: 0.3
                        color: "blue"
                    }
                    Rectangle{
                        width: parent.width
                        height: 100
                        opacity: 0.3
                        color: "red"
                    }
                    Rectangle{
                        width: parent.width
                        height: 100
                        opacity: 0.3
                        color: "green"
                    }
                }

            }
        }



    }

}

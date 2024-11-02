import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    required property var team;
    readonly property int delegateHeight: 30

    height:((!team)?0: (team.players.length+1) * delegateHeight)

    ListView{
        id: listView
        anchors.fill: parent

        model: (!team)?null:team.players
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        interactive: false
        cacheBuffer: 500

        footer: Item{
            width: listView.width
            height: 50
        }

        delegate: Item{
            width: listView.width - 40
            anchors.horizontalCenter: parent.horizontalCenter // cannot solve TypeError: Cannot read property 'horizontalCenter' of null
            height: delegateHeight

            Rectangle{
                anchors.fill: parent
                color: "transparent"
                border.color: Qt.rgba(1,1,1, 0.2)
                border.width: 1
            }

            Label{
                id: l1
                anchors{
                    top: parent.top
                    left: parent.left
                    bottom: parent.bottom
                }
                width: 140

                text: modelData.fname + " " + modelData.lname
            }

            Item{
                id: l2
                anchors{
                    top: parent.top
                    left: l1.right
                    right: parent.right
                    bottom: parent.bottom
                }
                width: parent.width/2

                RadioButton{
                    id: rb1
                    anchors{
                        top: parent.top
                        left: parent.left
                        bottom: parent.bottom
                    }
                    width: 140
                    text: "group 1"
                }
                RadioButton{
                    id: rb2
                    anchors{
                        top: parent.top
                        left: rb1.right
                        bottom: parent.bottom
                    }
                    width: 140
                    text: "group 2"
                }
            }


        }

    }


    Rectangle{
        anchors.fill: parent
        color: "transparent"
        border.color: Qt.rgba(1,1,1, 0.5)
        border.width: 1
    }
}

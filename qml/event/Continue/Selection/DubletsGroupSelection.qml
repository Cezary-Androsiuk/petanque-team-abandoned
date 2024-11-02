import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    required property var team;
    readonly property int delegateHeight: 30

    height:((!team)?0: (team.players.length+1) * delegateHeight)

    property var listOfSelected: []

    Component.onCompleted: {
        // create list for checked
        for(let i=0; i<team.players.length; i++)
            listOfSelected.push({1: false, 2: false, 3: false})
    }

    ListView{
        id: listView
        anchors.fill: parent

        model: (!team)?null:team.players
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        interactive: false
        cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling

        footer: Item{
            width: listView.width
            height: 50
        }

        delegate: Item{
            width: listView.width - 40
            anchors.horizontalCenter: parent.horizontalCenter
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

                text: modelData.fname + " " + modelData.lname // set here new created for this purpose player delegate
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
                    onCheckedChanged: {
                        listOfSelected[index][1] = checked
                    }
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
                    onCheckedChanged: {
                        listOfSelected[index][2] = checked
                    }
                }
                RadioButton{
                    id: rb3
                    anchors{
                        top: parent.top
                        left: rb2.right
                        bottom: parent.bottom
                    }
                    width: 140
                    text: "group 3"
                    onCheckedChanged: {
                        listOfSelected[index][3] = checked
                    }
                }
            }


        }

    }

    Component.onDestruction: {
        console.log("")
        for(let selected of listOfSelected)
            console.log("1: " + selected[1] + ", 2: " + selected[2] + ", 3: " + selected[3])
    }

    Rectangle{
        anchors.fill: parent
        color: "transparent"
        border.color: Qt.rgba(1,1,1, 0.5)
        border.width: 1
    }
}

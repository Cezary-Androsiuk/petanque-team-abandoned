import QtQuick 2.15
import QtQuick.Controls.Material

import "../../delegates"

Item {
    id: startEvent

    Item{
        id: listField
        anchors{
            top: parent.top
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
            anchors.fill: scrollView
            color: "transparent"
            border.color: Qt.rgba(1,1,1, 0.5)
            border.width: 1
        }

        ScrollView{
            id: scrollView
            anchors{
                fill: parent
                margins: 30
            }
            clip: true

            // // left hand side scrollBar
            // ScrollBar.vertical: ScrollBar{
            //     parent: scrollView
            //     x: 0
            //     y: scrollView.topPadding
            //     height: scrollView.availableHeight
            //     active: scrollView.ScrollBar.horizontal.active
            // }
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

            ListView{
                id: listView
                anchors{
                    fill: parent
                    rightMargin: 20
                    leftMargin: 20
                }

                model: Backend.teams
                boundsBehavior: Flickable.StopAtBounds
                clip: true

                footer: Item{
                    width: listView.width
                    height: 50
                    Button{
                        anchors.fill: parent
                        text: qsTr("Add new team")
                        onClicked: {
                            var t = Backend.addEmptyTeam()
                            startStackView.push("AddTeam.qml", {team: t})
                        }
                    }
                }

                delegate: TeamDelegate{
                    defaultHeight: 50
                    width: listView.width
                    object: modelData
                }


            }
        }
    }

    Item{
        id: eventInfoField
        anchors{
            top: parent.top
            left: listField.right
            right: parent.right
            bottom: footer.top
        }
        Rectangle{
            anchors.fill: parent
            opacity: 0.2
            color: "Blue"
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
            anchors{
                right: parent.right
                rightMargin: 10
                verticalCenter: parent.verticalCenter
            }

            onClicked: {
                Memory.save();
            }
        }
    }


}

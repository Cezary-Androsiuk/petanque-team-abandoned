import QtQuick 2.15
import QtQuick.Controls.Material

import ".."

Item {
    id: teamsList

    required property var event
    required property var parentStackView

    Loader{
        id: listLoader
        anchors.fill: parent
        // I prefer hiding whole list than changing model to 0
        // seems more natural while closing site
        sourceComponent: event !== null ? listComponent : null
    }

    Component{
        id: listComponent
        ScrollView{
            id: scrollView
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

                model: event.teams
                boundsBehavior: Flickable.StopAtBounds
                clip: true

                footer: Item{
                    width: listView.width
                    height: 50
                    Button{
                        anchors.fill: parent
                        text: qsTr("Add new team")
                        onClicked: {
                            teamsList.event.createDetachedTeam()
                            teamsList.parentStackView.push(
                                        "../Team.qml",
                                        {
                                            parentStackView: teamsList.parentStackView,
                                            event: teamsList.event,
                                            team: teamsList.event.detachedTeam
                                        }
                            )
                        }
                    }
                }

                delegate: TeamDelegate{
                    defaultHeight: 50
                    width: listView.width
                    teamObject: modelData
                    parentStackView: teamsList.parentStackView
                }


            }
        }
    }
}

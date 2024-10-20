import QtQuick 2.15
import QtQuick.Controls.Material

import "../../delegates"

Item {
    id: configureEvent

    readonly property var event: Backend !== null ? Backend.event : null
    required property var parentStackView

    Connections{
        target: Backend
        function onDataValidatedCorrectly(){
            console.log("data are valid")

            // confirm
            Memory.save(); // this should be deleted from that method
        }

        function onDataValidationFailed(description){
            console.log("data are NOT valid")
        }

    }

    /////////////////// onEventStartConfirmed
    // Memory.save();

    Item{
        id: listField
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
                                configureEvent.event.createDetachedTeam()
                                parentStackView.push(
                                            "Team.qml",
                                            {
                                                parentStackView: configureEvent.parentStackView,
                                                event: configureEvent.event,
                                                team: configureEvent.event.detachedTeam
                                            }
                                )
                            }
                        }
                    }

                    delegate: TeamDelegate{
                        defaultHeight: 50
                        width: listView.width
                        teamObject: modelData
                        parentStackView: configureEvent.parentStackView
                    }


                }
            }
        }

    }

    Item{
        id: eventInfoField
        anchors{
            top: header.bottom
            left: listField.right
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

            placeholderText: qsTr("Event data")
            onTextEdited: {

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

            text: "start event"
            onClicked: {
                Backend.validateData()
            }
        }
    }


}

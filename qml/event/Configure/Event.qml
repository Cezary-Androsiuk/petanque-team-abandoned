import QtQuick 2.15
import QtQuick.Controls.Material

import "Event"

Item {
    id: configureEvent

    readonly property var event: Backend !== null ? Backend.event : null
    required property var parentStackView

    Connections{
        target: Backend
        function onDataValidatedCorrectly(){
            log.i("data are valid")

            // confirm popup
            onConfirmed()
        }

        function onDataValidationFailed(description){
            log.i("data are NOT valid")
        }

    }

    /////////////////// onEventStartConfirmed
    // Memory.save();
    function onConfirmed(){
        Memory.save();
        Backend.event.goToNextStage() // changes stage from Configure to Continue
    }

    Item{
        id: eventTeamsList
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


        Item{
            anchors{
                fill: parent
                margins: 30
            }
            clip: true

            Rectangle{
                id: teamListBorder
                anchors.fill: teamsList
                color: "transparent"
                border.color: Qt.rgba(1,1,1, 0.5)
                border.width: 1
            }

            TeamsList{
                id: teamsList
                anchors.fill: parent
                event: configureEvent.event
                parentStackView: configureEvent.parentStackView
            }
        }
    }




    Item{
        id: eventInfoField
        anchors{
            top: header.bottom
            left: eventTeamsList.right
            right: parent.right
            bottom: footer.top
        }
        clip: true
        Rectangle{
            anchors.fill: parent
            opacity: 0.2
            color: "Blue"
        }

        Item{
            anchors{
                fill: parent
                margins: 30
            }
            clip: true

            Rectangle{
                id: infoFieldFlickableBorder
                anchors.fill: infoFieldFlickable
                color: "transparent"
                border.color: Qt.rgba(1,1,1, 0.5)
                border.width: 1
            }

            Flickable{
                id: infoFieldFlickable
                anchors.fill: parent
                contentWidth: parent.width
                contentHeight: infoField.height
                boundsBehavior: Flickable.StopAtBounds

                onHeightChanged: { // keep visible, as long as content is larger than flickable area
                    // console.log("CH: " + infoFieldFlickable.contentHeight + ", H:" + infoFieldFlickable.height)
                    ScrollBar.vertical.policy =
                            infoFieldFlickable.contentHeight > infoFieldFlickable.height ?
                                ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
                }

                ScrollBar.vertical: ScrollBar{
                    policy: ScrollBar.AsNeeded
                }

                InfoField{
                    id: infoField
                    width: parent.width
                    event: configureEvent.event
                }
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

        Button{
            id: setExampleData
            anchors{
                left: parent.left
            }
            text: "create example data"
            onClicked:{
                Backend.createExampleData()
            }
        }
    }


}

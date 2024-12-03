import QtQuick 2.15
import QtQuick.Controls.Material

import "Event"

Item {
    id: configureEvent

    required property var parentStackView

    readonly property int headerHeight: 70
    readonly property int footerHeight: 70


    Connections{
        target: Backend.event
        function onConfigureDataValidatedCorrectly(){
            log.i("data are valid")

            // confirm popup
            onConfirmed()
        }

        function onConfigureDataValidationFailed(description){
            log.i("data are NOT valid")
        }

    }

    /////////////////// onEventStartConfirmed
    function onConfirmed(){
        Memory.save(); // saves data
        Backend.event.goToNextStage() // changes stage from Configure to Continue
        // Memory.save(); // saves changed stage // exiting doing it as well // and timer will be
    }

    Item{
        id: eventTeamsList
        anchors{
            top: header.bottom
            left: parent.left
            bottom: footer.top
        }
        width: parent.width * 0.5
        clip: true

        Item{
            anchors{
                fill: parent
                leftMargin: 30
                rightMargin: 15
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
                parentStackView: configureEvent.parentStackView
            }
        }
    }




    Item{
        id: eventInfoField
        anchors{
            top: header.bottom
            right: parent.right
            bottom: footer.top
        }
        width: parent.width * 0.5
        clip: true

        Item{
            anchors{
                fill: parent
                leftMargin: 15
                rightMargin: 30
            }
            clip: true

            Rectangle{
                id: infoFieldFlickableBorder
                anchors.fill: parent
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
        height: configureEvent.headerHeight

        Label{
            id: titleLabel
            anchors{
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 5
            }
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            text: qsTr("Team Selection")
            font.pixelSize: 30
        }

        Label{
            id: phaseLabel
            anchors{
                horizontalCenter: parent.horizontalCenter
                bottom: parent.bottom
                bottomMargin: 5
            }

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            text: qsTr("Phase ") + (Backend.event.phase +1)
            font.pixelSize: 20
        }
    }

    Item{
        id: footer
        anchors{
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        height: configureEvent.footerHeight

        Button{
            anchors{
                right: parent.right
                rightMargin: 20
                verticalCenter: parent.verticalCenter
            }

            text: "start event"
            onClicked: {
                Backend.event.validateConfigureData();
            }
        }

        Button{
            id: setExampleData
            anchors{
                left: parent.left
                leftMargin: 20
                verticalCenter: parent.verticalCenter
            }
            text: "create example data"
            onClicked:{
                Backend.event.createExampleConfigureData();
            }
        }
    }


}

import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: finish
    anchors.fill: parent

    readonly property var event: Backend.event

    readonly property bool isFirstPhase: (Backend.event.phase+1) == 1

    property int headerHeight: 70
    property int footerHeight: 70

    function startSecondPhase(){
        log.i("startSecondPhase")
        // confirm popup
        onConfirmed1()
    }

    function startNewEvent(){
        log.i("startNewEvent")
        // confirm popup
        onConfirmed2()
    }

    /////////////////// startSecondPhase
    function onConfirmed1(){
        log.i("onConfirmed1")
        Backend.event.startSecondPhase();
        Memory.save();
    }

    function onConfirmed2(){
        log.i("onConfirmed2")
        Backend.event.startNewEvent();
        Memory.save();
    }

    Connections{
        target: event
        function onSecondPhaseStarted(){
            log.i("onSecondPhaseStarted")
            Backend.event.goToConfigureStage(); // changes stage from Finish back to Configure (but with second phase)
            Backend.event.goToFirstRoundStage();
            Memory.save();
        }
        function onNewEventStarted(){
            log.i("onNewEventStarted")

        }
    }

    Item{
        id: header
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: headerHeight

        Label{
            id: roundLabel
            anchors{
                centerIn: parent
            }
            height: parent.height * 0.6
            text: qsTr("Phase ") + (Backend.event.phase+1) + qsTr(" Summary");
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 34
        }
    }

    Item{
        id: finishContent
        anchors{
            top: header.bottom
            left: parent.left
            right: parent.right
            bottom: footer.top
        }

    }

    Item{
        id: footer
        anchors{
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        height: footerHeight

        Button{
            id: nextButton
            anchors{
                right: parent.right
                rightMargin: 30
                verticalCenter: parent.verticalCenter
            }
            text: {
                if(finish.isFirstPhase)
                    "Start the second phase"
                else
                    "Start the new event"
            }
            onClicked: {
                if(finish.isFirstPhase)
                    finish.startSecondPhase();
                else
                    finish.startNewEvent();
            }
        }
    }
}

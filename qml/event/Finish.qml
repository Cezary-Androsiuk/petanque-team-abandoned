import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: finish
    anchors.fill: parent

    readonly property var event: Backend.event

    function startSecondPhase(){
        log.i("startSecondPhase")
        // confirm popup
        onConfirmed()
    }

    /////////////////// startSecondPhase
    function onConfirmed(){
        log.i("onConfirmed")
        Backend.event.startSecondPhase();
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
    }

    Item{
        id: header
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: 70

        Label{
            id: roundLabel
            anchors{
                top: parent.top
                horizontalCenter: parent.horizontalCenter
            }
            height: parent.height * 0.6
            text: "Finish"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 26
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
        height: 70

        Button{
            id: nextButton
            anchors{
                right: parent.right
                rightMargin: 30
                verticalCenter: parent.verticalCenter
            }
            text: "Start the second phase"
            onClicked: {
                finish.startSecondPhase();
            }
        }
    }
}

import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: continueEvent
    anchors.fill: parent

    property int round: (!Backend)?0: Backend.event.round
    property int roundStage: (!Backend)?0: Backend.event.roundStage

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
            text: "Round " + continueEvent.round
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 22
        }

        Label{
            id: roundStageLabel
            anchors{
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
            }
            height: parent.height * 0.4
            text: "Stage " + continueEvent.roundStage
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 14
        }

        Rectangle{
            anchors.fill: parent
            color: "red"
            opacity: 0.2
        }
    }

    Rectangle{
        anchors.fill: parent
        color: "blue"
        opacity: 0.2
    }


}

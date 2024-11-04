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

    Loader{
        id: continueLoader
        anchors{
            top: header.bottom
            left: parent.left
            right: parent.right
            bottom: footer.top
        }
        source: {
            if(roundStage === 0)
                "Continue/Selection.qml";
            else if(roundStage === 1)
                "Continue/Triplets.qml";
            else if(roundStage === 2)
                "Continue/Dublets.qml";
            else if(roundStage === 3)
                "Continue/Singiels.qml";
            else if(roundStage === 4)
                "Continue/Confirm.qml";
            else{
                console.log("Error: received roundStage=" + roundStage + " in Continue.qml");
                "";
            }
        }
        onLoaded:{
            if(continueLoader.item)
            {
                continueLoader.item.verifiedData.connect(internalDataAreVerified)
            }
        }
    }

    function internalDataAreVerified(){
        console.log("verified")
        if(Backend.event.roundStage !== 4)
            Backend.event.roundStage += 1
        Memory.save()
    }

    Item{
        id: footer
        anchors{
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        height: 70

        Item{
            id: centerItem
            anchors{
                centerIn: parent
            }
        }

        Button{
            id: backButton
            anchors{
                right: centerItem.left
                rightMargin: 5
                verticalCenter: parent.verticalCenter
            }
            enabled: (!Backend)?false: Backend.event.roundStage !== 0
            text: "left"
            onClicked: {
                if(Backend.event.roundStage !== 0)
                    Backend.event.roundStage -= 1
            }
        }

        Button{
            id: nextButton
            anchors{
                left: centerItem.right
                leftMargin: 5
                verticalCenter: parent.verticalCenter
            }
            enabled: (!Backend)?false: Backend.event.roundStage !== 4
            text: "right"
            onClicked: {
                continueLoader.item.verifyData();
            }
        }

        Button{
            id: exampleDataButton
            anchors{
                left: nextButton.right
                leftMargin: 30
                verticalCenter: parent.verticalCenter
            }
            text: "Set Example Data"
            onClicked:{
                continueLoader.item.setExampleData()
            }
        }
    }

    Component.onDestruction: {
        Memory.save(false /*reload after saved*/);
    }

}

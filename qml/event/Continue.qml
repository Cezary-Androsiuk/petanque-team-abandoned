import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: continueEvent
    anchors.fill: parent

    property int round: Backend.event.round
    property int roundStage: Backend.event.roundStage

    Component.onCompleted: {
        Backend.event.createMatchIfNotExist();
    }

    Connections{
        target: Backend.event
        function onRoundChanged(){
            Backend.event.createMatchIfNotExist();

        }
        function onRoundStageChanged(){
        }

        function onCurrentRoundStageVerified(){
            console.log("verified")
            if(roundStage === 4)
            {
                Backend.event.roundStage = 0;
                Backend.event.round += 1;
            }
            else
                Backend.event.roundStage += 1;

            Memory.save()
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
            if(roundStage === 0)   "Continue/Selection.qml";    else
            if(roundStage === 1)   "Continue/Triplets.qml";     else
            if(roundStage === 2)   "Continue/Dublets.qml";      else
            if(roundStage === 3)   "Continue/Singiels.qml";     else
            {
                console.log("Error: received roundStage=" + roundStage + " in Continue.qml");
                "";
            }
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
            enabled: round === 1 ? (roundStage !== 0) : true

            text: "left"
            onClicked: {
                if(round == 1)
                {
                    if(roundStage !== 0)
                        Backend.event.roundStage -= 1;
                    else
                        ;
                }
                else
                {
                    if(roundStage === 0)
                    {
                        Backend.event.roundStage = 4;
                        Backend.event.round -= 1;
                    }
                    else
                        Backend.event.roundStage -= 1;
                }

            }
        }

        Button{
            id: nextButton
            anchors{
                left: centerItem.right
                leftMargin: 5
                verticalCenter: parent.verticalCenter
            }
            enabled: true
            text: "right"
            onClicked: {
                Backend.event.verifyCurrentRoundStage();
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

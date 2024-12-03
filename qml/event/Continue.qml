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

    Component.onDestruction: {
        Memory.save();
    }

    Connections{
        target: Backend.event
        function onRoundChanged(){
            Backend.event.createMatchIfNotExist();
        }
        function onRoundStageChanged(){
            Backend.event.createMatchIfNotExist();
        }

        function onMatchWasCreated(){
            continueLoader.active = true;
        }
        function onMatchAlreadyExist(){
            continueLoader.active = true;
        }

        function onCurrentRoundStageVerified(){
            continueLoader.active = false;
            if(Backend.event.hasNextRoundStage)
            {
                Backend.event.goToNextRoundStage();
                Memory.save()
            }
            else
            {
                // confirm popup
                onConfirmed()
            }
        }
        function onCurrentRoundStageVerificationFailed(message){
            console.log("verification current stage failed: " + message)
        }
    }

    /////////////////// onCurrentRoundStageVerified
    function onConfirmed(){
        Memory.save(); // saves data
        Backend.event.goToNextStage(); // changes stage from Continue to Finish
        // Memory.save(); // saves changed stage // exiting doing it as well // and timer will be
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
    }

    BusyIndicator{
        anchors.centerIn: parent
        running: loaderSource === ""
    }

    Loader{
        id: continueLoader
        anchors{
            top: header.bottom
            left: parent.left
            right: parent.right
            bottom: footer.top
        }
        active: false
        source: {
            if(roundStage === 0)    "Continue/SingielsSelection.qml";   else
            if(roundStage === 1)    "Continue/SingielsMatch.qml";       else
            if(roundStage === 2)    "Continue/DubletsSelection.qml";    else
            if(roundStage === 3)    "Continue/DubletsMatch.qml";        else
            if(roundStage === 4)    "Continue/TripletsSelection.qml";   else
            if(roundStage === 5)    "Continue/TripletsMatch.qml";       else
            if(roundStage === 6)    "Continue/MatchSummary.qml";        else
            {
                log.e("Error: received roundStage=" + roundStage + " in Continue.qml");
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
            enabled: Backend.event.hasPrevRoundStage;

            text: "Back"
            onClicked: {
                Backend.event.goToPrevRoundStage();
            }
        }

        Button{
            id: nextButton
            anchors{
                left: centerItem.right
                leftMargin: 5
                verticalCenter: parent.verticalCenter
            }
            text: "Next"
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

        Button{
            id: exampleDataAndNextButton
            anchors{
                left: exampleDataButton.right
                leftMargin: 30
                verticalCenter: parent.verticalCenter
            }
            text: "Set Example Data And Go Next"
            onClicked:{
                exampleDataButton.clicked();
                nextButton.clicked();
            }
        }
    }


}

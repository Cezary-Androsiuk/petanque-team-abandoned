import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: infoField
    height: childrenRect.height + 20

   readonly property var event: Backend.event

    TextField{
        id: eventNameTextField
        anchors{
            top: parent.top
            topMargin: 10
        }
        height: 60
        width: 230

        placeholderText: qsTr("Event name")
        // text: (!event)?null: event.name
        onTextEdited: {
            event.name = text
        }
    }

    TextField{
        id: firstPhaseDateTextField
        anchors{
            top: eventNameTextField.bottom
            topMargin: 10
        }
        height: 60
        width: 230

        placeholderText: qsTr("First phase date (YYYY-MM-DD)")
        onTextEdited: {
            event.date = text
        }
    }
    Button{
        id: setTodayFirstPhaseDateButton
        anchors{
            left: firstPhaseDateTextField.right
            top: firstPhaseDateTextField.top
            bottom: firstPhaseDateTextField.bottom
            leftMargin: 10
        }
        text: qsTr("Todays Date")
        onClicked: {
            var now = new Date();
            var todaysDate = now.toISOString().slice(0, 10); // Gemini

            firstPhaseDateTextField.text = todaysDate;
            event.date = todaysDate
        }
    }

    // TextField{
    //     id: secondPhaseDateTextField
    //     anchors{
    //         top: firstPhaseDateTextField.bottom
    //         topMargin: 10
    //     }
    //     height: 60
    //     width: 230

    //     placeholderText: qsTr("Second phase date (YYYY-MM-DD)")
    //     onTextEdited: {
    //         event.secondPhaseDate = text
    //     }
    // }
    // Button{
    //     id: setTodaySecondPhaseDateButton
    //     anchors{
    //         left: secondPhaseDateTextField.right
    //         top: secondPhaseDateTextField.top
    //         bottom: secondPhaseDateTextField.bottom
    //         leftMargin: 10
    //     }
    //     text: qsTr("Todays Date")
    //     onClicked: {
    //         var now = new Date();
    //         var todaysDate = now.toISOString().slice(0, 10); // Gemini

    //         secondPhaseDateTextField.text = todaysDate;
    //         event.secondPhaseDate = todaysDate
    //     }
    // }

    TextField{
        id: competitionOrganizerTextField
        anchors{
            top: firstPhaseDateTextField.bottom
            topMargin: 10
        }
        height: 60
        width: 230

        placeholderText: qsTr("Competition Organizer")
        onTextEdited: {
            event.competitionOrganizer = text
        }
    }

    TextField{
        id: firstPhasePlaceTextField
        anchors{
            top: competitionOrganizerTextField.bottom
            topMargin: 10
        }
        height: 60
        width: 230

        placeholderText: qsTr("First phase place")
        onTextEdited: {
            event.firstPhasePlace = text
        }
    }

    TextField{
        id: secondPhasePlaceTextField
        anchors{
            top: firstPhasePlaceTextField.bottom
            topMargin: 10
        }
        height: 60
        width: 230

        placeholderText: qsTr("Second phase place")
        onTextEdited: {
            event.secondPhasePlace = text
        }
    }

    Item{
        id: judgesItem
        anchors{
            top: secondPhasePlaceTextField.bottom
            topMargin: 10
        }
        height: ((!event)?1: (event.judges.length+1)) * judgesItem.judgeHeight
        width: 230

        readonly property int judgeHeight: 80

        Rectangle{
            anchors.fill: parent
            color: "transparent"
            border.color: Qt.rgba(1,1,1, 0.5)
            border.width: 1
        }

        ListView{
            id: judgesListView
            anchors.fill: parent
            boundsBehavior: Flickable.StopAtBounds
            model: (!event)?null: event.judges

            footer: Item{
                width: judgesListView.width
                height: judgesItem.judgeHeight
                Button{
                    id: addJudgeButton
                    anchors{
                        fill: parent
                        margins: 15
                    }
                    text: qsTr("Add judge")
                    onClicked: {
                        event.addJudge();
                    }
                }
            }

            delegate: Item{
                width: judgesListView.width
                height: judgesItem.judgeHeight
                TextField{
                    id: judgeTextField
                    anchors{
                        left: parent.left
                        top: parent.top
                        right: deleteJudgeButton.left
                        bottom: parent.bottom
                        margins: 5
                    }
                    placeholderText: qsTr("Judge " + index)
                    text: modelData
                    onEditingFinished: {
                        event.setJudge(index, text);
                    }
                }

                Button{
                    id: deleteJudgeButton
                    anchors{
                        top: parent.top
                        right: parent.right
                        bottom: parent.bottom
                        margins: 15
                    }
                    width: height
                    text: "X"
                    onClicked: {
                        event.deleteJudge(index);
                    }
                }
            }
        }
    }


    TextField{
        id: unionDelegateTextField
        anchors{
            top: judgesItem.bottom
            topMargin: 10
        }
        height: 60
        width: 230

        placeholderText: qsTr("Union delegate")
        onTextEdited: {
            event.unionDelegate = text
        }
    }
}

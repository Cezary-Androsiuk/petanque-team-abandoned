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
        text: (!event)?null: event.name
        onTextEdited: {
            event.name = text
        }
    }

    TextField{
        id: dateTextField
        anchors{
            top: eventNameTextField.bottom
            topMargin: 10
        }
        height: 60
        width: 230

        placeholderText: qsTr("First phase date (YYYY-MM-DD)")
        text: (!event)?null: event.date
        onTextEdited: {
            event.date = text
        }
    }
    Button{
        id: setTodayDateButton
        anchors{
            left: dateTextField.right
            top: dateTextField.top
            bottom: dateTextField.bottom
            leftMargin: 10
        }
        text: qsTr("Todays Date")
        onClicked: {
            var now = new Date();
            var todaysDate = now.toISOString().slice(0, 10); // Gemini

            dateTextField.text = todaysDate;
            event.date = todaysDate
        }
    }

    TextField{
        id: competitionOrganizerTextField
        anchors{
            top: dateTextField.bottom
            topMargin: 10
        }
        height: 60
        width: 230

        placeholderText: qsTr("Competition Organizer")
        text: (!event)?null: event.competitionOrganizer
        onTextEdited: {
            event.competitionOrganizer = text
        }
    }

    TextField{
        id: placeTextField
        anchors{
            top: competitionOrganizerTextField.bottom
            topMargin: 10
        }
        height: 60
        width: 230

        placeholderText: qsTr("First phase place")
        text: (!event)?null: event.place
        onTextEdited: {
            event.place = text
        }
    }

    Item{
        id: judgesItem
        anchors{
            top: placeTextField.bottom
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
        text: (!event)?null: event.unionDelegate
        onTextEdited: {
            event.unionDelegate = text
        }
    }
}

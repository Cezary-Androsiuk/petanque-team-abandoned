import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: configureEvent

    readonly property var event: Backend !== null ? Backend.event : null
    required property var parentStackView

    Connections{
        target: Backend
        function onDataValidatedCorrectly(){
            console.log("data are valid")

            // confirm popup
            onConfirmed()
        }

        function onDataValidationFailed(description){
            console.log("data are NOT valid")
        }

    }

    /////////////////// onEventStartConfirmed
    // Memory.save();
    function onConfirmed(){
        Memory.save(); // handled in Main.qml
    }

    Item{
        id: listField
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

        Rectangle{
            id: scrollViewBorder
            anchors.fill: listLoader
            color: "transparent"
            border.color: Qt.rgba(1,1,1, 0.5)
            border.width: 1
        }

        Loader{
            id: listLoader
            anchors{
                fill: parent
                margins: 30
            }
            // I prefer hiding whole list than changing model to 0
            // seems more natural while closing site
            sourceComponent: event !== null ? listComponent : null
        }

        Component{
            id: listComponent
            ScrollView{
                id: scrollView
                clip: true

                // // left hand side scrollBar
                // ScrollBar.vertical: ScrollBar{
                //     parent: scrollView
                //     x: 0
                //     y: scrollView.topPadding
                //     height: scrollView.availableHeight
                //     active: scrollView.ScrollBar.horizontal.active
                // }
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

                ListView{
                    id: listView
                    anchors{
                        fill: parent
                        rightMargin: 20
                        leftMargin: 20
                    }

                    model: event.teams
                    boundsBehavior: Flickable.StopAtBounds
                    clip: true

                    footer: Item{
                        width: listView.width
                        height: 50
                        Button{
                            anchors.fill: parent
                            text: qsTr("Add new team")
                            onClicked: {
                                configureEvent.event.createDetachedTeam()
                                parentStackView.push(
                                            "Team.qml",
                                            {
                                                parentStackView: configureEvent.parentStackView,
                                                event: configureEvent.event,
                                                team: configureEvent.event.detachedTeam
                                            }
                                )
                            }
                        }
                    }

                    delegate: TeamDelegate{
                        defaultHeight: 50
                        width: listView.width
                        teamObject: modelData
                        parentStackView: configureEvent.parentStackView
                    }


                }
            }
        }

    }


    // property var judgesModel: ["", "", ""]
    ListModel{
        id: judgesModel
        ListElement{ judgeName: "" }
    }

    Item{
        id: eventInfoField
        anchors{
            top: header.bottom
            left: listField.right
            right: parent.right
            bottom: footer.top
        }
        clip: true
        Rectangle{
            anchors.fill: parent
            opacity: 0.2
            color: "Blue"
        }

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
                event.firstPhaseDate = text
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
                event.firstPhaseDate = todaysDate
            }
        }

        TextField{
            id: secondPhaseDateTextField
            anchors{
                top: firstPhaseDateTextField.bottom
                topMargin: 10
            }
            height: 60
            width: 230

            placeholderText: qsTr("Second phase date (YYYY-MM-DD)")
            onTextEdited: {
                event.secondPhaseDate = text
            }
        }
        Button{
            id: setTodaySecondPhaseDateButton
            anchors{
                left: secondPhaseDateTextField.right
                top: secondPhaseDateTextField.top
                bottom: secondPhaseDateTextField.bottom
                leftMargin: 10
            }
            text: qsTr("Todays Date")
            onClicked: {
                var now = new Date();
                var todaysDate = now.toISOString().slice(0, 10); // Gemini

                secondPhaseDateTextField.text = todaysDate;
                event.secondPhaseDate = todaysDate
            }
        }

        TextField{
            id: competitionOrganizerTextField
            anchors{
                top: setTodaySecondPhaseDateButton.bottom
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
            height: 240//(judgesModel.length+1) * 60
            width: 230

            ListView{
                id: judgesListView
                anchors.fill: parent
                boundsBehavior: Flickable.StopAtBounds
                model: configureEvent.judgesModel

                footer: Item{
                    width: judgesListView.width
                    height: 60
                    Button{
                        id: addJudgeButton
                        anchors.fill: parent
                        text: qsTr("Add judge button")
                        onClicked: {
                            configureEvent.judgesModel.append({judgeName: ""})

                            for(var judge2 of configureEvent.judgesModel)
                                console.log("judge: " + judge2.judgeName)
                        }
                    }
                }

                delegate: Item{
                    Rectangle{
                        anchors.fill: parent
                        color: "red"
                        opacity: 0.6
                    }

                    width: judgesListView.width
                    height: 60
                    TextField{
                        id: judgeTextField
                        anchors.fill: parent
                        placeholderText: qsTr("Judge")
                        text: modelData.judgeName
                        onTextEdited: {
                            modelData.judgeName = text
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
                for(var judge2 of judgesModel)
                    console.log("judge: " + judge2)
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

import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: addPlayer
    Rectangle{
        anchors.fill: parent
        color: "#1c1b1f" // dark theme color
    }

    required property var team
    required property var player

    Item{
        id: playerInfoField
        anchors{
            top: header.bottom
            left: parent.left
            right: parent.right
            bottom: footer.top
        }

        Rectangle{
            anchors.fill: parent
            opacity: 0.2
            color: "Green"
        }

        TextField{
            id: fnameTextField
            anchors{
                top: parent.top
            }
            height: 60
            width: 230

            placeholderText: qsTr("First Name")
            onTextEdited: {
                player.fname = text
            }
        }

        TextField{
            id: lnameTextField
            anchors{
                top: fnameTextField.bottom
                topMargin: 10
            }
            height: 60
            width: 230

            placeholderText: qsTr("Last Name")
            onTextEdited: {
                player.lname = text
            }
        }

        TextField{
            id: licenseTextField
            anchors{
                top: lnameTextField.bottom
                topMargin: 10
            }
            height: 60
            width: 230

            placeholderText: qsTr("License")
            onTextEdited: {
                player.license = text
            }
        }

        TextField{
            id: ageTextField
            anchors{
                top: licenseTextField.bottom
                topMargin: 10
            }
            height: 60
            width: 230

            placeholderText: qsTr("Age")
            validator: IntValidator{
                bottom: 0
                top: 200
            }
            onTextEdited: {
                var t = text
                if(t === "") t = "0"
                player.age = t
            }
        }

        ComboBox{
            id: genderComboBox
            anchors{
                top: ageTextField.bottom
                topMargin: 10
            }
            model: [
                {value: 0, text: qsTr("Male")},
                {value: 1, text: qsTr("Female")}
            ]
            textRole: "text"
            valueRole: "value"

            onCurrentValueChanged: {
                player.gender = currentValue
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

        Button{
            anchors{
                left: parent.left
                leftMargin: 10
                verticalCenter: parent.verticalCenter
            }

            text: "back"

            onClicked: {
                startStackView.pop();
                addPlayer.team.deleteDetachedPlayer();
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
        Rectangle{
            anchors.fill: parent
            opacity: 0.2
            color: "Red"
        }

        Button{
            anchors.centerIn: parent

            text: "save player"

            onClicked: {
                startStackView.pop();
                addPlayer.team.addPlayerUsingDetachedPlayer();
            }
        }
    }
}

import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: configurePlayer
    Rectangle{
        anchors.fill: parent
        color: "#1c1b1f" // dark theme color
    }

    required property var parentStackView
    required property var team
    required property var player
    property bool edit: false

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
            text: (!player)?null: player.fname
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
            text: (!player)?null: player.lname
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
            text: (!player)?null: player.license
            onTextEdited: {
                player.license = text
            }
        }

        ComboBox{
            id: ageGroupComboBox
            anchors{
                top: licenseTextField.bottom
                topMargin: 10
            }
            model: ["Junior", "Youth", "Senior", "Veteran"]
            currentIndex: (!player)?currentIndex: player.ageGroup

            onCurrentIndexChanged: {
                if(player)
                {
                    player.ageGroup = currentIndex
                }
            }
        }

        ComboBox{
            id: genderComboBox
            anchors{
                top: ageGroupComboBox.bottom
                topMargin: 10
            }
            model: ["Male", "Female"]
            currentIndex: (!player)?currentIndex: player.gender

            onCurrentIndexChanged: {
                if(player)
                {
                    player.gender = currentIndex
                }
            }
        }

        CheckBox{
            id: isTeamLeaderCheckBox
            anchors{
                top: genderComboBox.bottom
                topMargin: 10
            }
            checked: (!player)?checked: player.isTeamLeader
            onCheckedChanged: {
                if(player)
                {
                    if(checked === player.isTeamLeader)
                         return;

                    configurePlayer.team.uncheckAllLeaders();

                    if(checked)
                        player.isTeamLeader = true
                }
            }
            text: "Is Team Leader"
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

            visible: configurePlayer.edit
            onClicked: {
                parentStackView.pop();
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

        Item{
            id: footerButtons
            anchors.fill: parent
            visible: !configurePlayer.edit

            Button{
                anchors{
                    right: centerPoint.left
                    verticalCenter: parent.verticalCenter
                }

                text: "cancel"

                onClicked: {
                    parentStackView.pop();
                    configurePlayer.team.deleteDetachedPlayer();
                }
            }

            Item{
                id: centerPoint
                anchors.centerIn: parent
                width: 20
            }

            Button{
                anchors{
                    left: centerPoint.right
                    verticalCenter: parent.verticalCenter
                }

                text: "save player"

                onClicked: {
                    parentStackView.pop();
                    configurePlayer.team.addPlayerUsingDetachedPlayer();
                }
            }
        }

    }
}

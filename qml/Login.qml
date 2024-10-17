import QtQuick
import QtQuick.Controls.Material

Item {
    id: login
    anchors.fill: parent


    MouseArea{
        id: looseFocus
        anchors.fill: parent
        onClicked:{
            login.focus = true
        }
    }

    Item{
        id: centeredField
        anchors.centerIn: parent
        width: 250
        height: 250

        // Rectangle{
        //     anchors.fill: parent
        //     color: "red"
        // }

        TextField{
            id: loginTextField
            anchors{
                top: parent.top
                horizontalCenter: parent.horizontalCenter
            }
            width: 230
            height: 60

            placeholderText: qsTr("Login")
        }

        Label{
            id: loginWarningLabel
            anchors{
                top: loginTextField.bottom
                left: loginTextField.left
                leftMargin: 5
            }
            text: qsTr("some text1")
            visible: false
            color: Qt.rgba(0.8, 0.3, 0.3)
        }

        TextField{
            id: passwordTextField
            anchors{
                top: loginWarningLabel.visible ? loginWarningLabel.bottom : loginTextField.bottom
                topMargin: 10
                horizontalCenter: parent.horizontalCenter
            }
            width: 230
            height: 60

            placeholderText: qsTr("Password")
            echoMode: TextInput.Password
        }

        Label{
            id: passwordWarningLabel
            anchors{
                top: passwordTextField.bottom
                left: passwordTextField.left
                leftMargin: 5
            }
            text: qsTr("some text1")
            visible: false
            color: Qt.rgba(0.8, 0.3, 0.3)
        }

        CheckBox{
            id: showPasswordCheckBox
            anchors{
                top: passwordWarningLabel.visible ? passwordWarningLabel.bottom : passwordTextField.bottom
                topMargin: 10
                left: passwordTextField.left
                // leftMargin: 10
            }

            checked: false
            text: qsTr("Show Password")
            onCheckedChanged: {
                passwordTextField.echoMode =
                        checked ? TextInput.Normal : TextInput.Password;
            }
        }
        Button{
            id:  loginButtin
            anchors{
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
            }
            width: 160
            height: 60

            text: qsTr("Login")
            onClicked:{
                var login = loginTextField.text;
                var password = passwordTextField.text;
                var somethingMissing = false;

                loginWarningLabel.visible = false
                passwordWarningLabel.visible = false

                if(login === "")
                {
                    console.log("Login is missing")
                    loginWarningLabel.visible = true
                    somethingMissing = true;
                }

                if(password === "")
                {
                    console.log("Password is missing")
                    passwordWarningLabel.visible = true
                    somethingMissing = true;
                }

                if(somethingMissing)
                {
                    return
                }

                // console.log( + " " + )
            }
        }
    }
}

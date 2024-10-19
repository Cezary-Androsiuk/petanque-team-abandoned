import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: startEvent
    anchors.fill: parent

    Item{
        id: listField
        anchors{
            top: parent.top
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
            anchors.fill: scrollView
            color: "transparent"
            border.color: Qt.rgba(1,1,1, 0.5)
            border.width: 1
        }

        ScrollView{
            id: scrollView
            anchors{
                fill: parent
                margins: 30
            }
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
                    leftMargin: rightMargin
                }

                model: Backend.teams
                boundsBehavior: Flickable.StopAtBounds
                clip: true

                footer: Item{
                    width: listView.width
                    height: 50
                    Button{
                        anchors.fill: parent
                        text: qsTr("Add new team")
                    }
                }


                delegate: Item{
                    id: teamDelegate

                    readonly property double defaultHeight: 50
                    height: defaultHeight
                    width: listView.width
                    clip: true

                    property bool extended: false

                    Item{
                        id: teamInfo
                        anchors{
                            top: parent.top
                            left: parent.left
                            right: parent.right
                        }
                        height: defaultHeight

                        Label{
                            anchors{
                                left: parent.left
                                top: parent.top
                                leftMargin: 10
                            }
                            height: defaultHeight
                            text: modelData.teamName

                            horizontalAlignment: Text.AlignLeft
                            verticalAlignment: Text.AlignVCenter
                        }

                        Button{
                            anchors{
                                top: parent.top
                                right: parent.right
                            }
                            height: defaultHeight
                            width: height * 2

                            text: teamDelegate.extended ? "^" : "v"

                            onClicked: {
                                teamDelegate.height =
                                        teamDelegate.extended ?
                                            defaultHeight :
                                            teamDelegate.height + playersInfo.height

                                teamDelegate.extended = !teamDelegate.extended
                            }
                        }
                    }

                    Item{
                        id: playersInfo
                        anchors{
                            top: teamInfo.bottom
                            left: parent.left
                            right: parent.right
                            leftMargin: parent.width * 0.1
                        }
                        height: modelData.playersCount * defaultHeight

                        ListView{
                            anchors.fill: parent

                            boundsBehavior: Flickable.StopAtBounds
                            clip: true
                            model: modelData.players

                            delegate: Item{
                                width: playersInfo
                                height: teamDelegate.defaultHeight

                                Label{
                                    anchors{
                                        left: parent.left
                                        top: parent.top
                                        leftMargin: 10
                                    }
                                    height: defaultHeight
                                    text: modelData.fname + " " + modelData.lname
                                }

                            }
                        }
                    }


                }


            }
        }
    }

    Item{
        id: eventInfoField
        anchors{
            top: parent.top
            left: listField.right
            right: parent.right
            bottom: footer.top
        }
        Rectangle{
            anchors.fill: parent
            opacity: 0.2
            color: "Blue"
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

            onClicked: {
                Memory.save();
            }
        }
    }


}

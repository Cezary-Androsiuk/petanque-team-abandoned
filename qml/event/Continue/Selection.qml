import QtQuick 2.15
import QtQuick.Controls.Material

import "Selection"

Item {
    id: selection
    anchors.fill: parent

    readonly property var event: Backend !== null ? Backend.event : null

    Item{
        anchors{
            fill: parent
            margins: 30
        }
        clip: true

        ListView{
            id: listView
            anchors.fill: parent

            model: (!event)?null:event.teams.length
            boundsBehavior: Flickable.StopAtBounds
            clip: true
            cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling

            ScrollBar.vertical: ScrollBar{
                policy: ScrollBar.AsNeeded
            }

            footer: Item{
                width: listView.width
                height: 50
            }

            delegate: Item{
                width: listView.width - 40
                anchors.horizontalCenter: parent.horizontalCenter
                height: ml1.height + tgs.height + dgs.height + sgs.height + 50

                Item{
                    id: ml1
                    anchors{
                        top: parent.top
                        left: parent.left
                        right: parent.right
                    }
                    height: 60
                    Label{
                        anchors.fill: parent
                        text: (!event)?"": event.teams[index].teamName
                        font.pixelSize: 26
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                TripletsGroupSelection{
                    id: tgs
                    anchors{
                        top: ml1.bottom
                        left: parent.left
                        right: parent.right
                        margins: 10
                    }
                    team: event.teams[index]
                }

                DubletsGroupSelection{
                    id: dgs
                    anchors{
                        top: tgs.bottom
                        left: parent.left
                        right: parent.right
                        margins: 10
                    }
                    team: event.teams[index]
                }

                SingielsGroupSelection{
                    id: sgs
                    anchors{
                        top: dgs.bottom
                        left: parent.left
                        right: parent.right
                        margins: 10
                    }
                    team: event.teams[index]
                }
                Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                    border.color: Qt.rgba(1,1,1, 0.5)
                    border.width: 1
                }

            }

            Rectangle{
                id: selectionFlickableBorder
                anchors.fill: parent
                color: "transparent"
                border.color: Qt.rgba(1,1,1, 0.5)
                border.width: 1
            }

        }

        /*
        Flickable{
            id: selectionFlickable
            anchors.fill: parent
            contentWidth: parent.width
            contentHeight: selectionField.height
            boundsBehavior: Flickable.StopAtBounds

            ScrollBar.vertical: ScrollBar{
                policy: ScrollBar.AsNeeded
            }

            Item{
                id: selectionField
                width: parent.width - 40
                x: 20
                y: 10
                height: 500

                Rectangle{
                    anchors{
                        top: parent.top
                        left: parent.left
                        right: parent.right
                    }
                    height: parent.height/2
                    opacity: 0.8
                    color: "blue"
                }

                Rectangle{
                    anchors{
                        bottom: parent.bottom
                        left: parent.left
                        right: parent.right
                    }
                    height: parent.height/2
                    opacity: 0.8
                    color: "green"
                }
                // ListView{
                //     id: listView
                //     anchors{
                //         fill: parent
                //         rightMargin: 20
                //         leftMargin: 20
                //     }

                //     onHeightChanged: {
                //         console.log("height: " + height)
                //     }

                //     model: (!event)?null:event.teams.length
                //     boundsBehavior: Flickable.StopAtBounds
                //     clip: true

                //     footer: Item{
                //         width: listView.width
                //         height: 50

                //         Rectangle{
                //             anchors.fill: parent
                //             opacity: 0.8
                //             color: "white"
                //         }
                //     }

                //     delegate: Item{
                //         width: listView.width
                //         height: tgs.height + dgs.height + sgs.height + 10

                //         TripletsGroupSelection{
                //             id: tgs
                //             anchors{
                //                 top: parent.top
                //                 left: parent.left
                //                 right: parent.right
                //             }
                //         }

                //         DubletsGroupSelection{
                //             id: dgs
                //             anchors{
                //                 top: tgs.bottom
                //                 left: parent.left
                //                 right: parent.right
                //             }
                //         }

                //         SingielsGroupSelection{
                //             id: sgs
                //             anchors{
                //                 top: dgs.bottom
                //                 left: parent.left
                //                 right: parent.right
                //             }
                //         }

                //     }

                // }
            }
        }
        */

        /*
        ScrollView{
            id: scrollView
            clip: true
            anchors.fill: parent

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

                model: (!event)?null:event.teams.length
                boundsBehavior: Flickable.StopAtBounds
                clip: true

                footer: Item{
                    width: listView.width
                    height: 50

                    Rectangle{
                        anchors.fill: parent
                        opacity: 0.8
                        color: "white"
                    }
                }

                delegate: Item{
                    width: listView.width
                    height: tgs.height + dgs.height + sgs.height + 10

                    TripletsGroupSelection{
                        id: tgs
                        anchors{
                            top: parent.top
                            left: parent.left
                            right: parent.right
                        }
                    }

                    DubletsGroupSelection{
                        id: dgs
                        anchors{
                            top: tgs.bottom
                            left: parent.left
                            right: parent.right
                        }
                    }

                    SingielsGroupSelection{
                        id: sgs
                        anchors{
                            top: dgs.bottom
                            left: parent.left
                            right: parent.right
                        }
                    }

                }

            }
        }
        */

        /*
        Flickable{
            id: selectionFlickable
            anchors.fill: parent
            contentWidth: parent.width
            contentHeight: selectionField.height
            boundsBehavior: Flickable.StopAtBounds

            ScrollBar.vertical: ScrollBar{
                policy: ScrollBar.AsNeeded
            }

            Item{
                id: selectionField
                width: parent.width - 40
                x: 20
                y: 10
                height: 890

                Column{
                    id: col
                    anchors.fill: parent
                    spacing: 10
                    Rectangle{
                        width: parent.width
                        height: 100
                        opacity: 0.8
                        color: "red"
                    }
                    Rectangle{
                        width: parent.width
                        height: 100
                        opacity: 0.8
                        color: "green"
                    }
                    Rectangle{
                        width: parent.width
                        height: 100
                        opacity: 0.8
                        color: "blue"
                    }
                    Rectangle{
                        width: parent.width
                        height: 100
                        opacity: 0.8
                        color: "red"
                    }
                    Rectangle{
                        width: parent.width
                        height: 100
                        opacity: 0.8
                        color: "green"
                    }
                    Rectangle{
                        width: parent.width
                        height: 100
                        opacity: 0.8
                        color: "blue"
                    }
                    Rectangle{
                        width: parent.width
                        height: 100
                        opacity: 0.8
                        color: "red"
                    }
                    Rectangle{
                        width: parent.width
                        height: 100
                        opacity: 0.8
                        color: "green"
                    }
                }

            }
        }
        */

    }

}

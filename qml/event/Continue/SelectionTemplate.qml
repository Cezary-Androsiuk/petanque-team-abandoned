import QtQuick 2.15
import QtQuick.Controls.Material

import "Selection"

Item {
    id: selectionTemplate
    anchors.fill: parent

    required property int selectionType; // 1 - SingielsSelection, 2 - DubletsSelection, 3 - TripletsSelection
    readonly property var event: Backend !== null ? Backend.event : null

    function setExampleData(){
        for(let i=0; i<listView.count; i++)
        {
            let delegate = listView.itemAtIndex(i);
            if(delegate)
            {
                delegate.itemGroupSelection.setExampleData();
                // delegate.itemDubletsGroupSelection.setExampleData();
                // delegate.itemSingielsGroupSelection.setExampleData();
            }
            else{
                log.e("item at index " + i + " not found")
            }
        }
    }

    Item{
        anchors{
            fill: parent
            margins: 30
        }
        clip: true

        ListView{
            id: listView
            anchors.fill: parent

            model: event.match.matchTeams.length // or event.teams.length
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
                height: teamNameField.height + 50
                        + groupSelectionLoader.height;
                        // + tripletsGroupSelection.height
                        // + dubletsGroupSelection.height
                        // + singielsGroupSelection.height

                property alias itemGroupSelection: groupSelectionLoader.item

                Item{
                    id: teamNameField
                    anchors{
                        top: parent.top
                        left: parent.left
                        right: parent.right
                    }
                    height: 60
                    Label{
                        anchors.fill: parent
                        text: (!event)?"": (!event.teams[index])?"": event.teams[index].teamName
                        font.pixelSize: 26
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                Loader{
                    id: groupSelectionLoader
                    anchors{
                        top: teamNameField.bottom
                        left: parent.left
                        right: parent.right
                        margins: 10
                    }
                    sourceComponent: {
                        if(selectionType === 1) singielsGroupSelection; else
                        if(selectionType === 2) dubletsGroupSelection; else
                        if(selectionType === 3) tripletsGroupSelection; else{
                            log.w("unknown selectionType, required 1, 2 or 3")
                        }
                    }
                    onLoaded: {
                        console.log(item.height);
                        height = item.height;
                    }
                }

                Component{
                    id: tripletsGroupSelection
                    GroupSelection{
                        anchors{
                            top: teamNameField.bottom
                            left: parent.left
                            right: parent.right
                            margins: 10
                        }
                        teamIndex: index
                        groupSize: 3
                    }
                }

                Component{
                    id: dubletsGroupSelection
                    GroupSelection{
                        anchors{
                            top: tripletsGroupSelection.bottom
                            left: parent.left
                            right: parent.right
                            margins: 10
                        }
                        teamIndex: index
                        groupSize: 2
                    }
                }


                Component{
                    id: singielsGroupSelection
                    GroupSelection{
                        anchors{
                            top: dubletsGroupSelection.bottom
                            left: parent.left
                            right: parent.right
                            margins: 10
                        }
                        teamIndex: index
                        groupSize: 1
                    }
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


    }

}

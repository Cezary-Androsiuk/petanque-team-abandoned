import QtQuick 2.15
import QtQuick.Controls.Material

import "Selection"

Item {
    id: selection
    anchors.fill: parent

    readonly property var event: Backend !== null ? Backend.event : null

    function verifyData(){
        // console.log("verifyData - selection")
        for(let i=0; i<listView.count; i++)
        {
            let delegate = listView.itemAtIndex(i);
            if(delegate)
            {
                let valid
                valid = delegate.itemTripletsGroupSelection.inputDataAreValid()
                if(!valid)
                    return;

                valid = delegate.itemDubletsGroupSelection.inputDataAreValid()
                if(!valid)
                    return;

                valid = delegate.itemSingielsGroupSelection.inputDataAreValid()
                if(!valid)
                    return;
            }
            else{
                console.log("item at index " + i + " not found")
            }
        }
        selection.verifiedData();
    }
    signal verifiedData();

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
                height: teamNameField.height +
                        tripletsGroupSelection.height +
                        dubletsGroupSelection.height +
                        singielsGroupSelection.height + 50

                property alias itemTripletsGroupSelection: tripletsGroupSelection
                property alias itemDubletsGroupSelection: dubletsGroupSelection
                property alias itemSingielsGroupSelection: singielsGroupSelection

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
                        text: (!event)?"": event.teams[index].teamName
                        font.pixelSize: 26
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                GroupSelection{
                    id: tripletsGroupSelection
                    anchors{
                        top: teamNameField.bottom
                        left: parent.left
                        right: parent.right
                        margins: 10
                    }
                    team: event.teams[index]
                    groupSize: 3
                }

                GroupSelection{
                    id: dubletsGroupSelection
                    anchors{
                        top: tripletsGroupSelection.bottom
                        left: parent.left
                        right: parent.right
                        margins: 10
                    }
                    team: event.teams[index]
                    groupSize: 2
                }

                GroupSelection{
                    id: singielsGroupSelection
                    anchors{
                        top: dubletsGroupSelection.bottom
                        left: parent.left
                        right: parent.right
                        margins: 10
                    }
                    team: event.teams[index]
                    groupSize: 1
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

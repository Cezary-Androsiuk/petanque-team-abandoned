import QtQuick 2.15
import QtQuick.Controls.Material

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
            }
            else{
                log.w("item at index " + i + " not found")
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
                height: teamNameField.height + groupSelection.height + delegateFooter.height;

                property alias itemGroupSelection: groupSelection

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

                GroupSelection{
                    id: groupSelection
                    anchors{
                        top: teamNameField.bottom
                        left: parent.left
                        right: parent.right
                        margins: 10
                    }
                    teamIndex: index
                    groupSize: selectionType
                }

                Item{
                    id: delegateFooter
                    anchors{
                        top: groupSelection.bottom
                        left: parent.left
                        right: parent.right
                    }
                    height: 50
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
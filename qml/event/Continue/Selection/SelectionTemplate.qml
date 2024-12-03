import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: selectionTemplate
    anchors.fill: parent

    required property int matchTypeIndex; // 1 - SingielsSelection, 2 - DubletsSelection, 3 - TripletsSelection
    readonly property var event: Backend ? Backend.event : null
    readonly property var match: event ? event.match : null

    function setExampleData(){
        for(let i=0; i<listView.count; i++)
        {
            let delegate = listView.itemAtIndex(i);
            delegate.itemGroupSelection.setExampleData();
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

            model: selectionTemplate.match.matchTeamList.length // or event.teams.length
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
                        text: {
                            if(!event)
                                return "";

                            if(!event.teams[index])
                                return "";

                            event.teams[index].teamName
                        }

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
                    team: selectionTemplate.event.teams[index]
                    matchTypeIndex: selectionTemplate.matchTypeIndex
                    matchType: selectionTemplate.match.matchTeamList[index].getMatchType(matchTypeIndex)
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

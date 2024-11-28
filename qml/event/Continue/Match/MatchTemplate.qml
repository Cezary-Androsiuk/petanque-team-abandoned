import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: matchTemplate
    anchors.fill: parent

    required property int matchTypeIndex; // 1 - SingielsMatch, 2 - DubletsMatch, 3 - TripletsMatch
    readonly property var event: Backend.event
    readonly property var match: event.match

    function setExampleData(){
        for(let i=0; i<listView.count; i++)
        {
            let delegate = listView.itemAtIndex(i);
            delegate.itemTeamsMatch.setExampleData();
        }
    }

    Item{
        anchors{
            fill: parent
            margins: 30
        }
        clip: true

        ListView {
            id: listView
            anchors.fill: parent

            model: 1//match.matchCombinations.length
            boundsBehavior: Flickable.StopAtBounds
            clip: true
            cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling

            ScrollBar.vertical: ScrollBar{
                policy: ScrollBar.AsNeeded
            }

            delegate: Item{
                width: listView.width - 40
                anchors.horizontalCenter: parent.horizontalCenter
                height: teamsMatch.height

                property alias itemTeamsMatch: teamsMatch

                TeamsMatch{
                    id: teamsMatch
                    anchors{
                        top: parent.top
                        left: parent.left
                        right: parent.right
                    }

                    event: matchTemplate.event
                    combinationIndex: index
                    matchTypeIndex: matchTemplate.matchTypeIndex
                }
            }


        }
    }
}

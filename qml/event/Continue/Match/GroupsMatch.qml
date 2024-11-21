import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: groupsMatch

    required property var team;
    required property var matchTypes;
    required property int matchTypeIndex; // 1 - SingielsMatch, 2 - DubletsMatch, 3 - TripletsMatch

    readonly property var matchType: {
        if(matchTypeIndex === 1)         matchTypes.singiels;
        else if(matchTypeIndex === 2)    matchTypes.dublets;
        else /* matchTypeIndex === 3 */  matchTypes.triplets;
    }
    onMatchTypeChanged: console.log("changed to: "+ matchType, matchType.groupsCount, matchType.playersCount)

    readonly property int groupsCount: matchType.groupsCount;
    readonly property int playersCountInGroup: matchTypeIndex // for now value //matchType.playersCountInGroup // ? can be 1 for singiels, 2 or 3 for dublets and 3 or 4 for triplets
    readonly property int playerDelegateHeight: 60;
    readonly property int groupHeaderHeight: 60
    readonly property int groupDelegateHeight: playerDelegateHeight * playersCountInGroup;

    height: groupHeaderHeight + ( (groupDelegateHeight + (10*2)) * groupsCount )

    ListView{
        id: groupsListView
        anchors.fill: parent

        model: groupsMatch.groupsCount
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        interactive: false
        cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling

        header: Item{
            width: groupsListView.width
            height: groupsMatch.playerDelegateHeight

            Label{
                id: leftTeamName
                anchors.centerIn: parent
                height: 50
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                text: team.teamName
            }
        }

        delegate: Item{
            id: delegateItem
            width: groupsListView.width
            height: groupsMatch.groupDelegateHeight + playersListViewContainer.anchors.margins*2

            readonly property int groupIndex: index

            Item{
                id: playersListViewContainer
                anchors{
                    fill: parent
                    margins: 10
                }

                ListView{
                    id: playersListView
                    anchors.fill: parent

                    model: groupsMatch.playersCountInGroup
                    boundsBehavior: Flickable.StopAtBounds
                    clip: true
                    interactive: false
                    cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling

                    delegate: Item{
                        width: groupsListView.width - playersListViewContainer.anchors.margins*2
                        height: groupsMatch.playerDelegateHeight

                        Rectangle{
                            anchors.fill: parent
                            color: "transparent"
                            border.color: Qt.rgba(1,1,1, 0.4)
                            border.width: 1
                        }
                    }
                }
            }

            Rectangle{
                anchors.fill: parent
                color: "transparent"
                border.color: Qt.rgba(1,1,1, 0.4)
                border.width: 1
            }

        }

    }

}

import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: groupsMatch

    required property var team;
    required property var matchTeam;
    required property int matchTypeIndex; // 1 - SingielsMatch, 2 - DubletsMatch, 3 - TripletsMatch

    readonly property int groupsCount: {
        if(matchTypeIndex === 1)         6;
        else if(matchTypeIndex === 2)    3;
        else /* matchTypeIndex === 3 */  2;
    }
    readonly property int groupsSize: matchTypeIndex
    readonly property int playerDelegateHeight: 60;
    readonly property int groupDelegateHeight: playerDelegateHeight * groupsSize;

    height: (groupDelegateHeight + (10*2)) * groupsCount

    ListView{
        id: groupsListView
        anchors.fill: parent

        model: groupsMatch.groupsCount
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        interactive: false
        cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling

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

                    model: groupsMatch.groupsSize
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

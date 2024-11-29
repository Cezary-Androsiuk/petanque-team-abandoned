import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: groupsMatch

    property bool isLeft: true; // default is left

    required property var team;
    required property var matchTeam;
    required property var matchType;
    required property int matchTypeIndex; // 1 - SingielsMatch, 2 - DubletsMatch, 3 - TripletsMatch

    readonly property var matchPoints: matchType.matchPoints;
    readonly property int groupsCount: matchPoints.groupsCount;
    readonly property int playersCountInGroup: matchTypeIndex // for now value //matchType.playersCountInGroup // ? can be 1 for singiels, 2 or 3 for dublets and 3 or 4 for triplets
    readonly property int playerDelegateHeight: 60;
    readonly property int groupHeaderHeight: 60
    readonly property int groupDelegateHeight: playerDelegateHeight * playersCountInGroup;

    height: groupHeaderHeight + ( (groupDelegateHeight + (10*2)) * groupsCount )

    function setPFP(row, value) { matchPoints.setPointsForGroup(row, value); }

    function setExampleData(){

    }

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

            Item{
                id: spinBoxField
                anchors{
                    top: parent.top
                    bottom: parent.bottom
                    right: groupsMatch.isLeft ? parent.right : undefined
                    rightMargin: groupsMatch.isLeft ? 10 : 0
                    left: groupsMatch.isLeft ? undefined : parent.left
                    leftMargin: groupsMatch.isLeft ? 0 : 10
                }
                width: spinBox.width

                Rectangle{
                    anchors.fill: spinBox
                    color: Qt.rgba(0.8,0,0, 0.6)
                    visible: spinBox.value > 31
                }

                SpinBox{
                    id: spinBox
                    anchors{
                        verticalCenter: parent.verticalCenter
                        right: groupsMatch.isLeft ? parent.right : undefined
                        left: groupsMatch.isLeft ? undefined : parent.left
                    }

                    editable: true
                    to: 999

                    value: groupsMatch.matchPoints.points[index]
                    onValueChanged: {
                        groupsMatch.setPFP(index, value);
                        focus = false; // prevents keeping spinbox constantly selected
                    }
                }
            }

            readonly property int groupIndex: index

            Item{
                id: playersListViewContainer
                anchors{
                    top: parent.top
                    bottom: parent.bottom
                    right: groupsMatch.isLeft ? spinBoxField.left : parent.right
                    left: groupsMatch.isLeft ? parent.left : spinBoxField.right
                    margins: 10
                }

                // ListView{
                //     id: playersListView
                //     anchors.fill: parent

                //     model: groupsMatch.playersCountInGroup
                //     boundsBehavior: Flickable.StopAtBounds
                //     clip: true
                //     interactive: false
                //     cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling

                //     delegate: Item{
                //         width: groupsListView.width - playersListViewContainer.anchors.margins*2
                //         height: groupsMatch.playerDelegateHeight


                //         Rectangle{
                //             anchors.fill: parent
                //             color: "transparent"
                //             border.color: Qt.rgba(1,1,1, 0.4)
                //             border.width: 1
                //         }
                //     }
                // }

                Rectangle{
                    anchors.fill: parent
                    color: "red"
                    opacity: 0.2
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

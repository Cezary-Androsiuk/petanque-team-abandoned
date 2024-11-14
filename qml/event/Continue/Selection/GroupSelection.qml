import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: groupSelection
    required property int teamIndex;
    required property int groupSize; // 1, 2 or 3

    readonly property var team: event.teams[teamIndex];
    readonly property var matchTeam: event.match.matchTeams[teamIndex];
    readonly property var currentMatchType: {
        if(groupSize === 3)         matchTeam.triplets;
        else if(groupSize === 2)    matchTeam.dublets;
        else /* groupSize === 1 */  matchTeam.singiels;
    }
    readonly property var selectionArray: currentMatchType.selection
    readonly property var selectionArrayRows: currentMatchType.rows
    readonly property var selectionArrayColumns: currentMatchType.columns
    readonly property string groupsSelectionName: {
        if(groupSize === 3)         "Triplets";
        else if(groupSize === 2)    "Dublets";
        else /* groupSize === 1 */  "Singiels";
    }


    // readonly property int groupsCount: {
    //     if(groupSize === 3)         2;
    //     else if(groupSize === 2)    3;
    //     else /* groupSize === 1 */  6;
    // }

    readonly property int delegateHeight: 30;
    readonly property int headerHeight: 60;
    readonly property int footerHeight: 30;
    readonly property int playersCount: selectionArray.length
    readonly property int groupSelectionHeight: playersCount * delegateHeight + headerHeight + footerHeight

    height: groupSelectionHeight

    function setExampleData(){
        var i,j,h;

        for(i=0; i<selectionArrayRows; i++)
        {
            for(j=0; j<selectionArrayColumns; j++)
            {
                currentMatchType.setSelectionCell(i, j, true);
            }
        }
    }


    ListView{
        id: listView
        anchors.fill: parent

        model: selectionArray.length
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        interactive: false
        cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling

        footer: Item{
            width: listView.width
            height: footerHeight
        }

        header: Item{
            width: listView.width
            height: headerHeight

            Item{
                id: groupsSelectionNameTitle
                anchors{
                    top: parent.top
                    left: parent.left
                    right: parent.right
                }
                height: parent.height/2

                Label{
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 18 // default is 14
                    text: groupSelection.groupsSelectionName
                }
                Item{
                    id: exampleSelectionButtonField
                    anchors{
                        top: parent.top
                        left: parent.left
                        bottom: parent.bottom
                    }
                    width: 3* height

                    Button{
                        id: exampleSelectionButton
                        anchors.fill: parent
                        onClicked: {
                            setExampleData();
                        }
                    }

                    Label{
                        id: exampleSelectionButtonText
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 14
                        text: "Set Example"
                    }

                }

                Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                    border.color: Qt.rgba(1,1,1, 0.4)
                    border.width: 1
                }
            }

            Row{
                anchors{
                    top: groupsSelectionNameTitle.bottom
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }

                spacing: 0

                Label{
                    width: 140
                    height: parent.height
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 16 // default is 14
                    text: "Player Info"
                }

                Repeater{
                    model: groupSelection.selectionArrayColumns
                    Item{
                        height: parent.height
                        width: 140
                        Rectangle{
                            anchors.fill: parent
                            color: Qt.rgba(1,1,1, (8-(index+1))/14)
                        }

                        Label{
                            anchors.fill: parent
                            width: 140
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: 16 // default is 14
                            text: "Group " + (index+1)
                        }
                    }
                }
            }

            Rectangle{
                anchors.fill: parent
                color: "transparent"
                border.color: Qt.rgba(1,1,1, 0.2)
                border.width: 1
            }
        }

        delegate: Item{
            width: listView.width
            height: delegateHeight

            Row{
                id: row
                anchors.fill: parent
                spacing: 0

                readonly property int parentIndex: index

                Label{
                    id: playerInfo
                    width: 140
                    height: parent.height
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    // pixelSize is 14
                    text: modelData.fname + " " + modelData.lname
                }
                Repeater{
                    id: radioButtons
                    model: groupSelection.selectionArrayColumns
                    RadioButton{
                        id: radioButton
                        width: 140
                        height: parent.height
                        // text: "group " + (row.parentIndex+1) +  "" + (index+1)

                        // disable row exclusive
                        autoExclusive: false

                        // uncheck mechanic
                        property bool wasCheckedWhilePressing: false
                        onPressed: {
                            wasCheckedWhilePressing = checked
                        }
                        onClicked: {
                            if(wasCheckedWhilePressing)
                                checked = false
                        }

                        checked: groupSelection.selectionArray[row.parentIndex][index]
                        onCheckedChanged: {
                            groupSelection.currentMatchType.setSelectionCell(row.parentIndex, index, checked)
                        }
                    }
                }
            }

            Rectangle{
                anchors.fill: parent
                color: "transparent"
                border.color: Qt.rgba(1,1,1, 0.2)
                border.width: 1
            }


        }

    }



    Rectangle{
        anchors.fill: parent
        color: "transparent"
        border.color: Qt.rgba(1,1,1, 0.5)
        border.width: 1
    }

}

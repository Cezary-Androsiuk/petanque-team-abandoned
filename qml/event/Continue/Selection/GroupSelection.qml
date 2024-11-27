import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: groupSelection
    required property var team;
    required property var matchTeam;
    required property var matchType;
    required property int matchTypeIndex; // 1, 2 or 3

    readonly property var selection: matchType.selection
    readonly property var matrixRows: selection.rows
    readonly property var matrixColumns: selection.columns

    readonly property int delegateHeight: 30;
    readonly property int headerHeight: 30;
    readonly property int footerHeight: 30;
    readonly property int groupSelectionHeight: matrixRows * delegateHeight + headerHeight + footerHeight

    height: groupSelectionHeight

    function setSC(row, column, value){ selection.setValueForCell(row, column, value); }

    function setExampleData(){
        var i,j,h;

        // turn off all rows
        for(i=0; i<matrixRows; i++)
        {
            // (using mechanic that uncheck rest of the radioButtons)
            setSC(i, 0, true);
            setSC(i, 0, false);
        }

        // depends on the type set example data
        if(matchTypeIndex === 3)
        {
            setSC(0, 0, true); setSC(1, 0, true); setSC(2, 0, true); // group 1
            setSC(3, 1, true); setSC(4, 1, true); setSC(5, 1, true); // group 2
        }
        else if(matchTypeIndex === 2)
        {
            setSC(0, 0, true); setSC(1, 0, true); // group 1
            setSC(2, 1, true); setSC(3, 1, true); // group 2
            setSC(4, 2, true); setSC(5, 2, true); // group 3
        }
        else /* matchTypeIndex === 1 */
        {
            setSC(0, 0, true); // group 1
            setSC(1, 1, true); // group 2
            setSC(2, 2, true); // group 3
            setSC(3, 3, true); // group 4
            setSC(4, 4, true); // group 5
            setSC(5, 5, true); // group 6
        }

    }


    ListView{
        id: listView
        anchors.fill: parent

        model: groupSelection.matrixRows
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
            height: groupSelection.headerHeight

            Row{
                anchors.fill: parent

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
                    model: groupSelection.matrixColumns
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
            id: rowDelegate
            width: listView.width
            height: groupSelection.delegateHeight

            readonly property int rowIndex: index

            Row{
                id: row
                anchors.fill: parent
                spacing: 0


                Label{
                    id: playerInfo
                    width: 140
                    height: parent.height
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    // pixelSize is 14
                    text: {
                        if(!groupSelection.team)
                            "";
                        else{
                            var player = groupSelection.team.players[rowDelegate.rowIndex];
                            player.fname + " " + player.lname;
                        }
                    }
                }
                Repeater{
                    id: radioButtons
                    model: groupSelection.matrixColumns


                    RadioButton{
                        id: radioButton
                        readonly property int colIndex: index
                        width: 140
                        height: parent.height
                        // text: "group " + (rowDelegate.rowIndex+1) +  "" + (radioButtons.colIndex+1)

                        // disable row exclusive // will be handled in backend
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

                        checked: groupSelection.selection.values[rowDelegate.rowIndex][radioButton.colIndex]
                        onCheckedChanged: {
                            groupSelection.setSC(rowDelegate.rowIndex, radioButton.colIndex, checked)
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

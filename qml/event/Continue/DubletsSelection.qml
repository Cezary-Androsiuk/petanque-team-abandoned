import QtQuick 2.15

import "Selection"

Item {
    id: dubletsSelection
    anchors.fill: parent

    function setExampleData(){
        selectionTemplate.setExampleData()
    }

    SelectionTemplate{
        id: selectionTemplate
        matchTypeIndex: 2
    }
}

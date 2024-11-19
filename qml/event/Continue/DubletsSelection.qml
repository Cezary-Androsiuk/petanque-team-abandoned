import QtQuick 2.15

import "Selection"

Item {
    id: singielsSelection
    anchors.fill: parent

    function setExampleData(){
        selectionTemplate.setExampleData()
    }

    SelectionTemplate{
        id: selectionTemplate
        selectionType: 2
    }
}

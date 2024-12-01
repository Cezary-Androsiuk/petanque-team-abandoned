import QtQuick 2.15
import QtQuick.Controls.Material

Item{
    id: configure
    anchors.fill: parent

    readonly property int transitionTime: 200

    component LineAnimation: NumberAnimation {
        duration: transitionTime
        easing.type: Easing.OutCubic
    }

    component StayStillAnimation: NumberAnimation{
        duration: transitionTime
    }

    component FadeIn: LineAnimation {
        property: "opacity"
        from: 0.0
        to: 1.0
    }

    component FadeOut: LineAnimation {
        property: "opacity"
        from: 1.0
        to: 0.0
    }

    Component.onCompleted: {
        const args = {parentStackView: configureStackView}
        configureStackView.replace("Configure/Event.qml", args)
        rootWindow.minimumWidth = 500;
        rootWindow.minimumHeight = 350;
    }

    StackView{
        id: configureStackView
        anchors.fill: parent
        // initialItem: "Configure/Event.qml" // idk how to parse arguments/properies


        pushEnter: Transition{
            // LineAnimation {
            //     property: "y";
            //     from: -configure.height;
            //     to: 0
            // }
            // FadeIn{}
        }
        pushExit: Transition{
            // StayStillAnimation{}
        }
        popEnter: Transition{
            // StayStillAnimation{}
        }
        popExit: Transition{
            // LineAnimation {
            //     property: "y";
            //     from: 0
            //     to: -configure.height;
            // }
            // FadeOut{}
        }
        replaceEnter: Transition{}
        replaceExit: Transition{}
    }
}

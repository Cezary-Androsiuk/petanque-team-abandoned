import QtQuick 2.15
import QtQuick.Controls.Material

Item{
    id: start
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

    StackView{
        id: startStackView
        anchors.fill: parent
        initialItem: "Start/StartEvent.qml"

        pushEnter: Transition{
            LineAnimation {
                property: "y";
                from: -startStackView.height;
                to: 0
            }
            FadeIn{}
        }
        pushExit: Transition{
            StayStillAnimation{}
        }
        popEnter: Transition{
            StayStillAnimation{}
        }
        popExit: Transition{
            LineAnimation {
                property: "y";
                from: 0
                to: -startStackView.height;
            }
            FadeOut{}
        }
    }
}


import Qt 4.7

Item {
    property alias color : rectangle.color
    property alias border: rectangle.border
    property alias shadowIntensity: shadow.opacity

    BorderImage {
        id: shadow
        anchors.fill: rectangle
        anchors { leftMargin: -6; topMargin: -6; rightMargin: -8; bottomMargin: -8 }
        border { left: 10; top: 10; right: 10; bottom: 10 }
        source: "qrc:///img_source/visuallayer/img/shadow.png"; smooth: true
        opacity:0.5
    }

    Rectangle { id: rectangle; anchors.fill: parent}
}

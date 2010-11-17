import Qt 4.7

Item {
    id: resizer
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    width: 20
    height: 20

    Rectangle {
        id: rectangle1
        color: "transparent"
        anchors.fill: parent
    }

    Image {
        id: closeIcon
        fillMode: Image.PreserveAspectFit
        anchors.fill: parent
        source: "qrc:///img_source/visuallayer/img/resizer.png"
    }

    MouseArea{
        id:resizeArea
        anchors.fill: parent
        onPositionChanged: {

            qmlInterface.setMainSize()
        }
        onReleased: qmlInterface.resetSizeCursor()
    }
}

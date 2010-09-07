import Qt 4.7
import "elements"


Item {
    id: listView
    property alias listmodel: mainList.model
    property color backgroundColor1: "gray"
    property color backgroundColor2: backgroundColor1
    property int backgroundColorRotation: 0
    property double backgroundOpacity: 1.0
    property color itemColor1: "lightgrey"
    property color itemColor2: itemColor1
    property double itembackgroundOpacity: 1.0
    property int itemColorRotation: 0
    property color highlightColor1: "lightsteelblue"
    property color highlightColor2: highlightColor1
    property int highlightColorRotation: 0
    property int contextDelayTime: 300
    property int contextShowWidth: 250
    property alias contextHideWidth: listView.width
    property int itemRadius: 4

    property alias currentIndex: mainList.currentIndex
    property alias currentItem: mainList.currentItem
    /*property list of informations provided by the current item of mainList*/
    property string currentItemName
    property string currentItemFilePath



    width: 15
    anchors { left: parent.left; top: parent.top; bottom: parent.bottom }

    Image {
        id: arrow
        source: "img/arrow.png"
        rotation: 90
        anchors.verticalCenter: parent.verticalCenter
    }

    Rectangle {
        id: listViewBox
        width: 12
        color: "transparent"
        clip: true
        opacity: 0.0
        Rectangle{
            id:background
            anchors.fill:parent
            opacity: backgroundOpacity
            gradient: Gradient {
                    GradientStop { position: 0.0; color:  backgroundColor1}
                    GradientStop { position: 1.0; color:  backgroundColor2 }
            }
        }
        anchors { left: parent.left; top: parent.top; bottom: parent.bottom }


        /*ListView definition*/
        ListView {
            id: mainList
            anchors.fill: listViewBox
            //model: imageDataModel
            delegate: ImageListDelegate {}
            highlight: highlight; highlightFollowsCurrentItem: true
            focus: true
            onCurrentIndexChanged: {
                currentItemName = currentItem.fileName
                currentItemFilePath = currentItem.filePath
                //qmlInterface.index = currentIndex

            }
         }

        states: [
            State {
                name: "shown"
                PropertyChanges {
                    target: listViewBox
                    width: contextShowWidth
                    opacity: 1.0
                }
                PropertyChanges {
                    target: arrow
                    opacity: 0.0
                }
            }
        ]
        transitions: [

            Transition {
                from: ""
                to: "shown"
                reversible: true
                NumberAnimation { target: listViewBox; property: "width"; duration: 400; easing.type: "OutBack" }
                NumberAnimation { properties: "opacity"; duration: 300 }
            }
        ]
        /*this Area is used to hide the context menu when the mouse leave the context area*/
        MouseArea {
            z: -1
            anchors.fill:parent
            hoverEnabled: true
            enabled: true
            onExited: {
                //console.log ("exited " )
                listViewBox.state = ""
            }
        }
    }
    /*the timer is used to delay the appearance of the context menu*/
    Timer {
        id: timer
        interval: contextDelayTime;
        onTriggered: {
            //console.log ("time elapsed")
            listViewBox.state = "shown"
        }
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            timer.start()
            //console.log ("timer started ")
        }
        onExited: {
            timer.stop()
            //console.log ("timer stopped " )
        }
    }

    Component {
        id: highlight
        Rectangle {
            width: mainList.width; //height: labelHeight
            radius: itemRadius
            gradient: Gradient {
                    GradientStop { position: 0.0; color:  highlightColor1}
                    GradientStop { position: 1.0; color:  highlightColor2 }
                 }
            //y: mainList.currentItem.y
            //SpringFollow on y { to: mainList.currentItem.y; spring: 3; damping: 0.2 }

        }
    }



}

import Qt 4.7
import "elements"
Item {
    id: mainUiLayer
    width: 640
    height: 480

    property double main_opacity : qmlInterface.main_opacity
    property color main_color : qmlInterface.main_color


    CustomTitleBar{
        id: qimTitleBar
        Connections{
            target: qmlInterface
            onMainTitleChanged: qimTitleBar.title = new_title
        }

    }

    CustomMenuBar{
        id:qimMenuBar
        z:1
        anchors.top: qimTitleBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 40
        anchors.rightMargin: 40
        height: 20
        opacity: 0.5
    }

    CustomWindowResizer{
        id: resizer
        z:1
    }


    Item {
        id: mainContent
        anchors.top: qimTitleBar.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        Rectangle{
            id: mainContentBackground
            anchors.fill: parent
            color: main_color
            opacity: main_opacity
        }

        Loader{
            id: mainContentLoader
            anchors.fill: parent
            source: "QimDefaultLayer.qml"

            Connections{
                target: qmlInterface
                onActiveLayerChanged:{
                    console.log ("new layer is " + new_layer)
                    mainContentLoader.source = new_layer
                }


            }

        }

    }

}

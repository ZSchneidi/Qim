//import "QmlInterface" 1.0
import Qt 4.7
import "elements"


 Rectangle {
     id: page
     width: 640; height: 480
     color: "#D8D8D8"
     //property int currentIndex: index

    ContextListView {
         id: listView
         listmodel: imageDataModel
         currentIndex: qmlInterface.index
         z: 1
         backgroundColor1: "#a2a2a2"
         backgroundColor2: "#cacacf"
         itemColor1: "grey"
         itemColor2: "lightgray"
         backgroundOpacity: 0.2
         highlightColor1: "#a2a2a2"
         highlightColor2: "#cacacf"
         itembackgroundOpacity: 0.9
         Connections {
             target: qmlInterface
             //onIndexChanged: console.log("foo")
         }
     }

    Item {
        id: mainView
        property int image_width: page.width
        property int image_height: page.height

        ShadowBox{
            id: imageLabel
            color: "#E5E5E5"
            shadowIntensity: 0.5
            anchors.centerIn: parent
            anchors.margins: 10
            width: 800
            height: 500
            opacity: 0.0

            Image {
                id: mainpicture
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: listView.currentItemFilePath
                onSourceChanged:
                        {
                    console.log("page size " + page.width + ":" + mainView.image_height )
                }
                /*define the picture size in the view*/
                onWidthChanged:
                        {
                        console.log("size changed: "+ mainpicture.sourceSize.width)
                        imageLabel.opacity = 1
                    }
                Connections {
                    target: qmlInterface
                    onZoomIn:
                            {
                           console.log("zoomed IN "+mainpicture.width/2)
                           mainpicture.width = (mainpicture.width/2)
                           mainpicture.height = (mainpicture.height/2)
                    }
                }
            }
        }
    }




     Text {
         id: info
         anchors.horizontalCenter: parent.horizontalCenter
         anchors.bottom: parent.bottom

         color: icolor
         text:
                //"index " + listView.currentItemFilePath
                 "index is : " + qmlInterface.index
     }

 }

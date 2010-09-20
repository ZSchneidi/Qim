//import "QmlInterface" 1.0
import Qt 4.7
import "elements"


 Rectangle {
     id: page
     //width: 640; height: 480
     color: "#D8D8D8"
     //property int currentIndex: index

    ContextListView {
         id: listView
         /*as listmodel the image data model from coreengine is called
          *the definition can be found in ImageHandler::initImageDataModel()
          *and in the imagedatamodel class
          */
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


         ShadowBox{
             id: imageLabel
             color: "#E5E5E5"
             shadowIntensity: 0.5
             anchors.centerIn: parent
             anchors.margins: 10
             width: mainpicture.sourceSize.width
             height: mainpicture.sourceSize.height
             opacity: 0.0

             Image {
                 id: mainpicture
                 anchors.fill: parent
                 fillMode: Image.PreserveAspectFit
                 source: listView.currentItemFilePath
                 onSourceChanged:
                         {
                         console.log("load: "+listView.currentItemFilePath)
                         console.log("height "+ sourceSize.height)
                         //console.log("width "+ )
                         width: sourceSize.width/2
                         height: sourceSize.height/2
                 }
                 /*define the picture size in the view*/

                 //sourceSize.width:800
                 //sourceSize.height:500
                 onSourceSizeChanged:
                         {
                         //console.log("filepath: "+listView.currentItemFilePath)
                         imageLabel.opacity = 1
                     }
             }

         }
//     }


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

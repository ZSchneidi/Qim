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
         currentIndex: qmlInterface.currIndex
         z: 1
         backgroundColor1: "#a2a2a2"
         backgroundColor2: "#cacacf"
         itemColor1: "grey"
         itemColor2: "lightgray"
         backgroundOpacity: 0.2
         highlightColor1: "#a2a2a2"
         highlightColor2: "#cacacf"
         itembackgroundOpacity: 0.9

     }

     /*ListView {
         id: list
          width: 180; height: 200
          highlight: Rectangle { color: "white" }
          model: imageDataModel
          focus:true
          delegate: Text { text: name + path }
      }*/

 /*   Flickable {
        id: flickView
        contentWidth: imageLabel.width; contentHeight: imageLabel.height
        anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter
*/

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
                "index " + listView.currentItemFilePath
     }

 }

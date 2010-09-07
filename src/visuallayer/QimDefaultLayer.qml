import Qt 4.7
import "elements"

Rectangle {
    width: 640
    height: 480
    color: "#D8D8D8"

    Text {
        id: infotext
        anchors.centerIn: parent
        text: "no image data loaded"
    }
/*
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
            source: "N:/Projekte/Qt/Qim/src/demo-data/demo-2.jpg"
            onSourceChanged:
                    {
                //console.log("height "+page.height)
            }
            //sourceSize.width:800
            //sourceSize.height:500
            onSourceSizeChanged:
                    {
                    //console.log("filepath: "+listView.currentItemFilePath)
                    imageLabel.opacity = 1
                }
        }

    }
*/
}

import Qt 4.7

Rectangle {
    id: detail
    Text {id: detailsTitle; x: 10; font.pixelSize: 12; text: 'Details'}
    Text {id:width_txt; x: 10; anchors.top: detailsTitle.bottom; font.pixelSize: 12; text: '<b>width</b> ' + m_width }
    Text {id:heigth_txt; x: 10; anchors.top: width_txt.bottom; font.pixelSize: 12; text: '<b>heigth</b> ' + m_height }


}



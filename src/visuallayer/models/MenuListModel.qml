import Qt 4.7

 ListModel {
     id: fileMenuModel

     ListElement {
         name: "Open"
         signal: 1
     }
     ListElement {
         name: "Save"
         signal: 2
     }
     ListElement {
         name: "Exit"
         signal: 3
     }
 }

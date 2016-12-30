import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2

ToolBar {
    RowLayout {
        anchors.fill: parent

        Item { Layout.preferredWidth: 10}

        RowLayout {
            ComboBox {
                currentIndex: 0
                model: ListModel {
                    id: cbItems
                    ListElement { text: "Font1";}
                    ListElement { text: "Font2";}
                    ListElement { text: "Font3";}
                }
                width: 200
                onCurrentIndexChanged: ;
            }

            TextField {
                text: "10"
            }

            ToolButton {
                id: boldButton
                text: "B" // icon-bold
                checkable: true
                checked: false
                onClicked: ;
                Layout.preferredWidth: 30
                style: ButtonStyle {
                    label: Text {
                        text: control.text
                        font.bold: true
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }
            ToolButton {
                id: italicButton
                text: "I" // icon-italic
                checkable: true
                checked: false
                onClicked: ;
                Layout.preferredWidth: 30
                style: ButtonStyle {
                    label: Text {
                        text: control.text
                        font.italic: true
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }
            ToolButton {
                id: underlineButton
                text: "U" // icon-underline
                checkable: true
                checked: false
                onClicked: ;
                Layout.preferredWidth: 30
                style: ButtonStyle {
                    label: Text {
                        text: control.text
                        font.underline: true
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }
        }


        RowLayout {
            TextField {
                text: ""
            }
            ToolButton {
                text: "Find"
            }
        }
    }
}



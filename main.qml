import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2


ApplicationWindow {
    title: qsTr("Text Editor")
    width: 1000
    height: 1000
    visible: true

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Open")
                onTriggered: messageDialog.show(qsTr("Open action triggered"));
            }
            MenuItem {
                text: qsTr("Save")
                onTriggered: messageDialog.show(qsTr("Save action triggered"));
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
        Menu {
            title: qsTr("Edit")
            MenuItem {
                text: qsTr("Cut")
                onTriggered: messageDialog.show(qsTr("Cut action triggered"));
            }
            MenuItem {
                text: qsTr("Copy")
                onTriggered: messageDialog.show(qsTr("Copy action triggered"));
            }
            MenuItem {
                text: qsTr("Paste")
                onTriggered: messageDialog.show(qsTr("Paste action triggered"));
            }
        }
    }

    toolBar : ToolBar {
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

    Rectangle
    {
        anchors.fill: parent
        color: "white"
        objectName: "rect"


        Canvas {
            property string test: ""
            focus: true

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    viewer.OnMouseClicked(mouseX, mouseY);
                    mouse.accepted = true;
                }
                onPositionChanged: {
                    if (pressedButtons & Qt.LeftButton)
                        viewer.OnMouseDragged(mouseX, mouseY);
                }
                onReleased: {
                    viewer.OnMouseReleased();
                    mouse.accepted = true;
                }
            }

            Keys.onPressed:
            {
                if (event.key === Qt.Key_Left || event.key === Qt.Key_Right ||
                        event.key === Qt.Key_Up || event.key === Qt.Key_Down)
                    viewer.OnKeyPressed(event.key);
                else
                    viewer.OnKeyTyped(event.key);
                event.accepted = true;
            }

            function test()
            {
                return "this is coming from gui";
            }

            objectName: "canvas"
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d");
                ctx.reset();

                var centreX = width / 2;
                var centreY = height / 2;
                ctx.font = "20px arial";
                ctx.beginPath();
                ctx.text(test, centreX, centreY);
                ctx.stroke();

                ctx.font = "10px arial";
                ctx.text(test, centreX, centreY+20);
                ctx.stroke();
            }


        }

    }
}


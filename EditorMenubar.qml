import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2

MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Open")
                onTriggered: {
                    viewer.OnLoadFile("C:/Users/dstoeg/JKU/SystemSoftware/editor/test.txt");
                }

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
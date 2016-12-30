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
                onTriggered: {
                    viewer.OnSaveFile("");
                }
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
                onTriggered: viewer.OnCut();
            }
            MenuItem {
                text: qsTr("Copy")
                onTriggered: viewer.OnCopy();
            }
            MenuItem {
                text: qsTr("Paste")
                onTriggered: viewer.OnPaste();
            }
        }
    }

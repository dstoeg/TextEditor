import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2
import QtQuick.Dialogs 1.0


MenuBar {
    Menu {
        title: qsTr("File")
        MenuItem {
            id: openAction;
            text: qsTr("Open")
            onTriggered: {
                fileDialog.openFile();
            }

        }
        MenuItem {
            id: saveAction;
            text: qsTr("Save")
            onTriggered: {
                fileDialog.saveFile();
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




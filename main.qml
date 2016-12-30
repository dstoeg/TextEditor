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

    menuBar : EditorMenubar { }

    toolBar : EditorToolbar { }

    Rectangle
    {
        anchors.fill: parent
        color: "white"
        objectName: "rect"

        EditorCanvas { }
    }
}


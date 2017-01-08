import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2


ApplicationWindow {
    title: qsTr("Text Editor")
    width: 1000
    height: 1200
    visible: true
    minimumWidth: 1000;
    maximumWidth: 1000;
    //minimumHeight: 1200;
    //maximumHeight: 1200;

    menuBar : EditorMenubar { }

    toolBar : EditorToolbar { }

    Rectangle
    {
        anchors.fill: parent
        color: "white"
        objectName: "rect"

        EditorCanvas { }
    }

    property bool isloadAction : true;

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        visible: false
        selectMultiple: false


        onAccepted: {
            if (isloadAction)
                viewer.OnLoadFile(fileDialog.fileUrl);
            else
                viewer.OnSaveFile(fileDialog.fileUrl);
        }

        function openFile()
        {
            fileDialog.selectExisting = true;
            isloadAction = true;
            fileDialog.open();
        }

        function saveFile()
        {
            fileDialog.selectExisting = false;
            isloadAction = false;
            fileDialog.open();
        }
    }
}


import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2

ToolBar {
    RowLayout {
        anchors.fill: parent

        Item { Layout.preferredWidth: 5}

        RowLayout {

            ComboBox {
                currentIndex: 0
                Layout.preferredWidth: 180
                model: ListModel {
                    id: cbItems

                    ListElement { text: "Calibri";}
                    ListElement { text: "Garamond";}
                    ListElement { text: "Impact";}
                    ListElement { text: "Verdana";}
                    ListElement { text: "Arial";}
                }

                onCurrentIndexChanged: viewer.OnFontChanged(currentText);
            }

            ComboBox {
                currentIndex: 0
                Layout.preferredWidth: 80

                model: ListModel {
                    id: cbSize

                    ListElement { text: 10;}
                    ListElement { text: 20;}
                    ListElement { text: 30;}
                    ListElement { text: 40;}
                    ListElement { text: 50;}
                }

                onCurrentIndexChanged: viewer.OnFontSizeChanged(currentText);
            }

            function styleChanged()
            {
                viewer.OnFontStyleChanged(boldButton.checked, italicButton.checked, underlineButton.checked);
            }

            ToolButton {
                id: boldButton
                text: "B" // icon-bold
                checkable: true
                checked: false
                onClicked: parent.styleChanged();
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
                onClicked: parent.styleChanged();
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
                onClicked: parent.styleChanged();
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
            property string text: ""

            TextField {
                onTextChanged: parent.text = text;
            }
            ToolButton {
                text: "Find"
                onClicked: viewer.OnFind(parent.text);
            }
        }
    }
}



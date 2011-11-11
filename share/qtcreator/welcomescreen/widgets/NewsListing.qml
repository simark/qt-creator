/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**************************************************************************/

import QtQuick 1.1
import qtcomponents 1.0 as Components

Item {
    id: root

    property int currentItem: 0
    property alias model: view.model
    property alias itemCount: view.count

    Timer {
        id: nextItemTimer
        repeat: true
        interval: 30*1000
        onTriggered: view.incrementCurrentIndex()
    }

    Timer {
        id: modelUpdateTimer
        repeat: false
        interval: 1000
        onTriggered: view.handleModelUpdate();
    }

    ListView {
        id: view

        function handleModelUpdate() {
            nextItemTimer.stop();
            currentIndex = 0;
            nextItemTimer.start();
        }

        function handleModelChanged() {
            modelUpdateTimer.restart();
        }

        anchors.fill: parent
        highlightMoveDuration: 1 // don't show any scrolling
        keyNavigationWraps: true // start from 0 again if at end
        interactive: false

        onModelChanged: handleModelChanged()

        delegate: Item {
            id: delegateItem
            property bool active: ListView.isCurrentItem
            opacity: 0
            height: root.height
            width: root.width
            Column {
                spacing: 10
                width: parent.width
                id: column
                Text {
                    id: heading1;
                    text: title;
                    font.bold: true;
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere;
                    textFormat: Text.RichText;
                    width: parent.width-icon.width-16
                }
                Row {
                    spacing: 5
                    width: parent.width
                    Image {
                        id: icon;
                        source: blogIcon;
                        asynchronous: true
                    }
                    Text {
                        id: heading2;
                        text: blogName;
                        font.italic: true;
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere;
                        textFormat: Text.RichText;
                        width: parent.width-icon.width-5
                    }
                }
                Text {
                    id: text;
                    text: description;
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    textFormat: Text.RichText
                    width: parent.width-10
                }
                Text { visible: link !== "";
                    id: readmore;
                    text: qsTr("Click to read more...");
                    font.italic: true;
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere;
                    textFormat: Text.RichText
                    width: parent.width-10
                }
            }
            Components.QStyleItem {
                id: styleItem;
                cursor: "pointinghandcursor";
                anchors.fill: column
                visible: link !== ""
            }
            Timer {
                id: toolTipTimer
                interval: 500
                onTriggered: styleItem.showToolTip(link)
            }

            MouseArea {
                anchors.fill: column;
                onClicked: Qt.openUrlExternally(link);
                hoverEnabled: true;
                onEntered: { nextItemTimer.stop(); toolTipTimer.start(); }
                onExited: { nextItemTimer.restart(); toolTipTimer.stop(); }
                id: mouseArea
            }

            StateGroup {
                id: activeState
                states: [ State { name: "active"; when: delegateItem.active; PropertyChanges { target: delegateItem; opacity: 1 } } ]
                transitions: [
                    Transition { from: ""; to: "active"; reversible: true; NumberAnimation { target: delegateItem; property: "opacity"; duration: 1000 } }
                ]
            }

            states: [
                State { name: "clicked"; when: mouseArea.pressed;  PropertyChanges { target: text; color: "black" } },
                State { name: "hovered"; when: mouseArea.containsMouse && link !== ""; PropertyChanges { target: text; color: "#074C1C" } }
            ]


        }
    }
}

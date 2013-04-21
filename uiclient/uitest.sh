#!/bin/sh
# Runs the QtQuick ui with mocked C++ client

export LIBGL_ALWAYS_SOFTWARE=1

#$QT_INSTALL_BINS/qmlscene -I mock --resize-to-root main.qml
$QT_INSTALL_BINS/qmlscene -I mock main.qml


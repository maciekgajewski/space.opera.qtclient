// Copyright (c) 2013 Maciej Gajewski
#include "../libclient/client.h"

#include <QFile>
#include <QtQuick/QQuickView>
#include <QDebug>
#include <QGuiApplication>
#include <QtQml>

int main(int argc, char *argv[])
{
    qmlRegisterType<SpaceOpera::Client::Client>("spaceopera.client", 1, 0, "Client");

    QGuiApplication app(argc, argv);

    QQuickView* view = new QQuickView();
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->setSource(QUrl("qrc:/qmls/main.qml"));
    view->show();

    return app.exec();
}

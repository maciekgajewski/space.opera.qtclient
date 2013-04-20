#include <QFile>
#include <QtQuick/QQuickView>
#include <QDebug>
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView* view = new QQuickView();
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->setSource(QUrl("qrc:/qmls/main.qml"));
    view->show();

    return app.exec();
}

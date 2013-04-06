#include <QCoreApplication>

#include "../protocol_cpp/protocol.pb.h"

int main(int argc, char *argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    QCoreApplication a(argc, argv);
    
    return a.exec();
}

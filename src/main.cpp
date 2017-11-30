#include "Window.h"
#include <QApplication>
#include "tools.h"
#include "WindowController.h"

#include <xercesc/util/PlatformUtils.hpp>
#include <xalanc/Include/PlatformDefinitions.hpp>
#include <xalanc/XalanTransformer/XalanTransformer.hpp>

XALAN_USING_XERCES(XMLPlatformUtils)
XALAN_USING_XALAN(XalanTransformer)

int main(int argc, char *argv[])
{
    XMLPlatformUtils::Initialize();
    XalanTransformer::initialize();

    QApplication app(argc, argv);

    Window window;
    WindowController controller(&window);
    window.SetController(&controller);
    window.show();

    return app.exec();
}

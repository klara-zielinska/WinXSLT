#include "stdafx.h"
#include "Window.h"

using namespace WinXSLT;
XALAN_USING_XERCES(XMLPlatformUtils)
XALAN_USING_XALAN(XalanTransformer)

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	XMLPlatformUtils::Initialize();
	XalanTransformer::initialize();

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	Application::Run(gcnew Window());

	return 0;
}

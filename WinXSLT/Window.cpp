#include "stdafx.h"
#include "Window.h"
#include "tools.h"

using namespace System::IO;
using namespace WinXSLT;

XALAN_USING_XERCES(XMLPlatformUtils)
XALAN_USING_XALAN(XalanTransformer)
XALAN_USING_XALAN(XSLTInputSource)
XALAN_USING_XALAN(XSLTResultTarget)


System::Void Window::fileClick(System::Object^  sender, System::EventArgs^  e) 
{
	openFileDialog1->FileName = "";

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		sourcePathBox->Text = openFileDialog1->FileName;
		sourcePathBox->Refresh();
	}
}

System::Void Window::folderClick(System::Object^ sender, System::EventArgs^ e)
{
	if (folderBrowserDialog->ShowDialog() == 
			System::Windows::Forms::DialogResult::OK)
	{
		sourcePathBox->Text = folderBrowserDialog->SelectedPath + "\\*.xml";
		sourcePathBox->Refresh();
	}
}

System::Void Window::loadFromFileClick(System::Object^  sender, System::EventArgs^  e) 
{
	openFileDialog2->FileName = "";

	if (openFileDialog2->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		Stream^       stream;
		StreamReader^ reader;

		if ( (stream = openFileDialog2->OpenFile()) != nullptr )
        {
			reader = gcnew StreamReader(stream);

			schemeBox->Text = reader->ReadToEnd();
			schemeBox->Refresh();
			
            stream->Close();
         }
	}
}

System::Void Window::transformClick(System::Object^ sender, 
									System::EventArgs^ e)
{
	String^        sourcePath       = sourcePathBox->Text;
	List<String^>^ sourceFilesPaths = GetFilesByPattern(sourcePath);
			
	for each (String^ sourceFilePath in sourceFilesPaths)
	{
		char* sourceFilePathCh = (char*)(void*)Marshal::
									StringToHGlobalAnsi(sourceFilePath);

		XSLTInputSource   source(sourceFilePathCh);
		XSLTResultTarget  target(sourceFilePathCh);

		char* schemeCh         = (char*)(void*)Marshal::
									StringToHGlobalAnsi(schemeBox->Text);
		std::string       schemeString(schemeCh);
		std::stringstream schemeStream(schemeString);
		XSLTInputSource   scheme = XSLTInputSource(&schemeStream);
				
		XalanTransformer* transformer = new XalanTransformer();
		int res = transformer->transform(source, scheme, target);
		if (res == 0) 
			logsBox->Items->Add(sourceFilePath + " OK");
		else
			logsBox->Items->Insert(0, sourceFilePath + " Fail");
		logsBox->Refresh();

		delete transformer;
		Marshal::FreeHGlobal(IntPtr((void*)sourceFilePathCh));
		Marshal::FreeHGlobal(IntPtr((void*)schemeCh));
	}
}
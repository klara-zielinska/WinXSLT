/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the  "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "stdafx.h"
#include "Window.h"
#include "tools.h"
#include "WindowController.h"

using namespace System::IO;
using namespace System::Windows::Forms;
using namespace WinXSLT;

XALAN_USING_XERCES(XMLPlatformUtils)
XALAN_USING_XALAN(XalanTransformer)
XALAN_USING_XALAN(XSLTInputSource)
XALAN_USING_XALAN(XSLTResultTarget)


void WindowController::LoadXSLT()
{
    window->XSLTFileDialog->FileName = "";

    if (window->XSLTFileDialog->ShowDialog() == DialogResult::OK)
    {
        Stream^       stream;
        StreamReader^ reader;

        if ( (stream = window->XSLTFileDialog->OpenFile()) != nullptr )
        {
            reader = gcnew StreamReader(stream);
            window->XSLT = reader->ReadToEnd();
            stream->Close();
         }
    }
}

void WindowController::ChooseSourceFile()
{
    window->SourceFileDialog->FileName = "";

    if (window->SourceFileDialog->ShowDialog() == DialogResult::OK)
        window->SourcePath = window->SourceFileDialog->FileName;
}

void WindowController::ChooseSourceFolder()
{
    if (window->SourceFolderDialog->ShowDialog() == DialogResult::OK)
        window->SourcePath = window->SourceFolderDialog->SelectedPath + 
                             "\\*.xml";
}

void WindowController::Transform()
{
    String^        sourcePath       = window->SourcePath;
    List<String^>^ sourceFilesPaths = GetFilesByPattern(sourcePath);
            
    for each (String^ sourceFilePath in sourceFilesPaths)
    {
        char* sourceFilePathCh = (char*)(void*)Marshal::
                                    StringToHGlobalAnsi(sourceFilePath);

        XSLTInputSource   source(sourceFilePathCh);
        XSLTResultTarget  target(sourceFilePathCh);

        char* schemeCh         = (char*)(void*)Marshal::
                                    StringToHGlobalAnsi(window->XSLT);
        std::string       schemeString(schemeCh);
        std::stringstream schemeStream(schemeString);
        XSLTInputSource   scheme = XSLTInputSource(&schemeStream);
                
        XalanTransformer* transformer = new XalanTransformer();
        int res = transformer->transform(source, scheme, target);
        if (res == 0) 
            window->AddLog(sourceFilePath + " OK");
        else
            window->AddLog(sourceFilePath + " Fail");

        delete transformer;
        Marshal::FreeHGlobal(IntPtr((void*)sourceFilePathCh));
        Marshal::FreeHGlobal(IntPtr((void*)schemeCh));
    }
}

WindowController::WindowController(Window^ window)
{
    this->window = window;
}
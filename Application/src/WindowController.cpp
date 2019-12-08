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

#include "Window.h"
#include "WindowController.h"
#include "Utils/tools.h"
#include "Utils/xsltutils.h"
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
#include <QFileDialog>
#include <QString>
#include <QTextStream>
#include <QXmlStreamReader>
#include <sstream>


using namespace std;


void WindowController::LoadXSLT()
{
    QString path = QFileDialog::getOpenFileName(
        window, "Load", "", "All Files (*)");

    QFile       file(path);
    QTextStream stream(&file);
    file.open(QFile::ReadOnly);
    window->SetXSLT(stream.readAll());
    file.close();
}

void WindowController::SaveXSLT()
{
    QString path = QFileDialog::getSaveFileName(
        window, "Save", "", "All Files (*)");

    QFile       file(path);
    QTextStream stream(&file);
    file.open(QFile::WriteOnly);
    stream << window->GetXSLT();
    stream.flush();
    file.close();
}

void WindowController::ChooseSourceFile()
{
    QString fileName = QFileDialog::getOpenFileName(
        window, "Choose", "", "All Files (*)");

    window->SetSourcePath(fileName);
}

void WindowController::ChooseSourceFolder()
{
    QString dirName = QFileDialog::getExistingDirectory(
        window, "Choose", "", QFileDialog::ShowDirsOnly);

    window->SetSourcePath(dirName + "/*.xml");
}

void WindowController::Transform()
{
    try {

    QString       sourcePath  = window->GetSourcePath();
    QFileInfoList sourceFiles = getFilesByPattern(sourcePath);

    string    xsltStr = window->GetXSLT().toStdString();
    xmlDocPtr xsltDoc = xmlParseDocEx(reinterpret_cast<const xmlChar*>(
                                      xsltStr.c_str()));
    xsltStylesheetPtr xsltStylesheet = xsltParseStylesheetDocEx(xsltDoc);

    foreach (const QFileInfo& sourceFile, sourceFiles)
    try
    {
        QByteArray docPath = sourceFile.absoluteFilePath().toLocal8Bit();
        xmlDocPtr  doc     = xmlParseFileEx(docPath);
        xmlDocPtr  resDoc  = xsltApplyStylesheetEx(xsltStylesheet, doc,
                                                   { nullptr });
        FILE* docFile = fopen(docPath, "w");
        if (docFile == nullptr) throw std::exception();
        xsltSaveResultToFileEx(docFile, resDoc, xsltStylesheet);
        fclose(docFile);

        window->AddLog(sourceFile.absoluteFilePath() + " OK");
    }
    catch (const std::exception& ex)
    {
        window->AddLog(sourceFile.absoluteFilePath() + " Fail");
    }

//        istringstream sourceStream = readFileToString(sourceFile);
//        XSLTInputSource source(sourceStream);

//        ostringstream targetStream;
//        XSLTResultTarget target(targetStream);

//        istringstream schemeStream(
//            window->GetXSLT().toStdString());
//        XSLTInputSource scheme(&schemeStream);
                
//        XalanTransformer* transformer = new XalanTransformer();
//        int res = transformer->transform(source, scheme, target);
//        if (res == 0)
//        {
//            writeSStreamToFile(targetStream, sourceFile);
//            window->AddLog(sourceFile.absoluteFilePath() + " OK");
//        }
//        else
//            window->AddLog(sourceFile.absoluteFilePath() + " Fail");

//        delete transformer;

    }
    catch (const std::exception& ex)
    {
        window->AddLog("Fatal error");
    }
}

WindowController::WindowController(Window* window)
{
    this->window = window;
}

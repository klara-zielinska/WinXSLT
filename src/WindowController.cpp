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
#include "tools.h"
#include "WindowController.h"
#include <sstream>
#include <QFileDialog>
#include <QString>
#include <QTextStream>
#include <QXmlStreamReader>
#include <xalanc/XalanTransformer/XalanTransformer.hpp>

XALAN_USING_XALAN(XalanTransformer)
XALAN_USING_XALAN(XSLTInputSource)
XALAN_USING_XALAN(XSLTResultTarget)

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


istringstream readFileToString(const QFileInfo& ifile)
{
    QFile file(ifile.absoluteFilePath());
    file.open(QFile::ReadOnly);
    QString text = QTextStream(&file).readAll();
    istringstream stream(text.toStdString());
    file.close();
    return stream;
}

void writeSStreamToFile(
        const ostringstream& istream, const QFileInfo& ifile)
{
    QFile file(ifile.absoluteFilePath());
    file.open(QFile::WriteOnly);
    QTextStream ostream(&file);
    ostream << QString::fromStdString(istream.str());
    ostream.flush();
    file.close();
}

void WindowController::Transform()
{
    QString       sourcePath  = window->GetSourcePath();
    QFileInfoList sourceFiles = GetFilesByPattern(sourcePath);

    foreach (const QFileInfo& sourceFile, sourceFiles)
    {
        istringstream sourceStream = readFileToString(sourceFile);
        XSLTInputSource source(sourceStream);

        ostringstream targetStream;
        XSLTResultTarget target(targetStream);

        istringstream schemeStream(
            window->GetXSLT().toStdString());
        XSLTInputSource scheme(&schemeStream);
                
        XalanTransformer* transformer = new XalanTransformer();
        int res = transformer->transform(source, scheme, target);
        if (res == 0)
        {
            writeSStreamToFile(targetStream, sourceFile);
            window->AddLog(sourceFile.absoluteFilePath() + " OK");
        }
        else
            window->AddLog(sourceFile.absoluteFilePath() + " Fail");

        delete transformer;
    }
}

WindowController::WindowController(Window* window)
{
    this->window = window;
}

#include "stdafx.h"
#include "tools.h"
#include <assert.h>

using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Linq;


/// <summary>
/// The function finds all files specified by a path pattern.
/// </summary>
///
/// <param name=pathPattern>
/// A path that can contain wildcards ? and *.
/// It must contain at least the file name pattern.
/// </param>

List<String^>^ GetFilesByPattern(String^ path)
{
    assert(!String::IsNullOrEmpty(path));

    String^ delimStr              = gcnew String("\\");
    array<String^>^ splittedPath  = path->Split(delimStr->ToCharArray());

    List<String^>^ dirsToProccess = gcnew List<String^>();
    dirsToProccess->Add(splittedPath[0]);

    for (int pathDirIndex = 1; 
         pathDirIndex < splittedPath->Length - 1; 
         pathDirIndex++)
    {
        List<String^>^ newDirsToProccess = gcnew List<String^>();

        for (int dirIndex = 0; dirIndex < dirsToProccess->Count; dirIndex++)
        {
            String^ dirPath = dirsToProccess[dirIndex];

            try {
            array<String^>^ paths = 
                Directory::GetDirectories(dirPath + "\\", 
                                          splittedPath[pathDirIndex]);

            for each (String^ path in paths)
                newDirsToProccess->Add(path);
            }
            catch (UnauthorizedAccessException^) {}
            catch (IOException^) {}
        }

        dirsToProccess = newDirsToProccess;
    }

    List<String^>^ filesToProcess = gcnew List<String^>();
    for each (String^ dirPath in dirsToProccess)
    {
        try {
        array<String^>^ paths = 
            Directory::GetFiles(dirPath, 
                                Enumerable::Last<String^>(splittedPath));

        for each (String^ path in paths)
            filesToProcess->Add(path);
        }
        catch (UnauthorizedAccessException^) {}
        catch (IOException^) {}
    }

    return filesToProcess;
}

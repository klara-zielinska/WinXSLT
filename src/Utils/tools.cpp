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

#include "tools.h"
#include <QDir>
#include <QTextStream>
#include <sstream>

using namespace std;


QList<QDir> findDirs(QList<QDir>& dirsToSearch, const QString& pattern)
{
    QList<QDir> newDirsToSearch;
    foreach (const QDir& dir, dirsToSearch)
    {
        QFileInfoList childDirs =
            dir.entryInfoList(QStringList(pattern),
                              QDir::Dirs | QDir::NoDotAndDotDot);

        foreach (const QFileInfo& childDir, childDirs)
            newDirsToSearch.append(QDir(childDir.absoluteFilePath() + "/"));
    }
    return newDirsToSearch;
}


QFileInfoList findFiles(QList<QDir>& dirsToSearch, const QString& pattern)
{
    QFileInfoList foundFiles;
    foreach (const QDir& dir, dirsToSearch)
    {
        foundFiles +=
            dir.entryInfoList(QStringList(pattern), QDir::Files);
    }
    return foundFiles;
}

QDir rootDir(const QString& rootPath)
{
#if defined(Q_OS_WIN)
    return QDir(rootPath + "/");

#elif defined(Q_OS_LINUX) || defined(Q_OS_UNIX)
    return QDir("/");

#else
  __UNSUPPORTED_SYSTEM

#endif
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

QFileInfoList GetFilesByPattern(const QString& path)
{
    QString absPath =
            QDir::fromNativeSeparators(

            QDir::isAbsolutePath(path) ?
                path :
                QDir::currentPath() + QDir::separator() + path);

    QStringList splittedAbsPath = absPath.split("/");
    QString     filesPattern    = splittedAbsPath.last();
    QList<QDir> dirsToSearch;
    dirsToSearch.append(rootDir(splittedAbsPath.first()));

    splittedAbsPath.removeFirst();
    splittedAbsPath.removeLast();

    foreach (const QString& pattern, splittedAbsPath)
        dirsToSearch = findDirs(dirsToSearch, pattern);

    return findFiles(dirsToSearch, filesPattern);
}

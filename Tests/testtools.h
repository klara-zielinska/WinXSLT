#pragma once

#include <QFile>
#include <QDir>
#include <QTemporaryFile>
#include <QString>

bool qIODevEq(QIODevice& dev1, QIODevice& dev2);

/*!
 * \brief Copies the content of an IO device to another
 */
void copyIODevContent(QIODevice &source, QIODevice &dest);

///*!
// * \brief Untars an archive to a current folder
// * \attention Does not wait on unavailable resources
// * \attention Ignores archived file properties (attributes, permissions, etc.)
// */
//void untar(QFileDevice &source, const QDir &targetDir);

void copyDir(QDir source, QDir target);

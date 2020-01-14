#pragma once

#include <libxml2/libxml/tree.h>
#include <QFile>
#include <QDir>
#include <QTemporaryFile>
#include <QString>


/*!
 * \brief Checks if a content of two IO devices is equal
 */
bool qIODevEq(QIODevice& dev1, QIODevice& dev2);

/*!
 * \brief Copies the content of an IO device to another
 */
void copyIODevContent(QIODevice &source, QIODevice &dest);

/*!
 * \brief Recursively copies a directory
 */
void copyDir(QDir source, QDir target);

/*!
 * \brief Recursively compares content of two xml nodes
 * \returns p true if the nodes are equal, p false otherwise
 */
bool xmlSimpleNodesEq(xmlNodePtr node1, xmlNodePtr node2);

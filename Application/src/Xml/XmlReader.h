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

#pragma once

#include "XmlPatterns.h"
#include "XmlToken.h"
#include <QString>


/*!
 * \brief This class provides an XML lexer
 */
class XmlReader
{
private:
    static XmlPatterns::Level nextLevel(
            XmlPatterns::Level l, XmlToken::Type t);

    static XmlToken::Type capGroupToTokenType(
            XmlPatterns::Level l, int capGroup);

    static XmlToken matchToToken(
            XmlPatterns::Level l, const QRegularExpressionMatch& match);

    QString            xml;
    XmlPatterns::Level level;

public:
    /*!
     * \brief Constructs a lexer
     * \param xmldoc An XML document
     */
    XmlReader(const QString& xmldoc);

    /*!
     * \brief Reads the next unread token
     */
    XmlToken NextToken();
};

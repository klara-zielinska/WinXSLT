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

#include <QString>


/*!
 * \brief This structure stores an XML token
 */
struct XmlToken
{
    /*!
     * \brief Types of XML tokents.\n
     * \p TagOpen   - "<"\n
     * \p TagClose  - ">"\n
     * \p TagName   - a tag name\n
     * \p AttrName  - an attribute name\n
     * \p AttrEq    - "="\n
     * \p AttrValue - an attribute value\n
     * \p InS       - spaces in a body of a tag\n
     * \p Text      - text\n
     * \p Comment   - a comment\n
     * \p End       - the token that terminates an XML document\n
     * \p InvTagEnding - an invalid piece of an XML doccument
     */
    enum Type { TagOpen, TagClose, TagName, AttrName, AttrEq, AttrValue, InS,
                Text, Comment, End, InvTagEnding };
    /*!
     * \brief The number of token types
     */
    static const int TypesCount = 11;

    /*!
     * \brief The type of a token
     */
    Type type;
    /*!
     * \brief The text that corresponds in a document to a token
     */
    QString text;
};

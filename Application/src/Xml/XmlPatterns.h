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
#include <QRegularExpression>


// TO DO: CDATA support
// TO DO: correct the grammar

/*!
 * \brief Regular expressions for parsing XML
 */
class XmlPatterns
{
private:
    static constexpr int maxCapGroupsInLevel = 4;

public:
    /*!
     * \brief Levels of depth in XML grammar
     */
    enum Level { Open, InTag, InAttrs, InAttr, InVal };
    /*!
     * \brief The number of XML grammar levels
     * \hideinitializer
     */
    static const int ParseLevelsCount = 5;

    /*!
     * \brief An array of all regular expressions used to parse XML. Each index
     * corresponds to an XML grammar level
     * \hideinitializer
     */
    static const QRegularExpression *const Patterns[ParseLevelsCount];
    /*!
     * \brief Numbers of capture groups in the patterns per level
     * \hideinitializer
     */
    static const int CapGroupsCount[ParseLevelsCount];
    /*!
     * \brief CapGroups[n] is an array of names of capture groups in the
     * n'th pattern
     * \hideinitializer
     */
    static const QString CapGroups[ParseLevelsCount][maxCapGroupsInLevel];

private:
    static const QRegularExpression openPattern;
    static const QRegularExpression inTagPattern;
    static const QRegularExpression inAttrsPattern;
    static const QRegularExpression inAttrPattern;
    static const QRegularExpression inValPattern;
};

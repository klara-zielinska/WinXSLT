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

#include "XmlReader.h"


/*!
 * \brief This class provides an XML highlighting
 */
class XmlHighlight
{
public:
    /*!
     * \brief Highlights XML syntax in HTML
     * \param xml An XML string
     * \return xml wrapped in HTML
     */
    static QString InHtml(const QString& xml);

private:
    static const QString tagStyle;
    static const QString attrNameStyle;
    static const QString attrEqStyle;
    static const QString attrValStyle;
    static const QString textStyle;
    static const QString commentStyle;
    static const QString invTagStyle;
    static const QString defaultStyle;

    static const QString stylesByTokenType[XmlToken::TypesCount];
};

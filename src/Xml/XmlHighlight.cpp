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

#include "XmlHighlight.h"




const QString XmlHighlight::tagStyle      = "color: Blue;";
const QString XmlHighlight::attrNameStyle = "color: Red;";
const QString XmlHighlight::attrEqStyle   = "color: Black;";
const QString XmlHighlight::attrValStyle  = "color: BlueViolet; "
                                            "font-weight: bold;";
const QString XmlHighlight::textStyle     = "color: Black; "
                                            "font-weight: bold;";
const QString XmlHighlight::commentStyle  = "color: Green;";
const QString XmlHighlight::invTagStyle   = "color: Red; "
                                            "font-style: italic;";
const QString XmlHighlight::defaultStyle  = "";


const QString XmlHighlight::stylesByTokenType[XmlToken::TypesCount] =
{
    tagStyle,
    tagStyle,
    tagStyle,
    attrNameStyle,
    attrEqStyle,
    attrValStyle,
    defaultStyle,
    textStyle,
    commentStyle,
    defaultStyle,
    invTagStyle
};



QString XmlHighlight::InHtml(const QString& xml)
{
    XmlReader reader(xml);
    QString html;
    for (XmlToken token = reader.NextToken();
         token.type != XmlToken::End;
         token = reader.NextToken())
    {
        html += "<span style=\"" + stylesByTokenType[token.type] + "\">" +
                token.text.toHtmlEscaped() +
                "</span>";
    }
    return "<code style=\"white-space:pre-wrap;\">" +
            html +
            "</code>";
}

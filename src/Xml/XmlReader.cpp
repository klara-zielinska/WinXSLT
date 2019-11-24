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

#include "XmlReader.h"
#include <QRegularExpression>




XmlReader::XmlReader(const QString& xmldoc)
{
    this->xml    = xmldoc;
    this->level  = XmlPatterns::Open;
}

XmlPatterns::Level XmlReader::nextLevel(XmlPatterns::Level l, XmlToken::Type t)
{
    switch (l)
    {
    case XmlPatterns::Open:
        switch (t)
        {
        case XmlToken::TagOpen:   return XmlPatterns::InTag;
        case XmlToken::Comment:   return XmlPatterns::Open;
        case XmlToken::Text:      return XmlPatterns::Open;
        }
    case XmlPatterns::InTag:
        switch (t)
        {
        case XmlToken::TagName:    return XmlPatterns::InAttrs;
        case XmlToken::InvTagEnding: return XmlPatterns::Open;
        }
    case XmlPatterns::InAttrs:
        switch (t)
        {
        case XmlToken::InS:        return XmlPatterns::InAttrs;
        case XmlToken::AttrName:   return XmlPatterns::InAttr;
        case XmlToken::TagClose:   return XmlPatterns::Open;
        case XmlToken::InvTagEnding: return XmlPatterns::Open;
        }
    case XmlPatterns::InAttr:
        switch (t)
        {
        case XmlToken::InS:        return XmlPatterns::InAttr;
        case XmlToken::AttrEq:     return XmlPatterns::InVal;
        case XmlToken::TagClose:   return XmlPatterns::Open;
        case XmlToken::InvTagEnding: return XmlPatterns::Open;
        }
    case XmlPatterns::InVal:
        switch (t)
        {
        case XmlToken::InS:        return XmlPatterns::InVal;
        case XmlToken::AttrValue:  return XmlPatterns::InAttrs;
        case XmlToken::InvTagEnding: return XmlPatterns::Open;
        }
    }

    Q_ASSERT(false);
}


XmlToken::Type XmlReader::capGroupToTokenType(XmlPatterns::Level l,
                                              int capGroup)
{
    switch (l)
    {
    case XmlPatterns::Open:
        switch (capGroup)
        {
        case 0: return XmlToken::Comment;
        case 1: return XmlToken::TagOpen;
        case 2: return XmlToken::Text;
        }
    case XmlPatterns::InTag:
        switch (capGroup)
        {
        case 0: return XmlToken::TagName;
        case 1: return XmlToken::InvTagEnding;
        }
    case XmlPatterns::InAttrs:
        switch (capGroup)
        {
        case 0: return XmlToken::InS;
        case 1: return XmlToken::AttrName;
        case 2: return XmlToken::TagClose;
        case 3: return XmlToken::InvTagEnding;
        }
    case XmlPatterns::InAttr:
        switch (capGroup)
        {
        case 0: return XmlToken::InS;
        case 1: return XmlToken::AttrEq;
        case 2: return XmlToken::TagClose;
        case 3: return XmlToken::InvTagEnding;
        }
    case XmlPatterns::InVal:
        switch (capGroup)
        {
        case 0: return XmlToken::InS;
        case 1: return XmlToken::AttrValue;
        case 2: return XmlToken::InvTagEnding;
        }
    }

    Q_ASSERT(false);
}


XmlToken XmlReader::matchToToken(XmlPatterns::Level l,
                                 const QRegularExpressionMatch& match)
{
    for (int i = 0; i < XmlPatterns::CapGroupsCount[l]; i++)
    {
        QString tokenText = match.captured(XmlPatterns::CapGroups[l][i]);
        if (!tokenText.isNull())
            return XmlToken { capGroupToTokenType(l, i),
                              tokenText };
    }

    Q_ASSERT(false);
}

XmlToken XmlReader::NextToken()
{
    if (xml.isEmpty())
    {
        return XmlToken { XmlToken::End, QString::null };
    }
    else
    {
        const QRegularExpression* regex = XmlPatterns::Patterns[level];
        const QRegularExpressionMatch& match =
                regex->match(xml, 0,
                             QRegularExpression::NormalMatch,
                             QRegularExpression::AnchoredMatchOption);
        XmlToken token = matchToToken(level, match);
        level = nextLevel(level, token.type);
        xml.remove(0, token.text.length());
        return token;
    }
}

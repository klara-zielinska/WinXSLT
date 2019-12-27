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

#include "XmlPatterns.h"


const QString ch = QString::fromUtf8(
        u8"\x09|\x0A|\x0D|"
        u8"[\u0020-\uD7FF]|"
        u8"[\uE000-\uFFFD]|"
        u8"[\U00010000-\U0010FFFF]");

const QString ws = QString::fromUtf8(
        u8"\x20|\x09|\x0D|\x0A");

const QString s =
        "(?:" + ws + ")+";

const QString comment =
        "<!--"
        "(?:"
            "(?!-)(?:"  + ch + ")|"
            "-(?!-)(?:" + ch + ")"
        ")*"
        "-->";

const QString tagOpen =
        "<[?/!]?";

const QString text =
        "[^<]+";

const QRegularExpression XmlPatterns::openPattern(
        "(?'comment'" + comment + ")|"
        "(?'tagOpen'" + tagOpen + ")|"
        "(?'text'"    + text    + ")");


const QString tagNameStartCh = QString::fromUtf8(
        u8"[:_A-Za-z]|"
        u8"[\xC0-\xD6]|"
        u8"[\xD8-\xF6]|"
        u8"[\u00F8-\u02FF]|"
        u8"[\u0370-\u037D]|"
        u8"[\u037F-\u1FFF]|"
        u8"[\u200C-\u200D]|"
        u8"[\u2070-\u218F]|"
        u8"[\u2C00-\u2FEF]|"
        u8"[\u3001-\uD7FF]|"
        u8"[\uF900-\uFDCF]|"
        u8"[\uFDF0-\uFFFD]|"
        u8"[\U00010000-\U000EFFFF]");

const QString tagNameCh =
        tagNameStartCh + "|" + QString::fromUtf8(
        u8"[-\\.0-9]|"
        u8"\xB7|"
        u8"[\u0300-\u036F]|"
        u8"[\u203F-\u2040]");

const QString name =
        "(?:" + tagNameStartCh + ")(?:" + tagNameCh + ")*";

const QString invTagEnding =
        "[^>]+>?";

const QRegularExpression XmlPatterns::inTagPattern(
        "(?'tagName'" + name + ")|"
        "(?'invTag'"  + invTagEnding  + ")");


const QString tagClose =
        "[?/]?>";

const QRegularExpression XmlPatterns::inAttrsPattern(
        "(?'s'"        + s        + ")|"
        "(?'attrName'" + name     + ")|"
        "(?'tagClose'" + tagClose + ")|"
        "(?'invTag'"   + invTagEnding   + ")");

const QRegularExpression XmlPatterns::inAttrPattern(
        "(?'s'"        + s        + ")|"
        "(?'eq'"         "="        ")|"
        "(?'tagClose'" + tagClose + ")|"
        "(?'invTag'"   + invTagEnding   + ")");

const QString entityRef =
        "&" + name + ";";

const QString charRef =
        "&#[0-9]+;|"
        "&#x[0-9a-fA-F]+;";

const QString reference =
        entityRef + "|" +
        charRef;

const QString value =
        "\"(?:[^<&\"]|" + reference + ")*\"|"
        "'(?:[^<&\']|'" + reference + ")*'";

const QRegularExpression XmlPatterns::inValPattern(
        "(?'s'"      + s      + ")|"
        "(?'value'"  + value  + ")|"
        "(?'invTag'" + invTagEnding + ")");


const QRegularExpression *const XmlPatterns::Patterns[5] =
    { &openPattern,
      &inTagPattern,
      &inAttrsPattern,
      &inAttrPattern,
      &inValPattern };


const int XmlPatterns::CapGroupsCount[5] =
    { 3, 2, 4, 4, 3 };


const QString XmlPatterns::CapGroups[5][4] =
{
    {"comment", "tagOpen", "text"},
    {"tagName", "invTag"},
    {"s", "attrName", "tagClose", "invTag"},
    {"s", "eq", "tagClose", "invTag"},
    {"s", "value", "invTag"}
};

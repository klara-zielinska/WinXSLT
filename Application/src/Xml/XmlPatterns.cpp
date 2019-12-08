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
        u8"[\x20-\uD7FF]|"
        u8"[\uE000-\uFFFD]|"
        u8"[\U00010000-\U0010FFFF]");

const QString ws = QString::fromUtf8(
        u8"\x20|\x09|\x0D|\x0A");

const QString s =
        "(" + ws + ")+";

const QString comment =
        "<!--"
        "("
            "(?!-)("  + ch + ")|"
            "-(?!-)(" + ch + ")"
        ")*"
        "-->";

const QString tagOpen =
        "<[\\?/]?";

const QString text =
        "[^<]+";

const QRegularExpression XmlPatterns::openPattern(
        "(?'comment'" + comment + ")|"
        "(?'tagOpen'" + tagOpen + ")|"
        "(?'text'"    + text    + ")");



const QString tagName =
        "((?!" + ws + ")(?!>).)+";

const QString invTagEnding =
        "[^>]+>?";

const QRegularExpression XmlPatterns::inTagPattern(
        "(?'tagName'" + tagName + ")|" +
        "(?'invTag'"  + invTagEnding  + ")");



const QString attrName =
        "("
            "(?!" + ws + ")"
            "(?![>=\\?/])"
            "."
        ")+";

const QString tagClose =
        "[\\?/]?>";

const QRegularExpression XmlPatterns::inAttrsPattern(
        "(?'s'"        + s        + ")|"
        "(?'attrName'" + attrName + ")|"
        "(?'tagClose'" + tagClose + ")|"
        "(?'invTag'"   + invTagEnding   + ")");

const QRegularExpression XmlPatterns::inAttrPattern(
        "(?'s'"        + s        + ")|"
        "(?'eq'"         "="        ")|"
        "(?'tagClose'" + tagClose + ")|"
        "(?'invTag'"   + invTagEnding   + ")");


const QString value =
        "(\"[^\"]*\")|"
        "('[^\']*')";

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

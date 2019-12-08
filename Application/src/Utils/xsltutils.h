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
/*! \file
 *  \brief Wrappers for functions from libxml2, libxslt
 */

#pragma once

#include <libxml/tree.h>
#include <libxslt/xsltInternals.h>
#include <exception>
#include <iostream>


/*!
 * \brief Exception thown by wrappers
 */
class XmlException : public std::exception
{ };


/*!
 * \brief The structure is a wrapper for `xmlChar*` and provides non-cost
 * casting between `char*` and `xmlChar*`
 * \remark `const XmlCString` is an equivalent to `const xmlChar *const`, thus
 * you cannot obtain a `const xmlChar*&` and `const char*&` from this class.
 */
struct XmlCString
{
private:
    xmlChar* c_str;

public:
    inline operator char*&()
    { return (char*&)c_str; }

    inline operator const char *const &() const
    { return (const char *const &)c_str; }

    inline operator xmlChar*&()
    { return c_str; }

    inline operator const xmlChar *const &() const
    { return (const xmlChar *const &)c_str; }

    inline static XmlCString& of(char*& c_str)
    { return reinterpret_cast<XmlCString&>(c_str); }

    inline static const XmlCString& of(const char *const & c_str)
    { return reinterpret_cast<const XmlCString&>(c_str); }

    inline static XmlCString&& of(char*&& c_str)
    { return reinterpret_cast<XmlCString&&>(c_str); }

    inline static const XmlCString&& of(const char *const && c_str)
    { return reinterpret_cast<const XmlCString&&>(c_str); }

    inline static XmlCString& of(xmlChar*& xc_str)
    { return reinterpret_cast<XmlCString&>(xc_str); }

    inline static const XmlCString& of(const xmlChar *const & xc_str)
    { return reinterpret_cast<const XmlCString&>(xc_str); }

    inline static XmlCString&& of(xmlChar*&& xc_str)
    { return reinterpret_cast<XmlCString&&>(xc_str); }

    inline static const XmlCString&& of(const xmlChar *const && xc_str)
    { return reinterpret_cast<const XmlCString&&>(xc_str); }

private:
    XmlCString();
};

/*! \fn */
xmlDocPtr xmlParseDocEx(const xmlChar* cur);
/*! \fn */
xmlDocPtr xmlParseFileEx(const char* filename);
/*! \fn */
xsltStylesheetPtr xsltParseStylesheetDocEx(xmlDocPtr doc);
/*! \fn */
xmlDocPtr xsltApplyStylesheetEx(xsltStylesheetPtr style, xmlDocPtr doc,
                                const char ** params);
/*! \fn */
int       xsltSaveResultToFileEx(FILE* file, xmlDocPtr result,
                                 xsltStylesheetPtr style);

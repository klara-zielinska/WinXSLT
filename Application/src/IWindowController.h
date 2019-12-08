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


/*!
 * \brief This class is an interface for the application controller
 */
class IWindowController
{
public:
    /*!
     * \brief Loads XSLT from a file into the application
     */
    virtual void LoadXSLT()           = 0;
    /*!
     * \brief Saves XSLT from the application to a file
     */
    virtual void SaveXSLT()           = 0;
    /*!
     * \brief Asks a user for the location of a file to translate
     */
    virtual void ChooseSourceFile()   = 0;
    /*!
     * \brief Asks a user for the location of a folder that contains files
     * to translate
     */
    virtual void ChooseSourceFolder() = 0;
    /*!
     * \brief Runs the procedure that translates chosen XML files using the
     * present XSLT scheme
     */
    virtual void Transform()          = 0;
};

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

#include "IWindowController.h"
#include <QMainWindow>


namespace Ui {
class Window;
}

/*!
 * \brief This class provides the implementation of the main window
 */
class Window : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Constructs the window by calling the QMainWindow constructor
     */
    explicit Window(QWidget *parent = 0);
    ~Window();

    /*!
     * \brief Sets the application controller
     */
    void SetController(IWindowController* controller);
    /*!
     * \brief Adds an entry to the log list
     */
    void AddLog(const QString& entry);
    /*!
     * \brief Sets the content of the XSLT text area
     * \param xslt An XSLT document
     */
    void SetXSLT(const QString& xslt);
    /*!
     * \brief Returns the cntent of the XSLT text area
     */
    QString GetXSLT() const;
    /*!
     * \brief Sets the content of the source text field
     */
    void SetSourcePath(const QString& path);
    /*!
     * \brief Returns the content of the source text field
     */
    QString GetSourcePath() const;

private slots:
    void on_xsltLoadButton_clicked();
    void on_xsltSaveButton_clicked();
    void on_targetFileButton_clicked();
    void on_targetFolderButton_clicked();
    void on_transformButton_clicked();
    void on_xsltBox_textChanged();

private:
    Ui::Window *ui;
    IWindowController* controller;
};

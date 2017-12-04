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

#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "IWindowController.h"




namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();
    void    SetController(IWindowController* controller);
    void    AddLog(const QString& entry);
    void    SetXSLT(const QString& xslt);
    QString GetXSLT() const;
    void SetSourcePath(const QString& path);
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

#endif // WINDOW_H

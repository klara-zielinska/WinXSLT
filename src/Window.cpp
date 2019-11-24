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

#include "Window.h"
#include "ui_Window.h"
#include "Xml/XmlHighlight.h"




Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
}

Window::~Window()
{
    delete ui;
}

void Window::SetController(IWindowController* controller)
{
    this->controller = controller;
}

QString Window::GetSourcePath() const
{
    return ui->targetPathBox->text();
}

void Window::SetSourcePath(const QString& path)
{
    ui->targetPathBox->setText(path);
}

QString Window::GetXSLT() const
{
    return ui->xsltBox->toPlainText();
}

void Window::SetXSLT(const QString& path)
{
    ui->xsltBox->setText(path);
}

void Window::AddLog(const QString& entry)
{
    // the figure space (\u2007) is added, because width of items
    // in a list box is badly calcualted
    ui->logsBox->addItem(entry + QString::fromStdWString(L"\u2007"));
    QListWidgetItem* lastItem = ui->logsBox->item(ui->logsBox->count() - 1);
    ui->logsBox->scrollToItem(lastItem);
    ui->logsBox->update();
}

void Window::on_xsltLoadButton_clicked()
{
    controller->LoadXSLT();
}

void Window::on_xsltSaveButton_clicked()
{
    controller->SaveXSLT();
}

void Window::on_targetFileButton_clicked()
{
    controller->ChooseSourceFile();
}

void Window::on_targetFolderButton_clicked()
{
    controller->ChooseSourceFolder();
}

void Window::on_transformButton_clicked()
{
    controller->Transform();
}

void Window::on_xsltBox_textChanged()
{
    ui->xsltBox->blockSignals(true);

    int tpos     = ui->xsltBox->textCursor().position();

    QString html = XmlHighlight::InHtml(ui->xsltBox->toPlainText());
    ui->xsltBox->setHtml(html);

    QTextCursor cur = ui->xsltBox->textCursor();
    cur.setPosition(tpos);
    ui->xsltBox->setTextCursor(cur);

    ui->xsltBox->blockSignals(false);
}

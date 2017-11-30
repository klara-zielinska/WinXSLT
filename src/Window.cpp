#include "Window.h"
#include "ui_window.h"


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

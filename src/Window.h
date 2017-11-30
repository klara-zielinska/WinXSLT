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

private:
    Ui::Window *ui;
    IWindowController* controller;
};

#endif // WINDOW_H

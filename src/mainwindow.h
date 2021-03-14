#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include <QLineEdit>
#include <QtConcurrent/QtConcurrent>
#include <QMessageBox>

#include "stream.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_browseButton_clicked();

    void on_playButton_clicked();

private:
    Ui::MainWindow *ui;
    QLineEdit *addressLineEdit;
    QLineEdit *fileLineEdit;
};

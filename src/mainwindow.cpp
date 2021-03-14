#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->fileLineEdit = this->centralWidget()->findChild<QLineEdit*>("fileLineEdit");
    this->addressLineEdit = this->centralWidget()->findChild<QLineEdit*>("addressLineEdit");
}

MainWindow::~MainWindow()
{
    delete this->addressLineEdit;
    delete this->fileLineEdit;
    delete ui;
}


void MainWindow::on_browseButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open movie"), QDir::homePath(), tr("Movie files (*.mp4 *.avi *.mov);; All files (*.*)"));
    this->fileLineEdit->setText(filename);
}

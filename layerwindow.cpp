#include "layerwindow.h"
#include "ui_layerwindow.h"

layerWindow::layerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::layerWindow)
{
    ui->setupUi(this);

}

layerWindow::~layerWindow()
{
    delete ui;
}

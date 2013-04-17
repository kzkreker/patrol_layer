#ifndef LAYERWINDOW_H
#define LAYERWINDOW_H

#include <QMainWindow>
#include "database.h"

namespace Ui {
class layerWindow;
}

class layerWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit layerWindow(QWidget *parent = 0);
    ~layerWindow();
    
private:
    Ui::layerWindow *ui;
};

#endif // LAYERWINDOW_H

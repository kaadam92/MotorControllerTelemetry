#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/** @brief Az ablak megjelenítéséért felelős objektum.
 *
 * Csak létezik, feladatot nem hajt végre.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

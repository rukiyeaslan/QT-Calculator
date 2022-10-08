#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT /*base class for all QT object*/

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_centralwidget_customContextMenuRequested(const QPoint &pos);
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ClearButtonPressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <blanks.h>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

    QVector<QRect> blanks_installed;
    QVector<blank_to_install> blanks_to_install;
    blanks* bl;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void change_text();
    void calculate_blanks_position();
    void repaint_metal_sheet(int i);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include "single_blank.h"
#include "blanks.h"
#include <algorithm>
#include <calculator_of_blanks.h>
#include <QRect>
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
     , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bl = new blanks(this);
    bl->setGeometry(580, 220, 500, 500);
    bl->show();

    //соединения
    connect(ui->buttonCalculate, SIGNAL(clicked()), this, SLOT(calculate_blanks_position()));
    connect(ui->sheet_X, SIGNAL(valueChanged(int)), this, SLOT(repaint_metal_sheet(int)));
    connect(ui->sheet_Y, SIGNAL(valueChanged(int)), this, SLOT(repaint_metal_sheet(int)));
    ui->openGLWidget->setMetalSheet(QRect(0,0,ui->sheet_X->value(),ui->sheet_Y->value()));
    ui->openGLWidget->repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete bl;
}

void MainWindow::change_text()
{

}

void MainWindow::calculate_blanks_position()
{
    //проверяем, что значения листового проката не равны 0
    if((ui->sheet_X->value() == 0) || (ui->sheet_Y->value() == 0))
    {
        QMessageBox msg;
        msg.setWindowTitle("Ошибка!");
        msg.setText("Не заданы габариты прокатного листа");
        msg.show();
        msg.exec();
        return;
    }
    //задаём габариты листового проката
    QRect metal_sheet(0,0,ui->sheet_X->value(), ui->sheet_Y->value());

    calculator_of_blanks calculator;

    calculator.set_metal_sheet(ui->sheet_X->value(), ui->sheet_Y->value());

    //считываем размеры заготовок
    blanks_to_install = bl->get_blanks_to_install();

    //проверяем, что хоть одна заготовка не равна 0
    if(blanks_to_install.size() == 0)
    {
        QMessageBox msg;
        msg.setWindowTitle("Ошибка!");
        msg.setText("Не заданы габариты заготовок");
        msg.show();
        msg.exec();
        return;
    }

    calculator.set_blanks_to_install(blanks_to_install);

    calculator.calculate_blanks_to_install();

    ui->openGLWidget->setBlanksToInstall(calculator.get_blanks_installed());
    ui->openGLWidget->repaint();

    QVector<blank_to_install> blanks_not_installed = calculator.get_blanks_not_installed();

    QMessageBox msg;
    QString message_text;
    message_text += "Рассчёт заготовок на листе окончен\n";
    if(blanks_not_installed.empty())
        message_text += "Все заготовки успешно установлены\n";
    else
    {
        message_text += "Не удалось установить заготовки со следующими габаритами: \n";
        for(int i = 0; i < blanks_not_installed.size(); ++i)
        {
            message_text += std::to_string(blanks_not_installed[i].X_size).c_str();
            message_text += "x";
            message_text += std::to_string(blanks_not_installed[i].Y_size).c_str();
            message_text += "\n";
        }
    }
    message_text += "Общая израсходованная длина листа: ";
    message_text += std::to_string(calculator.get_consumed()).c_str();
    message_text += "\n";
    message_text += "Отходы: ";
    message_text += std::to_string(calculator.get_waste()).c_str();
    message_text += " см^2\n";
    msg.setText(message_text);
    msg.setWindowTitle("Рассчёт окончен");
    msg.exec();

}

void MainWindow::repaint_metal_sheet(int i)
{
    if((ui->sheet_X->value() != 0) && (ui->sheet_Y->value() != 0))
    {

        ui->openGLWidget->setMetalSheet(QRect(0,0,ui->sheet_X->value(), ui->sheet_Y->value()));
        ui->openGLWidget->repaint();
    }
}

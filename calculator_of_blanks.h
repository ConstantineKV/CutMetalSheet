#ifndef CALCULATOR_OF_BLANKS_H
#define CALCULATOR_OF_BLANKS_H
#include <QRect>
#include <QVector>
#include <blanks.h>

class calculator_of_blanks
{
    QVector<QRect> blanks_installed;
    QVector<blank_to_install> blanks_to_install;
    QVector<blank_to_install> blanks_not_installed;
    QRect metal_sheet;

public:
    void calculate_blanks_to_install();
    void set_metal_sheet(int x_size, int y_size);
    void set_blanks_to_install(QVector<blank_to_install> blanks_to_install);
    QVector<QRect> get_blanks_installed();
    QVector<blank_to_install> get_blanks_not_installed();
    int get_consumed();
    int get_waste();
private:
    bool check_rectangle_crossing(QRect first_rect, QRect second_rect);
    bool check_blank_out_of_border(QRect steel_sheet, QRect blank);
    bool check_blank_crossing_others(QRect blank);
    bool install_the_blank(int x_size, int y_size, QRect metal_sheet);


};

#endif // CALCULATOR_OF_BLANKS_H

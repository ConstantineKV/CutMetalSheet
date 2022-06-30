#include <calculator_of_blanks.h>
#include <QMessageBox>

void calculator_of_blanks::set_metal_sheet(int x_size, int y_size)
{
    metal_sheet.setLeft(0);
    metal_sheet.setTop(0);
    metal_sheet.setWidth(x_size);
    metal_sheet.setHeight(y_size);
}

void calculator_of_blanks::set_blanks_to_install(QVector<blank_to_install> blanks_to_install)
{
    this->blanks_to_install = blanks_to_install;
}

QVector<QRect> calculator_of_blanks::get_blanks_installed()
{
    return blanks_installed;
}

QVector<blank_to_install> calculator_of_blanks::get_blanks_not_installed()
{
    return blanks_not_installed;
}

void calculator_of_blanks::calculate_blanks_to_install()
{
    //сортируем их по размеру
    std::sort(blanks_to_install.begin(), blanks_to_install.end(), [](blank_to_install first, blank_to_install second)
    {
        int first_square, second_square;
        first_square = first.X_size * first.Y_size;
        second_square = second.Y_size * second.Y_size;
        return (first_square > second_square);
    });

    //очищаем список установленных заготовок
    blanks_installed.clear();

    //добавляем заготовки
    for (QVector<blank_to_install>::iterator it_size = blanks_to_install.begin(); it_size != blanks_to_install.end(); ++it_size)
    {
        int X_size, Y_size;

        //если ширина заготовки больше, чем высота, то переворачиваем - экономим место
        if (it_size->X_size > it_size->Y_size)
        {
            X_size = it_size->Y_size;
            Y_size = it_size->X_size;
        }
        else
        {
            X_size = it_size->X_size;
            Y_size = it_size->Y_size;
        }

        if (it_size->X_size != it_size->Y_size)
        {
            //сначала пробуем разместить вертикально, так как это занимает меньшую длинну листа
            if (install_the_blank(X_size, Y_size, metal_sheet))
                continue;
            else
            {
                if (install_the_blank(Y_size, X_size, metal_sheet))
                    continue;
                else
                    blanks_not_installed.push_back(*it_size);
            }
        }
        else
        {
            if (install_the_blank(X_size, Y_size, metal_sheet))
                continue;
            else
                blanks_not_installed.push_back(*it_size);
        }
    }
}

bool calculator_of_blanks::install_the_blank(int x_size, int y_size, QRect metal_sheet)
{
    //размещаем заготовку в левом верхнем углу
    QRect blank_to_install(0,0,x_size, y_size);

    if (blanks_installed.size() == 0)
    {
        //если заготовка не выходит за границы листа, то размещаем её
        if (!check_blank_out_of_border(metal_sheet, blank_to_install))
        {
            blanks_installed.push_back(blank_to_install);
            return true;
        }
        else
            return false;
    }
    else
    {
        //сортировка blanks_position
        if (blanks_installed.size() > 1)
        {
            std::sort(blanks_installed.begin(), blanks_installed.end(), [](QRect first, QRect second)
            {
                int first_size = first.left() + first.width();
                int second_size = second.left() + second.width();
                return (first_size < second_size);
            });
        }

        for (QVector<QRect>::iterator it_installed = blanks_installed.begin(); it_installed != blanks_installed.end(); ++it_installed)
        {
            //размещаем заготовку снизу от уже размещённой заготовки
            int installed_left = it_installed->left();
            int installed_top = it_installed->top();
            int installed_x = it_installed->width();
            int installed_y = it_installed->height();

            blank_to_install.setLeft(installed_left);
            blank_to_install.setTop(installed_top + installed_y);
            blank_to_install.setWidth(x_size);
            blank_to_install.setHeight(y_size);

            //проверяем, что заготовка не выходит за пределы листа и не пересекается с уже установленными заготовками
            bool out_of_border = check_blank_out_of_border(metal_sheet, blank_to_install);
            bool crossing_others = check_blank_crossing_others(blank_to_install);
            if (!check_blank_out_of_border(metal_sheet, blank_to_install) && (!check_blank_crossing_others(blank_to_install)))
            {
                blanks_installed.push_back(blank_to_install);
                return true;
            }

            //условия не удовлетворены, размещаем заготовку справа от уже установленной
            blank_to_install.setLeft(installed_left + installed_x);
            blank_to_install.setTop(installed_top);
            blank_to_install.setWidth(x_size);
            blank_to_install.setHeight(y_size);

            out_of_border = check_blank_out_of_border(metal_sheet, blank_to_install);
            crossing_others = check_blank_crossing_others(blank_to_install);

            //проверяем, что заготовка не выходит за пределы листа и не пересекается с уже установленными заготовками
            if (!check_blank_out_of_border(metal_sheet, blank_to_install) && (!check_blank_crossing_others(blank_to_install)))
            {
                blanks_installed.push_back(blank_to_install);
                return true;
            }
        }
        return false;
    }
}
bool calculator_of_blanks::check_blank_out_of_border(QRect steel_sheet, QRect blank)
{
    if (blank.left() < steel_sheet.left())
        return true;

    if (blank.top() < steel_sheet.top())
        return true;

    if (blank.left() + blank.width() > steel_sheet.left() + steel_sheet.width())
        return true;

    if (blank.top() + blank.height() > steel_sheet.top() + steel_sheet.height())
        return true;

    return false;
    }

bool calculator_of_blanks::check_rectangle_crossing(QRect first_rect, QRect second_rect)
{
    QRect rect_inter;
    rect_inter = first_rect&second_rect;
    if (rect_inter.isNull())
        return false;
    else
        return true;
}

bool calculator_of_blanks::check_blank_crossing_others(QRect blank)
{
    for (int i = 0; i < blanks_installed.size(); i++)
    {
        if (check_rectangle_crossing(blank, blanks_installed[i]))
            return true;
    }
    return false;
}

int calculator_of_blanks::get_consumed()
{
    int max_consumed = 0;
    for (int i = 0; i < blanks_installed.size(); i++)
    {
        int consumed = blanks_installed[i].left() + blanks_installed[i].width();
        if (consumed > max_consumed)
            max_consumed = consumed;
    }
    return max_consumed;
}

int calculator_of_blanks::get_waste()
{
    if (blanks_installed.size() == 0)
        return 0;

    int total_consumed = metal_sheet.height() * get_consumed();
    int total_square = 0;

    for (int i = 0; i < blanks_installed.size(); i++)
    {
        total_square += blanks_installed[i].height() * blanks_installed[i].width();
    }

    return (total_consumed - total_square);
}

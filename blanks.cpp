#include <blanks.h>
#include <QFont>
blanks::blanks(QWidget* parent) : QWidget(parent)
{

    //single_blank* bl = new single_blank(this, 25, 10);
    blanks_list.push_back(new single_blank(this, 25, 10));
    //bl = new single_blank(this, 25, 55);
    blanks_list.push_back(new single_blank(this, 25, 55));

    buttonPlus = new QPushButton(this);
    buttonMinus = new QPushButton(this);

    QFont font;
    //задаём геометрию и шрифт кнопке +
    buttonPlus->setGeometry(355, 50, 30, 30);
    buttonPlus->setText("+");
    font.setBold(true);
    font.setFamily("Times New Roman");
    font.setPointSize(20);
    buttonPlus->setFont(font);

    //задаём геометрию и шрифт кнопке -
    buttonMinus->setGeometry(355, 90, 30, 30);
    buttonMinus->setText("-");
    font.setBold(true);
    font.setFamily("Times New Roman");
    font.setPointSize(20);
    buttonMinus->setFont(font);

    //соединения
    connect(buttonPlus, SIGNAL(clicked()), this, SLOT(addBlank()));
    connect(buttonMinus, SIGNAL(clicked()), this, SLOT(removeBlank()));
}

    QVector<blank_to_install> blanks::get_blanks_to_install()
    {
        QVector<blank_to_install> blanks_to_install;
        for(QList<single_blank*>::iterator it = blanks_list.begin(); it != blanks_list.end(); it++)
        {
            int value_x = (*it)->getX();
            int value_y = (*it)->getY();

            if((value_x > 0) && (value_y > 0))
            {
                blanks_to_install.push_back({value_x, value_y});
            }
            else
                continue;
        }
        return blanks_to_install;
    }

void blanks::addBlank()
{
    if(blanks_list.size() < 7)
    {
        int blanks_number = blanks_list.size();
        blanks_list.push_back(new single_blank(this, 25, 10 + 45 * blanks_number));
        blanks_number = blanks_list.size();
    }
}

void blanks::removeBlank()
{
    if(blanks_list.size() > 1)
    {
       int blanks_number = blanks_list.size();
       delete blanks_list.last();
        blanks_list.pop_back();


    }
}

blanks::~blanks()
{
    delete buttonPlus;
    delete buttonMinus;
    for(QList<single_blank*>::iterator it = blanks_list.begin(); it != blanks_list.end(); it++)
    {
        delete *it;
    }
}

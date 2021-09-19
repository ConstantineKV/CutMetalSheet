#ifndef BLANK_H
#define BLANK_H

#include <QWidget>
#include <QFrame>
#include <QSpinBox>

class single_blank : public QFrame
{
    QSpinBox* spinBox_X;
    QSpinBox* spinBox_Y;
public:
    single_blank();
    explicit single_blank(QWidget* parent, int x_pos, int y_pos);
    single_blank(const single_blank& other_bl);
    ~single_blank();
    int getX();
    int getY();

    single_blank& operator =(const single_blank& other_bl);
};


#endif // BLANK_H

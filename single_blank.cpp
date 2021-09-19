#include <single_blank.h>

single_blank::single_blank()
{
    delete spinBox_X;
    delete spinBox_Y;
}

single_blank::single_blank(QWidget* parent, int x_pos, int y_pos) : QFrame(parent)
{
    this->setGeometry(x_pos,y_pos,325,45);
    this->setFrameShape(QFrame::Panel);
    spinBox_X = new QSpinBox(this);
    spinBox_Y = new QSpinBox(this);
    spinBox_X->setGeometry(25,10,125,25);
    spinBox_Y->setGeometry(175,10,125,25);
    spinBox_X->setMaximum(1000);
    spinBox_X->setMinimum(0);
    spinBox_Y->setMaximum(700);
    spinBox_Y->setMinimum(0);
    this->show();

}

single_blank::single_blank(const single_blank& other_bl) : QFrame((QWidget*)other_bl.parent())
{

    this->setGeometry(other_bl.geometry());
    this->setFrameShape(other_bl.frameShape());
    spinBox_X = new QSpinBox(this);
    spinBox_Y = new QSpinBox(this);
    spinBox_X->setGeometry(other_bl.spinBox_X->geometry());
    spinBox_Y->setGeometry(other_bl.spinBox_Y->geometry());
    spinBox_X->setMaximum(other_bl.spinBox_X->maximum());
    spinBox_Y->setMaximum(other_bl.spinBox_Y->maximum());

}

single_blank&  single_blank::operator =(const single_blank& other_bl)
{
    this->setGeometry(other_bl.geometry());
    this->setFrameShape(other_bl.frameShape());
    spinBox_X = new QSpinBox(this);
    spinBox_Y = new QSpinBox(this);
    spinBox_X->setGeometry(other_bl.spinBox_X->geometry());
    spinBox_Y->setGeometry(other_bl.spinBox_Y->geometry());
    spinBox_X->setMaximum(other_bl.spinBox_X->maximum());
    spinBox_Y->setMaximum(other_bl.spinBox_Y->maximum());
}

single_blank::~single_blank()
{
    delete spinBox_X;
    delete spinBox_Y;
}

int single_blank::getX()
{
    return spinBox_X->value();
}

int single_blank::getY()
{
    return spinBox_Y->value();
}

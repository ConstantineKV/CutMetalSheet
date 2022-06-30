#include "metal_sheet.h"

metal_sheet::metal_sheet(QWidget* parent) : QOpenGLWidget(parent)
{

}
void metal_sheet::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1200, 1000, 0, 0, 1);
}

void metal_sheet::resizeGL(int w, int h)
{
    glClearColor(0.3, 0.3, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, w, h);
}

void metal_sheet::paintGL()
{
    glClearColor(1, 1, 1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //glColor3d(0.0, 0, 0);
    //paintRectangleEmpty(metal_sheet_rect, 2);
    glColor3d(0.0, 1, 1);
    paintRectangle(metal_sheet_rect);
    if (blanks_installed.size() != 0)
    {
        for (QVector<QRect>::iterator it = blanks_installed.begin(); it != blanks_installed.end(); it++)
        {
            glColor3d(0,0,0);
            paintRectangleEmpty(*it, 1);
        }
    }

}


void metal_sheet::paintRectangle(QRect rectangle)
{
    int left = rectangle.left();
    int top = rectangle.top();
    int width = rectangle.width();
    int height = rectangle.height();
    glBegin(GL_QUADS);
    glVertex2i(left, top);
    glVertex2i(left + width, top);
    glVertex2i(left + width, top + height);
    glVertex2i(left, top + height);
    glEnd();
}

void metal_sheet::paintRectangleEmpty(QRect rectangle, int line_width)
{
    glLineWidth(line_width);
    int left = rectangle.left();
    int top = rectangle.top();
    int width = rectangle.width();
    int height = rectangle.height();
    glBegin(GL_LINE_LOOP);
    glVertex2i(left, top);
    glVertex2i(left + width, top);
    glVertex2i(left + width, top + height);
    glVertex2i(left, top + height);
    glEnd();
}

void metal_sheet::setMetalSheet(QRect sheet)
{
    metal_sheet_rect.setLeft(sheet.left() + 10);
    metal_sheet_rect.setTop(sheet.top() + 10);
    metal_sheet_rect.setWidth(sheet.width());
    metal_sheet_rect.setHeight(sheet.height());
    blanks_installed.clear();
    update();
}

void metal_sheet::setBlanksToInstall(QVector<QRect> blanks_installed)
{
    this->blanks_installed.clear();
    for (QVector<QRect>::iterator it = blanks_installed.begin(); it != blanks_installed.end(); ++it)
    {
        QRect blank_to_install;
        blank_to_install.setLeft(it->left() + 10);
        blank_to_install.setTop(it->top() + 10);
        blank_to_install.setWidth(it->width());
        blank_to_install.setHeight(it->height());
        this->blanks_installed.push_back(blank_to_install);
    }
}

#ifndef STEEL_SHEET_H
#define STEEL_SHEET_H
#include <QOpenGLWidget>
#include <QRect>
#include <QVector>

class metal_sheet : public QOpenGLWidget
{
    Q_OBJECT

    QRect metal_sheet_rect;
    QVector<QRect> blanks_installed;
    const int offset = 10;
public:
    metal_sheet();
    metal_sheet(QWidget* parent);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    //функции отрисовки геометрических фигур
    void paintRectangle(QRect rectangle);
    void paintRectangleEmpty(QRect rectangle, int line_width);

    //функции задания параметров объектов
    void setMetalSheet(QRect sheet);
    void setBlanksToInstall(QVector<QRect> blanks_to_install);
};

#endif // STEEL_SHEET_H

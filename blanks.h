#ifndef BLANKS_H
#define BLANKS_H
#include <QWidget>
#include <QList>
#include <QVector>
#include <QPushButton.h>
#include <single_blank.h>

struct blank_to_install
{
    int X_size;
    int Y_size;
};

class blanks : public QWidget
{
    Q_OBJECT

    QList<single_blank*> blanks_list;
    QPushButton* buttonPlus;
    QPushButton* buttonMinus;
public:

    blanks(QWidget* parent);
    ~blanks();
    QVector<blank_to_install> get_blanks_to_install();
public slots:
    void addBlank();
    void removeBlank();
};

#endif // BLANKS_H

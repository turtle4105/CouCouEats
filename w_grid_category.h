#ifndef W_GRID_CATEGORY_H
#define W_GRID_CATEGORY_H

#include <QWidget>
#include <QStringList>
#include <QPushButton>
#include <QGridLayout>
const int SIZE = 60;

namespace Ui {
class w_grid_category;
}

class w_grid_category : public QWidget
{
    Q_OBJECT

public:
    explicit w_grid_category(QWidget *parent = nullptr);

    QStringList categories;
    ~w_grid_category();

private:
    Ui::w_grid_category *ui;
};

#endif // W_GRID_CATEGORY_H

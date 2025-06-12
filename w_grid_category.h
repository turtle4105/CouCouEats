#ifndef W_GRID_CATEGORY_H
#define W_GRID_CATEGORY_H

#include <QWidget>
#include <QStringList>
#include <QToolButton>
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
    int initial_count = 9;
    int max_column = 5;
    QVector<QToolButton*> extraBtns;
    QMap<QString, QString> categoryImageMap;
    QStringList categories;
    void showExtraCategories(int row, int col, QGridLayout *layout);
    void showMoreBtn(int row, int col, QGridLayout *layout);
    void hideExtraCategories(QGridLayout *layout, QPushButton *foldBtn);

    ~w_grid_category();

private:
    Ui::w_grid_category *ui;
};

#endif // W_GRID_CATEGORY_H

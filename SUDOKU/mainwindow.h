#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QVector>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void Free();
    void Projection();
    void SolutionProjection(QVector<QVector<int>> &track);
    bool Solve(QVector<QVector<int>>& board);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

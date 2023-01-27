#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
private slots:
    void on_cadd_btn_clicked();
    void on_os_btn_clicked();
    void on_clean_btn_clicked();
    void on_pushButton_3_clicked();
    void on_action_triggered();
    void on_action_2_triggered();
    void on_R_W_btn_clicked();
    void on_R_W_RUN_clicked();
};

#endif // MAINWINDOW_H

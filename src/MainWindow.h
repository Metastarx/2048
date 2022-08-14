#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent> //键盘事件
#include <QPushButton>
#include <QPainter>//画图库
#include <QTime> //内置随机种子
#include <QMessageBox>//自定义消息提示框
#include <QMouseEvent>
#include <QWidget>
#include <QVBoxLayout>

#include <QMediaPlayer>

#include "mymessagebox.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    QPushButton *button;
    QPushButton *buttonClose;
    QPushButton *buttonHelp;
    QPushButton *buttonAbout;
    QPushButton *buttonMusic;
    int grid[4][4];
    int score = 0;//分数
    int max_score = 0;
    bool state;//游戏状态 1正常 0停止
    bool state_music;

    //wasd 操作函数
    void PressUp();
    void PressDown();
    void PressLeft();
    void pressRight();

    void myRand();

    struct Ns
    {
        int i;
        int j;
    };

private:
    Ui::MainWindow *ui;

    //窗口移动参数
    QPoint dPos;
    QPoint mousePos;
    QPoint windowPos;


};

#endif // MAINWINDOW_H

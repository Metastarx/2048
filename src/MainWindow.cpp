#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    // 设置按钮样式及悬浮、按下时的状态

    QMediaPlayer *player = new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile("for.mp3"));
    player->setVolume(50);
    player->play();
    state_music = 1;
//C:/Users/45451/Desktop/qtcode/keshe/2048/sound.mp
    ui->setupUi(this);
    //初始化

    for(int i = 0;i < 4;i++)
        for(int j = 0;j < 4;j++)
        {
            grid[i][j] = 0;
        }


    buttonAbout = new QPushButton("!",this);
    buttonAbout -> setGeometry(350,15,45,25);

    buttonHelp = new QPushButton("?",this);
    buttonHelp ->setGeometry(400,15,45,25);

    buttonMusic = new QPushButton("♫",this);
    buttonMusic ->setGeometry(300,15,45,25);

    buttonClose = new QPushButton("X",this);
    buttonClose -> setGeometry(450,15,45,25);//520,700


    buttonMusic->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);border:2px groove gray;border-radius:10px;padding:2px 4px;border-style: outset;}"
                                              "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                              "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
    buttonClose->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);border:2px groove gray;border-radius:10px;padding:2px 4px;border-style: outset;}"
                                              "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                              "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
    buttonAbout->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);border:2px groove gray;border-radius:10px;padding:2px 4px;border-style: outset;}"
                                              "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                              "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
    buttonHelp->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);border:2px groove gray;border-radius:10px;padding:2px 4px;border-style: outset;}"
                                              "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                              "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");

    button = new QPushButton("开始游戏",this);

    //button -> setStyleSheet("background-color:white;font-size:40px;color:black");
    button -> setStyleSheet("QPushButton{background-color: rgb(143,122,102);font-size:40px;border:2px groove gray;border-radius:10px;padding:2px 4px;color:white;border-style: outset;}"
                                              "QPushButton:hover{background-color:rgb(150,130,120); color: white;}"
                                              "QPushButton:pressed{background-color:rgb(143,122,102);border-style: inset;}");
    button -> setGeometry(140,540,250,120);

    //随机种子 时间
    qsrand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));

    connect(button ,QPushButton::clicked,
            [=]
    {
        //QMessageBox::about(this," ","开始游戏");
        QPoint globalPos = this->mapToGlobal(QPoint(0,0));
        MymessageBox *i = new MymessageBox("开始游戏");
        i->show();
        i->move(globalPos.x()+110,globalPos.y()+200);

        score=0;
        for (int i=0;i<4;i++)
        {
            for (int j=0;j<4;j++)
            {
                grid[i][j]=0;
            }
        }
        button->setText("重新游戏");
        int randi=qrand()%4;
        int randj=qrand()%4;
        grid[randi][randj]=2;

        state=true;
        update();

        });

    connect(buttonClose ,QPushButton::clicked,
        [=]
    {
    this->close();

    });

    connect(buttonHelp ,QPushButton::clicked,
        [=]
    {

        QPoint globalPos = this->mapToGlobal(QPoint(0,0));
        MymessageBox *i = new MymessageBox("WSAD控制方块上下左右移动");
        i->show();
        i->move(globalPos.x()+110,globalPos.y()+200);
    //QMessageBox::about(this,"游戏规则","WSAD控制方块上下左右移动");
    });

    connect(buttonMusic ,QPushButton::clicked,
            [=]
    {
        if(state_music == 1)
        {
            player->stop();
            state_music = 0;
            buttonMusic -> setText("♬");
//            qDebug() << "sd";
        }
        else
        {
            player->play();
            state_music = 1;
            buttonMusic -> setText("♫");
        }
    });

    connect(buttonAbout ,QPushButton::clicked,
        [=]
    {

        QPoint globalPos = this->mapToGlobal(QPoint(0,0));
        MymessageBox *i = new MymessageBox("计科2101 张宏远 211303131  \n遵循material design原则  ");
        i->show();
        i->move(globalPos.x()+110,globalPos.y()+200);

   // QMessageBox::about(this,"游戏信息","计科2101 张宏远 211303131  \n遵循material design原则  ");
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    //圆滑的边界
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(250,248,239,200)));
    QRect rect = this->rect();
    painter.drawRoundedRect(rect,10,10);



    //网格的打印
    QPainter p(this);
    p.setBrush(Qt::blue);
    p.setFont(QFont("微软雅黑",20,700,false));

    p.setBrush(QBrush(QColor(187,173,160,120)));
    p.drawRect(69,138,375,375);

//    p.setBrush(QBrush(QColor(187,173,160,120)));
//    p.drawRect(13,15,300,50);
//    p.drawRect(13,75,300,50);

    p.drawText(QPoint(20,55),"当前分数: "+QString::number(score));
    p.drawText(QPoint(20,115),"最高分数: "+QString::number(max_score));
    //grid的实现
    for(int i = 0;i < 4;i++)
        for(int j = 0;j < 4;j++)
        {
            p.setPen(Qt::transparent);

            if(grid[i][j] == 0)
            {
                p.setBrush(QBrush(QColor(170,160,150,120)));
                p.drawRect(i*90+80,j*90+150,85,85);
            }
            else if(grid[i][j] == 2)
            {
                p.setBrush(QBrush(QColor(238,228,218)));
                p.drawRect(i*90+80,j*90+150,85,85);
                p.setPen(Qt::black);
                p.setFont(QFont("微软雅黑",30,700,false));
                p.drawText(QRectF(i*90+80,j*90+150,85,85),QString::number(2),QTextOption(Qt::AlignCenter));
            }
            else if(grid[i][j] == 4)
            {
                p.setBrush(QBrush(QColor(238,225,201)));
                p.drawRect(i*90+80,j*90+150,85,85);
                p.setPen(Qt::black);
                p.setFont(QFont("微软雅黑",30,700,false));
                p.drawText(QRectF(i*90+80,j*90+150,85,85),QString::number(4),QTextOption(Qt::AlignCenter));
            }
            else if(grid[i][j] == 8)
            {
                p.setBrush(QBrush(QColor(243,178,122)));
                p.drawRect(i*90+80,j*90+150,85,85);
                p.setPen(Qt::black);
                p.setFont(QFont("微软雅黑",30,700,false));
                p.drawText(QRectF(i*90+80,j*90+150,85,85),QString::number(8),QTextOption(Qt::AlignCenter));
            }
            else if(grid[i][j] == 16)
            {
                p.setBrush(QBrush(QColor(246,150,100)));
                p.drawRect(i*90+80,j*90+150,85,85);
                p.setPen(Qt::black);
                p.setFont(QFont("微软雅黑",30,700,false));
                p.drawText(QRectF(i*90+80,j*90+150,85,85),QString::number(16),QTextOption(Qt::AlignCenter));
            }
            else if(grid[i][j] == 32)
            {
                p.setBrush(QBrush(QColor(247,124,95)));
                p.drawRect(i*90+80,j*90+150,85,85);
                p.setPen(Qt::black);
                p.setFont(QFont("微软雅黑",30,700,false));
                p.drawText(QRectF(i*90+80,j*90+150,85,85),QString::number(32),QTextOption(Qt::AlignCenter));
            }
            else if(grid[i][j] == 64)
            {
                p.setBrush(QBrush(QColor(247,95,59)));
                p.drawRect(i*90+80,j*90+150,85,85);
                p.setPen(Qt::black);
                p.setFont(QFont("微软雅黑",30,700,false));
                p.drawText(QRectF(i*90+80,j*90+150,85,85),QString::number(64),QTextOption(Qt::AlignCenter));
            }
            else if(grid[i][j] == 128)
            {
                p.setBrush(QBrush(QColor(237,208,115)));
                p.drawRect(i*90+80,j*90+150,85,85);
                p.setPen(Qt::black);
                p.setFont(QFont("微软雅黑",30,700,false));
                p.drawText(QRectF(i*90+80,j*90+150,85,85),QString::number(128),QTextOption(Qt::AlignCenter));
            }
            else if(grid[i][j] == 256)
            {
                p.setBrush(Qt::darkCyan);
                p.drawRect(i*90+80,j*90+150,85,85);
                p.setPen(Qt::black);
                p.setFont(QFont("微软雅黑",30,700,false));
                p.drawText(QRectF(i*90+80,j*90+150,85,85),QString::number(256),QTextOption(Qt::AlignCenter));
            }
            else if(grid[i][j] == 512)
            {
                p.setBrush(Qt::magenta);
                p.drawRect(i*90+80,j*90+150,85,85);
                p.setPen(Qt::black);
                p.setFont(QFont("微软雅黑",30,700,false));
                p.drawText(QRectF(i*90+80,j*90+150,85,85),QString::number(512),QTextOption(Qt::AlignCenter));
            }
            else if(grid[i][j] == 1024)
            {
                p.setBrush(Qt::darkMagenta);
                p.drawRect(i*90+80,j*90+150,85,85);
                p.setPen(Qt::black);
                p.setFont(QFont("微软雅黑",30,700,false));
                p.drawText(QRectF(i*90+80,j*90+150,85,85),QString::number(1024),QTextOption(Qt::AlignCenter));
            }
            else if(grid[i][j] == 2048)
            {
                p.setBrush(Qt::blue);
                p.drawRect(i*90+80,j*90+150,85,85);
                p.setPen(Qt::black);
                p.setFont(QFont("微软雅黑",30,700,false));
                p.drawText(QRectF(i*90+80,j*90+150,85,85),QString::number(2048),QTextOption(Qt::AlignCenter));
            }
            else if(grid[i][j] == 4096)
            {
               QMessageBox::about(this,"游戏通关！","分数为："+QString::number(score)+" ");
            }
            else
            {
                p.setBrush(Qt::darkBlue);
                p.drawRect(i*90+85,j*90+120,85,85);
                p.setPen(Qt::black);
                p.setFont(QFont("微软雅黑",30,700,false));
                p.drawText(QRectF(i*90+85,j*90+120,85,85),QString::number(grid[i][j]),QTextOption(Qt::AlignCenter));
            }
        }

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!state)
    {
        return;
    }
    switch (event -> key()) {
    case Qt::Key_W:
        PressUp();
        break;
    case Qt::Key_S:
        PressDown();
        break;
    case Qt::Key_A:
        PressLeft();
        break;
    case Qt::Key_D:
        pressRight();
        break;
    default:
        return;//忽略其他按键
    }
    myRand();
    update();//刷新
}

//window可移动函数
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();//窗口相当于桌面的位置
    this->mousePos = event->globalPos();//触发点相对与桌面的位置
    this->dPos = mousePos - windowPos;//触发点与窗口的相对位置
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event ->globalPos() - this->dPos);
}

void MainWindow::PressUp()//i为列 j为行
{
    //相加
    for (int i=0;i<4;i++)
        for (int j=0;j<3;j++)
        {
            if(grid[i][j] == 0)
                continue;
            for(int p = j + 1;p < 4;p++)
            {
                if(grid[i][p]==0)
                    continue;
                if(grid[i][p] == grid[i][j])
                {
                    grid[i][j] *= 2;
                    grid[i][p] = 0;
                    score+=grid[i][j];
                    break;
                }
            }

        }
    //移动
    for (int i=0;i<4;i++)
        for (int j=1;j<4;j++)
        {
            if(grid[i][j]==0)
                continue;

            for (int p=0;p<j;p++)
                if(grid[i][p]==0) //查看前面是否有空格子可移动
                {
                    grid[i][p]=grid[i][j];
                    grid[i][j]=0;
                    break;
                }
        }

}

void MainWindow::PressDown()
{
    //相加
    for (int i=0;i<4;i++)
        for (int j=3;j>0;j--)
        {
            if(grid[i][j] == 0)
                continue;
            for(int p = j - 1;p >= 0;p--)
            {
                if(grid[i][p]==0)
                    continue;
                if(grid[i][p] == grid[i][j])
                {
                    grid[i][j] *= 2;
                    grid[i][p] = 0;
                    score+=grid[i][j];
                    break;
                }
            }

        }
    //移动
    for (int i=0;i<4;i++)
        for (int j=2;j >= 0;j--)
        {
            if(grid[i][j]==0)
                continue;

            for (int p=3;p>j;p--)
                if(grid[i][p]==0) //查看前面是否有空格子可移动
                {
                    grid[i][p]=grid[i][j];
                    grid[i][j]=0;
                    break;
                }
        }
}

void MainWindow::PressLeft()
{
    //相加
    for (int j=0;j<4;j++)
        for (int i=0;i<3;i++)
        {
            if(grid[i][j] == 0)
                continue;
            for(int p = i+1;p < 4;p++)
            {
                if(grid[p][j]==0)
                    continue;
                if(grid[p][j] == grid[i][j])
                {
                    grid[i][j] *= 2;
                    grid[p][j] = 0;
                    score+=grid[i][j];
                    break;
                }
            }

        }
    //移动
    for (int j=0;j<4;j++)
        for (int i=1;i<4;i++)
        {
            if(grid[i][j]==0)
                continue;

            for (int p=0;p<i;p++)
                if(grid[p][j]==0) //查看前面是否有空格子可移动
                {
                    grid[p][j]=grid[i][j];
                    grid[i][j]=0;
                    break;
                }
        }

}

void MainWindow::pressRight()
{
    //相加
    for (int j=0;j<4;j++)
        for (int i=3;i > 0;i--)
        {
            if(grid[i][j] == 0)
                continue;
            for(int p = i-1;p >= 0;p--)
            {
                if(grid[p][j]==0)
                    continue;
                if(grid[p][j] == grid[i][j])
                {
                    grid[i][j] *= 2;
                    grid[p][j] = 0;
                    score+=grid[i][j];
                    break;
                }
            }

        }
    //移动
    for (int j=0;j<4;j++)
        for (int i=2;i>=0;i--)
        {
            if(grid[i][j]==0)
                continue;

            for (int p=3;p>i;p--)
                if(grid[p][j]==0) //查看前面是否有空格子可移动
                {
                    grid[p][j]=grid[i][j];
                    grid[i][j]=0;
                    break;
                }
        }
}

void MainWindow::myRand()
{
    int i=0,j=0;
    //找出格子
    struct Ns n[15];
    int max = 0;
    int ni=0;
    for (i=0;i<4;i++)
    {
        for (j=0;j<4;j++)
        {
            if(grid[i][j] > max)
                max = grid[i][j];
            if(grid[i][j]==0){
                n[ni].i=i;
                n[ni].j=j;
                ni++;
            }
        }
    }

    //判断游戏是否结束
    if (ni==0)
    {
        for (i=0;i<4;i++)
        {
            for (j=0;j<3;j++)
            {
                if(grid[i][j]==grid[i][j+1])
                {
                    return;
                }
            }
        }
        for (j=0;j<4;j++)
        {
            for (i=0;i<3;i++)
            {
                if(grid[i][j] == grid[i+1][j])
                {
                    return;
                }
            }
        }

        if(score > max_score)
        {
            max_score = score;


        }


        QMessageBox::about(this,"游戏失败！","分数为："+QString::number(score)+" ");
        return;
    }

    int rand = qrand()%ni;
    int randnum = qrand()%4+1;

    //增加游戏难度
    if(max <= 64 )
    grid[n[rand].i][n[rand].j]=2;
    else
    {
        if(randnum == 1 || randnum == 2 || randnum == 3)
        grid[n[rand].i][n[rand].j] = 2;
        else
        grid[n[rand].i][n[rand].j] = 4;

    }

}



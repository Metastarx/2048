#include "mymessagebox.h"
#include <QDebug>

//MymessageBox::MymessageBox()
//{


//    setWindowFlags(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground);
//    this->resize(300,180);

//    btn_close = new QPushButton("X",this);
//    btn_close->setGeometry(240,15,45,25);
//    btn_close->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);border:2px groove gray;border-radius:10px;padding:2px 4px;border-style: outset;}"
//                           "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
//                           "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");

//    connect(btn_close,QPushButton::clicked,
//            [=]
//    {
//        this->close();
//    });

//    word = "a";

//    update();

//}


MymessageBox::MymessageBox(QString text)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    this->resize(300,180);

    btn_close = new QPushButton("X",this);
    btn_close->setGeometry(240,15,45,25);
    btn_close->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);border:2px groove gray;border-radius:10px;padding:2px 4px;border-style: outset;}"
                           "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                           "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");

    connect(btn_close,QPushButton::clicked,
            [=]
    {
        this->close();
    });

    this->setWindowTitle(text);

    word = text;
    update();
}


void MymessageBox::paintEvent(QPaintEvent *)
{
    //圆滑的边界
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(250,248,239,255)));
    QRect rect = this->rect();
    painter.drawRoundedRect(rect,10,10);

//    if(word != "a")
//    {
        painter.setFont(QFont("微软雅黑",10,700,false));
        painter.drawText(QRectF(50,50,195,100),word,QTextOption(Qt::AlignCenter));
//    }

}


void MymessageBox::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();//窗口相当于桌面的位置
    this->mousePos = event->globalPos();//触发点相对与桌面的位置
    this->dPos = mousePos - windowPos;//触发点与窗口的相对位置
}
void MymessageBox::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event ->globalPos() - this->dPos);
}

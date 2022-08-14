#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QString>
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>

class MymessageBox : public QDialog
{
public:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    MymessageBox(QString text);

    MymessageBox();
    QPushButton *btn_close;
    QString word;

private:
    QPoint dPos;
    QPoint mousePos;
    QPoint windowPos;
};

#endif // MYMESSAGEBOX_H

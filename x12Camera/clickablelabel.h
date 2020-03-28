#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

//Reference1: https://wiki.qt.io/Clickable_QLabel
//Reference2: http://hk.uwenku.com/question/p-xlzftvkv-bgb.html

#include <QLabel>
#include <QWidget>
#include <Qt>


class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
//    ClickableLabel();
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
        ~ClickableLabel();

signals:
    void clicked();

protected:
    void mouseReleaseEvent(QMouseEvent* event);
};

#endif // CLICKABLELABEL_H

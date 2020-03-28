#ifndef QCLICKABLELABEL_H
#define QCLICKABLELABEL_H

//Reference1: https://wiki.qt.io/Clickable_QLabel
//Reference2: http://hk.uwenku.com/question/p-xlzftvkv-bgb.html

#include <QLabel>
#include <QWidget>
#include <Qt>

class QClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~QClickableLabel();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // QCLICKABLELABEL_H

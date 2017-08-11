#include "graphicsview.h"

#include <qmath.h>

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    this->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    qreal factor = qPow(1.2, event->delta() / 240.0);
    scale(factor, factor);

    event->accept();
}

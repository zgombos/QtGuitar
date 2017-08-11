#include "graphicsnoteitem.h"

#include <QRadialGradient>

GraphicsNoteItem::GraphicsNoteItem(const QString &name, const QColor &color) : my_name{name}, my_color{color}
{}

QRectF GraphicsNoteItem::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(0-penWidth/2, 0-penWidth/2, 30+penWidth, 30+penWidth);
}

void GraphicsNoteItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Draw the note circle
    QRectF ellipse = boundingRect();
    QRadialGradient gradient = QRadialGradient(0, 8, 20, 0, 8);
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(0.8, my_color);
    painter->setBrush(gradient);
    painter->setPen(my_color);
    painter->drawEllipse(ellipse);

    // Draw the note name inside the circle
    painter->setFont(QFont("Verdana", 8));
    painter->setPen(QColor(Qt::white));
    painter->drawText(ellipse, Qt::AlignCenter, my_name);
}

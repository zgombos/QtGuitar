#ifndef GRAPHICSNOTEITEM_H
#define GRAPHICSNOTEITEM_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QWidget>
#include <QString>
#include <QColor>

class GraphicsNoteItem : public QGraphicsItem
{
public:
    GraphicsNoteItem(const QString &name, const QColor &color);
    int type() const override { return Type; }
    QRectF boundingRect() const override;
    enum {Type = UserType + 1};

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QString my_name;
    QColor my_color;
};

#endif // GRAPHICSNOTEITEM_H

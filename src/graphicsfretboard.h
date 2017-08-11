#ifndef GRAPHICSFRETBOARD_H
#define GRAPHICSFRETBOARD_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QWidget>
#include <QList>

#include "note.h"

class GraphicsFretboard : public QGraphicsItem
{
public:
    GraphicsFretboard(int frets, QList<Note> &tuning);
    int type() const override { return Type; }
    QRectF boundingRect() const override;
    QList<QList<QPoint>> getNoteCoordinateList() const { return noteCoordinateList; }
    void setTuning(QList<Note> &tuning);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

private:
    enum {Type = UserType + 2};
    int my_frets;
    QList<Note> my_tuning;
    QList<int> fretDistanceList;
    const int stringDistance {30}; // Distance between two strings
    QList<QPoint> noteCoordinate1;
    QList<QPoint> noteCoordinate2;
    QList<QPoint> noteCoordinate3;
    QList<QPoint> noteCoordinate4;
    QList<QPoint> noteCoordinate5;
    QList<QPoint> noteCoordinate6;
    QList<QList<QPoint>> noteCoordinateList;
};

#endif // GRAPHICSFRETBOARD_H

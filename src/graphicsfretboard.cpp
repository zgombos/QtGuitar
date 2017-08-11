#include "graphicsfretboard.h"

#include <QDebug>

GraphicsFretboard::GraphicsFretboard(int frets, QList<Note> &tuning) : my_frets{frets + 2}, my_tuning{tuning}
{
    // Set fret distance.This firts one is shorter (30), the rest is (60)
    fretDistanceList.append(0);
    fretDistanceList.append(30);
    int d {30};
    for (int i{2}; i < my_frets; ++i)
    {
        fretDistanceList.append(d);
        d += 60;
    }

    // Note coordinates on the fretboard
    for (int i{0}; i < fretDistanceList.size()-1; ++i)
    {
        // Reduce with half of the note size(15)
        int x = fretDistanceList[i] + ((fretDistanceList[i + 1] - fretDistanceList[i]) / 2) - 15;
        int y = 0;

        noteCoordinate1.append(QPoint(x, y));
        noteCoordinate2.append(QPoint(x, y + stringDistance));
        noteCoordinate3.append(QPoint(x, y + stringDistance * 2));
        noteCoordinate4.append(QPoint(x, y + stringDistance * 3));
        noteCoordinate5.append(QPoint(x, y + stringDistance * 4));
        noteCoordinate6.append(QPoint(x, y + stringDistance * 5));

        noteCoordinateList = {noteCoordinate6, noteCoordinate5, noteCoordinate4,
                           noteCoordinate3, noteCoordinate2, noteCoordinate1};
    }
}

QRectF GraphicsFretboard::boundingRect() const
{
    return QRectF(-60, -30, fretDistanceList.last() + 120, stringDistance * 9);
}

void GraphicsFretboard::setTuning(QList<Note> &tuning)
{
    my_tuning = tuning;
}

void GraphicsFretboard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);

    // Draw boundingRect
    QRectF bounding = boundingRect();
    painter->setBrush(Qt::gray);
    painter->drawRect(bounding);

    // Draw background
    QRectF rectBackground = QRectF(0, 0, fretDistanceList.last(), stringDistance * 6);
    painter->setBrush(QColor(51, 25, 0));
    painter->drawRect(rectBackground);

    // Draw the first fret with white
    QRectF rectFirst = QRectF(0, -1, fretDistanceList[1], (stringDistance * 6) + 2);
    painter->setPen(Qt::lightGray);
    painter->setBrush(Qt::lightGray);
    painter->drawRect(rectFirst);

    // Draw inlays
    QRectF source = QRectF(0, 0, 446, 585);
    for (int i{0}; i < 22; ++i)
    {
        if (i==3 || i==5 || i==7 || i ==9 || i==15 || i==17 || i==19 || i ==21)
        {
            int x = noteCoordinate1[i].x();
            QRectF target = QRectF(x-13, 30, 56, 120);
            QPixmap image = QPixmap(":/Inlays/Inlays/skull.png");
            painter->drawPixmap(target, image, source);
        }
    }

    // Draw the 12th inlay
    QRectF centralSrc = QRectF(0, 0, 590, 281);
    for (int i{0}; i < 2; ++i)
    {
        int x = noteCoordinate1[11].x();
        QRectF centralDst = QRectF(x-13, i * 90, 180, 86);
        QPixmap central = QPixmap(":/Inlays/Inlays/skull_laydown.png");
        painter->drawPixmap(centralDst, central, centralSrc);
    }

    // Draw the guitar strings
    QPen stringPen = QPen();
    stringPen.setColor(QColor(Qt::white));
    painter->setPen(QColor(Qt::white));
    for (int i{0}; i < 6; ++i)
    {
        stringPen.setWidth(i);
        painter->setPen(stringPen);
        painter->drawLine(0, (stringDistance * i) + 15, fretDistanceList.last(), (stringDistance * i) + 15);
    }

    // Draw frets
    QPen fretPen = QPen();
    fretPen.setColor(QColor(Qt::white));
    fretPen.setWidth(4);
    painter->setPen(fretPen);
    for (auto i : fretDistanceList)
    {
        painter->drawLine(i, 0, i, stringDistance * 6);
    }

    // Draw fret numbers
    painter->setFont(QFont("Verdana", 12));
    painter->setPen(QColor(Qt::white));
    for (int i{0}; i < fretDistanceList.length()-1; ++i)
    {
        int x = fretDistanceList[i] + ((fretDistanceList[i + 1] - fretDistanceList[i]) / 2) - 8;
        painter->drawText(x, stringDistance * 7, QString::number((i)));     // Cast int to QString
    }

    // Draw tunning
    int y = (stringDistance * 6) - 10;
    for (const auto &t : my_tuning)
    {
        painter->drawText(-30, y, t.getName());
        y -= stringDistance;
    }
}

#ifndef SCALE_H
#define SCALE_H

#include <QString>
#include <QStringList>
#include <QList>

enum Hint { BOX_PATTERN, THREE_NOTES, FOUR_NOTES };

class Scale
{
public:
    Scale(const QString &name,  const QList<int> &interval, const Hint &hint);
    QStringList getScaleNote(const QString &root);
    QString getName() const {return name;}
    QList<int> getInterval() const {return interval;}
    Hint getHint() const {return hint;}

private:
    QString name;
    QList<int> interval;
    Hint hint;
    const QStringList noteList = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
    QStringList notes;
};

#endif // SCALE_H

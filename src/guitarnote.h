#ifndef GUITARNOTE_H
#define GUITARNOTE_H

#include <QString>
#include <QDebug>
#include "note.h"

class GuitarNote
{
public:
    GuitarNote();
    GuitarNote(QString &name, int octave, int pos);
    GuitarNote(Note &note, int pos);
    QString getName() const {return myName;}
    int getOctave() const {return myOctave;}
    int getPos() const {return myPos;}

private:
    QString myName;
    int myOctave;
    int myPos;
};

inline bool operator==(const GuitarNote &note1, const GuitarNote &note2)
{
    return (note1.getName() == note2.getName() && note1.getOctave() == note2.getOctave() && note1.getPos() == note2.getPos());
}

inline QDebug operator<<(QDebug out, const GuitarNote &note)
{
    out.nospace() << "(" << note.getName() << "/" << note.getOctave() << "-" << note.getPos() << ")";
    return out;
}

#endif // GUITARNOTE_H

#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <QDebug>

class Note
{
public:
    Note(QString name, int octave);
    QString getName() const {return myName;}
    int getOctave() const {return myOctave;}

private:
    QString myName;
    int myOctave;

};

// Need it for QMap
inline bool operator==(const Note &note1, const Note &note2)
{
    return (note1.getName() == note2.getName() && note1.getOctave() == note2.getOctave());
}

// Need it for QMap
inline bool operator<(const Note &note1, const Note &note2)
{
    if (note1.getName() != note2.getName())
        return note1.getName() < note2.getName();
    return note1.getOctave() < note2.getOctave();
}

inline QDebug operator<<(QDebug out, const Note &note)
{
    out.nospace() << "(" << note.getName() << "/" << note.getOctave() << ")";
    return out;
}

#endif // NOTE_H

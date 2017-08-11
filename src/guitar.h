#ifndef GUITAR_H
#define GUITAR_H

#include <QList>
#include <QMap>
#include "note.h"
#include "guitarnote.h"

class Guitar
{
public:
    Guitar(int frets, QList<Note> tune);
    QList<QList<Note>> getstringList() {return stringNoteList;}
    QList<QList<GuitarNote>> getAllScaleNotes(const QStringList &scale);
    QList<QList<GuitarNote>> notePerStringView(const QStringList &scale, int startPos, int size);
    QList<QList<GuitarNote>> boxPatternView(QStringList &scale, int startPos);
    QList<GuitarNote> oneStringView(QStringList &scale, int stringNum);
    void setTuning(const QList<Note> &tune);

private:
    int frets;
    QList<Note> tuningList;
    QList<QList<Note>> stringNoteList;
    const QStringList noteList = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
    QList<Note> generateNotes(Note &startNote, int size);
    QList<Note> generateScaleNotes(const QStringList &scale, Note &startNote, int size);
};

#endif // GUITAR_H

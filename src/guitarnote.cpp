#include "guitarnote.h"

GuitarNote::GuitarNote()
{}

GuitarNote::GuitarNote(QString &name, int octave, int pos) : myName{name}, myOctave{octave}, myPos{pos}
{}

GuitarNote::GuitarNote(Note &note, int pos)
{
    myName = note.getName();
    myOctave = note.getOctave();
    myPos = pos;
}

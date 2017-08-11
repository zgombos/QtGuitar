#include "guitar.h"

Guitar::Guitar(int frets, QList<Note> tune):frets{frets + 1}, tuningList{tune}
{
    setTuning(tuningList);
}

QList<Note> Guitar::generateNotes(Note &startNote, int size)
{
    /*
     * Generate a list of Note objects up to the size
     * No scale pattern applied
     */

    QList<Note> result;
    int index = noteList.indexOf(startNote.getName());
    int octave = startNote.getOctave();
    for(int i = 0; i < size; ++i)
    {
        // Create circularity on the index
        if (index >= noteList.size() )
            index = index % noteList.size();
        // Increase the octave when necessary
        if (noteList[index]=="C")
            octave++;
        result.append(Note(noteList.at(index), octave));
        index++;
    }
    return result;
}

QList<Note> Guitar::generateScaleNotes(const QStringList &scale, Note &startNote, int size)
{
    /*
     * Generate a list of scale Note objects up to the size
     * For example: C major scale note list starting with "E"/2
     * ("E"/2), ("F"/2), ("G"/2), ("A"/2), ("B"/2), ("C"/3), ("D"/3), ("E"/3), ("F"/3), ("G"/3) ("A"/3), ("B"/3), ("C"/4)...
     */
    QList<Note> result;
    // Get the noteList index of the startNote
    int index = noteList.indexOf(startNote.getName());
    int octave = startNote.getOctave();
    // Double the size, because not all Notes are good to place in the list
    for(int i = 0; i < size*2; ++i)
    {
        // Create circularity on the index
        if (index >= noteList.size() )
            index = index % noteList.size();
        // Increase the ovtave if necessary
        if (noteList[index]=="C")
            octave++;
        // If the scale contains the note add it to the list
         if (scale.contains(noteList[index]))
            result.append(Note(noteList.at(index), octave));
        index++;
    }
    return result;
}

void Guitar::setTuning(const QList<Note> &tune)
{

    // Clear the previuous tuning
    stringNoteList.clear();

    // Create a new one
    for (Note note : tune)
    {
        QList<Note> noteList = generateNotes(note, frets);
        stringNoteList.append(noteList);
    }
}

QList<QList<GuitarNote>> Guitar::getAllScaleNotes(const QStringList &scale)
{
    /*
     * Generate a list of list of GuitarNotes from the scale
     * For example: C major scale on the low E guitar string:
     * (("E"/2-0), ("F"/2-1), ("G"/2-3), ("A"/2-5), ("B"/2-7), ("C"/3-8), ("D"/3-10), ("E"/3-12),
     *  ("F"/3-13), ("G"/3-15), ("A"/3-17), ("B"/3-19), ("C"/4-20), ("D"/4-22))
     */

    QList<QList<GuitarNote>> result;

    // Interate over the guitar notes per guitar string
    for (const QList<Note> &notesOnString : stringNoteList)
    {
       QList<GuitarNote> tmp;
       // Iterate over the notes
       for (Note note : notesOnString)
       {
           // If the scale contains the guitar note determinate the index and add it to the list
            if (scale.contains(note.getName()))
            {
                int index = notesOnString.indexOf(note);
                tmp.append(GuitarNote(note, index));
                //tmp.append(map);
            }
       }
       result.append(tmp);
    }
    return result;
}

QList<QList<GuitarNote>> Guitar::notePerStringView(const QStringList &scale, int startPos, int size)
{
    /*
     * Generate a view on the fretboard based on the given size
     * Size is usualy: 2-4
     * Return a list of list GuitarNotes
     *
     * For example: scale:C major, startPos=6, size=3:
     *  S0: (("B"/2-7), ("C"/3-8), ("D"/3-10))
     *  S1: (("E"/3-7), ("F"/3-8), ("G"/3-10))
     *  S2: (("A"/3-7), ("B"/3-9), ("C"/4-10))
     *  S3: (("D"/4-7), ("E"/4-9), ("F"/4-10))
     *  S4: (("G"/4-8), ("A"/4-10), ("B"/4-12))
     *  S5: (("C"/5-8), ("D"/5-10), ("E"/5-12))
     */

    QList<QList<GuitarNote>> result;

    // Generate the full note list on the gutar fretbord based on the sacle
    QList<QList<GuitarNote>> notesOnGuitarString = getAllScaleNotes(scale);

    // Generate the scale note pool
    Note E_Note("E", 2);
    QList<Note> tempScaleNotes = generateScaleNotes(scale, E_Note, 40);

    // Find the index of the startPos in the tempScaleNotes
    int index = 0;
    for (Note &note : tempScaleNotes)
    {
        if (note.getName() == scale.at(startPos))
        {
            index = tempScaleNotes.indexOf(note);
            break;
        }
    }

    // Iterate over the guitar strings
    for (int i{0}; i < 6; ++i)
    {
        QList<GuitarNote> tmp;
        // Iterate till the requested size
        for (int j{0}; j < size; ++j)
        {
            // Get the requested start Note based on the index
            Note scaleNote = tempScaleNotes.at(index);

            // Find the scale note in the notesOnGuitarString list
            for (auto guitarNote : notesOnGuitarString[i])
            {
                if(guitarNote.getName()==scaleNote.getName() && guitarNote.getOctave()==scaleNote.getOctave())
                {
                    tmp.append(guitarNote);
                }
            }
            index++;
        }
        result.append(tmp);
    }
    return result;
}

QList<QList<GuitarNote>> Guitar::boxPatternView(QStringList &scale, int startPos)
{
    /*
     * Generate a box pattern view on the fretboard
     * Return a list of list GuitarNotes
     * Notes are not farther than 4 frets on a string
     */

    QList<QList<GuitarNote>> result;

    // Generate the full note list on the gutar fretbord based on the sacle
    QList<QList<GuitarNote>> notesOnGuitarString = getAllScaleNotes(scale);

    // Find the index of the startPos on the low E string
    int index = 0;
    for (auto &note : notesOnGuitarString[0])
    {
        if (note.getName() == scale.at(startPos))
        {
            index = notesOnGuitarString[0].indexOf(note);
            break;
        }
    }

    // Get the requested start Note based on the index
    GuitarNote startNote = notesOnGuitarString[0].at(index);

    // Iterate over the guitar strings
    for (const auto &guitarString: notesOnGuitarString)
    {
        QList<GuitarNote> tmp;
        // Iterate over the Notes on the guitar string
        for (auto &note: guitarString)
        {
            //  Find positions between (-1 < startNote < 3)
            if ((note.getPos() - startNote.getPos() >= -1) && (note.getPos() - startNote.getPos() <= 3))
            {
                tmp.append(note);
            }
        }
        result.append(tmp);
    }
    return result;
}

QList<GuitarNote> Guitar::oneStringView(QStringList &scale, int stringNum)
{
    /*
     * Return a list of notes on a requested string from the scale
     */

    // Generate the full note list on the gutar fretbord based on the sacle
    QList<QList<GuitarNote>> notesOnGuitarString = getAllScaleNotes(scale);

    return notesOnGuitarString[stringNum];
}

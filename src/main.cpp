#include "mainwindow.h"
#include <QApplication>

#include "note.h"
#include "guitarnote.h"
#include "scale.h"
#include "guitar.h"

//void testGuitar()
//{
//    QList<int> major = {2, 2, 1, 2, 2, 2};
//    Scale Major("Major", major, Scale::THREE_NOTES);
//    QStringList c_major = Major.getScaleNote("C");
//    qDebug() << "C major scale:" << c_major << endl;

//    QList<int> minor = {2, 1, 2, 2, 1, 2};
//    Scale Minor("Minor", minor, Scale::THREE_NOTES);
//    QStringList a_minor = Minor.getScaleNote("A");
//    qDebug() << "A minor scale:" << a_minor << endl;

//    QList<Note> tuning {Note("E", 2), Note("A", 2), Note("D", 3), Note("G", 3), Note("B", 3), Note("E", 4)};
//    Guitar Gibson(22, tuning);

//    //QList<QList<QMap<Note, int>>> allNotes = Gibson.getAllScaleNotes(c_major);
//    QList<QList<GuitarNote>> allNotes = Gibson.getAllScaleNotes(c_major);
//    //qDebug() << "All notes from c major: " << allNotes;
//    qDebug() << "All notes from c major on the first string: " << allNotes[0] << endl;

//    qDebug() << "Three notes per string view:";
//    QList<QList<GuitarNote>> threeNotes = Gibson.notePerStringView(c_major, 1, 3);
//    int s{0};
//    for (auto note : threeNotes)
//    {
//        qDebug().nospace() << "S" << s << ": " << note;
//        s++;
//    }
//    qDebug() << endl;

//    qDebug() << "Four notes per string view:";
//    QList<QList<GuitarNote>> fourNotes = Gibson.notePerStringView(a_minor, 2, 4);
//    int s1{0};
//    for (auto note : fourNotes)
//    {
//        qDebug().nospace() << "S" << s1 << ": " << note;
//        s1++;
//    }
//    qDebug() << endl;

//    qDebug() << "Box pattern view:";
//    QList<QList<GuitarNote>> boxNotes = Gibson.boxPatternView(a_minor, 2);
//    int s2{0};
//    for (auto note : boxNotes)
//    {
//        qDebug().nospace() << "S" << s2 << ": " << note;
//        s2++;
//    }
//    qDebug() << endl;

//    qDebug() << "One string view:";
//    QList<GuitarNote> sNotes = Gibson.oneStringView(a_minor, 2);
//    qDebug().nospace() << "S:" << sNotes;
//    qDebug() << endl;
//}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //testGuitar();

    return a.exec();
}

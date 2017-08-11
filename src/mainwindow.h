#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QTimer>
#include <QFileDialog>
#include <QtSvg/QSvgGenerator>

#include "guitar.h"
#include "scale.h"
#include "graphicsfretboard.h"
#include "graphicsnoteitem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Guitar *GibsonGuitar;
    GraphicsFretboard *GibsonGuitarFretboard;

private slots:
    void on_actionExit_triggered();
    void showFirst();
    void showNext();
    void showPrev();
    void showAll();
    void startAnimation();
    void stopAnimation();
    void updateAnimation();
    void updateComboBox();
    void updateTuning();
    void saveAs();

    void on_actionSave_To_File_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    const QStringList noteList {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
    const int gibsonFret{22};       // Gibson guitar fret number
    QList<Scale*> scaleList;
    QMap<QString, QList<Note>> tuningMap;

    QString currentRootNote;
    QStringList currentScale;
    QList<Note> currentTuning;
    int currentPos {0};             // If showNext() call need an init value
    int currentStringNumber{0};     // If showNext() call need an init value

    Scale* PentaMajor;
    Scale* PentaMinor;
    Scale* PentaBlues;
    Scale* Major;
    Scale* Ionian;
    Scale* Dorian;
    Scale* Phrygian;
    Scale* Lydian;
    Scale* Mixolydian;
    Scale* Aeolian;
    Scale* Locrian;
    Scale* Minor;
    Scale* HarmonicMinor;
    Scale* MelodicMinorAsc;
    Scale* MelodicMinorDes;
    Scale* Chromatic;
    Scale* WholeTone;
    Scale* Diminished;

    QTimer* timer;
    bool isAnimationRunning;

    void clearFretboard();
    void drawNotes(int pos, int stringNumber);
    void drawPatternView(QList<QList<GuitarNote> > &notesToDraw);
    void drawStringView(QList<GuitarNote> &notesToDraw);
};

#endif // MAINWINDOW_H

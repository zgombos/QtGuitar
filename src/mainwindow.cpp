#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create a new QGraphicsScene and show it on the ui
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(QColor(120, 120, 120));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

    // Create tunnings
    QList<Note> standard = {Note("E", 2), Note("A", 2), Note("D", 3), Note("G", 3), Note("B", 3), Note("E", 4)};
    QList<Note> dropped_d = {Note("D", 2), Note("A", 2), Note("D", 3), Note("G", 3), Note("B", 3), Note("E", 4)};
    QList<Note> dropped_c = {Note("C", 2), Note("G", 2), Note("C", 3), Note("F", 3), Note("A", 3), Note("D", 4)};

    // Create a new Guitar object
    GibsonGuitar = new Guitar(gibsonFret, standard);

    // Create a new Guitar Fretboard object and show it on the scene
    GibsonGuitarFretboard = new GraphicsFretboard(gibsonFret, standard);
    GibsonGuitarFretboard->setPos(0, 0);
    scene->addItem(GibsonGuitarFretboard);

    // Fill the Root ComboBox
    for(const auto &note : noteList)
    {
        ui->comboBoxRoot->addItem(note);
    }

    // Fill the Scale ComboBox
    PentaMajor = new Scale("Pentatonic Major", QList<int>({2, 2, 3, 2, 3}), BOX_PATTERN);
    PentaMinor = new Scale("Pentatonic Minor", QList<int>({3, 2, 2, 3, 2}), BOX_PATTERN);
    PentaBlues = new Scale("Pentatonic Blues", QList<int>({3, 2, 1, 1, 3, 2}), BOX_PATTERN);
    Major = new Scale("Major", QList<int>({2, 2, 1, 2, 2, 2}), THREE_NOTES);
    Ionian = new Scale("Ionian", QList<int>({2, 2, 1, 2, 2, 2}), THREE_NOTES);
    Dorian = new Scale("Dorian", QList<int>({2, 1, 2, 2, 2, 1}), THREE_NOTES);
    Phrygian = new Scale("Phrygian", QList<int>({1, 2, 2, 2, 1, 2}), THREE_NOTES);
    Lydian = new Scale("Lydian", QList<int>({2, 2, 2, 1, 2, 2}), THREE_NOTES);
    Mixolydian = new Scale("Mixolydian", QList<int>({2, 2, 1, 2, 2, 1}), THREE_NOTES);
    Aeolian = new Scale("Aeolian", QList<int>({2, 1, 2, 2, 1, 2}), THREE_NOTES);
    Locrian = new Scale("Locrian", QList<int>({1, 2, 2, 1, 2, 2}), THREE_NOTES);
    Minor = new Scale("Minor", QList<int>({2, 1, 2, 2, 1, 2}), THREE_NOTES);
    HarmonicMinor = new Scale("Harmonic Minor", QList<int>({2, 1, 2, 2, 1, 3, 1}), THREE_NOTES);
    MelodicMinorAsc = new  Scale("Melodic Minor - Ascending", QList<int>({2, 1, 2, 2, 2, 2, 1}), THREE_NOTES);
    MelodicMinorDes = new Scale("Melodic Minor - Descending", QList<int>({2, 1, 2, 2, 1, 2, 2}), THREE_NOTES);
    Chromatic = new Scale("Chromatic", QList<int>({1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}), THREE_NOTES);
    WholeTone = new Scale("Whole Tone", QList<int>({2, 2, 2, 2, 2, 2}), THREE_NOTES);
    Diminished = new Scale("Diminished", QList<int>({2, 1, 2, 1, 2, 1, 2}), FOUR_NOTES);

    scaleList << PentaMajor << PentaMinor << PentaBlues << Major << Ionian << Dorian << Phrygian << Lydian << Mixolydian <<
                 Aeolian << Locrian << Minor << HarmonicMinor << MelodicMinorAsc << MelodicMinorDes << Chromatic << WholeTone << Diminished;

    for (const auto &scale : scaleList)
    {
        ui->comboBoxScale->addItem(scale->getName());
    }

    //Fill the Tuning ComboBox
    tuningMap["Standard"] = standard;
    tuningMap["Dropped D"] = dropped_d;
    tuningMap["Dropped C"] = dropped_c;
    QMapIterator<QString, QList<Note>> i(tuningMap);
    while (i.hasNext())
    {
        i.next();
        ui->comboBoxTuning->addItem(i.key());
    }

    // Set the current index for all ComboBox
    ui->comboBoxRoot->setCurrentIndex(0);
    ui->comboBoxScale->setCurrentIndex(0);
    ui->comboBoxTuning->setCurrentIndex(2);

    // Setup ComboBox signals
    connect(ui->comboBoxRoot, SIGNAL(currentIndexChanged(int)), this, SLOT(updateComboBox()));
    connect(ui->comboBoxScale, SIGNAL(currentIndexChanged(int)), this, SLOT(updateComboBox()));
    connect(ui->comboBoxTuning, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTuning()));

    // Get the current values
    currentRootNote = noteList[ui->comboBoxRoot->currentIndex()];
    Scale* scale = scaleList[ui->comboBoxScale->currentIndex()];
    currentScale = scale->getScaleNote(currentRootNote);
    currentTuning = tuningMap.value(ui->comboBoxTuning->currentText());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::updateComboBox()
{
    currentRootNote = noteList[ui->comboBoxRoot->currentIndex()];
    Scale* scale = scaleList[ui->comboBoxScale->currentIndex()];
    currentScale = scale->getScaleNote(currentRootNote);

    switch (scale->getHint()) {
    case BOX_PATTERN:
        ui->radioButtonBoxPattern->setChecked(true);
        break;
    case THREE_NOTES:
        ui->radioButtonThreeNotes->setChecked(true);
        break;
    case FOUR_NOTES:
        ui->radioButtonFourNotes->setChecked(true);
        break;
    }
}

void MainWindow::updateTuning()
{
    currentTuning = tuningMap.value(ui->comboBoxTuning->currentText());
    GibsonGuitar->setTuning(currentTuning);
    GibsonGuitarFretboard->setTuning(currentTuning);
    scene->update();
}

void MainWindow::drawNotes(int pos, int stringNumber)
{
    if(ui->radioButtonBoxPattern->isChecked())
    {
        QList<QList<GuitarNote>> notesToDraw = GibsonGuitar->boxPatternView(currentScale, pos);
        drawPatternView(notesToDraw);
    }
    else if(ui->radioButtonThreeNotes->isChecked())
    {
        QList<QList<GuitarNote>> notesToDraw = GibsonGuitar->notePerStringView(currentScale, pos, 3);
        drawPatternView(notesToDraw);
    }
    else if (ui->radioButtonFourNotes->isChecked())
    {
        QList<QList<GuitarNote>> notesToDraw = GibsonGuitar->notePerStringView(currentScale, pos, 4);
        drawPatternView(notesToDraw);
    }
    else if (ui->radioButtonOneString->isChecked())
    {
        QList<GuitarNote> notesToDraw = GibsonGuitar->oneStringView(currentScale, stringNumber);
        drawStringView(notesToDraw);
    }

}

void MainWindow::drawPatternView(QList<QList<GuitarNote>> &notesToDraw)
{
    QList<QList<QPoint>> noteCoordinates = GibsonGuitarFretboard->getNoteCoordinateList();
    for (auto i{0}; i < 6; ++i)
    {
        for (auto j{0}; j < notesToDraw[i].size(); ++j)
        {
            int pos = notesToDraw[i][j].getPos();
            QPoint coordinate = noteCoordinates[i][pos];
            QColor noteColor;
            if (notesToDraw[i][j].getName() == currentRootNote)
            {
                noteColor = Qt::red;
            }
            else
            {
                noteColor = Qt::darkGreen;
            }
            GraphicsNoteItem* note = new GraphicsNoteItem(notesToDraw[i][j].getName(), noteColor);
            note->setPos(coordinate);
            scene->addItem(note);
        }
    }
}

void MainWindow::drawStringView(QList<GuitarNote> &notesToDraw)
{
    QList<QList<QPoint>> noteCoordinates = GibsonGuitarFretboard->getNoteCoordinateList();
    for (auto j{0}; j < notesToDraw.size(); ++j)
    {
        int pos = notesToDraw[j].getPos();
        QPoint coordinate = noteCoordinates[currentStringNumber][pos];  // Need the string number for the noteCoordinates
        QColor noteColor;
        if (notesToDraw[j].getName() == currentRootNote)
        {
            noteColor = Qt::red;
        }
        else
        {
            noteColor = Qt::darkGreen;
        }
        GraphicsNoteItem* note = new GraphicsNoteItem(notesToDraw[j].getName(), noteColor);
        note->setPos(coordinate);
        scene->addItem(note);
    }
}

void MainWindow::showFirst()
{
    clearFretboard();

    // Stop the animation if it is active
    if (isAnimationRunning)
    {
        timer->stop();
    }

    if (ui->radioButtonOneString->isChecked())
    {
        currentStringNumber = 0;
    }
    else
    {
        currentPos = 0;
    }
    drawNotes(currentPos, currentStringNumber);
}

void MainWindow::showNext()
{
    clearFretboard();

//    // Stop the animation if it is active
//    if (isAnimationRunning)
//    {
//        timer->stop();
//    }

    if (ui->radioButtonOneString->isChecked())
    {
        if (currentStringNumber == 5)
        {
            currentStringNumber = 0;
        }
        else
        {
            currentStringNumber += 1;
        }
    }
    else
    {
        if (currentPos == currentScale.length()-1)
        {
            currentPos = 0;
        }
        else
        {
            currentPos += 1;
        }
    }
    drawNotes(currentPos, currentStringNumber);
}

void MainWindow::showPrev()
{
    clearFretboard();

    // Stop the animation if it is active
    if (isAnimationRunning)
    {
        timer->stop();
    }

    if (ui->radioButtonOneString->isChecked())
    {
        if (currentStringNumber == 0)
        {
            currentStringNumber = 5;
        }
        else
        {
            currentStringNumber -= 1;
        }
    }
    else
    {
        if (currentPos == 0)
        {
            currentPos = currentScale.length()-1;
        }
        else
        {
            currentPos -= 1;
        }
    }
    drawNotes(currentPos, currentStringNumber);
}

void MainWindow::showAll()
{
    clearFretboard();

    // Stop the animation if it is active
    if (isAnimationRunning)
    {
        timer->stop();
    }

    // Get the combobox items
    currentRootNote = noteList[ui->comboBoxRoot->currentIndex()];
    Scale* scale = scaleList[ui->comboBoxScale->currentIndex()];
    currentScale = scale->getScaleNote(currentRootNote);
    currentTuning = tuningMap.value(ui->comboBoxTuning->currentText());

    QList<QList<GuitarNote>> notesToDraw = GibsonGuitar->getAllScaleNotes(currentScale);
    drawPatternView(notesToDraw);
}

void MainWindow::clearFretboard()
{
    for (const auto &item : scene->items())
    {
        if (item->type() == GraphicsNoteItem::Type)
        {
            scene->removeItem(item);
            delete item;
        }
    }
    scene->update();
}

void MainWindow::startAnimation()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAnimation()));
    timer->start(1000);
    isAnimationRunning = true;
}

void MainWindow::stopAnimation()
{
    timer->stop();
    isAnimationRunning = false;
}

void MainWindow::updateAnimation()
{
    showNext();
}

void MainWindow::saveAs()
{
    QString dir;
    QString fileName = QFileDialog::getSaveFileName(this,
                       tr("Save SVG"), dir, tr("SVG files (*.svg)"));

    if (fileName.isEmpty())
        return;

    QSvgGenerator generator;                                            // Create a file generator object
    generator.setFileName(fileName);                                    // We set the path to the file where to save vector graphics
    generator.setSize(QSize(scene->width(), scene->height()));          // Set the dimensions of the working area of the document in millimeters
    generator.setViewBox(QRect(0, 0, scene->width(), scene->height())); // Set the work area in the coordinates
    generator.setTitle(tr("SVG Example"));                              // The title document
    generator.setDescription(tr("File created by SVG Example"));

    QPainter painter;
    if(!painter.begin(&generator))
    {
        // failed to open file
        qWarning("Failed to open file, is it writable?");
        return;
    }
    scene->render(&painter);
    painter.end();
}

void MainWindow::on_actionSave_To_File_triggered()
{
    saveAs();
}

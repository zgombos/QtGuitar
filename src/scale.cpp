#include "scale.h"

Scale::Scale(const QString &name, const QList<int> &interval, const Hint &hint)
{
    this->name = name;
    this->interval = interval;
    this->hint = hint;
}

QStringList Scale::getScaleNote(const QString &root)
{
       /*
        * Get a scale notes starting with a root note.
        * Return a QStrinList list.
        */
        QStringList result;
        result.append(root);
        int index = noteList.indexOf(root);
        for (const auto &i : interval)
        {
            /*
             * Add each intervall to the previous one
             * If it is greater than the size of the list take the modulo
             * You can achive a circular list with that technique
             */
            index += i;
            if (index >= noteList.size() )
                index = index % noteList.size();
            result.append(noteList.at(index));
        }
        return result;
}

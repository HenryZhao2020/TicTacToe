#include "File.h"

QString File::readAll(const QString &path) {
    QFile file(path);

    // If the file fails to open, return an empty string
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return "";
    }

    // Read file content
    QString content = file.readAll();
    file.close();

    return content;
}

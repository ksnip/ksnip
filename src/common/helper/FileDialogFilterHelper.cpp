#include "FileDialogFilterHelper.h"
#include <QImageReader>
#include <QImageWriter>

const QString &FileDialogFilterHelper::ImageFilesImport()
{
    const static QString importfilter(FileDialogFilterHelper::ImageFiles(true));
    return importfilter;
}
const QString &FileDialogFilterHelper::ImageFilesExport()
{
    const static QString exportfilter(FileDialogFilterHelper::ImageFiles(false));
    return exportfilter;
}
const QString &FileDialogFilterHelper::AllFiles()
{
    const static QString allfiles_str(QLatin1String("(*)"));
    return allfiles_str;
}

QString FileDialogFilterHelper::ImageFiles(bool import)
{
    QList<QByteArray> supported_formats = import ? QImageReader::supportedImageFormats() : QImageWriter::supportedImageFormats();
    QString filter_str(QLatin1String("("));

    for (int i = 0; i < supported_formats.count(); i++) {
        filter_str.append(((i == 0) ? "*." : " *.") + QString(supported_formats.at(i)));
    }
    filter_str.append(");;");
    return filter_str;
}

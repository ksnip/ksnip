#ifndef KSNIP_FILEDIALOGFILTERHELPER_H
#define KSNIP_FILEDIALOGFILTERHELPER_H

#include <QString>

class FileDialogFilterHelper
{
public:
    static const QString &ImageFilesImport();
    static const QString &ImageFilesExport();
    static const QString &AllFiles();

private:
    static QString ImageFiles(bool import);
};

#endif // KSNIP_FILEDIALOGFILTERHELPER_H

#include <QString>
typedef struct __lang_code {
    QString lang2;
    QString lang3;
} LANG_TABLE_T;

QString iso2to3(QString s);
QString iso3to2(QString s);


#ifndef ClassicNS_SqliteDB_h
#define ClassicNS_SqliteDB_h

#include "sqlite_modern_cpp/hdr/sqlite_modern_cpp.h"

namespace ClassicNS
{

class SqliteDB
{
    private:
        sqlite::database db;

    public:
        SqliteDB();

};

} // namespace

#endif

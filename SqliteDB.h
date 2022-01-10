#ifndef ClassicNS_SqliteDB_h
#define ClassicNS_SqliteDB_h

#include "sqlite_modern_cpp/hdr/sqlite_modern_cpp.h"

namespace ClassicNS
{

class SqliteDB
{
    private:
        sqlite::database db;
        void create_tables();

    public:
        // Constructs in output directory
        SqliteDB();

        // Get reference to underlying connection - use with care.
        sqlite::database& get_db();
};

} // namespace

#endif

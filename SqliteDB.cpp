#include "SqliteDB.h"

namespace ClassicNS
{

SqliteDB::SqliteDB()
:db("output/output.db")
{
    db << "PRAGMA JOURNAL_MODE = WAL;";
    db << "PRAGMA SYNCHRONOUS = 0;";
    create_tables();
}

void SqliteDB::create_tables()
{
    db << "BEGIN;";

    db << "DROP TABLE IF EXISTS sampler_info;";
    db << "DROP TABLE IF EXISTS particles;";

    db << "CREATE TABLE IF NOT EXISTS sampler_info\
            (rng_seed INTEGER NOT NULL PRIMARY KEY)\
            WITHOUT ROWID;";

    db << "CREATE TABLE IF NOT EXISTS particles\
            (iteration      INTEGER NOT NULL PRIMARY KEY,\
             params         TEXT NOT NULL,\
             log_likelihood REAL NOT NULL,\
             tiebreaker     REAL NOT NULL);";

    db << "COMMIT;";
}

sqlite::database& SqliteDB::get_db()
{
    return db;
}

} // namespace

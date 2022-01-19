#include "SqliteDB.h"
#include "Tools/Misc.hpp"

using Tools::logsumexp;

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
            (rng_seed      INTEGER NOT NULL,\
             num_particles INTEGER NOT NULL,\
             mcmc_steps    INTEGER NOT NULL);";

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

double SqliteDB::compute_ln_z()
{
    double log_numerator   = -1E300;
    double log_denominator = -1E300;

    int num_particles;
    db << "SELECT num_particles FROM sampler_info;" >> num_particles;

    db << "SELECT iteration, log_likelihood FROM particles;" >>
        [&](int iteration, double log_likelihood)
        {
            log_numerator = logsumexp({log_numerator,
                             -(double)iteration/num_particles + log_likelihood});
            log_denominator = logsumexp({log_denominator,
                                 -(double)iteration/num_particles});
        };
    return log_numerator - log_denominator;
}

} // namespace

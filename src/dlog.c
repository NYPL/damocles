#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <systemd/sd-journal.h>

#ifdef FOR_GNU_MAKE
#include <gnumake.h>
#endif

#ifndef LOG_FILE
#define LOG_FILE "build.log"
#endif


int plugin_is_GPL_compatible;

// TODO: split up the journal and file thing
// TODO:   and add console writing (with color)

// TODO: do some error checking
int dlog(const char* module, const char* log_message) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char buffer[20];
    size_t ret = strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm);

    int hold_len = sizeof(module) + sizeof(log_message) + 1;
    char* holder = malloc(sizeof(char*) * hold_len);
    sprintf(holder, "{ %s } %s", module, log_message);
    sd_journal_print(LOG_NOTICE, holder);
    free(holder);

    FILE* reglogfile = fopen(LOG_FILE, "a");
    fprintf(reglogfile, "[%s] { %s } %s\n",
                        buffer, module, log_message);

    fclose(reglogfile);
    return 0;
}

void dlog_for_R(char** module, char** log_message) {
    dlog(module[0], log_message[0]);
}

char* dlog_for_make(const char* fnname, unsigned int argc, char** argv) {
    dlog(argv[0], argv[1]);
    return NULL;
}

#ifdef FOR_GNU_MAKE
int dlog_gmk_setup(const gmk_floc *floc) {
    gmk_add_function("dlog", dlog_for_make, 2, 2, 0); // allow expansion
    return 1;
}
#endif

#ifndef GAME_QUERYSTATUS_H
#define GAME_QUERYSTATUS_H

/* Status values tested by the shared query-result check. */
#define QUERY_STATUS_ACCEPTED(status) \
    ((status) == 0 || (status) == 0x17 || (status) == 0x15 || (status) == 0x14)

#endif

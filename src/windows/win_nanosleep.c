#include "diurna_internal.h"

BOOLEAN nanosleep(const LONGLONG ns) {
    HANDLE timer = CreateWaitableTimer(NULL, TRUE, NULL);
    if (timer == NULL) {
        return (FALSE);
    }

    LARGE_INTEGER li;
    li.QuadPart = -ns;
    if (!SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE)) {
        CloseHandle(timer);
        return (FALSE);
    }

    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
}

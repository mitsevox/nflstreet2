#include "__os.h"
#include <dolphin/os.h>

#define OS_SYSTEMTIME_BASE 0x30D8

asm OSTime OSGetTime(void)
{
jump:
    nofralloc

    mftbu r3
    mftb r4

    mftbu r5
    cmpw r3, r5
    bne jump

    blr
}

asm OSTick OSGetTick(void)
{
    nofralloc

    mftb r3
    blr
}

OSTime __OSGetSystemTime(void)
{
    BOOL enabled;
    OSTime* timeAdjustAddr = (OSTime*)(OS_BASE_CACHED + OS_SYSTEMTIME_BASE);
    OSTime result;

    enabled = OSDisableInterrupts();
    result = *timeAdjustAddr + OSGetTime();
    OSRestoreInterrupts(enabled);

    return result;
}

static int YearDays[MONTH_MAX] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
static int LeapYearDays[MONTH_MAX] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};

static BOOL IsLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

static int GetLeapDays(int year)
{
    if (year < 1)
    {
        return 0;
    }
    return (year + 3) / 4 - (year - 1) / 100 + (year - 1) / 400;
}

static void GetDates(int days, OSCalendarTime* td)
{
    int year;
    int n;
    int month;
    int* p_days;

    td->wday = (days + 6) % WEEK_DAY_MAX;

    for (year = days / YEAR_DAY_MAX; days < (n = year * YEAR_DAY_MAX + GetLeapDays(year)); year--)
    {
    }

    days -= n;
    td->year = year;
    td->yday = days;

    p_days = IsLeapYear(year) ? LeapYearDays : YearDays;
    month = MONTH_MAX;
    while (days < p_days[--month])
    {
    }
    td->mon = month;
    td->mday = days - p_days[month] + 1;
}

void OSTicksToCalendarTime(OSTime ticks, OSCalendarTime* td)
{
    int days;
    int secs;
    OSTime d;

    d = ticks % OSSecondsToTicks(1);
    if (d < 0)
    {
        d += OSSecondsToTicks(1);
    }
    td->usec = (int)(OSTicksToMicroseconds(d) % USEC_MAX);
    td->msec = (int)(OSTicksToMilliseconds(d) % MSEC_MAX);

    ticks -= d;
    days = (int)(OSTicksToSeconds(ticks) / SECS_IN_DAY) + BIAS;
    secs = (int)(OSTicksToSeconds(ticks) % SECS_IN_DAY);
    if (secs < 0)
    {
        days -= 1;
        secs += SECS_IN_DAY;
    }

    GetDates(days, td);
    td->hour = secs / 60 / 60;
    td->min = (secs / 60) % 60;
    td->sec = secs % 60;
}


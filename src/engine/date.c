/* Calendar helpers: leap years and the number of days in a year or a month. */

int DateIsYearLeap(int year)
{
    int leap = 0;

    if (year % 4 == 0) {
        if (year % 100 != 0) {
            leap = 1;
        } else {
            leap = year == year / 400 * 400;
        }
    }
    return leap;
}

int DateGetNumDaysInYear(int year)
{
    return DateIsYearLeap(year) ? 366 : 365;
}

int DateGetNumDaysInMonth(int month, int year)
{
    int days = 31;

    switch (month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        days = 31;
        break;
    case 2:
        days = DateIsYearLeap(year) ? 29 : 28;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        days = 30;
        break;
    }
    return days;
}

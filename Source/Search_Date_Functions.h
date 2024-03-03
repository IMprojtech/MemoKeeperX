
void ParseDateTime(const char *datetime, time_t *timestamp) {
    struct tm timeinfo;
    sscanf(datetime, "%d-%d-%d %d:%d:%d", &timeinfo.tm_year, &timeinfo.tm_mon,
           &timeinfo.tm_mday, &timeinfo.tm_hour, &timeinfo.tm_min,
           &timeinfo.tm_sec);
    timeinfo.tm_year -= 1900;
    timeinfo.tm_mon -= 1;
    *timestamp = mktime(&timeinfo);
}

int SearchDate(time_t timestamp, time_t startTime, time_t endTime) {

    if (timestamp >= startTime && timestamp <= endTime)
        return 1;

    return 0;
}

int SearchLastHours(time_t timestamp, int hours) {
    time_t HoursAgo = time(NULL) - (hours + 1) * 60 * 60; // ore in secondi
    return SearchDate(timestamp, HoursAgo, time(NULL));
}

int SearchLastDay(time_t timestamp, int day) {
    time_t now = time(NULL);

    struct tm *startDay = localtime(&now);
    startDay->tm_mday -= day + 1; // Sottrai giorni
    startDay->tm_hour = 0;
    startDay->tm_min  = 0;
    startDay->tm_sec  = 0;
    mktime(startDay);

    return SearchDate(timestamp, mktime(startDay), now);
}

int SearchLastMonth(time_t timestamp, int month) {
    time_t currentTime = time(NULL);

    struct tm *monthAgo = localtime(&currentTime);
    monthAgo->tm_mday -= month + 1;
    mktime(monthAgo);

    return SearchDate(timestamp, mktime(monthAgo), currentTime);
}

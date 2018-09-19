static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year:  set day of year from month & day */
int
day_of_year(int year, int month, int day)
{
	int leap;
	char *m;

	if (year == 0 || month < 1 || month > 12)
		return -1;
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if (day > 366 || !leap && day > 365)
		return -1;
	m = daytab[leap];
	for (m=daytab[leap]; month-- > 0 ; m++)
		day += *m;
	return day;
}

/* month_day:  set month, day from day of year */
int
month_day(int year, int yearday,
		  int *pmonth, int *pday)
{
	int leap;
	char *days, *m;
	
	if (year == 0)
		return -1;
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	days = daytab[leap];
	if (yearday > 366 || !leap && yearday > 365)
		return -1;
	for (m = days; yearday > *m; m++)
		yearday -= *m;
	*pmonth = m - daytab[leap];
	*pday = yearday;
	return 0;
}

/* month_name:  return name of n-th month */
char *
month_name(int n)
{
	static char *name[] = {
		"Illegal month",
		"January", "February", "March",
		"April", "May", "June",
		"July", "August", "September",
		"October", "Novermber", "December"
	};

	return (n < 1 || n > 12) ? name[0] : name[n];
}


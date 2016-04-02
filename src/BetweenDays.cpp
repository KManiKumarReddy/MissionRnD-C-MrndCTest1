/*
Q4: Two dates are given in a 8 node single linked list form,where each node
has one digit only, dates 01-31, months 01-12, year 0000-9999.

Find the number of days in between those two dates .[Exclusive]

Ex : Date1:  0->1->0->1->2->0->0->4 .
     Date2 : 0->5->0->1->2->0->0->4 should return 3 .
As there are 3 days between Jan1st 2004 and Jan 5th 2004.

Ex 2 : Date1 : 3->1->1->2->2->0->1->2.
       Date2 : 0->2->0->1->2->0->1->3 should return 1 .
(There is only one day between 31st Dec 2012 and 2nd  Jan 2013 .)

Note : Consecutive Days and Same Days should return 0;
->Return -1 for NULL Inputs .
->Between Days have to be calculated by not including start and end date .
->The SLL will have 8 Nodes in all cases . Month 9 will be represented as 09.

Difficulty : Hard 
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct node{
	int data;
	struct node *next;
};

struct Date
{
	int d, m, y;
};

int countLeapYears(Date d) {
	int years = d.y;

	if (d.m <= 2)
		years--;

	return years / 4 - years / 100 + years / 400;
}

int getDifference(Date dt1, Date dt2) {
	int monthDays[12] = { 31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31 };
	long int n1 = dt1.y * 365 + dt1.d;

	for (int i = 0; i<dt1.m - 1; i++)
		n1 += monthDays[i];

	n1 += countLeapYears(dt1);


	long int n2 = dt2.y * 365 + dt2.d;
	for (int i = 0; i<dt2.m - 1; i++)
		n2 += monthDays[i];
	n2 += countLeapYears(dt2);

	return (n2 - n1);
}

int isLeapYear(int y) {
	// not divisible by 4
	if (y % 4)
		return 0;
	// divisible by 400
	if (!(y % 400))
		return 1;
	// divisible by 100, blocks cases like 2100
	if (!(y % 100))
		return 0;
	// divisible by 100 & not divisble by 400
	return 1;
}

int validate(char * in, int * d, int * m, int * y) {
	int firstSlash = -1, secondSlash = -1, i;
	for (i = 0; in[i]; i++)
	if (in[i] == '/')
	if (firstSlash >= 0)
	if (secondSlash >= 0)
		return 0;
	else
		secondSlash = i;
	else
		firstSlash = i;
	if (firstSlash < 1 || secondSlash - firstSlash < 1)
		return 0;
	*d = in[0] - '0';
	for (i = 1; i < firstSlash; i++)
		*d = *d * 10 + (in[i] - '0');
	*m = in[firstSlash + 1] - '0';
	for (i = firstSlash + 2; i < secondSlash; i++)
		*m = *m * 10 + (in[i] - '0');
	*y = in[secondSlash + 1] - '0';
	for (i = secondSlash + 2; in[i]; i++)
		*y = *y * 10 + (in[i] - '0');
	// checking month and year
	if (*m < 1 || *m > 12 || *y < 1 || *y > 9999)
		return 0;
	// initializing maximum days in a month
	int maxDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	// increasing max days in feb for leap years
	if (isLeapYear(*y))
		maxDays[1] ++;
	// checing date
	if (*d < 1 || *d > maxDays[*m - 1])
		return 0;

	// validated
	return 1;
}

int between_days(struct node *date1head, struct node *date2head) {
	if (!date1head || !date2head)
		return -1;
	char date1[11], date2[11];
	int i;
	struct node * temp = date1head;
	for (i = 0; i < 2; i++) {
		date1[i] = temp->data + '0';
		temp = temp->next;
	}
	date1[i++] = '/';
	for (; i < 5; i++) {
		date1[i] = temp->data + '0';
		temp = temp->next;
	}
	date1[i++] = '/';
	for (; i < 10; i++) {
		date1[i] = temp->data + '0';
		temp = temp->next;
	}
	date1[i] = '\0';

	temp = date2head;
	for (i = 0; i < 2; i++) {
		date2[i] = temp->data + '0';
		temp = temp->next;
	}
	date2[i++] = '/';
	for (; i < 5; i++) {
		date2[i] = temp->data + '0';
		temp = temp->next;
	}
	date2[i++] = '/';
	for (; i < 10; i++) {
		date2[i] = temp->data + '0';
		temp = temp->next;
	}
	date2[i] = '\0';
	int d, m, y;
	struct Date d1;
	struct Date d2;
	if (validate(date1, &d, &m, &y)) {
		d1.d = d;
		d1.m = m;
		d1.y = y;
	}
	else {
		return -1;
	}
	if (validate(date2, &d, &m, &y)) {
		d2.d = d;
		d2.m = m;
		d2.y = y;
	}
	else {
		return -1;
	}
	int res = getDifference(d1, d2);
	if (res < 2)
		return 0;
	else
		return res - 1;
}
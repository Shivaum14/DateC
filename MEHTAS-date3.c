#include <stdio.h>
/* calculates the difference between multiple dates */
/* with leap years */
/* and lists them in order */
#define MAX 1000

struct date {		/* defines a structure to use when handeling dates */
	int day;
	int month;
	int year;
};

int date_validity(struct date d) {		/* function to test if date given is valid and day mon and year values are within their natural ranges */
	int ndays;
	int monthlyd[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		/* array for days in the month */
	int leap_monthlyd[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		/* array for days in the month during leap year */
	if (d.year % 4 == 0){		/* checks if the current year is exatly divisable by 4 and inturn tests if its a leap year */
		ndays = leap_monthlyd[d.month-1];		/* if leap year it will use leap year array */
	} else {
		    ndays = monthlyd[d.month-1];		/* if its not a leap year it will use the regular array */
	}
	if (d.year < 1 || d.year > 10000 || d.month < 1 || d.month > 12 || d.day < 1 || d.day > ndays){
		return 0;
		/* will return false unless all conditions are met above for the date to be valid  */
	}
	return 1;
}

struct date date_form(void) {		/* function take a date from the user and test if its is of an acceptable format */
	struct date sample;
	int int_test, temp,  test = 1;
		do{ 
			fprintf(stderr,"Please enter the date (dd/mm/yyyy or dd-mm-yyyy):\n");

			int_test = scanf("%d %*[/-] %d %*[/-] %d",&sample.day,&sample.month,&sample.year);
			while(int_test!=3){		/* makes sure the user enters 3 integers between dashes and the input is of the form dd/mm/yyyy or dd-mm-yyyy */
				while((temp=getchar()) != EOF && temp != '\n');
				fprintf(stderr,"the date is of the wrong format please try again \n");
				int_test = scanf("%d %*[/-] %d %*[/-] %d",&sample.day,&sample.month,&sample.year);
			}
			test = 0;
			fprintf(stderr,"valid format");	

		    if (!date_validity(sample)) {		/* tests the ranges of the values */
		        fprintf(stderr," & Invalid date\n\n");
		        test = 1;
		    } else {
		    	fprintf(stderr," & valid date\n");
		    }
		} while (test == 1);		/* will continue looping until a valid date is entered */
	return sample;

}

int convert(struct date sample){		/* function to convert the date supplied to an integer value */
	int monthlyd[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int leap_monthlyd[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	long value = 0;		/* an integer value for the date */
	int i;
	for (i=0; i < sample.month; i++){
		if(sample.year % 4 == 0){
			value += leap_monthlyd[i];		/* finds the days passed in the previous months in the date for a leap year */
		} else {
			value += monthlyd[i];		/* finds the days passed in the previous months in the date */
		}
	}
	value += ((365*(sample.year - 1)) + sample.day + (sample.year / 4));
		/*adds the days passed in current month as well as previous years and adds adds days to compensate for passed yeap years */
	return value;
}

	/* difference function is not used in this program but is required in MEHTAS-date1.c and MEHTAS-date2.c */
int difference(struct date a, struct date b){		/* function to find the difference between the to dates entered */
	long first_value, second_value, difference_in_days;
	first_value = convert(a);		/* converts first date to integer so arithmetic can be performed */
	second_value = convert(b);		/* converts second date to integer so arithmetic can be performed */
	difference_in_days = second_value - first_value;
	/* finds the differeence between the two integers which is actualy the difference in days between the two dates */
	fprintf(stderr, "\nThe difference in days is %ld\n", difference_in_days);
	printf("%ld", difference_in_days);
	return 0;
}

int main(){
	struct date entries[MAX], temp;
	int loops, n, i, j, k, entries_value[MAX], temp_value, int_test, try;

	fprintf(stderr,"how many dates do you want to sort?\n");
	int_test = scanf("%d", &loops);
	while(int_test!=1){
		while((try=getchar()) != EOF && try != '\n');
		fprintf(stderr,"the entry is of the wrong format please try again \n");
		int_test = scanf("%d", &loops);		/* will continue looping until a valid date is entered */
	}

	for (n=0; n < loops; n++){
		entries[n] = date_form();		/* when each input is validatd it is assigned to an array  */
		fprintf(stderr,"you entered %d/%d/%d\n\n", entries[n].day, entries[n].month, entries[n].year);
		entries_value[n] = convert(entries[n]); /* simultaneously a integer value is calculated of each date and assigned accordingly to a seperate array */
	}

	/* bubble sort algorithm */
	for(j = 0; j < loops; j++){
		for(i = 0; i < loops; i++){		/* sorts the integers in entries_values by size while simultaneously sorting the dates in entries */
			if(entries_value[i] > entries_value[j]){		/* if one value in the array is greater than the next they are swapped */
				temp_value = entries_value[i];
				entries_value[i] = entries_value[j];
				entries_value[j] = temp_value;
				temp = entries[i];
				entries[i] = entries[j];
				entries[j] = temp;
			}		/* this will loop untill both arrays are sorted acording to size */
		}
	}
	/* prints all dates to stdout once sorted by itterating through array */
	for(k = 0; k < loops; k++){
		printf("%d/%d/%d", entries[k].day, entries[k].month, entries[k].year);
		if(k < (loops - 1)){
			printf("\n");
		}
	}

	return 0;
}
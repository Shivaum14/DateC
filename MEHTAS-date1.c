#include <stdio.h>
/* calculates the difference between two dates */

struct date {		/* defines a structure to use when handeling dates */
	int day;
	int month;
	int year;
};

int date_validity(struct date d) {		/* function to test if date given is valid and day mon and year valus are within their natural ranges */
    int ndays;
    int monthlyd[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    /* initializes an array containing the number of days in each month in order */
    ndays = monthlyd[d.month-1];		/* the number of days there should be in the current of the given date is set */
	if (d.year < 1 || d.year > 10000 || d.month < 1 || d.month > 12 || d.day < 1 || d.day > ndays){
		/* will return false unless all conditions are met above for the date to be valid  */
        return 0;
    }
    return 1;
}

struct date date_form(void) {		/* function take a date from the user and test if its is of an acceptable format */
	struct date sample;
	int int_test, temp, test = 1;
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
	long value = 0;		/* an integer value for the date */
	int i;
	for (i=0; i < (sample.month-1); i++){
		value += monthlyd[i];		/* finds the days passed in the previous months in the date */
	}
	value += ((365*(sample.year - 1)) + sample.day);	/* adds the days passed in current month as well as previous years */
	return value;
}

int difference(struct date a, struct date b){		/* function to find the difference between the to dates entered */
	long first_value, second_value, difference_in_days;
	first_value = convert(a);		/* converts first date to integer so arithmetic can be performed */
	second_value = convert(b);		/* converts second date to integer so arithmetic can be performed */
	difference_in_days = second_value - first_value;
	/* finds the differeence between the two integers which is actualy the difference in days between the two dates */
	fprintf(stderr, "\nThe difference in days is %d\n", difference_in_days);
	printf("%d", difference_in_days);
	return 0;
}

int main(){
	struct date first, second;		/* innitializes two variables of the artifitial structure date, so the user input can be used */
	fprintf(stderr,"For the first date\n");
	first = date_form();		/* takes and validates first date */
	fprintf(stderr,"you entered %d/%d/%d\n\n", first.day, first.month, first.year);
	fprintf(stderr,"For the second date\n");
	second = date_form();		/* takes and validates second date */
	fprintf(stderr,"you entered %d/%d/%d\n\n", second.day, second.month, second.year);
	difference(first, second);		/* calculates their difference */
	return 0;

}
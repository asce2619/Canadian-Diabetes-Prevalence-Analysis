// C libraries to be used in the code
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Global variables to be used in the code */

// Column numbers to where each column is in the formatted data
int geo_count, val_count, age_count, date_count, gender_count;
double ont_avg, que_avg, brit_avg, alb_avg; // Provincial Averages
double nationalavg; // Canada(excludingterritories) Average
char names[5][50] = {"Canada(excludingterritories)", "Ontario", "Alberta",
                     "Quebec", "BritishColumbia"};
// Arrays that store each places' averages depending on their place in the
// names[][] array
double avg_2015[5] = {0, 0, 0, 0, 0}, avg_2016[5] = {0, 0, 0, 0, 0},
       avg_2017[5] = {0, 0, 0, 0, 0}, avg_2018[5] = {0, 0, 0, 0, 0};
double avg_2019[5] = {0, 0, 0, 0, 0}, avg_2020[5] = {0, 0, 0, 0, 0},
       avg_2021[5] = {0, 0, 0, 0, 0};
// Averages for each Province depending on their age group
double ont_35_avg = 0, ont_50_avg = 0, ont_65_avg = 0, que_35_avg = 0,
       que_50_avg = 0, que_65_avg = 0, brit_35_avg = 0, brit_50_avg = 0,
       brit_65_avg = 0, alb_35_avg = 0, alb_50_avg = 0, alb_65_avg = 0,
       can_35_avg = 0, can_50_avg = 0, can_65_avg = 0;

/* converts csv file into a txt file */
void format() {
  // Files and variables to be used in the function
  FILE *in = fopen("statscan_diabetes.csv", "r");
  FILE *formattedData = fopen("formattedData.txt", "w");
  char input;
  int count = 0;
  // While function that goes through the given .csv file
  while (!feof(in)) {
    // Takes in each character of the given file
    fscanf(in, "%c", &input);
    // When a cell value from the .csv file is found, it is formatted and sent
    // to the formatted data file
    if (input == '"') {
      count++;
      while (count == 1) {
        fscanf(in, "%c", &input);
        if (input == '"') {
          fprintf(formattedData, " ");
          count--;
        } else {
          if (input != ' ')
            fprintf(formattedData, "%c", input);
        }
      }
      // If a newline character is found, the formatted data file also creates a
      // new line
    } else if (input == '\n') {
      fprintf(formattedData, "\n");
    }
  }

  // Closes the files used in the code
  fclose(in);
  fclose(formattedData);
}

/* Checks if the file string equals value needed */
int checking(char comp[], char org[]) {
  for (int i = 0; i < strlen(comp); i++) {
    if (comp[i] != org[i]) {
      return (1);
      // if not equal to needed string
    }
  }

  return (0); // if equal to needed string
}

/* assigns columns needed with a number */
void columns() {
  // Opens the files and variables to be used in the function
  FILE *formattedData = fopen("formattedData.txt", "r");
  int count = 1, columnsFound = 0;
  char check[50];

  // column headers needing to be found (given in assignment)
  char geo[] = {'G', 'E', 'O'}, val[] = {'V', 'A', 'L', 'U', 'E'},
       date[] = {'R', 'E', 'F', '_', 'D', 'A', 'T', 'E'},
       age[] = {'A', 'g', 'e', 'g', 'r', 'o', 'u', 'p'},
       gender[] = {'S', 'e', 'x'};

  // Find where each column is in the formatted data until all are found
  while (columnsFound != 5) {
    fscanf(formattedData, "%s", check);
    if (checking(check, geo) == 0) {
      geo_count = count;
      columnsFound++;
    } else if (checking(check, val) == 0) {
      val_count = count;
      columnsFound++;
    } else if (checking(check, age) == 0) {
      age_count = count;
      columnsFound++;
    } else if (checking(check, date) == 0) {
      date_count = count;
      columnsFound++;
    } else if (checking(check, gender) == 0) {
      gender_count = count;
      columnsFound++;
    }
    count++;
  }

  // Closes the formatted data file
  fclose(formattedData);
}

/* Question 1 a */
void question1a() {
  FILE *formattedData = fopen("formattedData.txt", "r");

  char check[50], value[50];
  double num;
  int ont_count = 0, que_count = 0, brit_count = 0, alb_count = 0;

  // rows needing to find
  char ont[] = {'O', 'n', 't', 'a', 'r', 'i', 'o'},
       que[] = {'Q', 'u', 'e', 'b', 'e', 'c'},
       brit[] = {'B', 'r', 'i', 't', 'i', 's', 'h', 'C',
                 'o', 'l', 'u', 'm', 'b', 'i', 'a'},
       alb[] = {'A', 'l', 'b', 'e', 'r', 't', 'a'};

  while (!feof(formattedData)) {
    for (int i = 1; i <= geo_count; i++) {
      fscanf(formattedData, "%s", check);
    }

    if (checking(check, ont) == 0) {
      for (int i = geo_count + 1; i <= val_count; i++) {
        fscanf(formattedData, "%s", value);
      }

      num = atof(value); // converts string to double

      if (num != 0) {
        ont_avg += num; // adds num to sum
        ont_count++;    // adds to count
      }
    } else if (checking(check, que) == 0) {
      for (int i = geo_count + 1; i <= val_count; i++) {
        fscanf(formattedData, "%s", value);
      }

      num = atof(value);

      if (num != 0) {
        que_avg += num;
        que_count++;
      }
    } else if (checking(check, brit) == 0) {
      for (int i = geo_count + 1; i <= val_count; i++) {
        fscanf(formattedData, "%s", value);
      }
      num = atof(value);

      if (num != 0) {
        brit_avg += num;
        brit_count++;
      }
    } else if (checking(check, alb) == 0) {
      for (int i = geo_count + 1; i <= val_count; i++) {
        fscanf(formattedData, "%s", value);
      }

      num = atof(value);

      if (num != 0) {
        alb_avg += num;
        alb_count++;
      }
    }

    // skips the rest of the row
    fscanf(formattedData, "%*[^\n]");
  }

  // calculates the average
  ont_avg = ont_avg / ont_count;
  que_avg = que_avg / que_count;
  brit_avg = brit_avg / brit_count;
  alb_avg = alb_avg / alb_count;

  printf("\nQuestion 1 a\n");
  printf("\nThe average for Ontario is: %.2lf %%", ont_avg);
  printf("\nThe average for Quebec is: %.2lf %%", que_avg);
  printf("\nThe average for British Columbia is: %.2lf %%", brit_avg);
  printf("\nThe average for Alberta is: %.2lf %%", alb_avg);

  fclose(formattedData);
}

/* Question 1 b */
void question1b() {
  FILE *formattedData = fopen("formattedData.txt", "r");

  char check[50], value[50];
  double num;
  double nationaltotal = 0;
  int nationalcount = 0;

  // rows needing to find
  char nat[] = {'C', 'a', 'n', 'a', 'd', 'a', '(', 'e', 'x', 'c',
                'l', 'u', 'd', 'i', 'n', 'g', 't', 'e', 'r', 'r',
                'i', 't', 'o', 'r', 'i', 'e', 's', ')'};

  while (!feof(formattedData)) {
    for (int i = 1; i <= geo_count; i++) {
      fscanf(formattedData, "%s", check);
    }

    if (checking(check, nat) == 0) {
      for (int i = geo_count + 2; i <= val_count; i++) {
        fscanf(formattedData, "%s", value);
      }

      num = atof(value);

      if (num != 0) {
        nationaltotal += num;
        nationalcount++;
      }
    }

    // skips the rest of the row
    fscanf(formattedData, "%*[^\n]");
  }

  nationalavg = nationaltotal / nationalcount;
  printf("\n\nQuestion 1 b\n");
  printf("\nThe average for Canada excluding territories is: %.2lf %%",
         nationalavg);
  fclose(formattedData);
}

/* Question 1 c */
void question1c() {
  // File with formatted data to be used in code
  FILE *formattedData = fopen("formattedData.txt", "r");
  // Variables and arrays to be used in the code
  char line[1024], value[50], place[50], date[50], avg[50];
  char *pointer;
  int count = 1, trigger = 0;
  int count2015[5] = {0, 0, 0, 0, 0}, count2016[5] = {0, 0, 0, 0, 0},
      count2017[5] = {0, 0, 0, 0, 0}, count2018[5] = {0, 0, 0, 0, 0};
  int count2019[5] = {0, 0, 0, 0, 0}, count2020[5] = {0, 0, 0, 0, 0},
      count2021[5] = {0, 0, 0, 0, 0};
  /* Date_count , geo_count, and val_count come from columns() function
   * They keep track of which column a required value is from
   */

  // While statement that goes through each line in the formatted code
  while (fgets(&line[0], 1024, formattedData) != NULL) {
    // Pointer variable that stores the column of the line
    pointer = strtok(line, " ");
    // While statement that goes through each column value in the line
    while (pointer != NULL) {
      // Variable that stores each column value in the line
      sscanf(pointer, "%s", value);
      // If statements that store the data needed from the line
      // Count variable keeps track on which column the pointer is at
      // in the formatted data line
      if (count == date_count) {
        strcpy(date, value);
      } else if (count == geo_count &&
                 strcmp(value, "Canada(excludingterritories)") == 0) {
        strcpy(place, value);
        // Since a line with this place value skews the column count,
        // an extra count is added to account for that
        count++;
      } else if (count == geo_count) {
        strcpy(place, value);
      } else if (count == val_count) {
        // If the average value is found to not be a number,
        // Trigger value is raised for the line
        trigger = 0;
        for (int i = 0; i < strlen(value); i++) {
          if (!isdigit(value[i]) && value[i] != '.') {
            trigger = 1;
          }
        }
        strcpy(avg, value);
      }
      // Advances to next column in the line
      count++;
      pointer = strtok(NULL, " ");
    }
    // When line reading is done, count is reset
    count = 1;
    // Sorts the data found depending on year of data
    // If trigger was raised, the data for the line is not used in final
    // result
    if (strcmp(date, "2015") == 0 && trigger == 0) {
      for (int i = 0; i < 5; i++) {
        // Goes through each place to find where to store it
        if (strcmp(place, names[i]) == 0) {
          avg_2015[i] += atof(avg);
          // Counts how many values were added to average for later use
          count2015[i]++;
        }
      }
    }
    // Same process from 2015 is done for the rest of the years
    if (strcmp(date, "2016") == 0 && trigger == 0) {
      for (int i = 0; i < 5; i++) {
        if (strcmp(place, names[i]) == 0) {
          avg_2016[i] += atof(avg);
          count2016[i]++;
        }
      }
    }
    if (strcmp(date, "2017") == 0 && trigger == 0) {
      for (int i = 0; i < 5; i++) {
        if (strcmp(place, names[i]) == 0) {
          avg_2017[i] = atof(avg) + avg_2017[i];
          count2017[i]++;
        }
      }
    }
    if (strcmp(date, "2018") == 0 && trigger == 0) {
      for (int i = 0; i < 5; i++) {
        if (strcmp(place, names[i]) == 0) {
          avg_2018[i] += atof(avg);
          count2018[i]++;
        }
      }
    }
    if (strcmp(date, "2019") == 0 && trigger == 0) {
      for (int i = 0; i < 5; i++) {
        if (strcmp(place, names[i]) == 0) {
          avg_2019[i] += atof(avg);
          count2019[i]++;
        }
      }
    }
    if (strcmp(date, "2020") == 0 && trigger == 0) {
      for (int i = 0; i < 5; i++) {
        if (strcmp(place, names[i]) == 0) {
          avg_2020[i] += atof(avg);
          count2020[i]++;
        }
      }
    }
    if (strcmp(date, "2021") == 0 && trigger == 0) {
      for (int i = 0; i < 5; i++) {
        if (strcmp(place, names[i]) == 0) {
          avg_2021[i] += atof(avg);
          count2021[i]++;
        }
      }
    }
  }
  // Prints the header for the results to the question
  printf("\n\nQuestion 1 c\n\n");

  // Opens a file to store all the data needed to answer Question 5
  FILE *q5 = fopen("q5plot.dat", "w");
  // Prints the heading line needed in the new file before storing data for
  /* Question 5 */
  fprintf(q5, "# Year Canada(excludingterritories) Ontario Alberta Quebec "
              "BritishColumbia\n");
  // For statement that calculates the average of each year from each place
  for (int i = 0; i < 5; i++) {
    avg_2015[i] /= count2015[i];
    // Prints the results of each average of each year from each place
    printf("2015 Average for %s: %.2lf%%\n", names[i], avg_2015[i]);
  }
  printf("\n");
  // Stores the data of each average from each place for the each specified
  fprintf(q5, "2015  %.2lf  %.2lf  %.2lf  %.2lf  %.2lf\n", avg_2015[0],
          avg_2015[1], avg_2015[2], avg_2015[3], avg_2015[4]);
  // Same process done for the rest of the years checked
  for (int i = 0; i < 5; i++) {
    avg_2016[i] /= count2016[i];
    printf("2016 Average for %s: %.2lf%%\n", names[i], avg_2016[i]);
  }
  printf("\n");
  fprintf(q5, "2016  %.2lf  %.2lf  %.2lf  %.2lf  %.2lf\n", avg_2016[0],
          avg_2016[1], avg_2016[2], avg_2016[3], avg_2016[4]);
  for (int i = 0; i < 5; i++) {
    avg_2017[i] /= count2017[i];
    printf("2017 Average for %s: %.2lf%%\n", names[i], avg_2017[i]);
  }
  printf("\n");
  fprintf(q5, "2017  %.2lf  %.2lf  %.2lf  %.2lf  %.2lf\n", avg_2017[0],
          avg_2017[1], avg_2017[2], avg_2017[3], avg_2017[4]);
  for (int i = 0; i < 5; i++) {
    avg_2018[i] /= count2018[i];
    printf("2018 Average for %s: %.2lf%%\n", names[i], avg_2018[i]);
  }
  printf("\n");
  fprintf(q5, "2018  %.2lf  %.2lf  %.2lf  %.2lf  %.2lf\n", avg_2018[0],
          avg_2018[1], avg_2018[2], avg_2018[3], avg_2018[4]);
  for (int i = 0; i < 5; i++) {
    avg_2019[i] /= count2019[i];
    printf("2019 Average for %s: %.2lf%%\n", names[i], avg_2019[i]);
  }
  printf("\n");
  fprintf(q5, "2019  %.2lf  %.2lf  %.2lf  %.2lf  %.2lf\n", avg_2019[0],
          avg_2019[1], avg_2019[2], avg_2019[3], avg_2019[4]);
  for (int i = 0; i < 5; i++) {
    avg_2020[i] /= count2020[i];
    printf("2020 Average for %s: %.2lf%%\n", names[i], avg_2020[i]);
  }
  printf("\n");
  fprintf(q5, "2020  %.2lf  %.2lf  %.2lf  %.2lf  %.2lf\n", avg_2020[0],
          avg_2020[1], avg_2020[2], avg_2020[3], avg_2020[4]);
  for (int i = 0; i < 5; i++) {
    avg_2021[i] /= count2021[i];
    printf("2021 Average for %s: %.2lf%%\n", names[i], avg_2021[i]);
  }
  fprintf(q5, "2021  %.2lf  %.2lf  %.2lf  %.2lf  %.2lf\n", avg_2021[0],
          avg_2021[1], avg_2021[2], avg_2021[3], avg_2021[4]);

  // Closes all files used in the function
  fclose(q5);
  fclose(formattedData);
}

/* Question 1 d */
void question1d() {
  FILE *formattedData = fopen("formattedData.txt", "r");

  char check[50], value[50], age[50];
  double num;
  int ont_35_count = 0, ont_50_count = 0, ont_65_count = 0, que_35_count = 0,
      que_50_count = 0, que_65_count = 0, brit_35_count = 0, brit_50_count = 0,
      brit_65_count = 0, alb_35_count = 0, alb_50_count = 0, alb_65_count = 0,
      can_35_count = 0, can_50_count = 0, can_65_count = 0;

  // rows needing to find
  char ont[] = "Ontario", que[] = "Quebec", brit[] = "BritishColumbia",
       alb[] = "Alberta", can[] = "Canada(excludingterritories)";
  char age_35[] = "35to49years", age_50[] = "50to64years",
       age_65[] = "65yearsandover";

  while (!feof(formattedData)) {
    for (int i = 1; i <= geo_count; i++) {
      fscanf(formattedData, "%s", check);
    }

    if (checking(check, ont) == 0) {
      for (int i = geo_count + 1; i <= age_count; i++) {
        fscanf(formattedData, "%s", age);
      }
      for (int i = age_count + 1; i <= val_count; i++) {
        fscanf(formattedData, "%s", value);
      }

      num = atof(value); // converts string to double

      if (num != 0) {
        if (checking(age, age_35) == 0) {
          ont_35_avg += num; // adds num to sum
          ont_35_count++;    // adds to count
        } else if (checking(age, age_50) == 0) {
          ont_50_avg += num;
          ont_50_count++;
        } else if (checking(age, age_65) == 0) {
          ont_65_avg += num;
          ont_65_count++;
        }
      }
    } else if (checking(check, que) == 0) {
      for (int i = geo_count + 1; i <= age_count; i++) {
        fscanf(formattedData, "%s", age);
      }

      for (int i = age_count + 1; i <= val_count; i++) {
        fscanf(formattedData, "%s", value);
      }

      num = atof(value); // converts string to double

      if (num != 0) {
        if (checking(age, age_35) == 0) {
          que_35_avg += num; // adds num to sum
          que_35_count++;    // adds to count
        } else if (checking(age, age_50) == 0) {
          que_50_avg += num;
          que_50_count++;
        } else if (checking(age, age_65) == 0) {
          que_65_avg += num;
          que_65_count++;
        }
      }
    } else if (checking(check, brit) == 0) {
      for (int i = geo_count + 1; i <= age_count; i++) {
        fscanf(formattedData, "%s", age);
      }

      for (int i = age_count + 1; i <= val_count; i++) {
        fscanf(formattedData, "%s", value);
      }

      num = atof(value); // converts string to double

      if (num != 0) {
        if (checking(age, age_35) == 0) {
          brit_35_avg += num; // adds num to sum
          brit_35_count++;    // adds to count
        } else if (checking(age, age_50) == 0) {
          brit_50_avg += num;
          brit_50_count++;
        } else if (checking(age, age_65) == 0) {
          brit_65_avg += num;
          brit_65_count++;
        }
      }
    } else if (checking(check, alb) == 0) {
      for (int i = geo_count + 1; i <= age_count; i++) {
        fscanf(formattedData, "%s", age);
      }

      for (int i = age_count + 1; i <= val_count; i++) {
        fscanf(formattedData, "%s", value);
      }

      num = atof(value); // converts string to double

      if (num != 0) {
        if (checking(age, age_35) == 0) {
          alb_35_avg += num; // adds num to sum
          alb_35_count++;    // adds to count
        } else if (checking(age, age_50) == 0) {
          alb_50_avg += num;
          alb_50_count++;

        } else if (checking(age, age_65) == 0) {
          alb_65_avg += num;
          alb_65_count++;
        }
      }
    } else if (checking(check, can) == 0) {
      for (int i = geo_count + 2; i <= age_count; i++) {
        fscanf(formattedData, "%s", age);
      }

      for (int i = age_count + 1; i <= val_count; i++) {
        fscanf(formattedData, "%s", value);
      }

      num = atof(value); // converts string to double

      if (num != 0) {
        if (checking(age, age_35) == 0) {
          can_35_avg += num; // adds num to sum
          can_35_count++;    // adds to count
        } else if (checking(age, age_50) == 0) {
          can_50_avg += num;
          can_50_count++;

        } else if (checking(age, age_65) == 0) {
          can_65_avg += num;
          can_65_count++;
        }
      }
    }

    // skips the rest of the row
    fscanf(formattedData, "%*[^\n]");
  }

  // calculates the average
  ont_35_avg = ont_35_avg / ont_35_count;
  ont_50_avg = ont_50_avg / ont_50_count;
  ont_65_avg = ont_65_avg / ont_65_count;

  que_35_avg = que_35_avg / que_35_count;
  que_50_avg = que_50_avg / que_50_count;
  que_65_avg = que_65_avg / que_65_count;

  brit_35_avg = brit_35_avg / brit_35_count;
  brit_50_avg = brit_50_avg / brit_50_count;
  brit_65_avg = brit_65_avg / brit_65_count;

  alb_35_avg = alb_35_avg / alb_35_count;
  alb_50_avg = alb_50_avg / alb_50_count;
  alb_65_avg = alb_65_avg / alb_65_count;

  can_35_avg = can_35_avg / can_35_count;
  can_50_avg = can_50_avg / can_50_count;
  can_65_avg = can_65_avg / can_65_count;

  printf("\nQuestion 1 d\n");
  printf("\nThe average for Ontario is:");
  printf("\n35 to 49 years: %.2lf%%", ont_35_avg);
  printf("\n50 to 64 years: %.2lf%%", ont_50_avg);
  printf("\n65 years and over: %.2lf%%\n", ont_65_avg);
  printf("\nThe average for Quebec is:");
  printf("\n35 to 49 years: %.2lf%%", que_35_avg);
  printf("\n50 to 64 years: %.2lf%%", que_50_avg);
  printf("\n65 years and over: %.2lf%%\n", que_65_avg);
  printf("\nThe average for British Columbia is:");
  printf("\n35 to 49 years: %.2lf%%", brit_35_avg);
  printf("\n50 to 64 years: %.2lf%%", brit_50_avg);
  printf("\n65 years and over: %.2lf%%\n", brit_65_avg);
  printf("\nThe average for Alberta is:");
  printf("\n35 to 49 years: %.2lf%%", alb_35_avg);
  printf("\n50 to 64 years: %.2lf%%", alb_50_avg);
  printf("\n65 years and over: %.2lf%%\n", alb_65_avg);
  printf("\nThe average for Canada (excluding territories) is:");
  printf("\n35 to 49 years: %.2lf%%", can_35_avg);
  printf("\n50 to 64 years: %.2lf%%", can_50_avg);
  printf("\n65 years and over: %.2lf%%\n", can_65_avg);

  /* Question 6 */
  FILE *q6 = fopen("q6plot.dat", "w");

  fprintf(q6, "# age\tCanada(excluding territories)\n");
  fprintf(q6, "35-49\t%.2lf\n", can_35_avg);
  fprintf(q6, "50-64\t%.2lf\n", can_50_avg);
  fprintf(q6, "65+\t%.2lf\n", can_65_avg);

  fclose(q6);
  fclose(formattedData);
}

/* Question 2 */
void question2() {
  double prov_avg[4];
  prov_avg[0] = ont_avg;
  prov_avg[1] = que_avg;
  prov_avg[2] = brit_avg;
  prov_avg[3] = alb_avg;

  double comp_low = ont_avg;
  double comp_high = ont_avg;

  int low = 0, high = 0;

  // getting the greatest and the lowest provincial average
  for (int i = 0; i < 4; i++) {
    if (prov_avg[i] < comp_low) {
      comp_low = prov_avg[i];
      low = i;
    } else if (prov_avg[i] > comp_high) {
      comp_high = prov_avg[i];
      high = i;
    }
  }

  printf("\nQuestion 2\n");

  switch (high) {
  case 0:
    printf("\nThe highest Provincial average percentage for diabetes belongs "
           "to...\nOntario @ %.2lf %%\n",
           ont_avg);
    break;
  case 1:
    printf("\nThe highest Provincial average percentage for diabetes belongs "
           "to...\nQuebec @ %.2lf %%\n",
           que_avg);
    break;
  case 2:
    printf("\nThe highest Provincial average percentage for diabetes belongs "
           "to...\nBritish Columbia @ %.2lf %%\n",
           brit_avg);
    break;
  case 3:
    printf("\nThe highest Provincial average percentage for diabetes belongs "
           "to...\nAlberta @ %.2lf %%\n",
           alb_avg);
    break;
  }

  switch (low) {
  case 0:
    printf("\nThe lowest Provincial average percentage for diabetes belongs "
           "to...\nOntario @ %.2lf %%\n",
           ont_avg);
    break;
  case 1:
    printf("\nThe lowest Provincial average percentage for diabetes belongs "
           "to...\nQuebec @ %.2lf %%\n",
           que_avg);
    break;
  case 2:
    printf("\nThe lowest Provincial average percentage for diabetes belongs "
           "to...\nBritish Columbia @ %.2lf %%\n",
           brit_avg);
    break;
  case 3:
    printf("\nThe lowest Provincial average percentage for diabetes belongs "
           "to...\nAlberta @ %.2lf %%\n",
           alb_avg);
    break;
  }
}

/* Question 3 */
void question3() {

  printf("\nQuestion 3\n");

  if (ont_avg < nationalavg) {
    printf("\nOntario is below the national average");
  }

  if (ont_avg > nationalavg) {
    printf("\nOntario is above the national average");
  }

  if (que_avg < nationalavg) {
    printf("\nQuebec is below the national average");
  }

  if (que_avg > nationalavg) {
    printf("\nQuebec is above the national average");
  }

  if (brit_avg < nationalavg) {
    printf("\nBritish Columbia is below the national average");
  }

  if (brit_avg > nationalavg) {
    printf("\nBritish Columbia is above the national average");
  }

  if (alb_avg < nationalavg) {
    printf("\nAlberta is below the national average");
  }

  if (alb_avg > nationalavg) {
    printf("\nAlberta is above the national average");
  }
}

/* Question 4 */
void question4() {
  // Variables to be used in the code
  // Since the bounds to the diabetes percentages is from 0-100, the min
  // and max were set beyond them as placeholders for the first values of the
  // code
  double min = 101, max = -1;
  char minYear[5], minPlace[50], maxYear[5], maxPlace[50];
  // For statement that cycles through each of the averages for this year
  // and finds the province with the highest and lowest averages
  for (int i = 1; i < 5; i++) {
    if (min > avg_2015[i]) {
      min = avg_2015[i];
      strcpy(minYear, "2015");
      strcpy(minPlace, names[i]);
    } else if (max < avg_2015[i]) {
      max = avg_2015[i];
      strcpy(maxYear, "2015");
      strcpy(maxPlace, names[i]);
    }
  }
  // Same process is done for the rest of the years checked
  for (int i = 1; i < 5; i++) {
    if (min > avg_2016[i]) {
      min = avg_2016[i];
      strcpy(minYear, "2016");
      strcpy(minPlace, names[i]);
    } else if (max < avg_2016[i]) {
      max = avg_2016[i];
      strcpy(maxYear, "2016");
      strcpy(maxPlace, names[i]);
    }
  }
  for (int i = 1; i < 5; i++) {
    if (min > avg_2017[i]) {
      min = avg_2017[i];
      strcpy(minYear, "2017");
      strcpy(minPlace, names[i]);
    } else if (max < avg_2017[i]) {
      max = avg_2017[i];
      strcpy(maxYear, "2017");
      strcpy(maxPlace, names[i]);
    }
  }
  for (int i = 1; i < 5; i++) {
    if (min > avg_2018[i]) {
      min = avg_2018[i];
      strcpy(minYear, "2018");
      strcpy(minPlace, names[i]);
    } else if (max < avg_2018[i]) {
      max = avg_2018[i];
      strcpy(maxYear, "2018");
      strcpy(maxPlace, names[i]);
    }
  }
  for (int i = 1; i < 5; i++) {
    if (min > avg_2019[i]) {
      min = avg_2019[i];
      strcpy(minYear, "2019");
      strcpy(minPlace, names[i]);
    } else if (max < avg_2019[i]) {
      max = avg_2019[i];
      strcpy(maxYear, "2019");
      strcpy(maxPlace, names[i]);
    }
  }
  for (int i = 1; i < 5; i++) {
    if (min > avg_2020[i]) {
      min = avg_2020[i];
      strcpy(minYear, "2020");
      strcpy(minPlace, names[i]);
    } else if (max < avg_2020[i]) {
      max = avg_2020[i];
      strcpy(maxYear, "2020");
      strcpy(maxPlace, names[i]);
    }
  }
  for (int i = 1; i < 5; i++) {
    if (min > avg_2021[i]) {
      min = avg_2021[i];
      strcpy(minYear, "2021");
      strcpy(minPlace, names[i]);
    } else if (max < avg_2021[i]) {
      max = avg_2021[i];
      strcpy(maxYear, "2021");
      strcpy(maxPlace, names[i]);
    }
  }
  // Displays header for the results to this question
  printf("\n\nQuestion 4\n");

  // Displays the answer to the question
  printf("\nMin Average...\nYear: %s \nPlace: %s \nAverage: %.2lf%%\n", minYear,
         minPlace, min);
  printf("\nMax Average...\nYear: %s \nPlace: %s \nAverage: %.2lf%%\n", maxYear,
         maxPlace, max);
}

/* Main Function */
int main(void) {
  format();  // formats the cvs file to txt file
  columns(); // gets the column number of needed data

  // Functions that run the code for each problem
  question1a();
  question1b();
  question1c();
  question1d();

  question2();
  question3();
  question4();

  // Ends the program
  return 0;
}

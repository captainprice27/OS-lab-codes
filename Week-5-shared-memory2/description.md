Memory shared among independent processes   
below is a sample  c program on structure  (not directly related to assignments but concept will be needed) ...  
```
#include <stdio.h>

// Define a structure named 'Date'
struct Date
{
    int day;
    int month;
    int year;
};

// Define a structure named 'Person' with a nested 'Date' structure
struct Person
{
    char name[50];
    struct Date birthdate;
};

int main()
{
    // Declare a variable of type 'Person'
    struct Person person1;

    // Assign values to the members of the structure
    strcpy(person1.name, "John");
    person1.birthdate.day = 15;
    person1.birthdate.month = 5;
    person1.birthdate.year = 1990;

    // Print the values
    printf("Name: %s\n", person1.name);
    printf("Birthdate: %d-%d-%d\n", person1.birthdate.day, person1.birthdate.month, person1.birthdate.year);

    return 0;
    
}
```



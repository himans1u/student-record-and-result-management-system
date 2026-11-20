
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define SEMESTERS 8

struct Student
{
    char sapID[20];
    char rollNo[20];
    char name[50];
    char phone[20];
    char email[60];
    int year;
    int semester;
    float sgpa[SEMESTERS];
};

struct Student students[MAX_STUDENTS];
int studentCount = 0;

// Calculate CGPA using completed semesters
float getCGPA(struct Student s)
{
    float total = 0;

    if (s.semester < 1 || s.semester > SEMESTERS)
        return 0;

    for (int i = 0; i < s.semester; i++)
        total += s.sgpa[i];

    return total / s.semester;
}

// Add a student
void addStudent()
{
    if (studentCount >= MAX_STUDENTS)
    {
        printf("\nDatabase is full!\n");
        return;
    }

    struct Student s;

    printf("\nEnter SAP ID: ");
    scanf("%19s", s.sapID);

    for (int i = 0; i < studentCount; i++)
    {
        if (strcmp(students[i].sapID, s.sapID) == 0)
        {
            printf("This SAP ID already exists!\n");
            return;
        }
    }

    printf("Enter Roll Number: ");
    scanf("%19s", s.rollNo);

    printf("Enter Name: ");
    scanf(" %49[^\n]", s.name);

    printf("Enter Phone: ");
    scanf("%19s", s.phone);

    printf("Enter Email: ");
    scanf("%59s", s.email);

    printf("Enter Year (1-4): ");
    scanf("%d", &s.year);

    printf("Enter current Semester (1-8): ");
    scanf("%d", &s.semester);

    if (s.year < 1 || s.year > 4 ||
        s.semester < 1 || s.semester > 8)
    {
        printf("Invalid year or semester!\n");
        return;
    }

    for (int i = 0; i < SEMESTERS; i++)
    {
        if (i < s.semester)
        {
            printf("Enter SGPA for Semester %d: ", i + 1);
            scanf("%f", &s.sgpa[i]);

            if (s.sgpa[i] < 0 || s.sgpa[i] > 10)
            {
                printf("Invalid SGPA! Enter a value from 0 to 10.\n");
                return;
            }
        }
        else
        {
            s.sgpa[i] = 0;
        }
    }

    students[studentCount] = s;
    studentCount++;

    printf("\nStudent added successfully!\n");
}

// Search student
void searchStudent()
{
    char id[20];

    printf("\nEnter SAP ID: ");
    scanf("%19s", id);

    for (int i = 0; i < studentCount; i++)
    {
        if (strcmp(students[i].sapID, id) == 0)
        {
            printf("\nStudent Found!\n");
            printf("SAP ID: %s\n", students[i].sapID);
            printf("Roll Number: %s\n", students[i].rollNo);
            printf("Name: %s\n", students[i].name);
            printf("Phone: %s\n", students[i].phone);
            printf("Email: %s\n", students[i].email);
            printf("Year: %d\n", students[i].year);
            printf("Semester: %d\n", students[i].semester);
            printf("CGPA: %.2f\n", getCGPA(students[i]));
            return;
        }
    }

    printf("\nStudent not found!\n");
}

// Display all students
void displayAllStudents()
{
    if (studentCount == 0)
    {
        printf("\nNo student records available!\n");
        return;
    }

    printf("\n========== STUDENT RECORDS ==========\n");

    for (int i = 0; i < studentCount; i++)
    {
        printf("\nStudent %d\n", i + 1);
        printf("SAP ID: %s\n", students[i].sapID);
        printf("Roll Number: %s\n", students[i].rollNo);
        printf("Name: %s\n", students[i].name);
        printf("Phone: %s\n", students[i].phone);
        printf("Email: %s\n", students[i].email);
        printf("Year: %d\n", students[i].year);
        printf("Semester: %d\n", students[i].semester);
        printf("CGPA: %.2f\n", getCGPA(students[i]));
    }
}

// Calculate individual CGPA
void calculateCGPA()
{
    char id[20];

    printf("\nEnter SAP ID: ");
    scanf("%19s", id);

    for (int i = 0; i < studentCount; i++)
    {
        if (strcmp(students[i].sapID, id) == 0)
        {
            printf("\nStudent: %s\n", students[i].name);
            printf("CGPA: %.2f\n", getCGPA(students[i]));
            return;
        }
    }

    printf("\nStudent not found!\n");
}

// Calculate average CGPA by year
void averageCGPAByYear()
{
    int year;
    int count = 0;
    float total = 0;

    printf("\nEnter year (1-4): ");
    scanf("%d", &year);

    if (year < 1 || year > 4)
    {
        printf("Invalid year!\n");
        return;
    }

    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].year == year)
        {
            total += getCGPA(students[i]);
            count++;
        }
    }

    if (count == 0)
        printf("No students found in this year.\n");
    else
        printf("Average CGPA for Year %d: %.2f\n",
               year, total / count);
}

// Delete a student
void deleteStudent()
{
    char id[20];

    printf("\nEnter SAP ID to delete: ");
    scanf("%19s", id);

    for (int i = 0; i < studentCount; i++)
    {
        if (strcmp(students[i].sapID, id) == 0)
        {
            for (int j = i; j < studentCount - 1; j++)
                students[j] = students[j + 1];

            studentCount--;
            printf("Student deleted successfully!\n");
            return;
        }
    }

    printf("Student not found!\n");
}

// Sort by SAP ID
void sortBySAPID()
{
    struct Student temp;

    for (int i = 0; i < studentCount - 1; i++)
    {
        for (int j = i + 1; j < studentCount; j++)
        {
            if (strcmp(students[i].sapID,
                       students[j].sapID) > 0)
            {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    printf("\nStudents sorted by SAP ID!\n");
    displayAllStudents();
}

// Sort by name
void sortByName()
{
    struct Student temp;

    for (int i = 0; i < studentCount - 1; i++)
    {
        for (int j = i + 1; j < studentCount; j++)
        {
            if (strcmp(students[i].name,
                       students[j].name) > 0)
            {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    printf("\nStudents sorted by name!\n");
    displayAllStudents();
}

// AI-based academic advisor
void academicAdvisor()
{
    char id[20];

    printf("\nEnter SAP ID: ");
    scanf("%19s", id);

    for (int i = 0; i < studentCount; i++)
    {
        if (strcmp(students[i].sapID, id) == 0)
        {
            float cgpa = getCGPA(students[i]);

            printf("\nAcademic Advisor Report\n");
            printf("Student: %s\n", students[i].name);
            printf("CGPA: %.2f\n", cgpa);

            if (cgpa >= 9.0)
            {
                printf("Category: Excellent\n");
                printf("Advice: Keep up the excellent performance!\n");
            }
            else if (cgpa >= 8.0)
            {
                printf("Category: Good\n");
                printf("Advice: Maintain consistency and aim higher.\n");
            }
            else if (cgpa >= 6.0)
            {
                printf("Category: Needs Improvement\n");
                printf("Advice: Practise regularly and focus on weak subjects.\n");
            }
            else
            {
                printf("Category: Immediate Attention\n");
                printf("Advice: Seek academic support and make a study plan.\n");
            }

            return;
        }
    }

    printf("Student not found!\n");
}

// Main menu
int main()
{
    int choice;

    do
    {
        printf("\n====================================\n");
        printf(" STUDENT RECORD AND RESULT SYSTEM\n");
        printf("====================================\n");

        printf("1. Add Student\n");
        printf("2. Search Student by SAP ID\n");
        printf("3. Display All Students\n");
        printf("4. Calculate Individual CGPA\n");
        printf("5. Average CGPA by Year\n");
        printf("6. Delete Student\n");
        printf("7. Sort by SAP ID\n");
        printf("8. Sort by Name\n");
        printf("9. AI Academic Advisor\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: addStudent(); break;
            case 2: searchStudent(); break;
            case 3: displayAllStudents(); break;
            case 4: calculateCGPA(); break;
            case 5: averageCGPAByYear(); break;
            case 6: deleteStudent(); break;
            case 7: sortBySAPID(); break;
            case 8: sortByName(); break;
            case 9: academicAdvisor(); break;
            case 0: printf("\nThank you for using the system!\n"); break;
            default: printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 0);

    return 0;
}

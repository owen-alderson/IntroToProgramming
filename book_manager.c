#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 100
#define CSV_FILE "./books.csv"

struct Book
{
    int book_id;
    char isbn[100];
    char authors[100];
    int original_publication_year;
    char original_title[100];
    float average_rating;
};

int isValidInt(char *str)
{
    for (int i = 0; str[i]; i++)
        if (!isdigit(str[i]) && str[i] != '\n')
            return 0;
    return 1;
}

float isValidFloat(char *str)
{
    int dotCount = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '.')
        {
            dotCount++;
            if (dotCount > 1)
                return -1;
        }
        else if (!isdigit(str[i]) && str[i] != '\n')
            return -1;
    }
    return 1;
}

void readBooks()
{
    FILE *file = fopen(CSV_FILE, "r");
    if (!file)
    {
        perror("Could not open CSV file");
        return;
    }

    int searchChoice;
    char searchTerm[100];

    printf("\nSearch by:\n");
    printf("1. Author\n2. Title\n3. Publication Year\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &searchChoice);

    printf("Enter search term: ");
    fgets(searchTerm, sizeof(searchTerm), stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0;

    char line[MAX_LINE];
    struct Book b;

    // Skip header
    fgets(line, MAX_LINE, file);
    int found = 0;

    printf("\n--- Matching Books ---\n");

    while (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, ",");
        b.book_id = atoi(token);
        token = strtok(NULL, ","); // skip goodreads_book_id
        token = strtok(NULL, ","); // skip best_book_id
        token = strtok(NULL, ","); // skip work_id
        token = strtok(NULL, ","); // skip books_count
        token = strtok(NULL, ",");
        strncpy(b.isbn, token, 19);
        b.isbn[19] = '\0';
        token = strtok(NULL, ",");
        strncpy(b.authors, token, 99);
        b.authors[99] = '\0';
        token = strtok(NULL, ",");
        b.original_publication_year = atoi(token);
        token = strtok(NULL, ",");
        strncpy(b.original_title, token, 99);
        b.original_title[99] = '\0';
        token = strtok(NULL, ","); // skip language_code
        token = strtok(NULL, ",");
        b.average_rating = atof(token);

        int match = 0;
        switch (searchChoice)
        {
        case 1:
            if (strstr(b.authors, searchTerm) != NULL)
                match = 1;
            break;
        case 2:
            if (strstr(b.original_title, searchTerm) != NULL)
                match = 1;
            break;
        case 3:
            if (atoi(searchTerm) == b.original_publication_year)
                match = 1;
            break;
        default:
            printf("Invalid choice.\n");
            fclose(file);
            return;
        }

        if (match)
        {
            found = 1;
            printf("\nBook ID: %d\n", b.book_id);
            printf("Title: %s\n", b.original_title);
            printf("Author(s): %s\n", b.authors);
            printf("Year: %d\n", b.original_publication_year);
            printf("ISBN: %s\n", b.isbn);
            printf("Rating: %.2f\n", b.average_rating);
        }
    }

    if (!found)
    {
        printf("No matching entries found.\n");
    }

    fclose(file);
}

// Function to save a new book to CSV
void savingmode()
{
    struct Book b;
    char buffer[100];

    printf("Enter Book ID: ");
    fgets(buffer, sizeof(buffer), stdin);
    while (!isValidInt(buffer))
    {
        printf("Invalid. Enter Book ID again: ");
        fgets(buffer, sizeof(buffer), stdin);
    }
    b.book_id = atoi(buffer);

    printf("Enter ISBN: ");
    fgets(b.isbn, sizeof(b.isbn), stdin);
    strtok(b.isbn, "\n");

    printf("Enter Author(s): ");
    fgets(b.authors, sizeof(b.authors), stdin);
    strtok(b.authors, "\n");

    printf("Enter Publication Year: ");
    fgets(buffer, sizeof(buffer), stdin);
    while (!isValidInt(buffer))
    {
        printf("Invalid. Enter year again: ");
        fgets(buffer, sizeof(buffer), stdin);
    }
    b.original_publication_year = atoi(buffer);

    printf("Enter Book Title: ");
    fgets(b.original_title, sizeof(b.original_title), stdin);
    strtok(b.original_title, "\n");

    printf("Enter Average Rating: ");
    fgets(buffer, sizeof(buffer), stdin);
    while (isValidFloat(buffer) == -1)
    {
        printf("Invalid. Enter rating again: ");
        fgets(buffer, sizeof(buffer), stdin);
    }
    b.average_rating = atof(buffer);

    FILE *file = fopen(CSV_FILE, "a");
    if (!file)
    {
        perror("Could not open file for appending");
        return;
    }

    // Other fields are skipped with placeholders
    fprintf(file, "%d,0,0,0,0,%s,%s,%d,%s,eng,%.2f,0\n",
            b.book_id, b.isbn, b.authors,
            b.original_publication_year, b.original_title,
            b.average_rating);

    fclose(file);
    printf("Book added successfully.\n");
}

// Main function (starts the program)
int main()
{
    int choice;
    while (1)
    {
        printf("\n--- Book CSV Manager ---\n");
        printf("1. Add new book\n");
        printf("2. View all books\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline left by scanf

        switch (choice)
        {
        case 1:
            savingmode();
            break;
        case 2:
            readBooks();
            break;
        case 3:
            printf("Exiting.\n");
            exit(0);
        default:
            printf("Invalid choice.\n");
        }
    }
    return 0;
}

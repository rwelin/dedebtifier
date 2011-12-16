/*
 * Dedebtifier
 *
 * debts.c
 *
 * Author: Robert Welin <robert dot welin at gmail dot com>
 * Last Change: Fri December 16 2011
 *
 */

#include "debts.h"

#define MAX_ERROR 0.001
#define FILE_BUFFER_SIZE 512

/*
 * Creates a default Debts object
 *
 * Returns: A new Debts object
 */
Debts new_debts(void)
{
    Debts debts;
    debts.persons = NULL;
    debts.length = 0;
    return debts;
}

/*
 * Test for init_debts
 */
#if _UNITTEST_
void test_new_debts(void)
{
    Debts debts;
    debts = new_debts();
    assert(debts.persons == NULL);
    assert(debts.length == 0);
}
#endif

/*
 * Creates a new Triangle object
 *
 * Returns: A new Triangle
 */
Triangle new_triangle(void)
{
    Triangle tri = (float**)malloc(sizeof(float*)*3);
    return tri;
}

/*
 * Test for new_triangle
 */
#if _UNITTEST_
void test_new_triangle(void)
{
    Triangle tri = new_triangle();
    assert(tri != NULL);
    free(tri);
    tri = NULL;
}
#endif

/*
 * Deletes a triangle object
 *
 * Parameter 1: The Triangle that will be deleted
 */
void delete_triangle(Triangle *triangle)
{
    free(*triangle);
    *triangle = NULL;
}

/*
 * Test for delete_triangle
 */
#if _UNITTEST_
void test_delete_triangle(void)
{
    Triangle tri = new_triangle();
    delete_triangle(&tri);
    assert(tri == NULL);
}
#endif

/*
 * Creates a Person
 *
 * Parameter 1: Sets Person.name
 * Parameter 2: Sets Person.debts
 * Parameter 3: Sets Person.number_of_debts
 *
 * Returns: A new Person
 */
Person new_person(const char * const name, Debt * const debts, const int number_of_debts)
{
    Person p;
    strcpy(p.name, name);
    p.debts = debts;
    p.number_of_debts = number_of_debts;
    return p;
}

/*
 * Test for new_person
 */
#if _UNITTEST_
void test_new_person(void)
{
    Person person;
    Debt *debts;

    person = new_person("Bob", NULL, 0);
    assert(strcmp(person.name, "Bob") == 0);
    assert(person.debts == NULL);
    assert(person.number_of_debts == 0);

    Person p1 = new_person("Bob", NULL, 0);
    Person p2 = new_person("John", NULL, 0);
    Person p3 = new_person("Meg", NULL, 0);

    Debt d1 = new_debt(&p1, 3.14);
    Debt d2 = new_debt(&p2, 42.0);
    Debt d3 = new_debt(&p3, 2.72);
    debts = (Debt*)malloc(3*sizeof(Debt));
    debts[0] = d1;
    debts[1] = d2;
    debts[2] = d3;
    person = new_person("Jeff", debts, 3);
    assert(strcmp(person.name, "Jeff") == 0);
    assert(person.number_of_debts == 3);
    assert(strcmp(person.debts[0].person->name, "Bob") == 0);
    assert(fabs(person.debts[0].amount - 3.14) < MAX_ERROR);
    assert(strcmp(person.debts[1].person->name, "John") == 0);
    assert(fabs(person.debts[1].amount - 42.0) < MAX_ERROR);
    assert(strcmp(person.debts[2].person->name, "Meg") == 0);
    assert(fabs(person.debts[2].amount - 2.72) < MAX_ERROR);

    free(debts);
    debts = NULL;
}
#endif

/*
 * Deletes a Person
 */
void delete_debts(Person *person)
{
    if (person != NULL)
    {
        if (person->debts != NULL)
        {
            free(person->debts);
            person->debts = NULL;
        }
    }
}

/*
 * Test for delete_person
 */
#if _UNITTEST_
void test_delete_debts(void)
{
    Person p = new_person("Bob", NULL, 0),
           p1 = new_person("John", NULL, 0),
           p2 = new_person("John", NULL, 0);
    Debt d0 = new_debt(&p1, 4.0),
         d1 = new_debt(&p2, 3.0);
    add_debt(&p, &d0);
    add_debt(&p, &d1);
    delete_debts(&p);
    assert(p.debts == NULL);
}
#endif

/*
 * Creates a Debt
 *
 * Parameter 1: The name of the debt
 * Parameter 2: The amount of the debt
 *
 * Returns: A new Debt
 */
Debt new_debt(Person * const person, const float debt)
{
    Debt d;
    d.person = person;
    d.amount = debt;
    return d;
}

/*
 * Test for new_debt
 */
#if _UNITTEST_
void test_new_debt(void)
{
    Debt debt;
    Person p = new_person("Bob", NULL, 0);
    debt = new_debt(&p, 1.23);
    assert(strcmp(debt.person->name, "Bob") == 0);
    assert(fabs(debt.amount - 1.23) < MAX_ERROR);
}
#endif

/*
 * Chacks if a Person has a debt to a Person
 * queried by name
 *
 * Parameter 1: The Person to check
 * Parameter 2: The name of the person to look for
 *
 * Returns: The index of the Debt that correspond
 * to parameter 1, otherwise -1
 */
int in_debt(const Person * const person, const char * const name)
{
    for (int i = 0; i < person->number_of_debts; i++)
    {
        if (strcmp(person->debts[i].person->name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

/*
 * Test for in_debt
 */
#if _UNITTEST_
void test_in_debt(void)
{
    Person p;
    Debt *debts;
    Person p1 = new_person("John", NULL, 0);
    Person p2 = new_person("Meg", NULL, 0);
    Person p3 = new_person("Jeff", NULL, 0);
    Debt d1 = new_debt(&p1, 1.23);
    Debt d2 = new_debt(&p2, 42.0);
    Debt d3 = new_debt(&p3, 3.14);
    debts = (Debt*)malloc(3*sizeof(Debt));
    debts[0] = d1;
    debts[1] = d2;
    debts[2] = d3;
    p = new_person("Bob", debts, 3);

    assert(in_debt(&p, "John") == 0);
    assert(in_debt(&p, "Meg") == 1);
    assert(in_debt(&p, "Jeff") == 2);
    assert(in_debt(&p, "Jim") == -1);

    free(debts);
    debts = NULL;
}
#endif

/*
 * Adds a debt to a Person
 *
 * Parameter 1: The Person to add a debt to
 * Parameter 2: The debt to be added
 */
void add_debt(Person * const person, const Debt * const debt)
{
    if (person == NULL) null_pointer_exception();
    int index;
    if ((index = in_debt(person, debt->person->name)) != -1)
    {
        person->debts[index] =
            new_debt(debt->person,
                        person->debts[index].amount + debt->amount);
    }
    else
    {
        person->number_of_debts++;
        person->debts =
            (Debt*)realloc(
                person->debts,
                person->number_of_debts*sizeof(Debt));
        person->debts[person->number_of_debts - 1] = *debt;
    }
}

/*
 * Test for add_debt
 */
#if _UNITTEST_
void test_add_debt(void)
{
    Person p;
    Debt d;
    Debt *debts = NULL;

    p = new_person("Bob", NULL, 0);
    Person p1 = new_person("Jeff", NULL, 0);
    d = new_debt(&p1, 3.14);

    add_debt(&p, &d);
    assert(p.debts != NULL);
    assert(p.number_of_debts == 1);
    assert(strcmp(p.debts[0].person->name, "Jeff") == 0);
    assert(fabs(p.debts[0].amount - 3.14) < MAX_ERROR);

    Person p2 = new_person("Alex", NULL, 0);
    Person p3 = new_person("John", NULL, 0);
    Person p4 = new_person("Meg", NULL, 0);

    Debt d1 = new_debt(&p2, 5.43);
    Debt d2 = new_debt(&p3, 42.0);
    Debt d3 = new_debt(&p4, 2.72);
    debts = (Debt*)malloc(3*sizeof(Debt));
    debts[0] = d1;
    debts[1] = d2;
    debts[2] = d3;

    p = new_person("Bob", debts, 3);

    add_debt(&p, &d);
    assert(p.number_of_debts == 4);
    assert(strcmp(p.debts[3].person->name, "Jeff") == 0);
    assert(fabs(p.debts[3].amount - 3.14) < MAX_ERROR);

    d = new_debt(&p3, 1.23);
    add_debt(&p, &d);

    assert(p.number_of_debts == 4);
    assert(strcmp(p.debts[1].person->name, "John") == 0);
    assert(fabs(p.debts[1].amount - 43.23) < MAX_ERROR);

    debts = NULL;
    free(p.debts);
    p.debts = NULL;
}
#endif

/*
 * Adds a Person to a Debts
 *
 * Parameter 1: The debts that will be modified
 * Parameter 2: The Person that is to be added
 */
void add_person(Debts *debts, const Person person)
{
    if (debts == NULL) null_pointer_exception();
    int index = -1;
    for (int i = 0; i < debts->length; i++)
    {
        if (strcmp(debts->persons[i].name, person.name) == 0)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        debts->length++;
        debts->persons =
            (Person*)realloc(
                debts->persons,
                debts->length*sizeof(Person));
        debts->persons[debts->length - 1] = person;
    }
    else
    {
        for (int i = 0; i < person.number_of_debts; i++)
        {
            add_debt(&debts->persons[index], &person.debts[i]);
        }
    }
}

/*
 * Test for add_person
 */
#if _UNITTEST_
void test_add_person(void)
{
    Debts debts;
    Person person, person1;

    debts = new_debts();

    person = new_person("Bob", NULL, 0);
    Person p1 = new_person("Jeff", NULL, 0),
           p2 = new_person("John", NULL, 0),
           p3 = new_person("Meg", NULL, 0);
    Debt d1 = new_debt(&p1, 3.14),
         d2 = new_debt(&p2, 42.0),
         d3 = new_debt(&p3, 2.72);
    add_debt(&person, &d1);
    add_debt(&person, &d2);
    add_debt(&person, &d3);

    add_person(&debts, person);

    assert(debts.length == 1);
    assert(strcmp(debts.persons[0].name, "Bob") == 0);

    person1 = new_person("Bob", NULL, 0);
    Person p4 = new_person("John", NULL, 0),
           p5 = new_person("Meg", NULL, 0);
    
    Debt d4 = new_debt(&p4, 4.12),
         d5 = new_debt(&p5, 5.63);
    add_debt(&person1, &d4);
    add_debt(&person1, &d5);
    add_person(&debts, person1);

    assert(debts.length == 1);
    assert(strcmp(debts.persons[0].name, "Bob") == 0);
    assert(fabs(debts.persons[0].debts[0].amount - 3.14) < MAX_ERROR);
    assert(fabs(debts.persons[0].debts[1].amount - 42.0 - 4.12) < MAX_ERROR);
    assert(fabs(debts.persons[0].debts[2].amount - 2.72 - 5.63) < MAX_ERROR);
}
#endif

/*
 * Searches a person for a debt and returns it
 * if found, otherwise NULL
 *
 * Parameter 1: The Person to be searched
 * Parameter 2: The name of the Person to be searched for
 *
 * Returns: A Debt with the corresponding name if found,
 * otherwise NULL
 */
Debt* get_debt(const Person * const person, const char * const name)
{
    int index;
    if ((index = in_debt(person, name)) != -1)
    {
        return &person->debts[index];
    }
    else
    {
        return NULL;
    }
}

/*
 * Test for query_debt
 */
#if _UNITTEST_
void test_get_debt(void)
{
    Person p, p1, p2, p3;
    Debt d1, d2, d3;
    Debt *search;
    p1 = new_person("John", NULL, 0);
    p2 = new_person("Meg", NULL, 0);
    p3 = new_person("Jeff", NULL, 0);
    d1 = new_debt(&p1, 3.13);
    d2 = new_debt(&p2, 4.24);
    d3 = new_debt(&p3, 5.35);

    p = new_person("Bob", NULL, 0);
    add_debt(&p, &d1);
    add_debt(&p, &d2);
    add_debt(&p, &d3);

    search = get_debt(&p, "Jeff");
    assert(strcmp(search->person->name, "Jeff") == 0);
    assert(fabs(search->amount - 5.35) < MAX_ERROR);

    search = get_debt(&p, "John");
    assert(strcmp(search->person->name, "John") == 0);
    assert(fabs(search->amount - 3.13) < MAX_ERROR);

    search = get_debt(&p, "Meg");
    assert(strcmp(search->person->name, "Meg") == 0);
    assert(fabs(search->amount - 4.24) < MAX_ERROR);

    search = get_debt(&p, "James");
    assert(search == NULL);
}
#endif

/*
 * Fetches a Person from a Debts object
 *
 * Parameter 1: The Debts object to search
 * Parameter 2: The name of the Person to search for
 *
 * Returns: The Person with the corresponding name
 * if it exists, otherwise NULL
 */
Person* get_person(const Debts * const debts, const char *name)
{
    for (int i = 0; i < debts->length; i++)
    {
        if (strcmp(debts->persons[i].name, name) == 0)
        {
            return &debts->persons[i];
        }
    }
    return NULL;
}

/*
 * Test for get_person
 */
#if _UNITTEST_
void test_get_person(void)
{
    Debts debts = new_debts();
    add_person(&debts, new_person("John", NULL, 0));
    add_person(&debts, new_person("Meg", NULL, 0));
    add_person(&debts, new_person("Bob", NULL, 0));

    assert(strcmp(get_person(&debts, "John")->name, "John") == 0);
    assert(strcmp(get_person(&debts, "Meg")->name, "Meg") == 0);
    assert(strcmp(get_person(&debts, "Bob")->name, "Bob") == 0);
}
#endif

/*
 * Adds to Debts objects
 *
 * Parameter 1: A Debts object
 * Parameter 2: A Debts object
 *
 * Returns: The two objects added
 */
Debts merge_debts(const Debts * const d1, const Debts * const d2)
{
    Debts debts = new_debts();
    for (int i = 0; i < d1->length; i++)
    {
        add_person(&debts, d1->persons[i]);
    }
    for (int i = 0; i < d2->length; i++)
    {
        add_person(&debts, d2->persons[i]);
    }
    return debts;
}

/*
 * Test for merge_debts
 */
#if _UNITTEST_
void test_merge_debts(void)
{
    Debts d1, d2, debts;

    system("echo \"D J=9.1 R=8.2 S=7.3\nJ D=6.4 R=5.5 S=4.6\nR D=3.7 J=2.8 S=1.9\nS D=1.4 J=2.6 R=3.8\n\" > tmp_file_test_src_1");
    system("echo \"D J=2.2 R=3.3 S=4.4\nJ D=5.5 R=7.7 S=8.8\nR D=9.9 J=1.2 S=3.4\nS D=4.5 J=5.6 R=6.7\n\" > tmp_file_test_src_2");

    d1 = read_debts("tmp_file_test_src_1");
    d2 = read_debts("tmp_file_test_src_2");

    debts = merge_debts(&d1, &d2);

    assert(debts.length == 4);
    assert(strcmp(debts.persons[0].name, "D") == 0);
    assert(strcmp(debts.persons[1].name, "J") == 0);
    assert(strcmp(debts.persons[2].name, "R") == 0);
    assert(strcmp(debts.persons[3].name, "S") == 0);

    assert(debts.persons[0].number_of_debts == 3);
    assert(strcmp(debts.persons[0].debts[0].person->name, "J") == 0);
    assert(fabs(debts.persons[0].debts[0].amount - 11.3) < MAX_ERROR);
    assert(strcmp(debts.persons[0].debts[1].person->name, "R") == 0);
    assert(fabs(debts.persons[0].debts[1].amount - 11.5) < MAX_ERROR);
    assert(strcmp(debts.persons[0].debts[2].person->name, "S") == 0);
    assert(fabs(debts.persons[0].debts[2].amount - 11.7) < MAX_ERROR);

    assert(debts.persons[1].number_of_debts == 3);
    assert(strcmp(debts.persons[1].debts[0].person->name, "D") == 0);
    assert(fabs(debts.persons[1].debts[0].amount - 11.9) < MAX_ERROR);
    assert(strcmp(debts.persons[1].debts[1].person->name, "R") == 0);
    assert(fabs(debts.persons[1].debts[1].amount - 13.2) < MAX_ERROR);
    assert(strcmp(debts.persons[1].debts[2].person->name, "S") == 0);
    assert(fabs(debts.persons[1].debts[2].amount - 13.4) < MAX_ERROR);

    assert(debts.persons[2].number_of_debts == 3);
    assert(strcmp(debts.persons[2].debts[0].person->name, "D") == 0);
    assert(fabs(debts.persons[2].debts[0].amount - 13.6) < MAX_ERROR);
    assert(strcmp(debts.persons[2].debts[1].person->name, "J") == 0);
    assert(fabs(debts.persons[2].debts[1].amount - 4.0) < MAX_ERROR);
    assert(strcmp(debts.persons[2].debts[2].person->name, "S") == 0);
    assert(fabs(debts.persons[2].debts[2].amount - 5.3) < MAX_ERROR);

    assert(debts.persons[3].number_of_debts == 3);
    assert(strcmp(debts.persons[3].debts[0].person->name, "D") == 0);
    assert(fabs(debts.persons[3].debts[0].amount - 5.9) < MAX_ERROR);
    assert(strcmp(debts.persons[3].debts[1].person->name, "J") == 0);
    assert(fabs(debts.persons[3].debts[1].amount - 8.2) < MAX_ERROR);
    assert(strcmp(debts.persons[3].debts[2].person->name, "R") == 0);
    assert(fabs(debts.persons[3].debts[2].amount - 10.5) < MAX_ERROR);

    system("rm tmp_file_test_src_1");
    system("rm tmp_file_test_src_2");
}
#endif

/*
 * Gets an array of all the names of the Persons in a Debts object
 *
 * Parameter 1: A Debts object
 *
 * Returns: The name of the Persons in a Debts object
 */
char** get_names(const Debts debts)
{
    char **names;
    names = (char**)malloc(debts.length*sizeof(char)*NAME_SIZE);
    for (int i = 0; i < debts.length; i++)
    {
        names[i] = debts.persons[i].name;
    }
    return names;
}

/*
 * Test for get_names
 */
#if _UNITTEST_
void test_get_names(void)
{
    Debts debts = new_debts();
    add_person(&debts, new_person("Bob", NULL, 0));
    add_person(&debts, new_person("John", NULL, 0));
    add_person(&debts, new_person("Meg", NULL, 0));
    char **names = get_names(debts);

    assert(strcmp(names[0], "Bob") == 0);
    assert(strcmp(names[1], "John") == 0);
    assert(strcmp(names[2], "Meg") == 0);

    free(names);
    names = NULL;
}
#endif

/*
 * Removes a Person from a Debts object
 *
 * Parameter 1: The Debts from which the Person should be removed
 * Parameter 2: The name of the Person to be removed
 */
void remove_debt(Person *person, const char *name)
{
    if (person == NULL) null_pointer_exception();
    Person p;
    p = new_person(person->name, NULL, 0);
    for (int i = 0; i < person->number_of_debts; i++)
    {
        if (strcmp(person->debts[i].person->name, name) != 0)
        {
            add_debt(&p, &person->debts[i]);
        }
    }
    delete_debts(person);
    *person = p;
}

/*
 * Test for remove_person
 */
#if _UNITTEST_
void test_remove_debt(void)
{
    Debts debts;
    system("echo \"D J=2.2 R=3.3 S=4.4\nJ D=5.5 R=7.7 S=8.8\nR D=9.9 J=1.2 S=3.4\nS D=4.5 J=5.6 R=6.7\n\" > tmp_file_test_remove_debt");

    debts = read_debts("tmp_file_test_remove_debt");

    remove_debt(&debts.persons[0], "R");

    assert(debts.length == 4);

    assert(debts.persons[0].number_of_debts == 2);
    assert(strcmp(debts.persons[0].debts[0].person->name, "J") == 0);
    assert(fabs(debts.persons[0].debts[0].amount - 2.2) < MAX_ERROR);
    assert(strcmp(debts.persons[0].debts[1].person->name, "S") == 0);
    assert(fabs(debts.persons[0].debts[1].amount - 4.4) < MAX_ERROR);

    assert(debts.persons[1].number_of_debts == 3);
    assert(debts.persons[2].number_of_debts == 3);
    assert(debts.persons[3].number_of_debts == 3);

    system("rm tmp_file_test_remove_debt");
}
#endif

/*
 * Reads the first line in a debt file and
 * returns a minimal Debts object with names
 * initialised
 *
 * Parameter 1: The name of the debt file
 */
Debts read_names(const char *file_name)
{
    FILE *file;
    if ((file = fopen(file_name, "r")) != NULL)
    {
        Debts debts = new_debts();
        char *name;
        size_t buf_size = FILE_BUFFER_SIZE;
        char *buf = (char*)malloc(sizeof(char)*buf_size);
        while (getline(&buf, &buf_size, file) != -1)
        {
            name = strtok(buf, " ");
            if (strcmp(name, "\n") != 0)
            {
                add_person(&debts, new_person(name, NULL, 0));
            }
        }
        free(buf);
        buf = NULL;
        fclose(file);
        return debts;
    }
    else
    {
        no_such_file_error(file_name);
    }
}

/*
 * Test for read_names
 */
#if _UNITTEST_
void test_read_names(void)
{
    Debts debts;
    system("echo \"D J=2.2 R=3.3 S=4.4\nJ D=5.5 R=7.7 S=8.8\nR D=9.9 J=1.2 S=3.4\nS D=4.5 J=5.6 R=6.7\n\" > tmp_file_test_read_names");

    debts = read_names("tmp_file_test_read_names");

    assert(debts.length == 4);
    assert(strcmp(debts.persons[0].name, "D") == 0);
    assert(strcmp(debts.persons[1].name, "J") == 0);
    assert(strcmp(debts.persons[2].name, "R") == 0);
    assert(strcmp(debts.persons[3].name, "S") == 0);

    system("rm tmp_file_test_read_names");
}
#endif

/*
 * Reads the debt file and returns an array of Persons containing
 * the debts
 *
 * Parameter 1: The name of the debts file
 */
Debts read_debts(const char *file_name)
{
    FILE *file;
    if ((file = fopen(file_name, "r")) != NULL)
    {
        Debts debts;
        char *data;
        char *name;
        char *owed_amount_str;
        size_t buf_size = FILE_BUFFER_SIZE;
        char *buf = (char*)malloc(sizeof(char)*buf_size);
        char *data_buf = (char*)malloc(sizeof(char)*buf_size);
        int person_id = 0;
        float owed_amount;
        debts = read_names(file_name);
        // Get debts
        for (int i = 0;
             i < debts.length && getline(&buf, &buf_size, file) != -1;
             i++)
        {
            data = strtok(buf, " ");
            strcpy(data_buf, data);
            for (char *buf_p = buf + (length(data)+1)*sizeof(char);
                 data = strtok(buf_p, " \n");
                 buf_p += (length(data)+1)*sizeof(char))
            {
                strcpy(data_buf, data);
                name = strtok(data_buf, "=");
                owed_amount_str = strtok(NULL, "=");
                sscanf(owed_amount_str, "%f", &owed_amount);
                Debt debt = new_debt(get_person(&debts, name), owed_amount);
                add_debt(&debts.persons[i], &debt);
            }
        }
        free(data_buf);
        data_buf = NULL;
        free(buf);
        buf = NULL;
        fclose(file);
        return debts;
    }
    else
    {
        no_such_file_error(file_name);
    }
}

/*
 * Test for read_debts
 */
#if _UNITTEST_
void test_read_debts(void)
{
    Debts debts;
    system("echo \"D J=2.2 R=3.3 S=4.4 \nJ D=5.5 R=7.7 S=8.8 \nR D=9.9 J=1.2 S=3.4 \nS D=4.5 J=5.6 R=6.7 \n\" > tmp_file_test_read_debts");

    debts = read_debts("tmp_file_test_read_debts");

    assert(debts.length == 4);
    assert(strcmp(debts.persons[0].name, "D") == 0);
    assert(strcmp(debts.persons[1].name, "J") == 0);
    assert(strcmp(debts.persons[2].name, "R") == 0);
    assert(strcmp(debts.persons[3].name, "S") == 0);

    assert(debts.persons[0].number_of_debts == 3);
    assert(strcmp(debts.persons[0].debts[0].person->name, "J") == 0);
    assert(fabs(debts.persons[0].debts[0].amount - 2.2) < MAX_ERROR);
    assert(strcmp(debts.persons[0].debts[1].person->name, "R") == 0);
    assert(fabs(debts.persons[0].debts[1].amount - 3.3) < MAX_ERROR);
    assert(strcmp(debts.persons[0].debts[2].person->name, "S") == 0);
    assert(fabs(debts.persons[0].debts[2].amount - 4.4) < MAX_ERROR);

    assert(debts.persons[1].number_of_debts == 3);
    assert(strcmp(debts.persons[1].debts[0].person->name, "D") == 0);
    assert(fabs(debts.persons[1].debts[0].amount - 5.5) < MAX_ERROR);
    assert(strcmp(debts.persons[1].debts[1].person->name, "R") == 0);
    assert(fabs(debts.persons[1].debts[1].amount - 7.7) < MAX_ERROR);
    assert(strcmp(debts.persons[1].debts[2].person->name, "S") == 0);
    assert(fabs(debts.persons[1].debts[2].amount - 8.8) < MAX_ERROR);

    assert(debts.persons[2].number_of_debts == 3);
    assert(strcmp(debts.persons[2].debts[0].person->name, "D") == 0);
    assert(fabs(debts.persons[2].debts[0].amount - 9.9) < MAX_ERROR);
    assert(strcmp(debts.persons[2].debts[1].person->name, "J") == 0);
    assert(fabs(debts.persons[2].debts[1].amount - 1.2) < MAX_ERROR);
    assert(strcmp(debts.persons[2].debts[2].person->name, "S") == 0);
    assert(fabs(debts.persons[2].debts[2].amount - 3.4) < MAX_ERROR);

    assert(debts.persons[3].number_of_debts == 3);
    assert(strcmp(debts.persons[3].debts[0].person->name, "D") == 0);
    assert(fabs(debts.persons[3].debts[0].amount - 4.5) < MAX_ERROR);
    assert(strcmp(debts.persons[3].debts[1].person->name, "J") == 0);
    assert(fabs(debts.persons[3].debts[1].amount - 5.6) < MAX_ERROR);
    assert(strcmp(debts.persons[3].debts[2].person->name, "R") == 0);
    assert(fabs(debts.persons[3].debts[2].amount - 6.7) < MAX_ERROR);

    system("rm tmp_file_test_read_debts");
}
#endif

/*
 * Removes all debts between Persons that are 0
 *
 * Parameter 1: Debts object to be cleaned
 */
void clean_debts(Debts *debts)
{
    for (int i = 0; i < debts->length; i++) 
    {
        for (int j = 0; j < debts->persons[i].number_of_debts; j++) 
        {
            if (fabs(debts->persons[i].debts[j].amount) < MAX_ERROR)
            {
                remove_debt(&debts->persons[i], debts->persons[i].debts[j].person->name);
                j = -1;
            }
        }
    }   
}

/*
 * Test for clean_debts
 */
#if _UNITTEST_
void test_clean_debts(void)
{
    Debts debts;
    system("echo \"D J=2.2 R=0.0 S=4.4 \nJ D=0.0 R=7.7 S=8.8 \nR D=9.9 J=1.2 S=0.0 \nS D=0.0 J=5.6 R=0.0 \n\" > tmp_file_clean_debts");

    debts = read_debts("tmp_file_clean_debts");

    clean_debts(&debts);

    assert(debts.length == 4);
    assert(strcmp(debts.persons[0].name, "D") == 0);
    assert(strcmp(debts.persons[1].name, "J") == 0);
    assert(strcmp(debts.persons[2].name, "R") == 0);
    assert(strcmp(debts.persons[3].name, "S") == 0);

    assert(debts.persons[0].number_of_debts == 2);
    assert(fabs(debts.persons[0].debts[0].amount - 2.2) < MAX_ERROR);
    assert(fabs(debts.persons[0].debts[1].amount - 4.4) < MAX_ERROR);

    assert(debts.persons[1].number_of_debts == 2);
    assert(fabs(debts.persons[1].debts[0].amount - 7.7) < MAX_ERROR);
    assert(fabs(debts.persons[1].debts[1].amount - 8.8) < MAX_ERROR);

    assert(debts.persons[2].number_of_debts == 2);
    assert(fabs(debts.persons[2].debts[0].amount - 9.9) < MAX_ERROR);
    assert(fabs(debts.persons[2].debts[1].amount - 1.2) < MAX_ERROR);

    assert(debts.persons[3].number_of_debts == 1);
    assert(fabs(debts.persons[3].debts[0].amount - 5.6) < MAX_ERROR);

    system("rm tmp_file_clean_debts");
}
#endif

/*
 * Simplifies debt situations where to people
 * owe eachother money
 *
 * Parameter 1: The Debts object to be simplified
 */
void simplify_mutual_debts(Debts * const debts)
{
    for (int i = 0; i < debts->length; i++)
    {
        for (int j = 0; j < debts->persons[i].number_of_debts; j++)
        {
            int index;
            if ((index = in_debt(debts->persons[i].debts[j].person, debts->persons[i].name)) != -1)
            {
                float *d1 = &debts->persons[i].debts[j].amount;
                float *d2 = &debts->persons[i].debts[j].person->debts[index].amount;
                if (*d1 > MAX_ERROR && *d2 > MAX_ERROR)
                {
                    if (*d1 < *d2)
                    {
                        *d2 -= *d1;
                        *d1 = 0;
                    }
                    else if (*d2 < *d1)
                    {
                        *d1 -= *d2;
                        *d2 = 0;
                    }
                    else
                    {
                        *d1 = *d2 = 0;
                    }
                }
            }
        }
    }
    //clean_debts(debts);
}

/*
 * Test for simplify_mutual_debts
 */
#if _UNITTEST_
void test_simplify_mutual_debts()
{
    Debts debts;
    system("echo \"D J=2.2 R=3.3 S=4.4 \nJ D=5.5 R=7.7 S=8.8 \nR D=9.9 J=1.2 S=3.4 \nS D=4.5 J=5.6 R=6.7 \n\" > tmp_file_test_simplify_mutual_debts");

    debts = read_debts("tmp_file_test_simplify_mutual_debts");

    simplify_mutual_debts(&debts);

    assert(debts.length == 4);
    assert(strcmp(debts.persons[0].name, "D") == 0);
    assert(strcmp(debts.persons[1].name, "J") == 0);
    assert(strcmp(debts.persons[2].name, "R") == 0);
    assert(strcmp(debts.persons[3].name, "S") == 0);

    assert(debts.persons[0].number_of_debts == 3);
    assert(strcmp(debts.persons[0].debts[0].person->name, "J") == 0);
    assert(fabs(debts.persons[0].debts[0].amount - 0.0) < MAX_ERROR);
    assert(strcmp(debts.persons[0].debts[1].person->name, "R") == 0);
    assert(fabs(debts.persons[0].debts[1].amount - 0.0) < MAX_ERROR);
    assert(strcmp(debts.persons[0].debts[2].person->name, "S") == 0);
    assert(fabs(debts.persons[0].debts[2].amount - 0.0) < MAX_ERROR);

    assert(debts.persons[1].number_of_debts == 3);
    assert(strcmp(debts.persons[1].debts[0].person->name, "D") == 0);
    assert(fabs(debts.persons[1].debts[0].amount - 3.3) < MAX_ERROR);
    assert(strcmp(debts.persons[1].debts[1].person->name, "R") == 0);
    assert(fabs(debts.persons[1].debts[1].amount - 6.5) < MAX_ERROR);
    assert(strcmp(debts.persons[1].debts[2].person->name, "S") == 0);
    assert(fabs(debts.persons[1].debts[2].amount - 3.2) < MAX_ERROR);

    assert(debts.persons[2].number_of_debts == 3);
    assert(strcmp(debts.persons[2].debts[0].person->name, "D") == 0);
    assert(fabs(debts.persons[2].debts[0].amount - 6.6) < MAX_ERROR);
    assert(strcmp(debts.persons[2].debts[1].person->name, "J") == 0);
    assert(fabs(debts.persons[2].debts[1].amount - 0.0) < MAX_ERROR);
    assert(strcmp(debts.persons[2].debts[2].person->name, "S") == 0);
    assert(fabs(debts.persons[2].debts[2].amount - 0.0) < MAX_ERROR);

    assert(debts.persons[3].number_of_debts == 3);
    assert(strcmp(debts.persons[3].debts[0].person->name, "D") == 0);
    assert(fabs(debts.persons[3].debts[0].amount - 0.1) < MAX_ERROR);
    assert(strcmp(debts.persons[3].debts[1].person->name, "J") == 0);
    assert(fabs(debts.persons[3].debts[1].amount - 0.0) < MAX_ERROR);
    assert(strcmp(debts.persons[3].debts[2].person->name, "R") == 0);
    assert(fabs(debts.persons[3].debts[2].amount - 3.3) < MAX_ERROR);

    system("rm tmp_file_test_simplify_mutual_debts");
}
#endif

/*
 * Finds a set of three debt related Persons with one 
 * of the Persons as a base
 *
 * Parameter 1: The Person to use as the base node
 *
 * Returns: An array of three pointers to Persons, if
 * no triangle is found the function returns NULL
 */
Triangle find_triangle_with(Person * const person)
{
    Person const *p1, *p2, *p3;
    p1 = person;
    for (int i = 0; i < p1->number_of_debts; i++) 
    {
        p2 = p1->debts[i].person;
        if (p1->debts[i].amount > MAX_ERROR)
        {
            for (int j = 0; j < p2->number_of_debts; j++) 
            {
                int index;
                p3 = p2->debts[j].person;
                if (p2->debts[j].amount > MAX_ERROR && (index = in_debt(p1, p3->name)) != -1)
                {
                    Triangle tri = new_triangle();
                    tri[0] = &p1->debts[i].amount;
                    tri[1] = &p2->debts[j].amount;
                    tri[2] = &p1->debts[index].amount;
                    return tri;
                }
            }
        }
    }
    return NULL;
}

/*
 * Test for find_traingle_with
 */
#if _UNITTEST_
void test_find_triangle_with(void)
{
    Debts debts;
    system("echo \"D J=3.2 R=1.5 \nJ R=4.6 \nR \" > test_find_triangle_with");

    debts = read_debts("test_find_triangle_with");

    Triangle t1 = find_triangle_with(&debts.persons[0]);
    Triangle t2 = find_triangle_with(&debts.persons[1]);
    Triangle t3 = find_triangle_with(&debts.persons[2]);

    assert(fabs(*t1[0] - 3.2) < MAX_ERROR);
    assert(fabs(*t1[1] - 4.6) < MAX_ERROR);
    assert(fabs(*t1[2] - 1.5) < MAX_ERROR);

    assert(t2 == NULL);
    assert(t3 == NULL);

    delete_triangle(&t1);
    delete_triangle(&t2);
    delete_triangle(&t3);

    system("rm test_find_triangle_with");

    system("echo \"D R=4.13 \nJ D=10.0 R=6.72 \nR \nS D=0.2 R=42.0 \" > test_find_triangle_with");

    debts = read_debts("test_find_triangle_with");
    
    Triangle t0 = find_triangle_with(&debts.persons[0]);
    t1 = find_triangle_with(&debts.persons[1]);
    t2 = find_triangle_with(&debts.persons[2]);
    t3 = find_triangle_with(&debts.persons[3]);

    assert(t1 != NULL);
    assert(fabs(*t1[0] - 10.0) < MAX_ERROR);
    assert(fabs(*t1[1] - 4.13) < MAX_ERROR);
    assert(fabs(*t1[2] - 6.72) < MAX_ERROR);

    assert(t0 == NULL);
    assert(t2 == NULL);

    assert(t3 != NULL);
    assert(fabs(*t3[0] - 0.2) < MAX_ERROR);
    assert(fabs(*t3[1] - 4.13) < MAX_ERROR);
    assert(fabs(*t3[2] - 42.0) < MAX_ERROR);

    system("rm test_find_triangle_with");

}
#endif

/*
 * Finds a set of three debt related Persons
 *
 * Parameter 1: The Debts object to search through
 *
 * Returns: An array of three pointers to Persons, if
 * no triangle is found the function returns NULL
 */
Triangle find_triangle(Debts * const debts)
{
    Triangle tri;
    for (int i = 0; i < debts->length; i++) 
    {
        if ((tri = find_triangle_with(&debts->persons[i])) != NULL)
        {
            return tri;
        }
    }
    return NULL;
}

/*
 * Test for find_triangle
 */
#if _UNITTEST_
void test_find_triangle(void)
{
    Debts debts;
    system("echo \"D J=3.2 R=1.5 \nJ R=4.6 \nR \" > test_find_triangle");
    system("echo \"S J=6.3 \nR S=4.3 D=5.1 \nJ D=7.2 S=1.2 \nD \" > test_find_triangle_2");

    debts = read_debts("test_find_triangle");

    Triangle triangle = find_triangle(&debts);

    assert(fabs(*triangle[0] - 3.2) < MAX_ERROR);
    assert(fabs(*triangle[1] - 4.6) < MAX_ERROR);
    assert(fabs(*triangle[2] - 1.5) < MAX_ERROR);

    delete_triangle(&triangle);
    debts = read_debts("test_find_triangle_2");
    triangle = find_triangle(&debts);

    assert(triangle == NULL);

    delete_triangle(&triangle);

    system("rm test_find_triangle");
    system("rm test_find_triangle_2");
}
#endif

/*
 * Simplifies a Triangle
 *
 * Parameter 1: The Triangle object to simplify
 */
void simplify_triangle(Triangle triangle)
{
    if (triangle == NULL) null_pointer_exception();
    float *ab = triangle[0],
          *bc = triangle[1],
          *ac = triangle[2];
/*
    printf("From: %s -> %s = %2f\n %s -> %s = %2f\n %s -> %s = %2f\n\n",
        triangle[0]->name, triangle[1]->name, *ab,
        triangle[1]->name, triangle[2]->name, *bc,
        triangle[0]->name, triangle[2]->name, *ac);
*/
    if (*ab < *bc)
    {
        *ac += *ab;
        *bc -= *ab;
        *ab = 0;
    } 
    else if (*ab > *bc)
    {
        *ac += *bc;
        *ab -= *bc;
        *bc = 0;
    }
    else
    {
        *ac += *ab;
        *ab = 0;
        *bc = 0;
    }
}

/*
 * Test for simplify_triangle
 */
#if _UNITTEST_
void test_simplify_triangle(void)
{
    Debts debts;
    system("echo \"D J=3.2 R=1.5 \nJ R=4.6 \nR \" > test_simplify_triangle");
        
    debts = read_debts("test_simplify_triangle");

    Triangle tri = find_triangle(&debts);

    simplify_triangle(tri);

    assert(fabs(*tri[0] - 0.0) < MAX_ERROR);
    assert(fabs(*tri[1] - 1.4) < MAX_ERROR);
    assert(fabs(*tri[2] - 4.7) < MAX_ERROR);

    delete_triangle(&tri);

    system("rm test_simplify_triangle");
}
#endif

/*
 * Calculates the sum of what a Person is owed minus what he owes
 *
 * Parameter 1: The Debts object that the Person is part of
 * Parameter 2: The name of the person
 */
float get_person_net_debt(const Debts * const debts, const char * const name)
{
    float sum = 0.0;
    Person *p = get_person(debts, name);
    if (p != NULL)
    {
        for (int i = 0; i < debts->length; i++)
        {
            if (strcmp(debts->persons[i].name, name) == 0)
            {
                for (int j = 0; j < p->number_of_debts; j++)
                {
                    sum -= p->debts[j].amount;
                }
            }
            else
            {
                Debt *d = get_debt(&debts->persons[i], name);
                if (d != NULL)
                {
                    sum += d->amount;
                }
            }
        }
    }
}

/*
 * Test for get_person_net_debt
 */
void test_get_person_net_debt(void)
{
    Debts debts;
    system("echo \"D J=2.2 R=3.3 S=4.4 \nJ D=5.5 R=7.7 S=8.8 \nR D=9.9 J=1.2 S=3.4 \nS D=4.5 J=5.6 R=6.7 \n\" > tmp_file_test_get_person_net_debt");
    debts = read_debts("tmp_file_test_get_person_net_debt");
    float d0 = get_person_net_debt(&debts, debts.persons[0].name),
          d1 = get_person_net_debt(&debts, debts.persons[1].name),
          d2 = get_person_net_debt(&debts, debts.persons[2].name),
          d3 = get_person_net_debt(&debts, debts.persons[3].name);
    assert(fabs(d0 - 10.0) < MAX_ERROR);
    assert(fabs(d1 + 13.0) < MAX_ERROR);
    assert(fabs(d2 - 3.2) < MAX_ERROR);
    assert(fabs(d3 + 0.2) < MAX_ERROR);
    system("rm tmp_file_test_get_person_net_debt");
}

/*
 * Fills an array with the net debts of the Persons in a Debts object
 *
 * Parameter 1: The Debts object to calculate the net debts from
 * Parameter 2: The array to be filled
 */
void get_net_debts(const Debts * const debts, float * const sums)
{
    for (int i = 0; i < debts->length; i++)
    {
        sums[i] = get_person_net_debt(debts, debts->persons[i].name);
    }    
}

/*
 * Test for debts_sums
 */
void test_get_net_debts(void)
{
    Debts debts;
    system("echo \"D J=2.2 R=3.3 S=4.4 \nJ D=5.5 R=7.7 S=8.8 \nR D=9.9 J=1.2 S=3.4 \nS D=4.5 J=5.6 R=6.7 \n\" > tmp_file_test_get_net_debts");
    debts = read_debts("tmp_file_test_get_net_debts");
    float sums[4];
    get_net_debts(&debts, sums);
    assert(fabs(sums[0] - 10.0) < MAX_ERROR);
    assert(fabs(sums[1] + 13.0) < MAX_ERROR);
    assert(fabs(sums[2] - 3.2) < MAX_ERROR);
    assert(fabs(sums[3] + 0.2) < MAX_ERROR);
    system("rm tmp_file_test_get_net_debts");
}

/*
 * Simplifies a debts object
 *
 * Parameter 1: The Debts to be simplified
 */
void simplify_debts(Debts * const debts)
{ 
    float *presums = (float*)malloc(sizeof(float)*debts->length),
          *postsums = (float*)malloc(sizeof(float)*debts->length);
    get_net_debts(debts, presums);
    simplify_mutual_debts(debts); 
    for (bool changes = true; changes;)
    {
        changes = false;
        Triangle tri = find_triangle(debts);
        if (tri != NULL)
        {
            simplify_triangle(tri);
            //clean_debts(debts);
            changes = true;
            delete_triangle(&tri);
        }
    }
    get_net_debts(debts, postsums);
    for (int i = 0; i < debts->length; i++)
    {
        assert(fabs(presums[i] - postsums[i]) < MAX_ERROR);
    }
    free(presums);
    presums = NULL;
    free(postsums);
    postsums = NULL;
    //clean_debts(debts);
}

/*
 * Test for simplify_debts
 */
#if _UNITTEST_
void test_simplify_debts(void)
{
    Debts debts;
    Person *d, *j, *r, *s;
    system("echo \"D J=2.2 R=3.3 S=4.4 \nJ D=5.5 R=7.7 S=8.8 \nR D=9.9 J=1.2 S=3.4 \nS D=4.5 J=5.6 R=6.7 \n\" > tmp_file_test_simplify_debts");
    
    debts = read_debts("tmp_file_test_simplify_debts");

    simplify_debts(&debts);

    assert(debts.length == 4);
    assert(strcmp(debts.persons[0].name, "D") == 0);
    assert(strcmp(debts.persons[1].name, "J") == 0);
    assert(strcmp(debts.persons[2].name, "R") == 0);
    assert(strcmp(debts.persons[3].name, "S") == 0);

    d = &debts.persons[0];
    j = &debts.persons[1];
    r = &debts.persons[2];
    s = &debts.persons[3];

    assert(d->number_of_debts == 3);
    assert(fabs(-d->debts[0].amount -
               d->debts[1].amount -
               d->debts[2].amount +
               j->debts[0].amount +
               r->debts[0].amount +
               s->debts[0].amount - 10.0) < MAX_ERROR);

    assert(j->number_of_debts == 3);
    assert(fabs(-j->debts[0].amount -
               j->debts[1].amount -
               j->debts[2].amount +
               d->debts[0].amount +
               r->debts[1].amount +
               s->debts[1].amount + 13.0) < MAX_ERROR);

    assert(r->number_of_debts == 3);
    assert(fabs(-r->debts[0].amount -
               r->debts[1].amount -
               r->debts[2].amount +
               d->debts[1].amount +
               j->debts[1].amount +
               s->debts[2].amount - 3.2) < MAX_ERROR);

    assert(s->number_of_debts == 3);
    assert(fabs(-s->debts[0].amount -
               s->debts[1].amount -
               s->debts[2].amount +
               d->debts[2].amount +
               j->debts[2].amount +
               r->debts[2].amount + 0.2) < MAX_ERROR);
    
    system("rm tmp_file_test_simplify_debts");
}
#endif

/*
 * Translates a Debt object into a printable string
 *
 * Parameter 1: The Debts to be turned into a string
 */
void debts_to_string(const Debts * const debts, char * const str)
{
    if (str == NULL) null_pointer_exception();
    strcpy(str, "");
    for (int i = 0; i < debts->length; i++)
    {
        strcat(str, debts->persons[i].name);
        strcat(str, " ");
        for (int j = 0; j < debts->persons[i].number_of_debts; j++)
        {
            if (debts->persons[i].debts[j].amount > MAX_ERROR)
            {
            char name[NAME_SIZE];
            char amount[NAME_SIZE];
            strcpy(name, debts->persons[i].debts[j].person->name);
            sprintf(amount, "=%.2f ", debts->persons[i].debts[j].amount);
            strcat(str, name);
            strcat(str, amount);
            }
        }
        strcat(str, "\n");
    }
}

/*
 * Test for to_string
 */
#if _UNITTEST_
void test_debts_to_string(void)
{
    char *debts_string = (char*)malloc(FILE_BUFFER_SIZE*sizeof(char));
    Debts debts;
    system("echo \"D J=2.2 R=3.3 S=4.4 \nJ D=5.5 R=7.7 S=8.8 \nR D=9.9 J=1.2 S=3.4 \nS D=4.5 J=5.6 R=6.7 \n\" > tmp_file_test_debts_to_string");

    debts = read_debts("tmp_file_test_debts_to_string");

    debts_to_string(&debts, debts_string);

    assert(strcmp(debts_string, "D J=2.20 R=3.30 S=4.40 \nJ D=5.50 R=7.70 S=8.80 \nR D=9.90 J=1.20 S=3.40 \nS D=4.50 J=5.60 R=6.70 \n") == 0);

    free(debts_string);
    debts_string = NULL;
    system("rm tmp_file_test_debts_to_string");
}
#endif

/*
 * Writes a Debts back to a file
 *
 * Parameter 1: The depts to be written
 * Parameter 2: The name of the file
 */
void write_debts(const Debts * const debts, const char * const file_name)
{
    FILE *file;
    if ((file = fopen(file_name, "w")) != NULL)
    {
        char *debts_string = (char*)malloc(FILE_BUFFER_SIZE*sizeof(char));
        debts_to_string(debts, debts_string);
        fprintf(file, "%s", debts_string);
        free(debts_string);
        debts_string = NULL;
        fclose(file);
    }
    else
    {
        no_such_file_error(file_name);
    }
}

/*
 * Test for write_debts
 */
#if _UNITTEST_
void test_write_debts(void)
{
    char *debts_string = (char*)malloc(FILE_BUFFER_SIZE*sizeof(char));
    Debts debts;

    system("echo \"D J=2.2 R=3.3 S=4.4 \nJ D=5.5 R=7.7 S=8.8 \nR D=9.9 J=1.2 S=3.4 \nS D=4.5 J=5.6 R=6.7 \n\" > tmp_file_test_write_debts");

    debts = read_debts("tmp_file_test_write_debts");

    write_debts(&debts, "tmp_file_test_write_debts_output");

    debts = read_debts("tmp_file_test_write_debts_output");

    debts_to_string(&debts, debts_string);

    assert(strcmp(debts_string, "D J=2.20 R=3.30 S=4.40 \nJ D=5.50 R=7.70 S=8.80 \nR D=9.90 J=1.20 S=3.40 \nS D=4.50 J=5.60 R=6.70 \n") == 0);

    free(debts_string);
    debts_string = NULL;
    system("rm tmp_file_test_write_debts");
    system("rm tmp_file_test_write_debts_output");
}
#endif

/*
 * Pretty strings a Debts object
 *
 * Parameter 1: The Debts to be turned into a pretty string
 * Parameter 2: The string buffer
 *
 * Returns: A pretty print formated string
 */
char* pretty_print_debts(Debts debts)
{
    int line_length = 256;
    char *debts_string =(char*)malloc(line_length*debts.length*sizeof(char));
    simplify_debts(&debts);
    strcpy(debts_string, "");
    for (int i = 0; i < debts.length; i++)
    {
        char buf[line_length];
        for (int j = 0; j < debts.persons[i].number_of_debts; j++)
        {
            if (debts.persons[i].debts[j].amount > MAX_ERROR)
            {
                sprintf(buf, "%s owes %s £%.2f\n",
                            debts.persons[i].name,
                            debts.persons[i].debts[j].person->name,
                            debts.persons[i].debts[j].amount);
                strcat(debts_string, buf);
            }
        }
    }
    return debts_string;
}

/*
 * Test for pretty_print_debts
 */
#if _UNITTEST_
void test_pretty_print_debts(void)
{
    char *debts_string;
    Debts debts;
    system("echo \"D J=2.2 R=3.3 S=4.4 \nJ D=5.5 R=7.7 S=8.8 \nR D=9.9 J=1.2 S=3.4 \nS D=4.5 J=5.6 R=6.7 \n\" > tmp_file_test_pretty_print_debts");

    debts = read_debts("tmp_file_test_pretty_print_debts");

    debts_string = pretty_print_debts(debts);

    assert(strcmp(debts_string, "J owes D £10.00\nJ owes R £3.00\nS owes R £0.20\n") == 0);

    free(debts_string);
    debts_string = NULL;
    system("rm tmp_file_test_pretty_print_debts");
}
#endif

/*
 * Prints simplified debts to the console
 *
 * Parameter 1: The Debts to be simplified and printed out
 */
void print_debts(const Debts * const debts)
{
    char *debts_string;
    debts_string = pretty_print_debts(*debts);
    printf("%s", debts_string);
    free(debts_string);
    debts_string = NULL;
}

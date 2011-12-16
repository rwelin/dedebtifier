/*
 * Dedebtifier
 *
 * cui.c
 *
 * Author: Robert Welin <robert dot welin at gmail dot com>
 * Last Change: Fri December 16 2011
 *
 */

#include "cui.h"

void print_help(void)
{
    printf("%s - a debt simplification program\n", NAME);
    printf("USAGE:\n");
    printf("   accumulate debts in file -  %s -f FILE -p PAYER -n NAME -n ... -a AMOUNTS\n", NAME);
    printf("   pretty print debts       -  %s -f FILE\n", NAME);
    printf("   print help message       -  %s -h\n", NAME);
    printf("\n");
    printf("AMOUNTS has the following format: £A£B... where A is the amount that the first person specified with the -n flag owes the payer for the payment you are adding. B is the mount that the second person after a -n flag owes the payer and so on.\n");
    printf("\n");
}

Options parse_options(int argc, const char *argv[])
{
    char oc;
    Options opts;
    opts.namesc = 0;
    opts.accumulate = false;
    opts.do_help = false;
    opts.file_spec = false;
    while ((oc = getopt(argc, (char *const*)argv, "hf:p:n:a:")) != -1) 
    {
        switch (oc) 
        {
            case 'f':
                strcpy(opts.debts_file, optarg);
                opts.file_spec = true;
                break;
            case 'p':
                strcpy(opts.payer, optarg);
                opts.payer_spec = true;
                break;
            case 'h':
                opts.do_help = true;
                break;
            case 'n':
                strcpy(opts.names[opts.namesc], optarg);
                opts.namesc++;
            case 'a':
                strcpy(opts.amount_str, optarg);
                opts.accumulate = true;
            default:
                break;
        }
    }
    return opts;
}

#if _UNITTEST_
void test_parse_options(void)
{
    const char *argv[] = {"dedebtifier","-f","tmp_file_test_parse_options","-p","R","-n","D","-n","J","-n","R","-n","S","-a","£3.14£2.72£42.0£1.01"};
    Options opts = parse_options(15, argv);    
    
    assert(!opts.do_help);
    assert(opts.payer_spec);
    assert(opts.accumulate);
    assert(opts.file_spec);
    assert(strcmp("tmp_file_test_parse_options", opts.debts_file) == 0);
    assert(strcmp("R", opts.payer) == 0);
    assert(opts.namesc == 4);
    assert(strcmp("D", opts.names[0]) == 0);
    assert(strcmp("J", opts.names[1]) == 0);
    assert(strcmp("R", opts.names[2]) == 0);
    assert(strcmp("S", opts.names[3]) == 0);
}
#endif

void parse_amounts(char const* amount_str, float *amounts)
{
    size_t buf_size = 512;
    char *buf = (char*)malloc(sizeof(char)*buf_size);
    int index = 0;
    strcpy(buf, amount_str);
    for (char *data = strtok(buf, SPLIT_CHARS);
         data != NULL;
         data = strtok(NULL, SPLIT_CHARS)) 
    {
        sscanf(data, "%f", &amounts[index]);
        index++;
    }
    free(buf);
    buf = NULL;
}

#if _UNITTEST_
void test_parse_amounts(void)
{
    char *amount_str = "£1.23£3.14£42.0";
    float amounts[3];
    parse_amounts(amount_str, amounts);

    assert(fabs(amounts[0] - 1.23) < MAX_ERROR);
    assert(fabs(amounts[1] - 3.14) < MAX_ERROR);
    assert(fabs(amounts[2] - 42.0) < MAX_ERROR);
}
#endif

Debts parse_debts_string(char const *payer, const int namesc, char *innames[], char const* amount_str)
{
    Debts debts = new_debts();
    int payer_index;
    float amounts[namesc];

    char names[NAMES_MAX][NAME_SIZE];
    memcpy(names, innames, NAME_SIZE*namesc);

    parse_amounts(amount_str, amounts);
    for (int i = 0; i < namesc; i++) 
    {
        add_person(&debts, new_person(names[i], NULL, 0));
        if (strcmp(payer, names[i]) == 0)
        {
            payer_index = i;
        }
    }
    for (int i = 0; i < namesc; i++) 
    {
        if (i != payer_index)
        {
            Debt d = new_debt(&debts.persons[payer_index], amounts[i]);
            add_debt(&debts.persons[i], &d);
        }
    }
    return debts;
}

#if _UNITTEST_
void test_parse_debts_string(void)
{
    char payer[NAME_SIZE] = "R";
    char names[16][NAME_SIZE];
    strcpy(names[0], "D");
    strcpy(names[1], "J");
    strcpy(names[2], "R");
    strcpy(names[3], "S");
    int namesc = 4;
    char *amount_str = "£3.14£2.72£24.0£6.42";
    Debts debts = parse_debts_string(payer, namesc, (char**)names, amount_str);
    
    assert(debts.length == 4);
    
    assert(strcmp(debts.persons[0].name, "D") == 0);
    assert(debts.persons[0].number_of_debts == 1);
    assert(fabs(debts.persons[0].debts[0].amount - 3.14) < MAX_ERROR);

    assert(strcmp(debts.persons[1].name, "J") == 0);
    assert(debts.persons[1].number_of_debts == 1);
    assert(fabs(debts.persons[1].debts[0].amount - 2.72) < MAX_ERROR);

    assert(strcmp(debts.persons[2].name, "R") == 0);
    assert(debts.persons[2].number_of_debts == 0);

    assert(strcmp(debts.persons[3].name, "S") == 0);
    assert(debts.persons[3].number_of_debts == 1);
    assert(fabs(debts.persons[3].debts[0].amount - 6.42) < MAX_ERROR);
}
#endif

void execute(const Options opts)
{
    if (opts.accumulate && opts.payer_spec && opts.file_spec && opts.namesc)
    {
        Debts acc = read_debts(opts.debts_file),
              new = parse_debts_string(opts.payer, opts.namesc,
                                       (char**)opts.names,
                                       opts.amount_str);  
        acc = merge_debts(&acc, &new);
        /* TODO: Fix this huge hack where the debts have to be written to
         * a file and then read back to make sure than the merging of the
         * debts work */
        write_debts(&acc, "tmp_dedebtifier_execute");
        acc = read_debts("tmp_dedebtifier_execute");
        system("rm tmp_dedebtifier_execute");
        simplify_debts(&acc);
        write_debts(&acc, opts.debts_file);
    }
    else if (opts.file_spec)
    {
        Debts debts = read_debts(opts.debts_file);
        printf(pretty_print_debts(debts));
    }
    else if (opts.do_help)
    {
        print_help();
    }
    else
    {
        print_help();
        exit(1);
    }
}

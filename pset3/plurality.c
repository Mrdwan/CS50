#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
bool compare_strings(string a, string b);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (compare_strings(candidates[i].name, name))
        {
            // candidate found, upvote
            candidates[i].votes++;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int max = i;

        for (int j = i + 1; j < candidate_count; j++)
        {
            if (candidates[j].votes > candidates[max].votes)
            {
                max = j;
            }
        }

        if (max != i)
        {
            candidate maximum = candidates[max];
            candidates[max] = candidates[i];
            candidates[i] = maximum;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        printf("%s\n", candidates[i].name);

        if (candidates[i + 1].votes != candidates[i].votes)
        {
            return;
        }
    }

    return;
}

bool compare_strings(string a, string b)
{
    // Compare strings' lengths
    if (strlen(a) != strlen(b))
    {
        return false;
    }

    // Compare strings character by character
    for (int i = 0, n = strlen(a); i < n; i++)
    {
        // Different
        if (a[i] != b[i])
        {
            return false;
        }
    }

    // Same
    return true;
}
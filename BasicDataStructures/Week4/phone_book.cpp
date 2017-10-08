#include <iostream>
#include <vector>
#include <string>
#include <sys/resource.h>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, name;
    int number;
};

const int MAX_PHONEBOOK_SIZE = 10000000;


void prepopulatePhonebook(string (&phonebook)[MAX_PHONEBOOK_SIZE])
{
    for (auto entry : phonebook) {
        entry = "not found";
    }
}

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add") {
            if (queries[i].number > MAX_PHONEBOOK_SIZE)
                continue;
            cin >> queries[i].number >> queries[i].name;
        }
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {

    string response = "not found";

    string phonebook[MAX_PHONEBOOK_SIZE];
    for (size_t j = 0; j < MAX_PHONEBOOK_SIZE; j++) {
        phonebook[j] = "not found";
    }
    //prepopulatePhonebook(&phonebook);

    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query> contacts;
    for (size_t i = 0; i < queries.size(); ++i) {
        if (queries[i].type == "add")
            phonebook[queries[i].number] = queries[i].name;
        else if (queries[i].type == "del") 
            phonebook[queries[i].number] = "not found";
        else {
            if ( (phonebook[queries[i].number]).compare(response) != 0)
                result.push_back(phonebook[queries[i].number]);
            else
                result.push_back(response);
        }
    }
    return result;
}

int main() {
    //write_responses(process_queries(read_queries()));

    const rlim_t kStackSize = 512L * 1024L * 1024L;   // min stack size = 512 Mb
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }

    vector<Query> queries = read_queries();
    write_responses(process_queries(queries));
    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    //vector<string> elems;
    
    vector<vector<string>> hashtable;

    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): 
        bucket_count(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end            
            for (int i = static_cast<int>(hashtable[query.ind].size()) - 1; i >= 0; --i)
                std::cout << hashtable[query.ind][i] << " ";
            std::cout << "\n";
        } else {
            size_t hashtable_bucket = hash_func(query.s);
            if (query.type == "find") {               
                vector<string>::iterator it = std::find(hashtable[hashtable_bucket].begin(), 
                                                        hashtable[hashtable_bucket].end(), 
                                                        query.s);
                writeSearchResult(it != hashtable[hashtable_bucket].end());
            } else if (query.type == "add") {                
                vector<string>::iterator it = std::find(hashtable[hashtable_bucket].begin(), 
                                                        hashtable[hashtable_bucket].end(), 
                                                        query.s);

                if (it == hashtable[hashtable_bucket].end())
                    hashtable[hashtable_bucket].push_back(query.s);
            } else if (query.type == "del") {                
                vector<string>::iterator it = std::find(hashtable[hashtable_bucket].begin(), 
                                                        hashtable[hashtable_bucket].end(), 
                                                        query.s);
                if (it != hashtable[hashtable_bucket].end())
                    hashtable[hashtable_bucket].erase(it);
            }
        }
    }

    void processQueries() {
        hashtable.resize(bucket_count);
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count; // m
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}

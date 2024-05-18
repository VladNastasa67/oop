#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
std::ifstream nameFileout;

struct Comparator {
    bool operator()(const pair<string, int>& a, const pair<string, int>& b) {
        if (a.second == b.second) {
            return a.first > b.first; 
        }
        return a.second < b.second; 
    }
};


int main()
{
    nameFileout.open("fraza.txt");
    std::string phrase;
    while (std::getline(nameFileout, phrase)) {
        std::cout << phrase << std::endl;
    }

    std::string separators = " ,?!.";


    int currentPos = 0;
    int real_word_pos;
    std::string currentString;

    std::map<std::string, int> word_map;
    while (phrase.size() != 0)
    {
        real_word_pos = phrase.find_first_not_of(separators);
        phrase = phrase.substr(real_word_pos, phrase.size());

        currentPos = phrase.find_first_of(separators);
        currentString = phrase.substr(0, currentPos);
        phrase = phrase.substr(currentPos + 1, phrase.size());

        std::transform(currentString.begin(), currentString.end(), currentString.begin(),
            [](unsigned char c) { return std::tolower(c); });
        word_map[currentString]++;
    }
    std::priority_queue<pair<string, int>, vector<pair<string, int>>, Comparator> pq;
    for (auto it : word_map)
    {
        cout << it.first <<':' << it.second << endl;
        pq.push(it);
    }
    cout << '\n';
    while (!pq.empty())
    {
        auto afis = pq.top();
        pq.pop();
        cout << afis.first <<"=>" << afis.second<<endl;
    }
    
    return 0;
}
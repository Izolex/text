#ifndef KMP_H
#define KMP_H

#include <string>
#include <vector>

namespace KMP {
    using namespace std;


    class Search {
        const string &needle;
        vector<int> backEdges;

    public:
        explicit Search(const string &needle): needle(needle)
        {
            backEdges = vector<int>(needle.length() + 1);
            createAutomaton();
        }

        vector<int> search(const string &haystack)
        {
            int state = 0;
            vector<int> founds;

            for (int i = 0; i < (int)haystack.length(); i++) {
                auto ch = haystack[i];
                state = step(ch, state);

                if (state == (int)needle.length()) {
                    founds.push_back(i - state + 1);
                    state = backEdges[state];
                }
            }

            return founds;
        }

    private:
        void createAutomaton()
        {
            int state = 0;
            backEdges[1] = 0;

            for (int i = 2; i <= (int)needle.length(); i++) {
                state = step(needle[i - 1], state);
                backEdges[i] = state;
            }

        }

        int step(const char character, int state)
        {
            while (needle[state] != character && state != 0) {
                state = backEdges[state];
            }

            if (needle[state] == character) {
                state++;
            }

            return state;
        }
    };
}

#endif

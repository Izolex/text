#ifndef BM_H
#define BM_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace BoyerMoore {
    using namespace std;


    typedef char Character;
    typedef struct {
        vector<int> N;
        vector<int> L;
        vector<int> l;
    } GoodSuffixTable;


    class Search {
        const string &needle;
        map<Character, int> badCharacter;
        map<Character, vector<int>> extendedBadCharacter;
        vector<int> horspool;
        GoodSuffixTable strongGoodSuffix;

    public:
        explicit Search(const string &needle): needle(needle)
        {
            badCharacter = Search::computeBadCharacter(needle);
            extendedBadCharacter = Search::computeExtendedBadCharacter(needle);
            horspool = Search::computeHorspool(needle);
            strongGoodSuffix = Search::computeStrongGoodSuffix(needle);
        }

        vector<int> search(const string &haystack)
        {
            vector<int> founds;
            int needleLength = (int)needle.length();
            int haystackLength = (int)haystack.length();
            int position = needleLength - 1;
            int galil = -1;

            while (position < haystackLength) {
                int i = needleLength - 1;
                int h = position;

                while (i >= 0 && h > galil && needle[i] == haystack[h]) {
                    i--, h--;
                }

                if (-1 == i || h == galil) {
                    founds.push_back(position);
                    position = position + needleLength - strongGoodSuffix.l[2];
                } else {
                    int bad = getExtendedBadCharacter(haystack[h], i);
                    int strong = strongGoodSuffix.L[i];
                    int shift = max(1, max(bad, strong));

                    if (shift >= i + 1) {
                        galil = position;
                    }
                    position += shift;
                }
            }

            return founds;
        }

    private:
        int getBadCharacter(const Character ch, const int i)
        {
            auto entry = badCharacter.find(ch);
            if (entry == badCharacter.end()) {
                return 0;
            }

            return i - entry->second;
        }

        int getExtendedBadCharacter(const Character ch, const int i)
        {
            auto entry = extendedBadCharacter.find(ch);
            if (entry == extendedBadCharacter.end()) {
                return 0;
            }

            int from = 0, to = (int)entry->second.size() - 1;

            while (from <= to) {
                int mid = (from + to) / 2;

                if (entry->second[mid] >= i) {
                    to = mid - 1;
                } else {
                    from = mid + 1;
                }
            }

            return from - 1 < 0 ? 0 : i - entry->second[from - 1];
        }


        static map<Character, int> computeBadCharacter(const string &text)
        {
            map<Character, int> table;
            for (int i = 0; i < (int)text.length(); i++) {
                table[text[i]] = i;
            }
            return table;
        }

        static map<Character, vector<int>> computeExtendedBadCharacter(const string &text)
        {
            map<Character, vector<int>> table;

            for (auto it = text.rbegin(); it != text.rend(); ++it) {
                auto idx = distance(begin(text), it.base()) - 1;
                auto entry = table.find(text[idx]);

                if (entry != table.end()) {
                    table.insert(make_pair(text[idx], vector<int>()));
                }

                table[text[idx]].push_back((int)idx);
            }
            return table;
        }

        static vector<int> computeHorspool(const string &text)
        {
            vector<int> table(256);
            auto n = (int)text.length();

            // ascii only
            for (int i = 0; i <= 255; i++) {
                table[i] = n;
            }
            for (int i = 0; i < n; i++) {
                char ch = text[i];
                table[ch] = n - 1 - i;
            }

            return table;
        }

        static GoodSuffixTable computeStrongGoodSuffix(const string &needle)
        {
            auto text = needle;
            reverse(text.begin(), text.end()); // :))

            vector<int> N = Search::computeZArray(text);

            reverse(text.begin(), text.end());
            reverse(N.begin(), N.end());

            return GoodSuffixTable{
                .N = N,
                .L = Search::computeBigL(text, N),
                .l = Search::computeSmallL(text, N),
            };
        }

        static vector<int> computeBigL(const string &text, const vector<int> N)
        {
            auto n = (int)text.length();
            vector<int> table(n+2);

            for (int j = 1; j < n - 1; j++) {
                int i = n - N[j] + 1;
                table[i] = j;
            }

            return table;
        }

        static vector<int> computeSmallL(const string &text, const vector<int> N)
        {
            auto n = (int)text.length();
            vector<int> table(n);

            for (int j = 1; j < n - 1; j++) {
                int i = 0;
                while (text[i] == text[n - N[j] + i]) {
                    i++;
                }
                table[j] = i;
            }
            return table;
        }

        static vector<int> computeZArray(const string &text)
        {
            auto length = (int)text.length();
            vector<int> Z(length);

            int L, R = 0;
            for (int i = 1; i < length; i++) {
                if (i > R) {
                    L = R = i;
                } else {
                    int K = i - L;

                    if (Z[K] < R - i + 1) {
                        Z[i] = Z[K];
                        continue;
                    } else {
                        L = i;
                    }
                }

                while (R < length && text[R-L] == text[R]) {
                    R++;
                }

                Z[i] = R-L;
                R--;
            }

            return Z;
        }
    };
}
#endif

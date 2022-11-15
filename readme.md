## Text algorithms

**WIP**

Implementation of few text search algorithms in [C++](https://en.wikipedia.org/wiki/C%2B%2B).
Contains simple unit tests build with [Google Test](https://en.wikipedia.org/wiki/Google_Test).

- [Knuth–Morris–Pratt algorithm](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm)
- [Ukkonen's algorithm](https://en.wikipedia.org/wiki/Ukkonen%27s_algorithm) for constructing [suffix tree](https://en.wikipedia.org/wiki/Suffix_tree) in linear time.
  Implemented by [white paper](https://www.cs.helsinki.fi/u/ukkonen/SuffixT1withFigs.pdf).
  See also algorithm [visualization](https://brenden.github.io/ukkonen-animation/), description in [plain english](https://stackoverflow.com/questions/9452701/ukkonens-suffix-tree-algorithm-in-plain-english) and [Gusfield's](https://www.cs.cornell.edu/courses/cs410/1999fa/Lectures/lec25.pdf) description.
- [Boyer-moore](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm) text search algorithm which uses extended bad character shift rule (uses [binary search](https://en.wikipedia.org/wiki/Binary_search_algorithm)), [Galil's rule](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm#The_Galil_rule) and [Z-Algorithm](https://www.geeksforgeeks.org/z-algorithm-linear-time-pattern-searching-algorithm/) for computing strong good suffix shift rule.
  Contains also bad character shift rule and [Horspool's](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore%E2%80%93Horspool_algorithm) heuristics (not used).
  It's inspired by [Algorithms on Strings, Trees, and Sequences](https://www.cambridge.org/core/books/algorithms-on-strings-trees-and-sequences/F0B095049C7E6EF5356F0A26686C20D3) book by Dan Gusfield, see [notes from book](https://web.cs.ucdavis.edu/~gusfield/cs224f09/bnotes.pdf) and algorithm [example](https://www.cs.utexas.edu/users/moore/best-ideas/string-searching/fstrpos-example.html).
- See also [Aho-Corasick algorithm](https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm) in [ac_dat repository](https://github.com/Izolex/ac_dat).

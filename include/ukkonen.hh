#ifndef UKKONEN_H
#define UKKONEN_H

#include <iostream>
#include <unordered_map>
#include <limits>
#include <vector>

namespace Ukkonen {
    using namespace std;

    typedef char Character;

    const char END_OF_TEXT = '\3';
    const int INF = numeric_limits<int>::max();


    class Node {
        typedef std::pair<int, int> substring; // start - end
        typedef std::pair<int, substring> mappedSubstring; // string id
        typedef std::pair<mappedSubstring, Node *> transition;
        typedef std::unordered_map<Character, transition> transitionMap;

        transitionMap transitions;
        Node *suffixLink = nullptr;

    public:
        Node() : transitions() {}

        void addTransition(Node *node, int needleId, int start, int end, Character transition) {
            auto interval = make_pair(start, end);
            auto idInterval = make_pair(needleId, interval);
            auto value = make_pair(idInterval, node);

            if (!hasTransition(transition)) {
                transitions.insert(make_pair(transition, value));
            } else {
                transitions[transition] = value;
            }
        }

        transition getTransition(Character transition) {
            return transitions.find(transition)->second;
        }

        bool hasTransition(Character transition) {
            return transitions.find(transition) != transitions.end();
        }

        transitionMap getTransitionMap() {
            return transitions;
        }


        void setSuffixLink(Node *link) {
            suffixLink = link;
        }

        Node *getSuffixLink() {
            return suffixLink;
        }
    };


    class SuffixTree {
        Node *root;
        vector<string> needles;

        Node *aux;
        int needleId = 0;


    public:
        SuffixTree() {
            root = new Node;
            aux = new Node;
            root->setSuffixLink(aux);
        }

        void addNeedle(const string &text) {
            string needle = text;
            needle.push_back(END_OF_TEXT);

            needleId = (int) needles.size();
            needles.push_back(needle);

            for (int i = 0; i <= (int) needle.length() - 1; i++) {
                aux->addTransition(root, needleId, i, i, needle[i]);
            }

            pair<Node *, int> pair = make_pair(root, 0);
            for (int i = 0; i <= (int) needle.length() - 1; i++) {
                pair = update(pair.first, pair.second, i);
                pair = canonize(pair.first, pair.second, i);

            }
        }

        void print() {
            cout << "root" << endl;
            printNode(root, 1);
        }

        Node *getRoot() {
            return root;
        }

    private:
        pair<Node *, int> update(Node *node, int start, int end) {
            Node *oldNode = root;
            Character transition = needles[needleId][end];

            auto canonicPair = make_pair(node, start);
            auto splitPair = testAndSplit(canonicPair.first, canonicPair.second, end - 1, transition);

            while (!splitPair.first) {
                splitPair.second->addTransition(new Node, needleId, end, INF, transition);

                if (oldNode != root) {
                    oldNode->setSuffixLink(splitPair.second);
                }

                oldNode = splitPair.second;

                canonicPair = canonize(canonicPair.first->getSuffixLink(), canonicPair.second, end - 1);
                splitPair = testAndSplit(canonicPair.first, canonicPair.second, end - 1, transition);
            }

            if (oldNode != root) {
                oldNode->setSuffixLink(canonicPair.first);
            }

            return canonicPair;
        }

        pair<Node *, int> canonize(Node *node, int start, int end) {
            if (end < start) {
                return make_pair(node, start);
            }

            auto tr = node->getTransition(needles[needleId][start]);

            while (tr.first.second.second - tr.first.second.first <= end - start) {
                int trStart = tr.first.second.first;
                int trEnd = tr.first.second.second;

                start = start + trEnd - trStart + 1;
                node = tr.second;

                if (start <= end) {
                    tr = node->getTransition(needles[needleId][start]);
                }
            }

            return make_pair(node, start);
        }

        pair<bool, Node *> testAndSplit(Node *node, int start, int end, Character transition) {
            if (start <= end) {
                auto tr = node->getTransition(needles[needleId][start]);

                int trStart = tr.first.second.first;
                int trEnd = tr.first.second.second;
                int newStart = trStart + end - start + 1;

                if (transition == needles[needleId][newStart]) {
                    return make_pair(true, node);
                } else {
                    Node *newNode = new Node;
                    node->addTransition(
                            newNode,
                            needleId,
                            trStart,
                            trStart + end - start,
                            needles[needleId][trStart]
                    );
                    newNode->addTransition(
                            tr.second,
                            needleId,
                            newStart,
                            trEnd,
                            needles[needleId][newStart]
                    );
                    return make_pair(false, newNode);
                }
            } else if (!node->hasTransition(transition)) {
                return make_pair(false, node);
            } else {
                return make_pair(true, node);
            }
        }

        void printNode(Node *node, int level) {
            for (const auto &[key, value]: node->getTransitionMap()) {
                int id = value.first.first,
                        start = value.first.second.first,
                        end = value.first.second.second;

                cout << std::string(level, ' ')
                     << "node: s: " << start
                     << " e: " << (end == INF ? 666 : end)
                     << " l: " << needles[id].length()
                     << " t :" << key
                     << " - ";
                for (int i = start; i < (end >= INF ? (int) needles[id].length() : end); i++) {
                    auto ch = needles[id][i];
                    cout << (ch == END_OF_TEXT ? '$' : ch);
                }
                cout << endl;

                printNode(value.second, level + 1);
            }
        }
    };
}

#endif

// ---DEPENDECIES---------------------------------------------------------------
#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <random>
#include <vector>

using namespace std;

// ---PROBLEM-------------------------------------------------------------------
// Text prediction system based on a dictionary of words and their frequencies.
// Given a prefix, output autocomplete suggestions sorted by frequency.

// ---INPUT---------------------------------------------------------------------
// User generated
// 1. 1st line contains an integer N denoting the number of words in the
//    dictionary.
// 2. Next N lines contain a word representing the user's word history.
std::tuple<std::map<std::string, int>> userInput() {
    std::map<std::string, int> dictionary;
    int N;
    std::cin >> N; // Read the number of words in the dictionary

    for (int i = 0; i < N; i++) {
        std::string word;
        std::cin >> word; // Read a word from the user's word history

        // Update the frequency of the word in the dictionary
        dictionary[word]++;
    }

    return std::make_tuple(dictionary);
}

// Randomly generated
// Vocabulary 
std::vector<std::string> vocabulary = {
    "apple",
    "appeal",
    "appetizer",
    "banana",
    "bandana",
    "bone",
    "cherry",
    "check",
    "date",
    "disaster",
    "elderberry",
    "fig",
    "grape",
    "honeydew",
    "ice cream",
};

// Function to generate a random word history: Uses a skewed distribution
std::vector<std::string> generateRandomWordHistory(int historyLength) {
    std::vector<std::string> history;
    std::random_device rd;
    std::mt19937 gen(rd());

    // Generate random weights for each word
    std::vector<double> weights(vocabulary.size());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double totalWeight = 0.0;
    for (int i = 0; i < vocabulary.size(); i++) {
        double weight = dist(gen);
        weights[i] = weight;
        totalWeight += weight;
    }
    for (int i = 0; i < vocabulary.size(); i++) {
        weights[i] /= totalWeight;
    }

    // Use a skewed distribution to generate the word history
    std::discrete_distribution<int> skewedDist(weights.begin(), weights.end());
    for (int i = 0; i < historyLength; i++) {
        int randomIndex = skewedDist(gen);
        history.push_back(vocabulary[randomIndex]);
    }

    return history;
}

std::tuple<std::map<std::string, int>> randomInput(int historyLength) {
    std::map<std::string, int> dictionary;
    std::vector<std::string> wordHistory = generateRandomWordHistory(historyLength);

    // Update the frequency of each word in the dictionary
    for (const std::string& word : wordHistory) {
        dictionary[word]++;
    }

    return std::make_tuple(dictionary);
}

// ---SOLUTION------------------------------------------------------------------
// reTRIEval tree data structure
class Trie {
    struct Node {
        std::map<char, Node*> children;
        bool isWord = false;
        int frequency = 0;
    };

    Node* root = new Node();

public:
    void insert(const std::string& word, int frequency) {
        Node* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new Node();
            }
            node = node->children[c];
        }
        node->isWord = true;
        node->frequency = frequency;
    }

    std::vector<std::pair<std::string, int>> getWords(const std::string& prefix) {
        std::vector<std::pair<std::string, int>> words;
        Node* node = root;
        for (char c : prefix) {
            if (node->children.find(c) == node->children.end()) {
                return words;
            }
            node = node->children[c];
        }
        getWordsHelper(node, prefix, words);
        return words;
    }

    // Autocomplete suggestions: takes a prefix and returns a list of words
    // sorted by frequency in descending order  


private:
    void getWordsHelper(Node* node, const std::string& prefix, std::vector<std::pair<std::string, int>>& words) {
        if (node->isWord) {
            words.push_back({ prefix, node->frequency });
        }
        for (auto& child : node->children) {
            getWordsHelper(child.second, prefix + child.first, words);
        }
    }
};

// ---MAIN----------------------------------------------------------------------
int main() {
    // Generate random input
    int N = 100;
    std::map<std::string, int> dictionary;
    std::tie(dictionary) = randomInput(N);

    // Print the dictionary
    std::cout << "Dictionary:" << std::endl;
    for (auto& word : dictionary) {
        std::cout << word.first << " " << word.second << std::endl;
    }
    cout << endl;

    // Build the trie
    Trie trie;
    for (auto& word : dictionary) {
        trie.insert(word.first, word.second);
    }

    // Get autocomplete suggestions
    std::string prefix = "app";
    std::vector<std::pair<std::string, int>> words = trie.getWords(prefix);

    // Sort the words by frequency in descending order
    std::sort(words.begin(), words.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second;
        });

    // Print only autocomplete suggestions not frequencies
    std::cout << "Autocomplete suggestions:" << std::endl;
    for (auto& word : words) {
        std::cout << word.first << std::endl;
    }
    return 0;
}

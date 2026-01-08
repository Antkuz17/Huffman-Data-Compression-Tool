#include <string>
#include <iostream>
#include <unordered_map>

int main () {
    std::cout << "Enter a sentence" << std::endl;

    // String holding our word
    std::string word;

    std::cin >> word;

    // Hashmap for counting the frequency of letters
    // Hashmaps are iterable in c++ so this is already fire
    std::unordered_map<char, int> counter;

    // We assume that we will have only generic charaters so no crazy odd characters
    for (char x : word) {
        counter[x]++;
    }
    for (const auto& pair : counter) {
    std::cout << pair.first << " " << pair.second << std::endl;
    }

    // Now we have all the frequency data in a hashmap


    //g++ main.cpp -o test.exe ; .\test.exe
    


    return 0;
}


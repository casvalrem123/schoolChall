#include <iostream>
#include <vector>
#include <map>

struct Node{
    int counter;
    char letter, lower, higher; 
    Node() : counter(1), letter(0), lower(0), higher(0) {}
}; 

int checkCounterTree(const std::string message){
    unsigned int singleChildCounter = 0; 
    std::vector<char>message_modified; 

//get letter in lowercase only 
    for(int i = 0; i < message.length(); i++){
        if (message[i] >= 97 && message[i] <= 122){
            message_modified.push_back(message[i]); 
        }
        if (message[i] >= 65 && message[i] <= 90){
            message_modified.push_back((char)(message[i] + 32)); 
        }
    }
    if(message.length() <= 1)
        return 0; 

    std::unordered_map<char, Node> keys; 
    for (char it : message_modified){
        keys[it].letter = it; 
    }

//for every char in modified string, make tree
    for(int i = 0; i < message_modified.size(); i++){
        Node iter; 
        iter.letter = message_modified[i]; 
        iter.counter++; 
        bool nodePut = false; 
        char k = message_modified[0]; 

        if(!i)
            nodePut = true; 
        
        while(!nodePut){
            if(iter.letter == keys[k].letter){
                keys[k].counter++;
                nodePut = true; 
            } else if (iter.letter < keys[k].letter){
                if (!keys[k].lower){
                    keys[k].lower = iter.letter; 
                    nodePut = true;
                } else {
                    k = keys[k].lower;  
                }
            } else {
                if (!keys[k].higher){
                    keys[k].higher = iter.letter; 
                    nodePut = true;
                } else {
                    k = keys[k].higher;  
                }
            }
            
        }
    }

//count for single node 
    for (auto& pair : keys) {
        if((pair.second.lower || pair.second.higher) && !(pair.second.lower && pair.second.higher)){
            singleChildCounter += pair.second.counter; 
        }
    }
    return singleChildCounter;
}

int main() {
    std::cout << checkCounterTree("the quick brown fox jumped over the lazy river") << std::endl; 
    return 0; 
}
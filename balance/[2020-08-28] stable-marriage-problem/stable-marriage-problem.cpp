// 28-08-2020

#include <iostream>
using namespace std;
#include <vector>
#include <queue>

#define SINGLE -1

/*!< The struct represents a man. It has a priority list and the index of the last woman in the priority list checked */
typedef struct person {
    int next_priority;
    vector<int> priority_list;
} PERSON;

/*
* Given a woman priority list, check if the new man or the fiance is the priority
* Return true if the new man is the priority
*/
bool prefers_new_man(const int number_of_marriages, const vector<int> woman_priority_list, const int new_man, const int fiance) {
    for(int i = 0; i < number_of_marriages; i++) {
        if(woman_priority_list[i] == new_man) 
            return true;
        if(woman_priority_list[i] == fiance) 
            return false;
    }
    return NULL; /*!< This case won't happen */
}

/*
* Print the final result incrementing in 1
*/
void print(const int number_of_marriages, const vector<int> marriages) {
    for(int i = 0; i < number_of_marriages; i++) printf("%d %d\n", i+1, marriages[i]+1);
}

void stable_matching_problem() {
    int number_of_marriages;
    int aux;
    cin >> number_of_marriages;

    /*!< The man represents the index and the value is the woman. Example: [0] = 3. Man 1 is marriaged with woman 4 */
    vector<int> marriage_men;
    /*!< The woman represents the index and the value is the man. Example: [0] = 3. Woman 1 is marriaged with man 4 */
    vector<int> marriage_woman; 
    
    /*!< Reading the women priority list */
    vector<vector<int>> women_priority;
    for(int i = 0; i < number_of_marriages; i++) {
        vector<int> priority_list;
        scanf("%*d "); /*!< The number of the person */
        for(int j = 0; j < number_of_marriages; j++) {
            cin >> aux;
            priority_list.push_back(aux - 1); /*!< The number that represents people are [number_of_people] - 1 */
        }
        women_priority.push_back(priority_list);
    }

    /*!< Reading men women priority list */
    vector<PERSON> men_priority;
    for(int i = 0; i < number_of_marriages; i++) {
        PERSON person;
        scanf("%*d "); /*!< The number of the person */
        for(int j = 0; j < number_of_marriages; j++) {
            cin >> aux;
            person.next_priority = 0;
            person.priority_list.push_back(aux - 1); /*!< The number that represents people are [number_of_people] - 1 */
        }
        men_priority.push_back(person);
    }

    /*!< A queue with all single man */
    queue<int> single_man;
    for(int i = 0; i < number_of_marriages; i++) {
        /*!< Initializing a queue that will keep track of the single man (the loop will iterate these men) */
        single_man.push(i); 
        /*!< Initializing all marriages as empty */
        marriage_men.push_back(SINGLE); marriage_woman.push_back(SINGLE);
    }

    while(!single_man.empty()) {
        int woman;
        int man = single_man.front(); 

        woman = men_priority[man].priority_list[men_priority[man].next_priority]; /*!< Getting the first priority not checked yet */
        men_priority[man].next_priority++; /*!< Incrementing the next_priority to the next priority that has to be checked */
        if(marriage_woman[woman] == SINGLE) {
            single_man.pop(); /*!< Removing the man from the single men list */
            marriage_men[man] = woman; /*!< Engage */
            marriage_woman[woman] = man; /*!< Engage */
        } else if(prefers_new_man(number_of_marriages, women_priority[woman], man, marriage_woman[woman])) {
            single_man.pop(); /*!< Removing the man from the single men list */
            single_man.push(marriage_woman[woman]); /*!< Adding the ex-fiance as single man */
            marriage_men[man] = woman; /*!< Engage */
            marriage_woman[woman] = man; /*!< Engage */
        }
    }

    print(number_of_marriages, marriage_men);
}

/*!< I defined that the count will start in 0, so the woman 1 is woman 0 in the program. The output will be incremented by 1. */
int main() {
    int number_of_test_cases;
    cin >> number_of_test_cases;
    for(int i = 0; i < number_of_test_cases; i++) stable_matching_problem();
    return 0;
}
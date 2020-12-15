/*!< UVA 10611 */
/*!< Divisao e Conquista */

#include <iostream>
using namespace std;
#include <vector>

void lunchu_band(const vector<int> heights_of_chimps, int goal, int left, int right) {
    if(left > right) {
        /*!< The taller of the lowers */
        if(right < 0)
            cout << "X" << " ";
        else
            cout << heights_of_chimps[right] << " ";

        /*!< The lower of the tallers */
        if(left >= (int) heights_of_chimps.size())
            cout << "X" << endl;
        else
            cout << heights_of_chimps[left] << endl;
    } else {
        int middle;
        middle = (left + right)/2;

        /*!< Find the height of the Lunchu Band */
        if(heights_of_chimps[middle] == goal) {
            /*!< The taller of the lowers */
            if(middle-1 < 0) 
                cout << "X" << " ";
            else
                cout << heights_of_chimps[middle-1] << " ";
            
            /*!< The lower of the tallers */
            if(middle+1 >= (int) heights_of_chimps.size())
                cout << "X" << endl;
            else
                cout << heights_of_chimps[middle+1] << endl;

            return;
        }
    
        /*!< Keep moving in the tree */
        if(heights_of_chimps[middle] < goal)
            lunchu_band(heights_of_chimps, goal, middle+1, right);
        else 
            lunchu_band(heights_of_chimps, goal, left, middle-1);
    }
}

int main(void) {
    vector<int> heights_of_chimps;
    int number_of_lady_chimps, number_of_queries;

    cin >> number_of_lady_chimps;
    int height_of_chimp;
    int index = 0;
    for(int i = 0; i < number_of_lady_chimps; i++) {
        cin >> height_of_chimp;
        /*!< Not accepting equals values */
        if(index-1 >= 0 && heights_of_chimps[index-1] == height_of_chimp) continue;
        heights_of_chimps.push_back(height_of_chimp);
        index++;
    }

    cin >> number_of_queries;
    int height_lunchu;
    for(int i = 0; i < number_of_queries; i++) {
        cin >> height_lunchu;
        lunchu_band(heights_of_chimps, height_lunchu, 0, ((int) heights_of_chimps.size())-1);
    }

    return 0;
}

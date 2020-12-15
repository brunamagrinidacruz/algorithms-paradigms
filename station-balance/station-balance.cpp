/*!< UVA 410 */

#include <iostream>
using namespace std;

#include <vector>
#include <map>

void merge(vector<int> *aVector, int size, int low, int middle, int high){
    int temp[size];
    for(int i = low; i <= high; i++){
        temp[i] = (*aVector)[i];
    }
    int i = low;
    int j = middle+1;
    int k = low;

    while (i <= middle && j <= high){
        if(temp[i] <= temp[j]){
            (*aVector)[k] = temp[i];
            ++i;
        }
        else {
            (*aVector)[k] = temp[j];
            ++j;
        }
        ++k;
    }
    while (i <= middle){
        (*aVector)[k] = temp[i];
        ++k;
        ++i;
    }
}

void merge_sort(vector<int> *aVector, int size, int low, int high){
    if (low < high){
        int middle = (low + high) / 2;
        merge_sort(aVector, size, low, middle);
        merge_sort(aVector, size, middle+1, high);
        merge(aVector, size, low, middle, high);
    }
}

void station_balance(const int set_number, const int chambers_amount, int specimens_amount) {
    vector<int> specimens_masses;
    double imbalance = 0, average_mass = 0;

    /*!< Reading the specimens massess */
    int specimen_mass;
    for(int i = 0; i < specimens_amount; i++) {
        cin >> specimen_mass;
        specimens_masses.push_back(specimen_mass);
        average_mass += specimen_mass; /*!< Sum of the all specimens masses */
    }

    /*!< It's better if we had 2*chambers_amount of specimens, so we are filling with 0  */
    for(int i = specimens_amount-1; i < 2*chambers_amount; i++) {
        specimens_masses.push_back(0);
    }     
    specimens_amount = 2*chambers_amount; /*!< Updating the amount of specimens */

    /*!< Sorting the specimens masses */
    merge_sort(&specimens_masses, specimens_amount, 0, specimens_amount-1);

    average_mass = average_mass/chambers_amount; /*!< "It is computed by dividing the sum of the masses of all specimens by the number of chambers" */

    int chamber_mass = 0;
    cout << "Set #" << set_number << endl;
    /*!< Getting the first and last, the second and anti penultimate, etc...*/
    for(int i = 0; i < specimens_amount/2; i++) {
        cout << " " << i << ":";
        /*!< If the mass is 0, it shoudn't be printed */
        if(specimens_masses[i] != 0) cout << " " << specimens_masses[i]; 
        if(specimens_masses[specimens_amount-i-1] != 0) cout << " " << specimens_masses[specimens_amount-i-1];
        chamber_mass = specimens_masses[i] + specimens_masses[specimens_amount-i-1]; /*!< "Summing the masses of the specimens assigned to chamber" */
        imbalance += chamber_mass - average_mass > 0 ? chamber_mass - average_mass : average_mass - chamber_mass;  /*!< Calculating the Imbalance */
        cout << endl;
    }

    printf("IMBALANCE = %.5f\n\n", imbalance);
}

int main(void) {
    int set_number = 0;
    int chambers_amount, specimens_amount;
    
    while(cin >> chambers_amount) {
        set_number++;
        cin >> specimens_amount;
        station_balance(set_number, chambers_amount, specimens_amount);
    }

    return 0;
}

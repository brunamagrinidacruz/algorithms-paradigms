//18-09-2020

#include <iostream>
using namespace std;

#include <vector>

void cd(vector<int> *final_path, int *final_sum, const int tape_minutes_long, const vector<int> durations_of_tracks, const int number_of_tracks, vector<int> current_path, int current_sum, int index) {
    current_path.push_back(durations_of_tracks[index]);
    current_sum += durations_of_tracks[index];

    if(current_sum > (*final_sum)) {
        (*final_sum) = current_sum;
        (*final_path) = current_path;
    }

    for(int i = index+1; i < number_of_tracks; i++) {
        if(current_sum + durations_of_tracks[i] <= tape_minutes_long) {
            cd(final_path, final_sum, tape_minutes_long, durations_of_tracks, number_of_tracks, current_path, current_sum, i);
        }
    }

}

int main(void) {
    int tape_minutes_long;
    while(cin >> tape_minutes_long) {
        vector<int> durations_of_tracks;

        vector<int> final_path;
        int final_sum = 0;

        int number_of_tracks;
        cin >> number_of_tracks;
        
        int duration_of_track;
        for(int i = 0; i < number_of_tracks; i++) {
            cin >> duration_of_track;
            durations_of_tracks.push_back(duration_of_track);
        }

        for(int i = 0; i < number_of_tracks; i++) {
            vector<int> current_path;
            cd(&final_path, &final_sum, tape_minutes_long, durations_of_tracks, number_of_tracks, current_path, 0, i);
        }

        for(int i = 0; i < (int) final_path.size(); i++) {
            cout << final_path[i] << " ";
        }
        cout << "sum:" << final_sum << endl;

    }

    return 0;
}
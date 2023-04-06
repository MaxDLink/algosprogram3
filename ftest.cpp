#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Define a struct to represent an applicant
struct Applicant {
    int id;             // unique identifier of the applicant
    float wpm;          // words per minute
    float ipm;          // improper words per minute
    bool eligible;      // whether the applicant is eligible or not
};

// Recursive function to find the best applicant
vector<Applicant> recursiveBestApplicant(const vector<Applicant>& applicants) {
    int n = applicants.size();
    if (n == 1) {
        // Base case: there is only one applicant
        return applicants;
    }
    else {
        // Recursive case: divide the applicants into two groups
        int mid = n / 2;
        vector<Applicant> left = recursiveBestApplicant(vector<Applicant>(applicants.begin(), applicants.begin() + mid));
        vector<Applicant> right = recursiveBestApplicant(vector<Applicant>(applicants.begin() + mid, applicants.end()));
        
        // Combine the results of the two sets
        // Find the best IPM in the left group
        float best_left_ipm = 0;
        if (!left.empty()) {
            best_left_ipm = left[0].ipm;
            for (int i = 1; i < left.size(); i++) {
                best_left_ipm = min(best_left_ipm, left[i].ipm);
            }
        }
        // Mark all applicants in the right group that are strictly better in both WPM and IPM
        for (int i = 0; i < right.size(); i++) {
            if (right[i].wpm > left.back().wpm && right[i].ipm < best_left_ipm) {
                right[i].eligible = true;
            }
        }
        // Merge the two groups and return the eligible candidates
        vector<Applicant> merged = left;
        merged.insert(merged.end(), right.begin(), right.end());
        vector<Applicant> eligible;
        for (int i = 0; i < merged.size(); i++) {
            if (merged[i].eligible) {
                eligible.push_back(merged[i]);
            }
        }
        return eligible;
    }
}

// Function to find the best applicant among a set of candidates
vector<int> BestApplicant(const vector<pair<float, float> >& applicants) {
    int n = applicants.size();
    // Convert the vector of pairs to a vector of Applicants
    vector<Applicant> apps(n);
    for (int i = 0; i < n; i++) {
        apps[i].id = i;
        apps[i].wpm = applicants[i].first;
        apps[i].ipm = applicants[i].second;
        apps[i].eligible = false;
    }
    // Run the recursive algorithm
    vector<Applicant> eligible = recursiveBestApplicant(apps);
    // Extract the IDs of the eligible candidates
    vector<int> result;
    for (int i = 0; i < eligible.size(); i++) {
        result.push_back(eligible[i].id);
    }
    return result;
}

int main() {
    int n;
    std::cout << "Enter the number of applicants: ";
    std::cin >> n;

    std::vector<std::pair<float, float> > applicants(n);
    for (int i = 0; i < n; i++) {
        float wpm, ipm;
        std::cout << "Enter the WPM and IPM of applicant " << i << ": ";
        std::cin >> wpm >> ipm;
        applicants[i] = std::make_pair(wpm, ipm);
    }

    std::vector<int> result = BestApplicant(applicants);

    if (result.empty()) {
        std::cout << "No eligible candidate found." << std::endl;
    } else {
        std::cout << "The following applicants are eligible:" << std::endl;
        for (int i = 0; i < result.size(); i++) {
            std::cout << "Applicant " << result[i] << std::endl;
        }
    }

    return 0;
}

/* 
input for eligible candidates: 

Enter the number of applicants: 3
Enter the WPM and IPM of applicant 0: 50 5
Enter the WPM and IPM of applicant 1: 60 4
Enter the WPM and IPM of applicant 2: 70 3
The following applicants are eligible:
Applicant 2

*/ 




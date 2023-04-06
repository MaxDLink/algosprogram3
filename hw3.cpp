#include <iostream>
#include <fstream>
#include <vector>

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

vector<int> BestApplicants(const vector<pair<float, float> >& applicants)
{
   vector<int> res;

   return res;
}


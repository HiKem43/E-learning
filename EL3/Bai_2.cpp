// File: Bai_2.cpp
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Job {
    int start; // a_i
    int end;   // b_i
};

bool compareJob(const Job& x, const Job& y) {
    if (x.end != y.end) return x.end < y.end;
    return x.start < y.start;
}

vector<Job> solveGreedy(vector<Job> jobs) {
    sort(jobs.begin(), jobs.end(), compareJob);

    vector<Job> selected;
    int lastEnd = -1;

    for (const Job& job : jobs) {
        if (job.start > job.end) continue;
        if (job.start >= lastEnd) {
            selected.push_back(job);
            lastEnd = job.end;
        }
    }
    return selected;
}

int main() {
    ifstream fin("input_B2.txt");
    if (!fin.is_open()) {
        cout << "Loi: Khong mo duoc input_B2.txt. Kiem tra xem file da ton tai chua \n";
        return 1;
    }

    int n;
    if (!(fin >> n) || n <= 0) {
        cout << "Loi: Gia tri n trong input_B2.txt khong hop le.\n";
        return 1;
    }

    vector<Job> jobs;
    jobs.reserve(n);
    int a, b;
    for (int i = 0; i < n && (fin >> a >> b); i++) {
        jobs.push_back({a, b});
    }
    fin.close();

    vector<Job> selected = solveGreedy(jobs);

    ofstream fout("output_B2.txt");
    if (!fout.is_open()) {
        cout << "Loi: Khong ghi duoc file output_B2.txt.\n";
        return 1;
    }

    // Ghi 1 so nguyen duy nhat theo dung yeu cau de bai
    fout << selected.size() << '\n';
    fout.close();

    // In ra man hinh de tien kiem tra nhanh
    cout << "Da ghi ket qua vao output_B2.txt: " << selected.size() << '\n';
    cout << "Cac cong viec duoc chon:";
    for (const Job& j : selected) {
        cout << " [" << j.start << ", " << j.end << "]";
    }
    cout << '\n';

    return 0;
}
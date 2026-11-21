#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Job {
    int start; // Thoi diem bat dau cong viec.
    int end;   // Thoi diem ket thuc cong viec.
};

// Sap xep theo thoi diem ket thuc tang dan; neu bang nhau, uu tien bat dau som.
bool compareJob(const Job& x, const Job& y) {
    if (x.end != y.end) return x.end < y.end;
    return x.start < y.start;
}

vector<Job> solveGreedy(vector<Job> jobs) {
    // Chon cong viec ket thuc som nhat truoc de con nhieu thoi gian cho viec tiep theo.
    sort(jobs.begin(), jobs.end(), compareJob);

    vector<Job> selected;
    int lastEnd = 0;
    bool hasSelected = false;

    for (const Job& job : jobs) {
        // Duoc phep chon cong viec bat dau dung luc cong viec truoc ket thuc.
        if (!hasSelected || job.start >= lastEnd) {
            selected.push_back(job);
            lastEnd = job.end;
            hasSelected = true;
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

    // input_B2.txt gom so luong cong viec n, sau do la n cap (thoi diem bat dau, ket thuc).
    int n;
    if (!(fin >> n) || n < 0) {
        cout << "Loi: Gia tri n trong input_B2.txt khong hop le.\n";
        return 1;
    }

    vector<Job> jobs;
    jobs.reserve(n);
    int a, b;
    // Doc du n cap thoi gian va tu choi khoang co start > end.
    for (int i = 0; i < n; i++) {
        if (!(fin >> a >> b)) {
            cout << "Loi: Thieu du lieu cong viec trong input_B2.txt.\n";
            return 1;
        }
        if (a > b) {
            cout << "Loi: Thoi gian cong viec trong input_B2.txt khong hop le.\n";
            return 1;
        }
        jobs.push_back({a, b});
    }
    fin.close();

    // Ap dung tham lam va nhan danh sach cac cong viec duoc chon.
    vector<Job> selected = solveGreedy(jobs);

    ofstream fout("output_B2.txt");
    if (!fout.is_open()) {
        cout << "Loi: Khong ghi duoc file output_B2.txt.\n";
        return 1;
    }

    // File output chi ghi so luong cong viec, theo dinh dang de bai.
    fout << selected.size() << '\n';
    fout.close();

    // In them danh sach cong viec duoc chon de de kiem tra ket qua.
    cout << "Da ghi ket qua vao output_B2.txt: " << selected.size() << '\n';
    cout << "Cac cong viec duoc chon:";
    for (const Job& j : selected) {
        cout << " [" << j.start << ", " << j.end << "]";
    }
    cout << '\n';

    return 0;
}
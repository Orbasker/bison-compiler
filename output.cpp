#include <iostream>
#include <set>
#include <string>
#include <algorithm>

std::set<int> intersection(const std::set<int>& a, const std::set<int>& b) {
    std::set<int> result;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));
    return result;
}

std::set<int> union_sets(const std::set<int>& a, const std::set<int>& b) {
    std::set<int> result = a;
    result.insert(b.begin(), b.end());
    return result;
}

std::set<std::string> intersection(const std::set<std::string>& a, const std::set<std::string>& b) {
    std::set<std::string> result;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));
    return result;
}

std::set<std::string> union_sets(const std::set<std::string>& a, const std::set<std::string>& b) {
    std::set<std::string> result = a;
    result.insert(b.begin(), b.end());
    return result;
}

std::ostream& operator<<(std::ostream& os, const std::set<std::string>& set) { os << "{"; for (auto it = set.begin(); it != set.end(); ++it) { if (it != set.begin()) os << ", "; os << *it; } os << "}"; return os; }
int main() {
int CPP_grd;
;
CPP_grd = 90;
std::cout << "alright" << std::endl;
if ((CPP_grd >= 90)) {
}
    return 0;
}

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
std::set<std::string> CPP_highTech,CPP_gaming;
;
std::set<std::string> CPP_software,CPP_hardware,CPP_industrial;
;
CPP_highTech.insert({"Apple", "Google", "Microsoft", "Nvidia", "Adobe", "Oracle", "Sap"});
CPP_highTech.insert({"PayPal", "Nice", "Amdocs", "OpenAI", "Ford", "Mercedes"});
CPP_gaming.insert({"Sony", "Apple", "Microsoft", "Google", "Nintendo", "Playtika"});
CPP_software.insert({"Apple", "Microsoft", "Oracle", "Google", "Sap", "PayPal", "Playtika", "Amdocs", "OpenAI"});
CPP_hardware.insert({"Apple", "Nice", "Sony", "Google", "Cummins", "Nucor", "Microsoft", "Nvidia"});
CPP_industrial.insert({"Caterpillar", "Cummins", "Nucor"});
std::cout << "Companies that sell hardware & software:" << intersection(CPP_software, CPP_hardware) << std::endl;
std::set<std::string> CPP_highSW;
;
CPP_highSW = intersection(CPP_software, CPP_highTech);
if ((CPP_highSW == CPP_software)) {
std::cout << "All software companies are high-tech companies:" << CPP_highSW << std::endl;
} else {
std::cout << "Not all software companies are high-tech companies:" << CPP_highSW << std::endl;
}
CPP_highSW.insert("Playtika");
if ((CPP_highSW == CPP_software)) {
std::cout << "Now all software companies are high-tech companies:" << CPP_highSW << std::endl;
} else {
std::cout << "Not all software companies are high-tech companies:" << CPP_highSW << std::endl;
}
std::cout << "Companies that do software or hardware:" << union_sets(CPP_software ,  CPP_hardware) << std::endl;
std::cout << "Companies that sell Hardware but not Gaming Software:" << intersection(CPP_hardware, (intersection(CPP_software, CPP_gaming))) << std::endl;
    return 0;
}

#include <iostream>
#include <set>
#include <string>
#include <algorithm>

std::set<int> intersection(const std::set<int> &a, const std::set<int> &b)
{
    std::set<int> result;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));
    return result;
}

std::set<int> union_sets(const std::set<int> &a, const std::set<int> &b)
{
    std::set<int> result = a;
    result.insert(b.begin(), b.end());
    return result;
}

std::set<std::string> intersection(const std::set<std::string> &a, const std::set<std::string> &b)
{
    std::set<std::string> result;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));
    return result;
}

std::set<std::string> union_sets(const std::set<std::string> &a, const std::set<std::string> &b)
{
    std::set<std::string> result = a;
    result.insert(b.begin(), b.end());
    return result;
}

template <typename T>
std::set<T> set_difference(const std::set<T> &a, const std::set<T> &b)
{
    std::set<T> result;
    std::set_difference(a.begin(), a.end(), b.begin(), b.end(),
                        std::inserter(result, result.begin()));
    return result;
}

std::ostream &operator<<(std::ostream &os, const std::set<std::string> &set)
{
    os << "{";
    for (auto it = set.begin(); it != set.end(); ++it)
    {
        if (it != set.begin())
            os << ", ";
        os << *it;
    }
    os << "}";
    return os;
}
int main()
{
    std::set<std::string> CPP_class, CPP_highGradeStudents, CPP_lowGradeStudents, CPP_avgGradeStudents;
    ;
    std::set<int> CPP_grades, CPP_gradesHigh;
    ;
    int CPP_grd;
    CPP_class.insert({"Rafi_Suisa", "Tamar_Even", "Avi_Maoz", "Eli_Kamer", "Shlomit_Raz", "Haim_Mizrachi", "Moshe_Samocha", "Tali_Raban", "Sharon_Tal", "Gal_Elbaz"});
    CPP_gradesHigh.insert({});
    CPP_highGradeStudents.insert({});
    for (const auto &CPP_student : CPP_class)
    {
        std::cout << "Grade for:" << CPP_student << std::endl;
        std::cout << ">";
        std::cin >> CPP_grd;
        CPP_grades.insert(CPP_grades.begin(), CPP_grades.end());
        if ((CPP_grd >= 90))
        {
            CPP_gradesHigh.insert(CPP_gradesHigh.begin(), CPP_gradesHigh.end());
            CPP_highGradeStudents.insert(CPP_highGradeStudents.begin(), CPP_highGradeStudents.end());
        }
    }
    if (&CPP_gradesHigh)
    {
        std::cout << "Number of top grades:" << CPP_gradesHigh.size() << std::endl;
        std::cout << "Top Grades are:";
        for (const auto &element : CPP_gradesHigh)
        {
            std::cout << " " << element;
        }
        std::cout << std::endl;
        std::cout << "High Grade Students are:";
        for (const auto &element : CPP_highGradeStudents)
        {
            std::cout << " " << element;
        }
        std::cout << std::endl;
    }
    for (const auto &CPP_student : CPP_lowGradeStudents)
    {
        std::cout << "Get better next time:" << CPP_student << std::endl;
    }
    std::cout << "Students with good grades:";
    for (const auto &element : CPP_avgGradeStudents)
    {
        std::cout << " " << element;
    }
    std::cout << std::endl;
    return 0;
}

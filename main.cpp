#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using filesystem::path;

path operator""_p(const char* data, std::size_t sz) {
    return path(data, data + sz);
}

// напишите эту функцию
void PrintTree(ostream& dst, const path& p) {


    dst << p.filename().string() << endl;

    vector<vector<std::filesystem::directory_entry>> result;
    vector<std::filesystem::directory_entry> result_latter;
    int i = 0;
    for (auto entry : std::filesystem::directory_iterator(p)) {
        result.resize(result.size() + 1);
        for (auto ent : std::filesystem::directory_iterator(entry)) {
            result[i].push_back(ent);
        }
        result_latter.push_back(entry);
        ++i;
    }



    for (int a = result_latter.size() - 1; a >= 0; a--) {
        dst << "  " << result_latter[a].path().filename().string() << endl;
        for (int x = result.size() - 1; x >= 0; x--) {
            for (int k = result[x].size() - 1; k >= 0; k--) {
                dst << "    " << result[x][k].path().filename().string() << endl;
            }
            if (a > 0) {
                --a;
                dst << "  " << result_latter[a].path().filename().string() << endl;
            }
        }
    }
}

int main() {
    error_code err;
    filesystem::remove_all("test_dir", err);
    filesystem::create_directories("test_dir"_p / "a"_p, err);
    filesystem::create_directories("test_dir"_p / "b"_p, err);

    ofstream("test_dir"_p / "b"_p / "f1.txt"_p);
    ofstream("test_dir"_p / "b"_p / "f2.txt"_p);
    ofstream("test_dir"_p / "a"_p / "f3.txt"_p);

    ostringstream out;
    PrintTree(out, "test_dir"_p);
    assert(out.str() ==
        "test_dir\n"
        "  b\n"
        "    f2.txt\n"
        "    f1.txt\n"
        "  a\n"
        "    f3.txt\n"s
    );
}
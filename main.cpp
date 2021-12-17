#include <cassert>
#include <QApplication>
#include "HashSet.h"
#include "mainwindow.h"
#include "HashSet.cpp"

int main(int argc, char **argv) {
    HashSet<int, std::hash<int>> hash_set(10);
    HashSet<int, std::hash<int>> hs1{};
    hash_set << 1 << 2 << 3;
    assert(hash_set.size() == 3);
    hash_set << 3;
    assert(hash_set.size() == 3);
    hash_set << 4;
    assert(hash_set.size() == 4);
    hash_set.erase(4);
    assert(hash_set.size() == 3);
    hash_set.erase(4);
    assert(hash_set.size() == 3);
    HashSet<int, std::hash<int>> other(10);
    other  << 1 << 2 << 3;
    assert(hash_set == other);
    other << 4;
    assert(hash_set != other);

    hash_set.save("output");
    hash_set.clear();
    assert(hs1.size() == 0);
    assert(hash_set == hs1);
    assert(hash_set.size() == 0);

    hash_set.load("output");
    assert(hash_set.size() == 3);

    hash_set << (3);
    hash_set << (4);
    assert(hash_set[3]);
    assert(hash_set[4]);
    assert(!hash_set[5]);
    hash_set.erase(3);
    assert(!hash_set[3]);
    assert(hash_set[4]);
    assert(!hash_set[5]);
    hash_set << (3);
    hash_set << (5);
    assert(hash_set[3]);
    assert(hash_set[4]);
    assert(hash_set[5]);
    hash_set.erase(5);
    assert(!hash_set[5]);


    printf("Success");
    QApplication app(argc, argv);
    MainWindow win;
    win.show();
    return app.exec();
}

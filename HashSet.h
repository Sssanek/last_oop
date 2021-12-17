#ifndef HASHSET_H
#define HASHSET_H

#include <algorithm>
#include <forward_list>
#include <iterator>
#include <vector>
#include <fstream>


template <typename Type, typename Hasher = std::hash<Type>>
class HashSet {
public:
    friend class MainWindow;
    //конструктор по умолчанию
    HashSet() = default;

    explicit HashSet(size_t num_buckets);

    explicit HashSet(size_t num_buckets, const Hasher& hasher);

    //конструктор копирования
    HashSet(const HashSet& other_) = default;

    HashSet(HashSet&& other_) noexcept = default;

    HashSet& operator=(const HashSet& other_) = default;

    HashSet& operator=(HashSet&& other_) noexcept = default;

    //деструктор
    ~HashSet() = default;

    //метод, удаляющий все хранящиеся значения из коллекции
    void clear();

    //метод, возвращающий количество хранящихся в коллекции значений
    size_t size() const;

    bool empty();

    //метод, принимающий путь к файлу и сохраняющий в него содержимое коллекции
    void save(const std::string &filename) const;

    //метод, принимающий путь к файлу и загружающий из него содержимое коллекции
    void load(const std::string &filename);

    //оператор ==, принимающий другую коллекцию и возвращающий истину, если
    // обе коллекции хранят одинаковые значения T
    // (или пары ключ-значение K, V) и ложь в противном случае
    bool operator==(const HashSet& rhs) const;

    bool operator!=(const HashSet& rhs) const;

    //оператор <<, добавляющий в коллекцию заданное значение T
    HashSet& operator<<(const Type& value);

    HashSet& operator<<(Type&& value);

    //метод, удаляющий из коллекции заданное значение T при его наличии
    void erase(const Type& value);

    //оператор [], принимающий значение T и возвращающий
    // при наличии значения в коллекции истину,
    // а при отсутствии – ложь
    bool operator[](const Type& value) const;

    //оператор &&, принимающий другую коллекцию и возвращающий
    // все общие значения T в виде новой коллекции
    HashSet operator&&(HashSet rhs) const;

    const std::forward_list<Type>& getBucket(const Type& value) const;

private:
    size_t getBucketIndex(const Type& value) const;

    Hasher hasher_;
    std::vector<std::forward_list<Type>> buckets_{1000};
    size_t size_{0};
};


#endif // HASHSET_H

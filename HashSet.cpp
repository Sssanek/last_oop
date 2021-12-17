#include <HashSet.h>
#include <list>
#include <functional>
#include <string>
#include <fstream>
#include <iostream>


struct IntHasher {
    size_t operator()(int value) const {
        return value;
    }
};

template <typename Type, typename Hasher>
HashSet<Type, Hasher>::HashSet(size_t num_buckets, const Hasher& hasher)
                                    : hasher_(hasher)
                                    , buckets_(num_buckets) { }

template <typename Type, typename Hasher>
HashSet<Type, Hasher>::HashSet(size_t num_buckets)
                                    : buckets_(num_buckets) { }

template<typename Type, typename Hasher>
HashSet<Type, Hasher> HashSet<Type, Hasher>::operator&&(const HashSet rhs)
const {
    HashSet<Type, Hasher> new_;
    for (int i=0; i<1000; i++){
        const auto& bucket = buckets_[i];
        for (Type value : bucket) {
            if (rhs[value])
                new_ << value;
        }
    }
    return new_;
}

template <typename Type, typename Hasher>
void HashSet<Type, Hasher>::erase(const Type& value) {
    if (!((*this)[value]))
        return;
    buckets_[getBucketIndex(value)].remove(value);
    --size_;
}

template<typename Type, typename Hasher>
bool HashSet<Type, Hasher>::operator[](const Type &value) const {
    const auto& bucket = getBucket(value);
    return find(begin(bucket), end(bucket), value) != bucket.end();
}

template <typename Type, typename Hasher>
const std::forward_list<Type>& HashSet<Type, Hasher>::
        getBucket(const Type& value) const {
    return buckets_[getBucketIndex(value)];
}

template <typename Type, typename Hasher>
size_t HashSet<Type, Hasher>::getBucketIndex(const Type& value) const {
    return hasher_(value) % buckets_.size();
}

template <typename Type, typename Hasher>
void HashSet<Type, Hasher>::clear() {
    size_t num_buckets = buckets_.size();
    buckets_.clear();
    buckets_.resize(num_buckets);
    size_ = 0;
}

template<typename Type, typename Hasher>
bool HashSet<Type, Hasher>::empty() {
    return (size_ == 0);
}

template <typename Type, typename Hasher>
size_t HashSet<Type, Hasher>::size() const {
    return size_;
}

template <typename Type, typename Hasher>
bool HashSet<Type, Hasher>::operator==(const HashSet& rhs) const {
    if (rhs.size() == 0 && size() == 0)
        return true;
    if (buckets_.size() != rhs.buckets_.size() || size_ != rhs.size_) {
        return false;
    }
    for (auto it_l = buckets_.begin(), it_r = rhs.buckets_.begin();
         it_l != buckets_.end() && it_r != rhs.buckets_.end();
         ++it_l, ++it_r) {
        if (!std::is_permutation(it_l->begin(), it_l->end(), it_r->begin())) {
            return false;
        }
    }
    return true;
}

template <typename Type, typename Hasher>
bool HashSet<Type, Hasher>::operator!=(const HashSet& rhs) const {
    return !operator==(rhs);
}

template<typename Type, typename Hasher>
HashSet<Type, Hasher>& HashSet<Type, Hasher>::operator<<(const Type& value) {
    auto& bucket = buckets_[getBucketIndex(value)];

    if (!(*this)[value]) {
        bucket.emplace_front(value);
        ++size_;
    }
    return *this;
}

template<typename Type, typename Hasher>
HashSet<Type, Hasher>& HashSet<Type, Hasher>::operator<<(Type&& value) {
    auto& bucket = buckets_[getBucketIndex(value)];

    if (!(*this)[value]) {
        bucket.emplace_front(std::move(value));
        ++size_;
    }
    return *this;
}

template <typename Type, typename Hasher>
void HashSet<Type, Hasher>::save(const std::string& filename) const {
    std::ofstream os;
    os.open(filename);
    for (const auto& bucket : buckets_) {
        for (const auto& elem : bucket) {
            os << elem << "\n";
        }
    }
    os.close();
}

template <typename Type, typename Hasher>
void HashSet<Type, Hasher>::load(const std::string& filename) {
    clear();
    std::ifstream is;
    is.open(filename);
    if (!is.is_open()) {
        throw std::runtime_error("File doesn't exists.");
    }
    Type new_value;
    while (is >> new_value) {
        operator<<(new_value);
    }
    is.close();
}

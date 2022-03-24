#ifndef KVPAIR_H
#define KVPAIR_H

#include <ostream>

using std::ostream;

template<typename K,typename V>
class KVPair {
public:
    K key;
    V value;

    KVPair() {}

    KVPair(K key) {
        this->key = key;
    }

    KVPair(K key, V value) {
        this->key = key;
        this->value = value;
    }

    void operator=(const KVPair& other) {
        this->key = other.key;
        this->value = other.value;
    }
    
    bool operator==(const KVPair& other) {
        return this->key == other.key;
    }

    bool operator!=(const KVPair& other) {
        return this->key != other.key;
    }

    bool operator<(const KVPair& other) {
        return this->key < other.key;
    }

    bool operator<=(const KVPair& other) {
        return this->key <= other.key;
    }

    bool operator>(const KVPair& other) {
        return this->key > other.key;
    }

    bool operator>=(const KVPair& other) {
        return this->key >= other.key;
    }

    
};

template<typename K,typename V>
ostream& operator<<(ostream& os, const KVPair<K,V> &p) {
        os << p.key << " : " << p.value;
        return os;
    }

#endif // KVPAIR_H

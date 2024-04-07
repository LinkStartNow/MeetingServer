#ifndef MYMAP_H
#define MYMAP_H

#include <unordered_map>
#include <mutex>

using namespace std;


// 线程安全的map
template<class K, class V>
class MyMap
{
    unordered_map<K, V*> m_map;
    mutex m_mutex;
public:
    MyMap() = default;

    ~MyMap()
    {
        unique_lock<mutex> lck(m_mutex);
        for (auto x: m_map) {
            delete x.second;
        }
        m_map.clear();
    }

    void AddValue(K key, V&& value)
    {
        unique_lock<mutex> lck(m_mutex);
        if (m_map.count(key)) {
            delete m_map[key];
        }
        m_map[key] = new V(value);
    }

    void Erase(K key)
    {
        unique_lock<mutex> lck(m_mutex);
        delete m_map[key];
        m_map.erase(key);
    }

    bool Count(K key)
    {
        unique_lock<mutex> lck(m_mutex);
        return m_map.count(key);
    }

    V& GetVal(K key)
    {
        unique_lock<mutex> lck(m_mutex);
        return *(m_map[key]);
    }
};

#endif // MYMAP_H

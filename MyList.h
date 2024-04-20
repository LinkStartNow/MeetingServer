#ifndef MYLIST_H
#define MYLIST_H

#include <list>
#include <mutex>
#include <vector>

using namespace std;

template<typename T>
class MyList
{
    list<T> m_list;
    mutex m_mtx;

public:
    vector<T> GetAll()
    {
        vector<T> res;
        for (auto x: m_list) res.emplace_back(x);
        return res;
    }

    void emplace_back(T& v)
    {
        unique_lock<mutex> lck(m_mtx);
        m_list.emplace_back(v);
    }

    bool count(T v)
    {
        unique_lock<mutex> lck(m_mtx);
        for (auto x: m_list) if (x == v) return true;
        return false;
    }

    void erase(T v)
    {
        unique_lock<mutex> lck(m_mtx);
        for (auto it = m_list.begin(); it != m_list.end(); ++it) {
            if (*it == v) {
                m_list.erase(it);
                break;
            }
        }
    }
};

#endif // MYLIST_H

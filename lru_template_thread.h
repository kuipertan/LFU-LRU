#ifndef _LRU_CACHE_H_
#define _LRU_CACHE_H_

#include <stdint.h>
#include <map>
#include <list>
#include <pthread.h>

template <class K, class T>
class LRUCache {

public:
    typedef typename std::list<K>::iterator lru_iterator;
    

    LRUCache(int32_t capacity) {
        cap_ = capacity;
        pthread_mutex_init(&the_mutex_, 0);
    }

    T get(K& key) {
        if (m1_.find(key) == m1_.end()){
            return T();
        }
        else{
            use(key);
            return m1_[key].first;
        }
    }

    void put(K& key, T value){
        if (cap_ <= 0){
            return;
        }
         
        if (m1_.find(key) != m1_.end()){//just change the value
            m1_[key].first = value;
            use(key);
            return;
        }
        else{
            pthread_mutex_lock(&the_mutex_);
            if (m1_.size() == cap_){
                m1_.erase(used_.back());
                used_.pop_back();
            }
            used_.push_front(key);
            //m1[key]={value,used.begin()};
            lru_iterator it = used_.begin();
            std::pair<T, lru_iterator> v(value, it);
            m1_.insert(std::pair<K, std::pair<T, lru_iterator> >(key, v));
            pthread_mutex_unlock(&the_mutex_);
        }
    }
    
    void use(K& key){
        pthread_mutex_lock(&the_mutex_);
        used_.erase(m1_.find(key)->second.second);
        used_.push_front(key);
        m1_.find(key)->second.second = used_.begin();
        pthread_mutex_unlock(&the_mutex_);
    }

    void clear(){
        pthread_mutex_lock(&the_mutex_);
        used_.clear();
        m1_.clear();
        pthread_mutex_unlock(&the_mutex_);
    }

private:
    int32_t cap_;
    std::map<K, std::pair<T, lru_iterator> > m1_;
    std::list<K> used_;
    pthread_mutex_t the_mutex_;
    
};

#endif

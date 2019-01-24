# LFU-LRU
Leetcode 460. LFU Cache 146. LRU Cache
## lru.h
lru是fork来的，该实现是key为字符串，值为int的缓存类型，一个样例。语法基于c++11特性，且没有线程安全
## lru_template_thread.h
基于lru.h修改过来的，模板实现，且兼容c++11之前版本的g++编译器，以及线程安全


class LRUCache {
	int cap = 0;
	std::unordered_map<int, std::pair<int,std::list<int>::iterator>> m1;//<key,pair<value, position in the list>>
	std::list<int> used;
public:
	LRUCache(int capacity) 
	{
	    cap = capacity;
	}

	int get(int key) 
	{
		if (m1.find(key) == m1.end())
		{
			return -1;
		}
		else
		{
			use(key);
			return m1[key].first;
		}
	}

	void put(int key, int value)
	{
		if (cap <= 0)
		{
			return;
		}
		 
		if (m1.find(key) != m1.end())//just change the value
		{
			m1[key].first = value;
			use(key);
			return;
		}
		else
		{
			if (m1.size() == cap)
			{
				m1.erase(used.back());//first in first out
				used.pop_back();
			}
			used.push_front(key);
			m1[key]={value,used.begin()};

		}
	}
	
	void use(int key)//change the list of used( the key is already in the map)
	{
		used.erase(m1.find(key)->second.second);
		used.push_front(key);
		m1.find(key)->second.second=used.begin();
	}
	
};

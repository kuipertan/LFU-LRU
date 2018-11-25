class LFUCache {
	int cap = 0;
	int minfreq = 0;
	std::unordered_map<int, std::pair<int,int>> m1;//key to <value,freq>
	std::unordered_map<int,std::list<int>> m2;//freq to a list of keys
	std::unordered_map<int, std::list<int>::iterator>m3;//key to its position in the list
public:
	LFUCache(int capacity) 
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
			m2[m1[key].second].erase(m3[key]);//remove the key from the list which it's origin freq points to
			m1[key].second++;//freq++
			m2[m1[key].second].push_back(key);//into a new list
			m3[key] = --m2[m1[key].second].end();//record new position
			if (m2[minfreq].size() == 0)
			{
				minfreq++;
			}
			return m1[key].first;
		}
	}

	void put(int key, int value)
	{
		if (cap <= 0)
		{
			return;
		}
		 
		if (get(key) !=-1)//just change the value
		{
			m1[key].first = value;
			return;
		}
		else
		{
			if (m1.size() == cap)
			{
				m1.erase(m2[minfreq].front());//pop the first one in the list of minfreq(first in first out)
				m3.erase(m2[minfreq].front());
				m2[minfreq].pop_front();
			}
			m1[key] = { value,1 };
			m2[1].push_back(key);
			m3[key] = --m2[1].end();//record the position
			minfreq = 1;

		}
	}
};
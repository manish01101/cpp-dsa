class Node {
public:
	int key, val;
	Node* prev;
	Node* next;
	Node(int key, int val) : key(key), val(val), prev(nullptr), next(nullptr) { }
};
class LRUCache {
	int capacity;
	unordered_map<int, Node*> mp;
	Node* head = nullptr;
	Node* tail = nullptr;

	void insertFront(Node* node) {
		node->next = head;
		if (head) {
			head->prev = node;
		}
		head = node;
		if (!tail) {
			tail = head;
		}
	}

	void removeNode(Node* temp) {
		Node* prevNode = temp->prev;
		Node* nextNode = temp->next;
		if (prevNode) {
			prevNode->next = nextNode;
		}
		if (nextNode) {
			nextNode->prev = prevNode;
		}
		if (temp == head) {
			head = nextNode;
		}
		if (temp == tail) {
			tail = prevNode;
		}
		temp->prev = nullptr;
		temp->next = nullptr;
	}
public:
	LRUCache(int capacity) {
		this->capacity = capacity;
	}

	int get(int key) {
		// if present -> return val
		if (mp.find(key) != mp.end()) {
			Node* temp = mp[key];
			removeNode(temp);
			insertFront(temp);
			return temp->val;
		}
		return -1;
	}

	void put(int key, int value) {
		// key is present
		if (mp.find(key) != mp.end()) {
			Node* temp = mp[key];
			temp->val = value;
			removeNode(temp);
			insertFront(temp);
		}
		// key is not present
		else {
			// check capacity is available
			if (mp.size() < capacity) {
				Node* newNode = new Node(key, value);
				insertFront(newNode);
				mp[key] = newNode;
			}
			// capacity not available
			else {
				// remove tail
				mp.erase(tail->key);
				Node* temp = tail;
				removeNode(temp);
				delete temp;

				// then insert new node
				Node* newNode = new Node(key, value);
				insertFront(newNode);
				mp[key] = newNode;
			}
		}
	}
	~LRUCache() {
		Node* curr = head;
		while (curr) {
			Node* next = curr->next;
			delete curr;
			curr = next;
		}
	}
};




// using stl
class LRUCache {
private:
	int capacity;
	list<pair<int, int>> dll; // {key, value}
	unordered_map<int, list<pair<int, int>>::iterator> cache;

	void moveToFront(int key, int value) {
		dll.erase(cache[key]);
		dll.push_front({ key, value });
		cache[key] = dll.begin();
	}

public:
	LRUCache(int cap) {
		capacity = cap;
	}

	int get(int key) {
		if (cache.find(key) == cache.end()) {
			return -1; // not found
		}
		int value = cache[key]->second;
		moveToFront(key, value);
		return value;
	}

	void put(int key, int value) {
		if (cache.find(key) != cache.end()) {
			// Key exists → update and move to front
			moveToFront(key, value);
		}
		else {
			// New key
			if ((int)dll.size() == capacity) {
				// Remove least recently used
				int oldKey = dll.back().first;
				dll.pop_back();
				cache.erase(oldKey);
			}
			dll.push_front({ key, value });
			cache[key] = dll.begin();
		}
	}
};


// leetcode: 1242
#include <bits/stdc++.h>
using namespace std;

class HtmlParser {
public:
	vector<string> getUrls(string url);
};

class MultiThreadedWebCrawler { // this has a race condition
private:
	unordered_map<string, int> isVis;
public:
	void executeDfs(string url, HtmlParser* htmlParser) {
		if (isVis.count(url)) {
			return;
		}
		isVis[url] = 1;
		cout << url << endl;
		vector<string> urls = htmlParser->getUrls(url);
		vector<thread> threads;

		for (auto node : urls) {
			threads.push_back(thread(&MultiThreadedWebCrawler::executeDfs, this, node, htmlPareer));
		}
		for (auto& t : threads) {
			t.join();
		}
	}
};
// removed race condition
class MultiThreadedWebCrawler {
private:
	mutex mtx;
	unordered_map<string, bool> isVis;
public:
	void executeDFS(string url, HtmlParser* htmlParser) {
		unique_lock<mutex> lock(mtx);
		if (isVis.count(url)) {
			return;
		}
		isVis[url] = true;
		cout << url << endl;
		lock.unlock();

		vector<string> urls = htmlParser->getUrls(url);
		vector<thread> threads;
		for (auto node : urls) {
			threads.push_back(thread(&MultiThreadedWebCrawler::executeDFS, this, node, htmlParser));
		}
		for (auto& t : threads) {
			t.join();
		}
	}
};
/*
Problems with the dfs: Each DFS node spawns new threads recursively — can cause thousands of threads
therefore: Use a thread pool or task queue (bounded number of worker threads).
*/
class MultiThreadedWebCrawler {
private:
	mutex mtx;
	unordered_set<string> isVis;
	condition_variable cv;
	queue<string> q;

public:
	void executeBFS(string url, HtmlParser* htmlParser) {
		while (1) {
			unique_lock<mutex> lock(mtx);
			// this will endlessly run
			// cv.wait(lock, [&] {return !q.empty();});
			// fix: wait for 1s
			cv.wait_for(lock, chrono::seconds(1), [&] {return !q.empty();});
			if (q.empty()) break;

			string temp = q.front();
			cout << temp << endl;
			q.pop();
			lock.unlock();

			vector<string> urls = htmlParser->getUrls(temp);

			for (auto node : urls) {
				unique_lock<mutex> lock(mtx);
				if (!isVis.count(node)) {
					isVis.insert(node);
					q.push(node);
				}
			}
			cv.notify_all();
		}
	}
};


class Solution {
public:
	vector<string> crawl(string startUrl, HtmlParser& htmlParser) {
		queue<string> q{ {startUrl} };
		unordered_set<string> seen{ {startUrl} };
		string hostname = getHostname(startUrl);

		vector<thread> threads;
		mutex mtx;
		condition_variable cv;

		auto worker = [&]() {
			while (true) {
				unique_lock<mutex> lock(mtx);
				cv.wait_for(lock, 30ms, [&]() { return !q.empty() });

				if (q.empty())
					return;

				auto url = q.front(); q.pop();
				auto urls = htmlParser.getUrls(url);

				lock.unlock();

				for (const auto& url : urls) {
					if (url.find(hostname) != string::npos) {
						lock_guard<mutex> lock(mtx);
						if (seen.insert(url).second) {
							q.push(url);
							cv.notify_one();
						}
					}
				}

				lock.lock();
				cv.notify_all();
			}
			};

		for (int i = 0; i < thread::hardware_concurrency(); ++i)
			threads.emplace_back(worker);

		for (auto& t : threads) t.join();

		return { seen.begin(), seen.end() };
	}
private:
	string getHostname(const string& url) {
		return url.substr(0, url.find('/', 7));
	}
};

class Solution {
public:
	vector<string> crawl(string startUrl, HtmlParser& htmlParser) {
		queue<string> q;
		unordered_set<string> seen;
		mutex mtx;
		condition_variable cv;

		string hostname = getHostname(startUrl);
		seen.insert(startUrl);
		q.push(startUrl);

		auto worker = [&]() {
			while (true) {
				string url;
				{
					unique_lock<mutex> lock(mtx);
					cv.wait(lock, [&]() { return !q.empty(); });

					url = q.front();
					q.pop();
				}

				auto urls = htmlParser.getUrls(url);

				for (const auto& next : urls) {
					if (next.find(hostname) == string::npos) continue;

					lock_guard<mutex> lock(mtx);
					if (seen.insert(next).second) {
						q.push(next);
						cv.notify_one();
					}
				}

				// stop condition
				unique_lock<mutex> lock(mtx);
				if (q.empty() && all_of(threadsRunning.begin(), threadsRunning.end(), [](bool r) { return !r; })) {
					cv.notify_all();
					return;
				}
			}
			};

		vector<thread> threads;
		int n = thread::hardware_concurrency();
		for (int i = 0; i < n; ++i)
			threads.emplace_back(worker);

		for (auto& t : threads) t.join();

		return { seen.begin(), seen.end() };
	}

private:
	string getHostname(const string& url) {
		return url.substr(0, url.find('/', 7));
	}
};



// using thread pool 
class MultiThreadedWebCrawler {
private:
	unordered_set<string> visited;
	mutex mtx;
	condition_variable cv;
	queue<string> tasks;
	bool done = false;

public:
	void crawl(string startUrl, HtmlParser* htmlParser) {
		{
			lock_guard<mutex> lock(mtx);
			visited.insert(startUrl);
			tasks.push(startUrl);
		}

		int numThreads = thread::hardware_concurrency();
		vector<thread> workers;

		for (int i = 0; i < numThreads; ++i) {
			workers.emplace_back([&]() {
				while (true) {
					string url;
					{
						unique_lock<mutex> lock(mtx);
						cv.wait(lock, [&]() { return !tasks.empty() || done; });
						if (done && tasks.empty()) return;
						url = tasks.front();
						tasks.pop();
					}

					vector<string> urls = htmlParser->getUrls(url);
					for (auto& next : urls) {
						lock_guard<mutex> lock(mtx);
						if (!visited.count(next)) {
							visited.insert(next);
							tasks.push(next);
							cv.notify_one();
						}
					}
				}
				});
		}

		// Wait for all work to finish
		while (true) {
			unique_lock<mutex> lock(mtx);
			if (tasks.empty()) {
				done = true;
				cv.notify_all();
				break;
			}
			lock.unlock();
			this_thread::sleep_for(chrono::milliseconds(100));
		}

		for (auto& w : workers) w.join();
	}
};

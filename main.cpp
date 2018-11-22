#include <iostream>
#include <memory>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "alias_sampling_generator.h"
#include "csv_row.h"
using std::max;
using std::vector;

std::shared_ptr<spdlog::logger> pLog;

void init_logger()
{
    try
    {
        pLog = spdlog::basic_logger_mt("basic_logger", "basic-log.txt");
		pLog->info("hello node2vec");
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }
}


std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

class Graph {
public:
	void init() {
		memset (head, -1, sizeof head);
	}
	void add(int x, int y) {
		key[cnt] = y;
		next[cnt] = head[x];
		len[x] ++;
		head[x] = cnt++;
	}
	void init_trans_prob() {
		vector<bool> adj(n);
		for (int u = 0; u < n; u ++) {
			for (int j = head[u]; ~ j; j = next[j]) adj[key[j]] = true;
			for (int j = head[i]; ~ j; j = next[j]) {
				int v = key[j];
				vector<double> weight;
				vector<int> idx;
				for (int k = head[v]; ~ k; k = next[k]) {
					int w = key[k];
					idx.push_back(w);
					if (w == u)
						weight.push_back(p);
					else if (adj[w])
						weight.push_back(1);
					else
						weight.push_back(q);
				}
				auto pAsg = make_shared<AliasSamplingGenerator(len[v], weight.data());
				edgeNext.emplace(make_pair(u, v), make_pair(pAsg, std::move(idx)));
			}
			for (int j = head[u]; ~ j; j = next[j]) adj[key[j]] = false;
		}
	}
	int key[M], next[M], head[N], cnt, len[N];
	using AsgPtr = std::shared_ptr<AliasSamplingGenerator>
	std::map<std::pair<int, int>, std::pair<AsgPtr, vector<int>>> edgeNext;
	double p, q;
}g;

void walk() {
	vector<int> node(N);
	for (int i = 0; i < num_iter; i ++) {
		std::shuffle(node.begin(), node.end());
		for (int x: node) {

		}
	}
}
int main()
{
	init_logger();
    std::ifstream file("graph.csv");
    CSVRow row;
    while(file >> row)
    {
		pLog->info("{} {}", row[0], row[1]);
		int a = row[0], b = row[1];
		g.add(a, b);
		g.n = max(g.n, max(a, b));
    }
	walk();
}

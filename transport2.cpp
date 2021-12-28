#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

std::ifstream f("transport2.in");
std::ofstream g("transport2.out");

int n, m;
struct Vecin {
	int nod;
	int cost;
};

std::vector<std::vector<Vecin>> la;
std::vector<bool> used;

void citire() {
	f >> n >> m;
	la.resize(n + 1);
	used.resize(n + 1);
	for (int i = 0; i < m; ++i) {
		int x, y, c;
		f >> x >> y >> c;
		la[x].push_back({ y, c });
		la[y].push_back({ x, c });
	}
}

bool bfs(int minCost) {
	std::queue<int> q;
	std::fill(used.begin(), used.end(), false);

	q.push(1);
	while (!q.empty()) {
		int top = q.front();
		q.pop();
		
		for (auto& v : la[top]) {
			if (!used[v.nod] && v.cost >= minCost) {
				if (v.nod == n)return true;

				used[v.nod] = 1;
				q.push(v.nod);
			}
		}
	}
	return false;
}

void sol() {
	// caut binar costul maxim astfel incat pot ajunge din 1 in n

	int left = 1, right = 10001;
	while (left <= right){
		int mid = (left + right) / 2;

		if (!bfs(mid)) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}

	g << left - 1;
}

int main() {
	citire();
	sol();
}

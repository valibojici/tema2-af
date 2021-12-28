#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

struct Vecin {
	int vecin;
	int indexSosea;
};

struct Cost {
	int cost;
	int index;
};

std::ifstream f("marmelada.in");
std::ofstream g("marmelada.out");

int n, m, start, end;
std::vector<std::vector<Vecin>> la;
std::vector<Cost> costuri;

void citire() {
	f >> n >> m >> start >> end;
	la.resize(n + 1);

	for (int i = 1; i <= m; ++i) {
		int x, y;
		f >> x >> y;
		la[x].push_back({ y, i });
		la[y].push_back({ x, i });
	}
	for (int i = 1; i <= m; ++i) {
		int x;
		f >> x;
		costuri.push_back({ x, i });
	}
}

void sol() {
	// fac un bfs din start in end ca sa iau drumul minim
	// dupa sortez costurile si le pun pe drumul asta minim
	// iar ce mai ramane pun pe restul drumurilor
	
	std::vector<int> sol(m + 1, -1); // sol[i] = j insemana ca soseaua cu index i are costul cu index j
	
	// din ce muchie vin
	std::vector<int> parent_edge(m + 1, -1);

	// din ce muchie ajung la final
	int end_edge;
	
	// nod, idx muchie prin care am ajuns in nod
	std::queue<std::pair<int, int> > q; 
	q.push({ start, -1 });

	std::vector<bool>used(n+1, false);
	used[start] = 1;

	while (!q.empty()) {
		auto top = q.front();
		q.pop();
		
		if (top.first == end) {
			// am ajung in end prin muchia top.second
			end_edge = top.second;
			break;
		}

		for (auto& v : la[top.first]) {
			if (!used[v.vecin]) {
				parent_edge[v.indexSosea] = top.second;
				q.push({ v.vecin, v.indexSosea });
				used[v.vecin] = 1;
			}
		}
	}

	// sortez costuri
	std::sort(costuri.begin(), costuri.end(), [](const Cost& a, const Cost& b) {return a.cost < b.cost; });
	int idx_costuri = 0;

	while (end_edge != -1) {
		sol[end_edge] = costuri[idx_costuri++].index;
		end_edge = parent_edge[end_edge];
	}

	for (int i = 1; i <= m; ++i) {
		if (sol[i] == -1) {
			sol[i] = costuri[idx_costuri++].index;
		}
	}


	for (int i = 1; i <= m; ++i) {
		g << sol[i] << '\n';	
	}
}

int main() {
	citire();
	sol();
}

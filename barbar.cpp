#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

std::ifstream f("barbar.in");
std::ofstream g("barbar.out");

int n, m;

int di[] = { 1, -1, 0, 0 };
int dj[] = { 0, 0, -1, 1 };

typedef std::pair<int, int> iPair;

iPair start, end;
std::vector<std::vector<int>> mat;

void citire() {
	f >> n >> m;
	mat.resize(n, std::vector<int>(m, 0));
	
	std::string linie;
	for (int i = 0; i < n; ++i) {
		f >> linie;
		for (int j = 0; j < linie.size(); ++j) {
			if (linie[j] == 'I') {
				start = { i, j };
			}
			else if (linie[j] == 'O') {
				end = { i, j };
			}
			else if (linie[j] == '*') {
				mat[i][j] = -1;
			}
			else if (linie[j] == 'D') {
				mat[i][j] = -2;
			}
		}
	}
}

bool ok(int i, int j) {
	return i >= 0 && i < n&& j >= 0 && j < m && mat[i][j] == 0;
}

bool bfs(int minCost) {
	std::queue<iPair> q;
	q.push({ start.first, start.second });

	std::vector<std::vector<bool>> used(n, std::vector<bool>(m, 0));
	used[start.first][start.second] = 1;

	// un bfs ca sa vad daca ajung de la start la end
	// trecand prin celule cu valorea mai mare sau egala cu minCost
	// ideea e sa maximizez minCost pana nu mai exista drum
	
	// daca din start nu merge
	if (mat[start.first][start.second] < minCost)
		return false;

	while (!q.empty()) {
		auto top = q.front();
		q.pop();
		for (int i = 0; i < 4; ++i) {
			int ni = top.first + di[i];
			int nj = top.second + dj[i];

			if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
				// verific distanta si daca am mai fost
				if (mat[ni][nj] >= minCost && !used[ni][nj]) {

					if (ni == end.first && nj == end.second)
						return true;

					used[ni][nj] = 1;
					q.push({ ni, nj });
				}
			}
		}
	}

	return false;
}

void sol() {
	std::queue<iPair> q;

	// mai intai pun dragonii in coada
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (mat[i][j] == -2) {
				q.push({ i, j });
			}

	// un bfs ca sa pun distanta pana la cel mai apropiat dragon
	while (!q.empty()) {
		auto top = q.front();
		q.pop();

		for (int i = 0; i < 4; ++i) {
			int ni = top.first + di[i];
			int nj = top.second + dj[i];
			if (ok(ni, nj)) {
				q.push({ ni, nj });
				mat[ni][nj] = 1 + mat[top.first][top.second];
				
				if (mat[ni][nj] == -1) mat[ni][nj] = 1; // la prima mutare
			}
		}
	}

	// fac o cautare binara pt rezultat
	int left = 0;
	int right = 10001;

	while (left <= right) {
		int mid = (left + right) / 2;
		
		if (!bfs(mid)) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}

	g << right;
}



int main() {
	citire();
	sol();
}

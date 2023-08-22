#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const double PI = acos(-1);

template<class T>
struct point {
	T x, y;
	point(T x, T y): x(x), y(y) {}
	friend ostream& operator<<(ostream& os, const point& p) {
		return os << "(" << p.x << "," << p.y << ")";
	}
};

void solve() {
	int k, n;
	ll ox, oy;
	cin >> k >> ox >> oy >> n;

	vector<point<ll>> servers;
	for (int i = 0; i < n; i++) {
		ll x, y;
		cin >> x >> y;

		// store relative position to Anorak
		ll dx = x - ox;
		ll dy = y - oy;
		servers.emplace_back(dx, dy);
	}

	// sort vectors in CCW order
	sort(servers.begin(), servers.end(), [&](const point<ll>& a, const point<ll>& b) {
		return atan2(a.y, a.x) < atan2(b.y, b.x);
	});

	int canSee = 0;

	for (int i = 0; i < n; i++) {
		// we'll increment this pointer until it can't be increased anymore
		int ptr = i;

		while (ptr < n + i) {
			double diff = atan2(servers[ptr % n].y, servers[ptr % n].x) - atan2(servers[i].y, servers[i].x);
			while (diff < 0) diff += 2 * PI;
			while (diff >= 2 * PI) diff -= 2 * PI;

			// adding a small epsilon, in case the actual difference between the angles is exactly PI / 2
			if (diff < (PI / 2) + 1e-9)
				ptr++;
			else
				break;
		}

		canSee = max(canSee, ptr - i);
	}

	cout << max(0, n - k - canSee) << '\n';
}

int main() {
	int t;
	cin >> t;

	while (t--)
		solve();

	return 0;
}

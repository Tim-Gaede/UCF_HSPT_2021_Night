#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<class T>
struct point {
	T x, y;
	point(T x, T y): x(x), y(y) {}
	T dot(const point& o) const { return x * o.x + y * o.y; }
	T cross(const point& o) const { return x * o.y - y * o.x; }
	int quadrant() const {
		if (x == 0 && y == 0) return -1;
		if (x == 0) return y > 0 ? 2 : 4;
		if (y == 0) return x > 0 ? 1 : 3;
		if (x > 0) return y > 0 ? 1 : 4;
		else return y > 0 ? 2 : 3;
	}
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
		// if the two points are not in the same quadrant, sort by that
		if (a.quadrant() != b.quadrant())
			return a.quadrant() < b.quadrant();

		// otherwise, if a x b > 0, then a comes before b in CCW order
		return a.cross(b) > 0;
	});

	int canSee = 0;
	int ptr = 0;

	// now we'll do a two pointer sweep, maintaining the maximum range we can see
	// when we fix a given server as the left pointer
	for (int i = 0; i < n; i++) {

		// if the dot product and cross product between our two vectors are nonnegative,
		// then the angle is at most 90 degrees
		while (ptr < n + i && servers[i].dot(servers[ptr % n]) >= 0 && servers[i].cross(servers[ptr % n]) >= 0)
			ptr++;

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

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const double PI = acos(-1);

void solve() {
	int k, n;
	ll ox, oy;
	cin >> k >> ox >> oy >> n;

	vector<double> angles;
	for (int i = 0; i < n; i++) {
		ll x, y;
		cin >> x >> y;

		// store relative position to Anorak
		ll dx = x - ox;
		ll dy = y - oy;

		// keep only the angle of this server
		angles.push_back(atan2(dy, dx));
		angles.push_back(atan2(dy, dx) + 2 * PI);
	}

	int canSee = 0;

	// for each starting angle, we'll count the number of angles in the array that are 
	// in between start and start + PI / 2
	for (double start : angles) {
		int inside = 0;
		for (double angle : angles)
			if (start <= angle && angle <= start + PI / 2)
				inside++;
			
		canSee = max(canSee, inside);
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

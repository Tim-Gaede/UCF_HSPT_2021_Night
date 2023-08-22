// Solution to Night (HSPT 2021 - On Site)
// Author: Meghan Lin

import java.util.*;
 
public class night {
	public static double halfPi= Math.PI/2.0;
	public static double pi = Math.PI;
	public static double twoPi = Math.PI*2;
	
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		// Scan in number of test cases
		int t = scan.nextInt();
		
		for(int tt = 0; tt < t; tt++) {
			// Scan in input
			int k = scan.nextInt();
			point chair = new point(scan.nextInt(), scan.nextInt(), 0);
			int n = scan.nextInt();
			
			// Scan servers into an array
			point[] servers = new point[n];
			for(int i = 0; i < n; i++) {
				int x = scan.nextInt();
				int y = scan.nextInt();
				// Calculate the angle of the server from the chair
				double angle = angleBetweenPoints(x, y, chair.x, chair.y);
				servers[i] = new point(x, y, angle);
			}
			
			// Sort the array of servers
			Arrays.sort(servers);
			
			// Use a double for-loop to find the max number of servers that can be seen from the chair at a 90 degree (pi/2 radian) angle
			int max = 0;
			for(int i = 0; i < n; i++) {
				// Go up to 2*n so that you can "wrap back around" to the beginning of the array by taking j mod n
				for(int j = i; j < 2*n; j++) {
					double angleCovered = angleBetweenAngles(servers[i].angle, servers[j%n].angle);
					if(angleCovered<=halfPi) max = Math.max(max, j-i+1);
					else break;
				}
			}
			
			// Find min number of servers that CAN'T be seen from the chair at a 90 degree angle
			int cantSee = n - max;
			
			// Find the number of servers that need to be moved - if none need to be moved, this should be 0
			int ans = Math.max(0, cantSee - k);
			
			// Print the answer
			System.out.println(ans);
		}
	}
	
	// Function to find the clockwise angle in radians between the y-axis and the line created by two points (x1, y1) and (x2, y2)
	public static double angleBetweenPoints(int x1, int y1, int x2, int y2) {
		double angle = Math.atan2(y2 - y1, x2 - x1);
		// The angle returned by atan2 is in the range -pi to pi, so add pi to make it within the normal range 0 to 2pi.
		return angle + pi;
	}
	
	// Function to find the angle in radians between two angles
		public static double angleBetweenAngles(double a, double b) {
			if(b<a) {
				return twoPi-a+b;
			}
			else return b-a;
		}
	
	// A custom point class to represent the servers
	public static class point implements Comparable<point> {
		public int x, y;
		public double angle;
		public point(int x, int y, double angle) {
			this.x = x;
			this.y = y;
			this.angle = angle;
		}
		@Override
		// The servers will be sorted in counter-clockwise order
		public int compareTo(point p) {
			if(angle>p.angle) return 1;
			if(angle<p.angle) return -1;
			return 0;
		}
	}
}
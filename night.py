# Solution to Night (HSPT 2021 - On Site)
# Author: Atharva Nagarkar

import math

# define some handy constants
PI = math.pi
RANGE = PI / 2 + 1e-6

# read in number of test cases
tests = int(input())

for tc in range(1, tests + 1):

    # read in the bounds for the problem
    k, sx, sy = map(int, input().split())
    n = int(input())

    # make a list for all the points
    pts = [ ]

    # read in all the points and add them to the list
    for i in range(n):
        x, y = map(int, input().split())
        # since we know our location, let's make it the origin
        # this can be done by subtracting our location from everyone else's location
        pts.append((x - sx, y - sy))
    
    # make a list out of the angles from all the points and sort it
    angles = [ math.atan2( y, x ) for x, y in pts ]
    angles.sort()

    # add a copy of the angles + 2 * PI
    for i in range(n):
        angles.append(angles[i] + 2 * PI)

    # initialize our answer
    max_see = 0

    # perform a 2-pointer sweep across all the points to find the max range of points in a
    # 90 degree (PI / 2 radian) angle
    j = 0
    for i in range(n):
        j = max(i, j)
        while j + 1 < i + n and angles[j + 1] - angles[i] <= RANGE:
            j += 1
        max_see = max(max_see, j - i + 1)

    # the number of points to move is (n - k) - max number of points we can see
    # this number might be negative, in which case we need to move 0 points
    need = n - k
    ans = max(0, need - max_see)

    # print the answer!
    print(ans)
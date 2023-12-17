const unsigned int sampleRate = 22050;
const unsigned int sampleCount = 4760;
const signed char samples[] = {
-1, 7, 8, -3, -7, -4, 5, -2, -11, -6, 9, 17, -1, -9, -13, -24, 
-30, -12, -19, -21, -1, 10, 15, 19, 6, 0, -8, -10, 9, 11, 11, 23, 
17, 8, 9, 12, -2, -26, -23, -9, -5, -1, 5, 18, 32, 37, 35, 20, 
-3, -26, -48, -66, -55, -26, 0, 12, 35, 93, 88, 73, 59, 24, -7, -42, 
-63, -76, -77, -65, -32, -1, 25, 45, 38, 11, 8, 8, -16, -45, -62, -60, 
-22, 2, 28, 53, 58, 42, 32, 11, -15, -39, -74, -90, -66, -46, -33, -24, 
-24, 0, 20, 20, 10, 3, 4, 20, 37, 44, 51, 58, 44, 17, 1, -5, 
-18, -37, -57, -46, -25, -15, -8, 9, 15, 26, 30, 21, 26, 38, 27, 35, 
58, 76, 76, 40, 14, 0, -8, -24, -51, -69, -73, -49, -16, -2, -14, -15, 
8, 40, 50, 47, 27, -4, -14, -1, 11, 23, 22, 11, 6, 17, 35, 18, 
5, -2, -25, -40, -35, -28, -31, -46, -40, -12, 21, 32, 33, 30, 46, 63, 
7, -32, -41, -42, -51, -54, -46, -45, -34, -20, -26, -28, -20, -29, -45, -44, 
-36, -20, 3, 18, 14, 13, 24, 17, 8, -4, -23, -34, -37, -11, 24, 40, 
60, 96, 122, 102, 41, -29, -49, -31, -57, -96, -88, -36, -3, -24, -15, 11, 
14, 3, -3, 19, 35, 19, 0, 17, 78, 88, 67, 48, 33, 15, -11, -6, 
-1, -9, -16, -9, 14, 13, 4, -27, -84, -108, -74, -51, -32, -6, 15, 37, 
50, 47, 25, 1, -28, -62, -41, -10, 3, -1, -10, 10, 33, 27, -6, -27, 
-16, 14, 55, 77, 72, 50, 24, 21, 11, -27, -64, -79, -66, -14, 31, 28, 
6, 1, 23, 32, 8, -32, -67, -54, -23, 16, 59, 90, 72, 56, 60, 50, 
12, -32, -63, -69, -44, 2, 36, 53, 41, 30, 24, 13, -11, -59, -77, -87, 
-82, -49, -4, 33, 34, 39, 65, 68, 32, 16, -3, -9, -20, -27, 1, -4, 
-25, -34, -19, -2, -13, -42, -56, -40, -33, -37, -25, -14, -10, -10, 1, 28, 
48, 61, 61, 52, 19, -24, -29, -43, -60, -59, -7, 38, 64, 84, 94, 75, 
18, -16, -16, 2, -10, -34, -16, 25, 50, 38, 10, -29, -40, -38, -33, -33, 
-27, -5, 7, 30, 48, 41, 19, -5, -18, -39, -47, -40, -51, -56, -42, -15, 
7, 15, 22, 30, 34, 32, 28, 17, 2, -7, -17, -14, -4, -9, -20, -22, 
-4, 9, -2, -25, -25, -19, -19, -19, -20, -22, -16, -2, 20, 38, 33, 12, 
-3, -13, -20, -17, -1, 16, 40, 73, 99, 100, 57, 6, -17, -21, -30, -83, 
-94, -72, -47, -18, 5, 0, -7, -8, -1, 15, -1, -26, -25, 5, 38, 59, 
86, 76, 54, 47, 41, 29, -1, -45, -77, -70, -36, -19, -25, -21, -22, -25, 
-21, -7, -16, -38, -41, -17, 10, 19, 11, 4, 9, 21, 28, 16, 12, 10, 
-8, -12, 9, -2, -14, -14, -7, 3, 7, 0, -7, -5, 3, 8, 1, 3, 
14, 12, 7, 32, 39, 28, 11, 4, -3, -30, -38, -41, -34, -27, -12, 3, 
10, 8, -1, -7, -10, -15, -18, -19, -11, 7, 27, 44, 49, 31, 14, 11, 
10, 4, -9, -26, -38, -33, -26, -19, -14, -15, -9, 11, 15, 11, 0, -14, 
-17, -9, -1, 2, -6, -16, -4, 18, 35, 27, 9, 4, 12, 19, 21, 17, 
4, -18, -18, -10, -3, -12, -24, -1, 20, 35, 41, 30, -2, -8, 1, 15, 
27, 23, 8, 29, 51, 47, 20, -14, -39, -45, -47, -43, -41, -49, -56, -38, 
-10, -4, -13, -22, -12, 2, 18, 25, 14, 11, 18, 27, 40, 33, 2, 4, 
15, 13, -5, -23, -34, -41, -37, -25, -21, -19, -12, -26, -46, -45, -30, -22, 
-24, -23, -1, 25, 41, 56, 61, 63, 60, 46, 30, 26, 13, -8, -29, -44, 
-32, -26, -23, -11, 9, 37, 54, 43, 45, 35, 14, 3, -12, -10, 4, 17, 
29, 42, 31, 19, 15, 9, -5, -29, -28, -19, -20, -34, -38, -12, -22, -40, 
-31, -7, 5, -3, -11, -13, -7, -5, -24, -29, -24, -17, 8, 35, -7, -53, 
-61, -20, 16, 21, 19, 18, 39, 71, 83, 19, -35, -60, -72, -79, -65, -43, 
-51, -44, -11, 29, 42, 15, -11, -14, 3, 23, 18, 5, -3, -13, -16, -2, 
3, -8, -28, -21, 14, 66, 76, 73, 65, 37, 14, 15, -3, -18, -13, 5, 
4, -22, -30, -24, -36, -59, -65, -32, 19, 57, 79, 91, 90, 80, 78, 75, 
49, -19, -41, -43, -38, -44, -58, -75, -75, -42, 1, 19, 6, -18, -11, 17, 
36, 23, 19, 46, 67, 58, 30, 4, -26, -67, -101, -106, -110, -102, -62, -46, 
-7, 44, 53, 3, -16, -20, -18, -17, -14, 18, 21, 13, 21, 24, 0, -7, 
14, 18, 13, 12, 24, 29, 18, 12, 17, 12, -14, -31, -38, -27, -12, -5, 
-1, 6, 18, 28, 52, 67, 37, 7, -13, -26, -29, -34, -53, -69, -55, -8, 
30, 3, -25, -20, 11, 39, 54, 58, 72, 72, 43, 25, 8, -9, -32, -55, 
-40, 9, 25, -1, -18, -31, -52, -62, -37, -10, -2, 0, 16, 9, -4, -13, 
-27, -23, 27, 54, 55, 56, 69, 69, 23, -12, -19, -30, -55, -46, -6, 9, 
25, 35, 24, -2, -8, -11, -12, -17, -23, -18, 9, 45, 60, 40, -5, -60, 
-82, -101, -101, -87, -58, -36, -20, 4, 38, 61, 54, 33, 13, 10, 19, 18, 
2, 4, 18, 30, 27, 11, 13, 10, -4, -18, -34, -44, -37, -17, 6, 14, 
21, 36, 25, 3, -10, -23, -50, -46, -40, -38, -17, 19, 42, 50, 65, 63, 
39, 10, -27, -36, -36, -29, -12, -13, -9, 10, 16, 15, 24, 24, 14, 22, 
35, 26, 2, -16, -6, 10, 16, -4, -59, -66, -45, -30, -29, -29, -43, -20, 
28, 49, 42, 38, 24, 13, 14, 11, -13, -46, -47, -41, -37, -27, -11, -4, 
8, 35, 67, 79, 62, 23, 17, 21, 14, -8, -35, -24, 5, 24, 19, 10, 
-12, -17, -2, 8, 4, -7, 0, 21, 34, 20, -8, -35, -36, -23, -14, -15, 
-20, -29, -16, -1, 5, 13, 15, 16, 25, 28, 12, -7, -18, -25, -31, -26, 
-9, 6, 23, 36, 42, 38, 20, -19, -32, -33, -37, -42, -41, -23, 0, 11, 
-2, -26, -34, -9, -11, -28, -29, 1, 37, 37, 34, 29, 28, 26, 10, -1, 
-2, 5, 20, 47, 57, 41, 26, 13, 0, -6, -11, -29, -39, -40, -36, -9, 
-3, -1, -1, -4, 1, 12, 11, 8, 2, 5, 27, 19, 1, -10, -17, -23, 
-40, -36, -30, -43, -48, -26, 11, 22, 18, 16, 21, 20, 10, 6, 1, -3, 
2, -4, -14, -20, -22, -26, -34, -31, -18, -15, -12, 4, 19, 13, 0, -4, 
3, 9, 3, -6, -11, 2, 29, 30, 5, 9, 13, 10, 4, 1, 0, 3, 
5, 12, 19, 4, 0, 0, 0, 3, 11, 17, 13, 8, 14, 15, 17, 16, 
2, -15, -14, -4, -19, -30, -31, -27, -28, -35, -32, -25, -14, -1, 19, 46, 
55, 63, 65, 58, 38, 4, -20, -35, -45, -47, -27, -17, -10, -1, 10, 15, 
15, 14, 7, -5, -14, -16, -14, -18, -26, -29, -29, -28, -50, -71, -69, -71, 
-67, -43, -23, 15, 45, 62, 69, 58, 50, 39, 28, 18, 2, 12, 22, 19, 
21, 49, 72, 60, 48, 34, 10, -15, -39, -56, -57, -44, -30, -5, 10, 19, 
20, 21, 25, 16, 16, 31, 36, 24, 11, -4, -6, -9, -22, -40, -46, -30, 
-15, -6, -4, -4, 2, -3, -11, -17, -28, -45, -76, -85, -67, -48, -48, -57, 
-38, 11, 49, 60, 65, 74, 59, 49, 55, 50, 29, 1, 1, 18, 22, -2, 
-30, -24, -21, -18, -11, -13, 0, 20, 35, 53, 55, -4, -37, -32, -29, -69, 
-113, -99, -63, -21, 12, 33, 54, 87, 81, 59, 46, 25, -13, -16, 3, 30, 
29, 11, 10, 23, 32, 16, -7, -11, 17, 16, 0, -4, 4, 6, -14, -18, 
8, 14, -27, -59, -34, -24, -39, -49, -48, -7, 29, 37, 22, 16, 3, -11, 
1, 13, 3, -10, -24, -20, -8, -16, -27, 3, 59, 54, 50, 59, 56, -4, 
-56, -68, -48, -40, -49, -29, 11, 26, -5, -31, -14, -4, -30, -50, -36, 21, 
67, 65, 86, 98, 80, 50, 23, -9, -46, -82, -103, -83, -16, 3, 5, 21, 
38, 38, 23, -5, -32, -72, -98, -53, -13, -7, -35, -33, 17, 41, -4, -37, 
-29, 2, 31, 27, 23, 24, 21, 15, 22, 19, 2, -2, 12, 34, 57, 33, 
0, -11, -18, -39, -50, -54, -44, -29, -11, 31, 34, 26, 23, 15, -15, -33, 
-34, -35, -40, -33, 10, 28, 37, 37, 21, 18, 18, 8, -7, -19, -9, 26, 
34, 44, 58, 60, 40, 1, -19, -52, -90, -105, -76, -8, 21, 32, 43, 61, 
49, 38, 35, 15, -11, -14, 13, 22, 20, 7, -5, 12, 26, -2, -15, -20, 
-44, -56, -37, -47, -69, -57, -15, 20, 16, 1, -10, -3, -8, -31, -25, -25, 
-23, -14, 5, 23, 24, 16, 20, 29, 32, 9, -15, -12, -9, -23, -18, -7, 
-4, 0, -2, 2, 13, -1, -23, -24, -15, 5, 14, 16, 30, 55, 65, 43, 
18, -7, -29, -45, -52, -43, -33, -22, -3, 15, 21, 10, 1, -4, -6, 8, 
26, 15, 4, 6, 11, -7, -25, -24, -12, -12, -7, 27, 36, 38, 30, 9, 
1, 11, 4, -2, 9, 20, 14, 19, 27, 9, -24, -37, -35, -30, -18, -12, 
-13, -11, -5, 13, 36, 38, 30, 12, -9, -10, -6, -12, -24, -31, -18, 6, 
23, 7, -42, -45, -28, -27, -27, -10, -1, 11, 35, 56, 67, 57, 19, 15, 
24, 18, -9, -28, -17, -9, -6, 0, -5, -34, -31, -35, -40, -36, -35, -35, 
-24, 3, 25, 33, 29, 24, 24, 24, 21, 7, -13, -2, 8, -2, -13, -10, 
-7, -16, -26, -30, -25, -13, -2, 3, 13, 25, 28, 35, 20, -1, -8, -5, 
5, 1, -10, -9, -6, -9, -17, -25, -16, -3, -5, -7, -13, -27, -24, -19, 
-24, -26, -14, -4, 1, 3, 3, 6, 11, 24, 29, 28, 30, 26, 26, 32, 
31, 23, 21, 32, 33, 26, 25, 24, 5, 2, 6, 8, 5, 0, -15, -16, 
-16, -30, -45, -54, -48, -31, -14, 0, 10, 6, 2, 9, 6, -9, -12, 8, 
21, 21, 11, 9, 17, 2, -16, -22, -17, -9, -12, -10, -6, -5, 0, 3, 
4, 1, -4, -3, 4, 3, 0, 4, 8, 9, 6, -17, -19, -16, -22, -21, 
-7, 10, 15, 21, 28, 39, 25, 3, 6, 6, -5, -13, -22, -18, -10, 0, 
1, -10, -14, -12, -7, -2, 1, -17, -21, -5, 1, 2, -8, -39, -44, -39, 
-27, -19, -21, -34, -18, 6, 20, 32, 32, 20, 27, 50, 51, 32, 27, 28, 
34, 36, 28, 22, 23, 31, 16, -8, -18, -16, -6, -4, -19, -36, -40, -32, 
-24, -18, -17, -17, -19, -8, 20, 26, 7, -1, 15, 48, 69, 47, 12, 1, 
21, 13, -21, -43, -36, -24, -6, -11, -36, -44, -28, -23, -34, -32, -35, -48, 
-43, -21, -15, -15, -20, -18, 2, 39, 45, 36, 9, -9, 8, 13, 6, -6, 
-6, 20, 65, 63, 41, 27, 30, 23, -2, -21, -13, 10, 7, -34, -28, -5, 
23, 32, 16, 9, 34, 51, 26, -10, -23, -15, -14, -21, -13, 11, 21, 22, 
14, 3, 18, 21, -8, 7, 2, -22, -11, -3, -45, -65, -47, -27, -14, -18, 
-22, 1, 34, 45, 29, 2, 0, 8, 11, 10, -31, -66, -79, -83, -68, -49, 
-65, -51, -16, 16, 38, 55, 85, 80, 51, 20, 14, 24, 17, 9, -17, -29, 
-6, 9, 2, -18, -31, -10, 16, 21, 26, 31, 16, -25, -55, -44, -31, -29, 
-23, -1, 40, 60, 51, 26, 20, 36, 17, -37, -65, -37, 12, 21, -18, -38, 
-17, 10, 25, 12, -2, -16, -23, 2, 33, 21, -23, -41, 0, 50, 23, -27, 
-58, -63, -43, -24, -43, -52, -37, 8, 60, 82, 20, -15, -4, 7, -10, -38, 
-34, -30, -19, 6, 25, 12, 23, 27, 11, 13, 33, 22, 9, 5, -14, -32, 
-16, -15, -27, -23, -13, -3, 19, 6, -7, -11, -3, 28, 33, 47, 63, 60, 
52, 49, 28, -8, -40, -51, -42, -40, -63, -73, -47, -12, -4, -25, -33, -13, 
-2, -8, -3, 10, 36, 58, 73, 73, 30, 6, -6, -15, -33, -44, -23, 9, 
26, 27, 15, -31, -22, 6, 7, -16, -56, -69, -10, 43, 32, -14, -6, 39, 
67, 49, 9, -13, -1, 12, 14, 20, 16, -7, 15, 60, 62, 19, -27, -32, 
5, 4, -35, -68, -76, -11, 17, 5, -11, -11, 9, 46, 53, 30, -1, 3, 
44, 52, 29, -8, -33, -29, 3, -15, -43, -48, -32, -10, -1, -20, -45, -51, 
-43, -25, -20, -19, -1, 15, 29, 50, 29, 9, 13, 21, 17, 2, -8, -26, 
-35, -34, -30, -26, -35, -41, -26, -5, 4, -6, -6, 13, 36, 58, 47, 28, 
13, 2, 4, 8, 0, 2, 12, 21, 16, 6, 10, -2, -23, -32, -10, -2, 
-15, -24, -13, -1, -2, -9, -4, 7, -2, -7, 18, 41, 45, 19, -1, 22, 
25, 13, 14, 5, -5, 7, 3, -9, -15, -20, -34, -36, -28, -35, -50, -48, 
2, 21, 27, 40, 52, 60, 38, 18, 13, -5, -15, -10, -17, -14, -3, 5, 
8, 3, 2, 5, 0, -18, -29, -39, -34, -20, -21, -15, 5, 18, 32, 32, 
16, 2, -5, -6, -2, 3, -1, -7, -11, -5, -3, -11, -14, -15, -8, -7, 
-10, -2, 0, -14, -5, -4, -15, 3, 25, 13, 19, 19, 4, -4, -7, -2, 
1, -6, -7, 8, 28, 16, 6, 4, 9, 14, 21, 11, -19, -44, -45, -29, 
-23, -31, -19, 4, 13, -1, 2, 23, 27, 10, 2, 23, 32, 21, 14, 7, 
-3, 7, 4, -4, -1, 1, 5, 7, 3, -13, -46, -73, -52, -17, 8, 18, 
20, 32, 54, 53, 22, -2, -6, 4, 6, -2, -14, -15, -5, 8, 7, -7, 
-15, -17, 4, 8, -5, -11, -12, -7, 6, -4, -24, -31, -27, -18, -9, -19, 
-27, -17, 14, 43, 42, 26, 14, 19, 21, -8, -36, -52, -44, -19, -3, 2, 
-6, -4, 12, 22, 16, 13, 14, 6, -1, 2, 11, 3, 9, 34, 51, 38, 
1, -3, -4, -2, 2, 6, 12, 21, 28, 30, 25, -9, -22, -22, -41, -62, 
-69, -73, -53, -30, -12, 12, 36, 33, 34, 30, 4, -26, -43, -40, -54, -61, 
-41, -18, 9, 14, 22, 35, 25, -9, -19, -6, 19, 41, 50, 52, 65, 59, 
34, 21, 2, -34, -54, -75, -75, -64, -66, -50, -10, 24, 38, 52, 85, 96, 
86, 55, 35, 48, 44, 17, -24, -41, -30, -21, -42, -69, -73, -58, -48, -34, 
-14, 1, 10, 36, 75, 74, 59, 31, 5, -4, -12, -34, -54, -44, -26, 0, 
45, 30, 14, 1, -21, -49, -81, -97, -82, -48, -9, 28, 49, 62, 66, 58, 
24, -25, -30, -17, 3, 9, 14, 21, 26, 29, 26, 14, -29, -48, -60, -65, 
-58, -57, -48, -35, -21, 6, 41, 56, 41, 27, 22, 33, 38, 11, -1, 6, 
32, 43, 31, 14, -1, 6, 26, 22, -1, -11, -20, -22, -14, -8, 19, 29, 
16, 21, 36, 19, -21, -41, -55, -40, -12, 2, -9, -23, -16, 13, 25, -14, 
-35, -37, -21, -18, -41, -50, -37, -10, 18, 26, 24, 30, 37, 45, 47, 43, 
34, 14, -6, -10, -1, 3, -9, -10, 4, 18, 11, -11, -23, -25, -8, -3, 
-28, -36, -26, -16, -4, -6, -9, -1, 8, 18, 44, 58, 23, 21, 34, 27, 
4, -14, -27, -5, 19, 8, -13, -35, -32, -22, -39, -53, -51, -62, -40, -23, 
-42, -55, -48, -34, -20, -5, 9, 26, 40, 46, 58, 70, 62, 35, 8, 2, 
-5, -11, -16, -16, -1, 3, 0, -3, -6, -2, -13, -24, -16, 4, 15, -3, 
-5, 13, 28, 22, 2, -33, -41, -25, -3, 25, 63, 48, 46, 69, 77, 55, 
6, -6, 2, 4, -9, -23, -53, -55, -26, 10, 21, 4, 19, 40, 44, 37, 
31, 29, 8, -16, -16, -2, 7, -21, -47, -52, -44, -37, -51, -46, -16, 11, 
27, 39, 38, 33, 30, 28, 28, 15, -15, -18, -21, -16, -9, -39, -53, -58, 
-57, -46, -41, -16, 4, 11, 20, 17, 0, -16, -12, -5, -5, -18, -27, -15, 
5, 24, 18, 17, 41, 40, 34, 17, -4, -25, -37, -32, -8, 15, 21, 5, 
-3, 11, 15, -6, -8, -5, -21, -17, 0, 17, 22, 11, 10, 26, 30, 6, 
-27, -37, -37, -24, -12, 0, 9, 9, 8, 4, 8, 14, 6, -5, -8, 8, 
37, 34, 5, -4, 2, 8, 13, -4, -26, -32, -34, -31, -7, -16, -24, -20, 
6, 37, 36, 24, 21, 34, 40, 27, 4, -10, -6, 8, 15, 10, -3, -15, 
-26, -31, -18, -7, -24, -31, -25, -10, 3, 2, -3, -4, 4, 12, 18, 1, 
-17, -11, -4, -5, -18, -24, -14, -9, -12, -9, -6, -10, -2, 19, 25, 7, 
0, -2, 0, -1, -12, -26, -14, -11, -16, -11, -11, -9, 4, 20, 31, 33, 
28, 28, 26, 28, 43, 33, -1, 2, 6, -2, -18, -30, -33, -19, -16, -17, 
-21, -24, -16, -21, -25, -19, -18, -15, -13, -11, -3, -3, -3, 3, 14, 20, 
21, 32, 47, 37, 30, 29, 25, 24, 13, -12, -27, -33, -42, -34, -36, -49, 
-35, -19, -20, -8, -11, -8, 9, 20, 23, 20, 18, 18, 17, 12, -4, -21, 
-43, -33, -11, -8, 11, 8, -3, 6, 27, 31, 20, 19, 21, 23, 27, 28, 
20, 10, 6, 17, 32, 30, 22, 13, 16, 33, 15, -51, -60, -42, -24, -22, 
-36, -39, -15, 8, 16, 7, -16, -12, 6, 38, 51, 37, 41, 65, 76, 71, 
59, 25, -10, -40, -56, -69, -82, -102, -127, -124, -71, -33, -37, -35, -13, 3, 
8, -10, -51, -45, -9, 40, 73, 83, 101, 113, 111, 103, 84, 55, -9, -35, 
-34, -34, -32, -28, -35, -36, -8, 19, 10, 8, 8, -9, -10, -1, -10, -43, 
-35, 3, 20, -8, -79, -104, -96, -86, -88, -92, -72, -21, 27, 55, 79, 107, 
116, 112, 101, 80, 48, 22, 12, 8, 11, 12, 8, -24, -51, -60, -72, -96, 
-114, -99, -57, -12, 5, 13, 62, 75, 74, 66, 40, 20, 20, 32, 44, 48, 
42, 32, 39, 41, 29, -3, -38, -60, -73, -77, -66, -68, -83, -42, 20, 63, 
81, 77, 67, 69, 46, 4, -33, -44, -20, 1, 23, 45, 44, 14, -36, -58, 
-72, -63, -45, -54, -34, 22, 71, 82, 65, 34, 34, 34, -6, -70, -102, -83, 
-81, -71, -28, 12, 19, 42, 68, 69, 58, 35, 6, -3, -6, -9, -10, -3, 
15, 38, 48, 37, 19, -30, -55, -59, -52, -35, -23, -15, -1, 0, 4, 11, 
-4, -30, -18, -9, -16, -26, -3, 6, 12, 32, 46, 49, 55, 58, 47, 41, 
36, 14, 3, 5, -4, -27, -58, -55, -45, -38, -15, 2, 7, 25, 22, 4, 
-7, -7, -34, -58, -59, -33, -8, -21, -44, -6, 27, 30, 20, 5, 11, 27, 
41, 61, 63, 31, 37, 46, 37, 17, -2, -1, -8, -27, -35, -42, -57, -74, 
-60, -25, 0, -5, -25, -24, -20, -16, -15, -12, -5, -8, -6, 4, 6, 4, 
0, 0, 13, 21, 12, -1, 14, 35, 48, 54, 58, 63, 46, 41, 49, 32, 
-2, -31, -50, -63, -63, -55, -38, -42, -34, 5, 41, 34, 6, 10, 15, 18, 
5, -13, 2, 29, 46, 43, 39, 57, 60, 38, 15, 1, -8, -21, -40, -51, 
-39, -29, -37, -44, -44, -49, -59, -70, -61, -37, -16, 4, 23, 38, 46, 48, 
51, 47, 34, 22, 14, 11, 17, 26, 28, 4, -1, 10, 3, -26, -42, -44, 
-63, -72, -64, -41, -21, -23, -14, 2, 6, 14, 26, 22, 13, 1, -4, -1, 
3, -2, 3, 20, 40, 63, 56, 39, 34, 33, 21, -13, -31, -40, -39, -33, 
-24, -7, 2, 11, 12, 15, 9, -7, 0, 17, 13, 8, 28, 24, -4, -30, 
-30, -25, -46, -48, -21, 3, 6, -2, 13, 37, 44, 48, 50, 28, 9, -5, 
-17, -40, -58, -63, -69, -58, -43, -41, -33, -18, -3, 13, 29, 40, 26, 29, 
45, 55, 51, 30, 17, 22, 10, -18, -41, -38, -19, -6, -3, 3, 12, 19, 
18, 15, 4, -10, -4, 1, -5, -5, -5, -2, 13, 18, 10, 12, 24, 26, 
22, 13, -1, -11, -16, -20, -40, -38, -21, -9, -4, 8, 11, 6, 1, -4, 
-10, -10, -8, -6, -7, -7, -3, -14, -20, -28, -31, -16, -8, -5, -2, -11, 
-14, -9, -7, -3, 2, 8, 20, 29, 17, 11, -2, -9, -1, -1, 7, 17, 
19, 18, 15, 8, 5, -3, -13, -22, -19, -5, 7, 1, 3, 25, 33, 21, 
7, 5, 10, 7, -2, -4, 6, 13, 6, 3, 3, -3, -4, -3, -12, -24, 
-18, -11, -6, -2, -3, 0, -1, -3, -6, -12, -17, -27, -27, -17, -18, -19, 
-18, -27, -21, -5, 5, 16, 25, 21, 25, 41, 52, 37, 22, 7, -2, -4, 
-5, -14, -21, -28, -40, -40, -24, -3, -9, -16, -12, -2, 25, 21, -1, -2, 
19, 30, 36, 34, 18, 12, 29, 44, 44, 41, 46, 51, 38, 8, -6, -24, 
-46, -62, -68, -42, -36, -35, -24, -14, 1, 22, 12, -7, -17, -14, -21, -33, 
-31, -15, -3, -14, -24, -1, 12, -1, -29, -42, -9, 0, -12, -13, 11, 67, 
75, 51, 43, 54, 38, -30, -53, -43, -21, -22, -29, -21, -14, -5, 2, 8, 
12, 19, 11, -13, -20, -11, -10, -15, -14, 12, 42, 36, 23, 7, -10, -23, 
-47, -77, -55, -37, -37, -27, -8, 4, 16, 26, 19, 5, 26, 54, 51, 28, 
24, 44, 68, 68, 42, 3, -11, -13, -27, -54, -68, -40, -11, 0, 3, -2, 
-13, -15, -1, 1, 14, 39, 34, 19, 29, 23, 13, 20, 7, -10, 7, -2, 
-23, -21, -6, -3, -7, 1, 6, -1, -16, -30, -29, -19, -20, -35, -17, 45, 
37, 13, 3, 5, -4, -34, -40, -26, -4, -4, -17, 1, 6, -8, -22, -27, 
5, 29, 27, 9, 6, 20, 27, 11, -8, -18, -12, 0, 17, 25, 36, 54, 
63, 64, 62, 58, 55, 37, -4, -74, -107, -124, -117, -116, -126, -77, -18, 18, 
19, 11, 34, 49, 42, 35, 48, 74, 72, 53, 57, 70, 60, 25, -21, -30, 
-26, -20, -14, -8, 3, 4, -9, -16, -21, -51, -76, -90, -101, -103, -63, -36, 
-18, 1, 29, 65, 85, 62, 38, 26, 21, 12, -4, -3, -10, -27, -39, -32, 
-25, -23, -16, 4, 36, 63, 53, 34, 18, 10, -2, -21, -19, -16, -12, -6, 
0, 0, -7, -23, -30, -14, 17, 13, -10, -18, 1, 13, 0, 12, 29, 35, 
34, 35, 46, 48, 29, 3, -15, -28, -28, -36, -49, -35, -1, 1, -19, -21, 
-23, -31, -25, -29, -36, -24, 1, 11, 8, 3, 11, 21, 12, -7, -12, 0, 
7, 13, 22, 60, 75, 58, 27, 12, 1, -36, -49, -53, -47, -37, -27, 0, 
32, 51, 51, 63, 75, 62, 45, 20, -4, -19, -31, -29, -37, -54, -63, -54, 
-40, -45, -49, -56, -43, 23, 50, 58, 68, 72, 56, 25, 21, 6, -20, -37, 
-43, -44, -37, -37, -26, 6, 20, 15, 17, 18, 6, -6, -7, -7, 0, 0, 
-14, -8, -3, -4, -9, -21, -21, -12, -5, 12, 33, 45, 39, 40, 37, 20, 
11, -10, -62, -61, -38, -20, -27, -39, -13, 1, 2, -2, -13, -21, 1, 3, 
-10, -4, 6, 11, 12, 16, 26, 26, 20, 0, 1, 10, 7, 5, 11, 22, 
29, 21, 10, 5, 8, 10, 1, -3, 2, -1, -9, -8, -16, -17, -1, 8, 
13, 13, 11, 10, 9, 3, -11, 0, 14, 18, 26, 14, 0, -16, -25, -26, 
-37, -38, -20, -2, 17, 29, 38, 26, 10, 4, -2, -13, -29, -33, -27, -19, 
-22, -25, -19, -17, -5, 12, 16, 7, 11, 12, 6, 7, 8, -14, -7, 4, 
-2, -15, -16, -4, -14, -17, -4, -2, 1, 13, 18, 25, 34, 34, 25, 15, 
1, -19, -42, -62, -55, -41, -31, -14, 1, 22, 33, 27, 23, 22, 0, -15, 
-8, -14, -7, 6, 4, 13, 16, 12, 13, 2, -28, -33, -25, -20, -14, -4, 
18, 41, 43, 29, 29, 22, 10, 0, -7, -7, -8, -7, -8, -13, -12, -5, 
-13, -21, -13, -16, -18, -13, -1, 11, 23, 31, 38, 34, 17, 10, -5, -38, 
-62, -58, -40, -18, 3, 23, 46, 53, 49, 46, 38, 19, -8, -28, -33, -34, 
-26, -13, -1, 9, 12, 9, -4, -17, -13, -15, -21, -13, 9, 32, 42, 42, 
40, 26, 13, -1, -22, -25, -39, -52, -48, -15, 3, 17, 29, 36, 43, 36, 
19, 6, -7, -23, -28, -18, -13, 0, 14, 25, 30, 21, 18, -2, -29, -33, 
-22, -23, -21, -17, -22, -11, 4, 0, 0, 2, 4, -21, -37, -36, -21, -6, 
0, 0, -5, -3, 4, -1, -11, -24, -31, -29, -23, -10, 16, 10, -6, -14, 
-17, -17, -13, 1, 20, 26, 19, 22, 27, 31, 38, 40, 40, 30, 10, -6, 
-7, -8, -23, -43, -38, -18, -5, 6, 17, 11, 17, 32, 38, 39, 38, 22, 
3, -12, -11, -6, -42, -72, -64, -23, 20, 45, 41, 34, 28, 32, 31, 7, 
-26, -43, -28, -7, 2, -10, -23, -21, -6, 5, 7, -4, -9, -8, -2, 6, 
-6, -11, -5, -2, 2, 24, 36, 5, -23, -28, -19, -6, -11, -17, -13, 5, 
26, 18, -3, -14, -23, -29, -18, -16, -32, -35, -20, 2, 34, 22, -1, -3, 
5, 22, 21, -19, -42, -33, -13, 10, 21, 8, 1, -2, 2, 26, 24, -5, 
-29, -29, -25, -20, 2, 14, 11, 19, 39, 58, 44, 23, -6, -39, -49, -46, 
-44, -25, 10, 34, 47, 47, 32, 14, -4, -26, -33, -31, -34, -33, -27, -10, 
-7, -14, -20, -10, 12, 26, 10, -15, -21, -18, -34, -26, -11, -10, -2, 15, 
14, 10, -4, -23, -18, 0, 15, 20, 19, 23, 53, 81, 46, -4, -23, -8, 
-8, -32, -16, 12, 31, 29, 18, 32, 53, 35, -5, -24, -22, -15, -13, 1, 
22, 31, 30, 26, 17, -1, -13, -12, -7, -11, -9, 2, 5, -19, -38, -45, 
-55, -75, -79, -32, 6, 30, 24, 15, 34, 35, 16, -1, -15, -29, -52, -55, 
-40, -18, -5, -3, -9, 15, 37, 32, 22, 9, 9, 5, -17, -22, -13, -9, 
3, 20, 21, 22, 28, 12, 13, 13, 4, -1, -2, 1, 6, 9, 3, 0, 
4, 8, 5, 11, 20, 17, 6, 11, 15, 4, -4, -2, 5, -15, -41, -41, 
-28, -14, -16, -15, -3, 11, 16, 8, 7, 2, -7, -7, 2, 2, -13, -15, 
0, 14, 23, 26, 14, 4, -3, -7, 2, 4, -2, -13, -10, 5, 12, 6, 
-16, -23, -21, -4, 8, -1, -23, -29, -16, 14, 20, 9, -11, -16, -3, 5, 
11, -5, -22, -23, -10, 1, 0, -7, -12, -6, 21, 18, 13, 15, -3, -22, 
-7, 4, 1, -5, -11, -19, -10, 4, 8, 5, 1, -2, 4, 9, 10, 9, 
-2, 1, 21, 29, 25, 20, 1, -5, -2, 15, 21, -2, -14, 5, 13, 11, 
-3, -26, -16, -19, -27, -26, -27, -11, -1, 0, 6, 17, 17, 9, 8, 8, 
14, 19, 24, 24, 14, -1, -4, -3, -1, -2, -11, -6, 10, 25, 7, -8, 
-9, -12, -16, -34, -36, -37, -32, -20, -7, 7, 19, 36, 35, 20, 14, 24, 
28, 23, 11, -5, -22, -15, -3, -3, -12, -17, -22, -22, -16, -7, -1, 0, 
-7, -2, 17, 15, 1, -1, 2, 3, -1, -2, -7, -21, -19, -16, -19, -21, 
-11, -12, -7, 9, 17, 7, -24, -24, -19, -6, 14, 16, -3, -11, -3, 18, 
22, -1, -8, 0, 14, 16, 16, 16, 5, 9, 19, 17, 9, -15, -22, -16, 
-8, -2, 2, 2, -3, -4, 4, 14, 10, -1, -2, 2, 8, 11, 4, 3, 
1, 2, 7, 6, 3, 2, 1, 0, };

const unsigned int revSampleRate = 22050;
const unsigned int revSampleCount = 3165;
const signed char revSamples[] = {
0, -1, -2, -3, -3, -4, -5, -6, -5, -1, 3, 6, 10, 10, 9, 8,
7, 3, 2, 3, 4, 4, 3, -1, -3, -3, -2, 0, 3, 9, 12, 15, 
15, 14, 7, 2, -1, -1, 4, 11, 20, 24, 26, 29, 31, 31, 35, 41, 
48, 55, 56, 55, 54, 54, 55, 55, 53, 55, 57, 59, 58, 58, 58, 60, 
59, 57, 54, 50, 40, 32, 21, 9, 0, -5, -11, -13, -16, -20, -24, -29, 
-36, -40, -42, -41, -37, -27, -22, -16, -12, -8, -5, 0, 1, 0, -1, -4, 
-7, -12, -17, -23, -28, -31, -31, -27, -24, -20, -17, -15, -16, -20, -26, -33, 
-38, -39, -36, -33, -30, -28, -28, -28, -27, -25, -22, -19, -16, -11, -8, -4, 
1, 7, 14, 23, 30, 36, 44, 54, 74, 90, 105, 112, 112, 112, 112, 112, 
112, 112, 112, 112, 112, 113, 113, 113, 112, 108, 109, 111, 111, 109, 100, 80, 
68, 56, 43, 31, 16, 12, 8, 1, -8, -16, -24, -28, -33, -36, -35, -30, 
-21, -16, -11, -2, 11, 29, 39, 45, 48, 49, 48, 44, 42, 42, 43, 45, 
46, 52, 59, 70, 81, 91, 98, 98, 93, 85, 73, 59, 40, 31, 25, 22, 
21, 21, 21, 19, 18, 14, 8, -3, -8, -9, -8, -7, -6, -5, 0, 9, 
22, 40, 58, 83, 94, 102, 106, 105, 101, 97, 92, 86, 79, 69, 47, 30, 
13, -3, -19, -33, -49, -55, -58, -61, -64, -72, -77, -80, -82, -81, -81, -83, 
-86, -86, -75, -54, -27, 7, 23, 35, 49, 62, 74, 74, 71, 67, 65, 62, 
57, 50, 36, 17, -7, -33, -63, -71, -72, -65, -53, -33, -25, -25, -33, -47, 
-62, -73, -69, -55, -31, -1, 45, 66, 72, 65, 47, 25, -3, -14, -17, -9, 
8, 30, 60, 73, 79, 76, 66, 37, 12, -10, -28, -41, -49, -59, -65, -73, 
-83, -95, -102, -100, -90, -76, -64, -55, -48, -47, -47, -46, -40, -26, 10, 33, 
49, 60, 68, 75, 80, 72, 54, 32, 12, -6, -5, 8, 28, 49, 64, 66, 
55, 37, 13, -16, -47, -86, -101, -106, -106, -106, -106, -106, -106, -106, -106, -106, 
-99, -91, -86, -87, -91, -91, -79, -65, -50, -32, -14, 8, 16, 20, 24, 28, 
32, 26, 14, -1, -15, -26, -31, -25, -12, 1, 6, 2, -19, -34, -46, -56, 
-63, -68, -68, -58, -41, -24, -14, -11, -13, -14, -12, -8, -2, 11, 23, 38, 
52, 62, 65, 62, 55, 45, 33, 19, 8, 0, -2, -5, -13, -24, -36, -40, 
-41, -40, -36, -31, -25, -30, -41, -54, -64, -68, -62, -49, -30, -10, 5, 15, 
16, 21, 33, 51, 70, 84, 82, 74, 64, 56, 48, 47, 49, 51, 50, 44, 
29, 17, 6, -3, -9, -13, -14, -12, -10, -7, -7, -11, -18, -26, -33, -34, 
-29, -11, 0, 6, 4, 1, 0, 3, 3, 0, -5, -7, -2, 3, 4, -1, 
-10, -19, -37, -53, -67, -73, -69, -58, -43, -42, -47, -56, -65, -77, -82, -86, 
-86, -84, -78, -70, -63, -54, -43, -26, -9, 10, 14, 13, 10, 10, 14, 19, 
27, 34, 40, 41, 28, 12, -2, -11, -15, -16, -15, -13, -8, -5, -9, -28, 
-41, -47, -45, -40, -35, -28, -24, -22, -21, -20, -17, -8, -5, -5, -6, -6, 
-4, -2, -1, -1, 0, 1, 0, -1, 0, 5, 12, 21, 29, 28, 23, 18, 
14, 10, 7, 5, 2, 2, 3, 5, 8, 12, 17, 20, 24, 24, 22, 17, 
12, 8, 6, 8, 8, 8, 6, 1, -11, -23, -31, -36, -36, -23, -15, -9, 
-10, -18, -27, -43, -51, -57, -58, -52, -42, -22, -13, -9, -11, -17, -24, -25, 
-23, -16, -8, 1, 13, 18, 17, 11, 1, -9, -20, -19, -11, -1, 8, 15, 
15, 13, 10, 7, 4, 4, 8, 14, 22, 29, 34, 35, 32, 26, 23, 25, 
35, 42, 46, 46, 44, 40, 31, 22, 16, 14, 18, 26, 35, 38, 37, 33, 
27, 20, 15, 12, 11, 12, 16, 30, 42, 52, 58, 60, 60, 59, 57, 55, 
50, 47, 49, 54, 62, 71, 82, 93, 109, 118, 124, 126, 126, 126, 126, 125, 
123, 121, 120, 121, 121, 122, 123, 125, 127, 127, 127, 126, 126, 126, 126, 126, 
125, 124, 124, 124, 126, 126, 126, 123, 109, 89, 53, 31, 14, -1, -13, -22, 
-25, -24, -24, -27, -34, -47, -52, -52, -46, -38, -30, -18, -10, -2, 3, 4, 
3, 5, 11, 19, 28, 37, 53, 65, 77, 86, 91, 92, 86, 79, 71, 64, 
61, 62, 65, 67, 71, 79, 90, 104, 106, 104, 104, 105, 106, 97, 87, 80, 
77, 75, 68, 60, 51, 41, 28, 11, -16, -35, -51, -67, -77, -79, -78, -79, 
-82, -84, -81, -65, -54, -48, -50, -56, -65, -77, -81, -78, -70, -57, -43, -31, 
-30, -32, -37, -45, -62, -70, -72, -67, -57, -45, -23, -9, -2, 0, -3, -5, 
1, 9, 15, 18, 19, 22, 20, 17, 11, 5, 3, 0, 0, 3, 12, 29, 
46, 65, 71, 74, 75, 73, 51, 29, 7, -11, -24, -34, -38, -33, -26, -22, 
-24, -30, -40, -52, -66, -81, -91, -93, -90, -84, -74, -64, -55, -53, -59, -66, 
-72, -77, -90, -98, -101, -98, -90, -82, -74, -69, -62, -54, -48, -44, -47, -53, 
-62, -75, -88, -93, -81, -60, -38, -20, -4, 18, 28, 34, 36, 36, 34, 19, 
-1, -28, -55, -74, -89, -93, -97, -103, -110, -117, -124, -125, -124, -123, -122, -122, 
-123, -125, -125, -124, -121, -102, -86, -70, -56, -46, -39, -31, -30, -31, -35, -37, 
-39, -40, -42, -45, -45, -42, -36, -32, -30, -28, -24, -20, -21, -26, -34, -42, 
-44, -43, -41, -38, -37, -33, -27, -18, -13, -10, -5, -1, 4, 10, 13, 15, 
18, 21, 25, 30, 31, 30, 28, 22, 10, -1, -12, -22, -28, -30, -33, -36, 
-42, -47, -52, -55, -54, -52, -52, -54, -60, -72, -81, -89, -94, -97, -98, -94, 
-86, -71, -52, -33, -17, -1, 5, 7, 5, -1, -13, -16, -15, -10, -7, -5, 
-4, -2, 1, 5, 7, 6, 2, -6, -18, -31, -42, -54, -59, -62, -63, -57, 
-46, -34, -34, -38, -39, -32, -19, -16, -17, -17, -15, -11, -11, -15, -14, -7, 
4, 14, 20, 22, 26, 30, 31, 21, 12, 5, 0, -4, -9, -8, -3, 3, 
5, 2, 0, 3, 8, 13, 16, 19, 25, 24, 18, 8, -1, -2, 7, 15, 
22, 28, 36, 46, 55, 55, 53, 50, 48, 43, 39, 39, 42, 49, 54, 58, 
58, 57, 54, 47, 37, 24, 17, 13, 10, 9, 8, 9, 10, 10, 8, 5, 
1, 1, 3, 7, 11, 14, 18, 20, 22, 25, 31, 45, 54, 61, 64, 63, 
59, 49, 42, 35, 26, 19, 15, 16, 19, 19, 18, 16, 17, 18, 17, 15, 
11, 9, 8, 4, -5, -17, -28, -34, -31, -28, -25, -22, -20, -16, -16, -17, 
-19, -21, -20, -18, -15, -11, -7, -2, 0, -3, -7, -11, -13, -12, -5, 0, 
4, 6, 2, -5, -12, -13, -11, -7, -3, 7, 18, 31, 47, 62, 78, 99, 
106, 110, 110, 109, 109, 110, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 
111, 111, 111, 111, 108, 101, 85, 75, 69, 67, 67, 61, 54, 45, 35, 26, 
18, 13, 14, 16, 16, 13, 9, 6, 8, 12, 15, 14, 7, 1, -4, -8, 
-9, -9, -7, -6, -7, -8, -10, -12, -13, -11, -8, -6, -4, -3, -1, 0, 
0, 0, 2, 14, 25, 36, 44, 49, 53, 55, 51, 43, 32, 24, 17, 15, 
14, 16, 21, 28, 34, 31, 26, 22, 20, 17, 8, 1, -4, -8, -11, -16, 
-15, -13, -11, -13, -19, -26, -28, -28, -28, -30, -29, -21, -18, -18, -19, -20, 
-17, -13, -8, -2, 7, 22, 48, 64, 75, 81, 82, 71, 55, 38, 22, 9, 
2, -5, -7, -8, -12, -17, -26, -37, -39, -36, -28, -21, -10, -2, 10, 23, 
38, 52, 69, 71, 61, 44, 25, 11, 1, -2, -10, -19, -25, -18, -5, 12, 
29, 46, 62, 81, 84, 80, 72, 59, 42, 7, -19, -36, -42, -38, -17, -1, 
18, 34, 42, 39, 19, 5, -4, -13, -24, -34, -37, -27, -9, 13, 36, 67, 
78, 80, 74, 66, 58, 53, 50, 47, 46, 48, 53, 59, 57, 53, 50, 48, 
43, 36, 27, 19, 10, -5, -43, -72, -92, -100, -99, -99, -104, -103, -95, -83, 
-76, -86, -97, -102, -97, -85, -72, -51, -34, -19, -7, 1, 6, 8, 3, -9, 
-23, -30, -33, -33, -34, -34, -31, -26, -25, -31, -42, -57, -74, -91, -108, -111, 
-110, -103, -94, -83, -82, -86, -93, -98, -95, -76, -58, -40, -24, -14, -7, -9, 
-12, -17, -20, -20, -18, -15, -12, -8, -4, 1, 11, 16, 21, 23, 22, 19, 
14, 7, -4, -16, -28, -37, -36, -34, -31, -29, -28, -26, -28, -36, -46, -55, 
-57, -52, -47, -45, -46, -47, -44, -42, -41, -36, -26, -12, 4, 7, 5, 1, 
-4, -9, -10, -8, -3, 2, 2, -10, -22, -34, -42, -46, -47, -41, -34, -30, 
-34, -49, -80, -95, -100, -97, -88, -74, -55, -46, -41, -41, -42, -40, -29, -21, 
-16, -16, -20, -30, -36, -41, -42, -44, -44, -39, -34, -27, -20, -16, -12, -10, 
-12, -17, -22, -27, -33, -37, -44, -53, -59, -62, -55, -46, -36, -24, -13, -1, 
9, 6, 0, -7, -8, -2, 3, 7, 8, 8, 8, 4, -1, -5, -7, -6, 
-4, -3, -5, -7, -9, -13, -19, -21, -20, -14, -6, 2, 11, 13, 13, 12, 
10, 12, 16, 24, 30, 32, 31, 24, 21, 22, 24, 27, 29, 27, 24, 19, 
15, 15, 19, 25, 32, 37, 39, 37, 27, 18, 8, -1, -7, -9, -4, 1, 
6, 10, 12, 13, 11, 8, 2, -4, -8, -10, -12, -16, -21, -25, -27, -28, 
-30, -34, -36, -32, -19, -12, -7, -6, -6, -5, 2, 6, 11, 15, 15, 12, 
1, -9, -14, -15, -7, 13, 27, 37, 43, 45, 44, 42, 42, 44, 47, 49, 
49, 46, 45, 46, 46, 46, 45, 44, 44, 45, 47, 49, 52, 53, 53, 53, 
56, 62, 76, 90, 103, 114, 122, 125, 124, 123, 123, 123, 125, 125, 126, 127, 
127, 127, 126, 117, 107, 99, 91, 84, 68, 55, 42, 30, 20, 12, 2, 2, 
5, 11, 18, 23, 32, 36, 40, 44, 50, 65, 77, 90, 102, 112, 120, 123, 
122, 122, 122, 122, 121, 121, 121, 120, 119, 119, 118, 119, 119, 119, 119, 118, 
109, 101, 92, 80, 64, 37, 21, 7, -4, -12, -20, -24, -23, -19, -10, 0, 
10, 23, 27, 31, 32, 31, 21, 10, -1, -11, -19, -24, -23, -16, -5, 8, 
19, 25, 22, 12, -4, -26, -50, -77, -86, -86, -79, -68, -53, -29, -14, -4, 
-1, -2, -2, -6, -9, -12, -14, -10, -4, -2, -3, -6, -7, -8, -11, -16, 
-21, -24, -25, -18, 0, 15, 28, 35, 38, 30, 19, 4, -15, -37, -61, -90, 
-101, -105, -104, -103, -101, -100, -98, -97, -98, -101, -107, -110, -110, -108, -100, -85, 
-54, -36, -23, -15, -11, -10, -16, -25, -36, -42, -40, -25, -11, 2, 8, 8, 
2, -9, -10, -8, -6, -4, -3, -4, -6, -12, -19, -27, -40, -51, -62, -69, 
-71, -70, -68, -66, -60, -51, -38, -13, 9, 33, 53, 64, 66, 61, 62, 64, 
62, 52, 34, 4, -10, -17, -18, -15, -7, -3, -3, -6, -12, -19, -32, -43, 
-56, -66, -73, -77, -82, -83, -82, -82, -84, -92, -95, -91, -82, -71, -61, -53, 
-49, -48, -51, -58, -68, -78, -78, -75, -68, -55, -31, -19, -15, -18, -24, -32, 
-46, -57, -66, -72, -70, -63, -47, -37, -31, -28, -30, -40, -48, -51, -46, -37, 
-27, -17, -17, -21, -28, -37, -46, -55, -55, -52, -44, -32, -12, -3, 1, 0, 
-4, -10, -22, -28, -34, -39, -44, -50, -59, -64, -66, -65, -64, -57, -50, -41, 
-32, -26, -20, -10, -1, 7, 15, 21, 25, 27, 24, 16, 7, -1, -7, -4, 
0, 4, 5, 1, -12, -19, -24, -25, -22, -17, -11, -14, -22, -33, -43, -52, 
-55, -56, -54, -48, -38, -22, -14, -10, -7, -8, -16, -25, -34, -37, -33, -23, 
-12, -11, -13, -17, -23, -28, -29, -22, -10, 2, 7, -5, -21, -35, -43, -46, 
-46, -40, -32, -21, -11, -4, 1, 11, 20, 27, 29, 27, 23, 22, 21, 18, 
12, 4, 0, 3, 10, 17, 24, 31, 38, 36, 27, 14, 1, -15, -23, -30, 
-35, -36, -33, -25, -21, -18, -14, -7, 0, 11, 13, 14, 17, 20, 24, 26, 
31, 41, 52, 64, 77, 81, 83, 83, 82, 79, 76, 75, 73, 72, 69, 65, 
65, 66, 66, 62, 57, 46, 37, 28, 19, 13, 12, 14, 15, 16, 17, 17, 
15, 12, 8, 4, -1, -7, -14, -15, -12, -7, -4, -1, 6, 14, 24, 35, 
44, 53, 56, 56, 53, 48, 40, 31, 27, 25, 25, 28, 33, 39, 38, 33, 
27, 22, 20, 20, 21, 23, 23, 19, 5, -3, -8, -11, -13, -11, -6, 4, 
14, 21, 23, 17, 12, 6, 2, 1, 5, 18, 26, 30, 27, 19, 6, -1, 
-4, -4, -3, 1, 10, 14, 14, 11, 6, -1, -8, -10, -10, -6, 1, 14, 
22, 28, 33, 37, 41, 48, 52, 57, 61, 68, 76, 87, 94, 100, 105, 110, 
116, 116, 116, 116, 115, 113, 112, 111, 111, 112, 112, 114, 115, 115, 115, 115, 
115, 114, 114, 113, 113, 114, 114, 113, 113, 113, 113, 112, 101, 69, 46, 27, 
10, -4, -23, -35, -47, -59, -70, -77, -78, -78, -78, -77, -75, -70, -66, -67, 
-68, -67, -62, -49, -40, -32, -27, -23, -19, -11, -5, 3, 14, 28, 42, 61, 
68, 71, 71, 67, 61, 59, 61, 67, 74, 81, 89, 91, 90, 86, 79, 72, 
66, 66, 65, 60, 52, 44, 44, 45, 45, 44, 41, 39, 37, 32, 26, 16, 
-2, -18, -33, -48, -59, -67, -78, -83, -85, -83, -77, -69, -62, -62, -64, -69, 
-75, -85, -89, -89, -85, -80, -75, -71, -70, -68, -65, -62, -60, -58, -56, -52, 
-44, -34, -12, 4, 18, 31, 38, 43, 47, 50, 54, 55, 54, 49, 45, 44, 
43, 39, 35, 30, 28, 26, 24, 24, 25, 26, 24, 20, 16, 13, 10, -1, 
-14, -29, -44, -56, -61, -53, -39, -21, -3, 12, 26, 31, 31, 27, 18, 5, 
-17, -29, -34, -32, -24, -2, 10, 14, 6, -10, -32, -63, -82, -96, -101, -97, 
-81, -49, -30, -16, -7, -5, -14, -26, -37, -45, -47, -45, -35, -27, -19, -15, 
-16, -23, -40, -47, -49, -46, -40, -28, -21, -14, -10, -7, -4, 1, 2, -1, 
-10, -20, -29, -40, -50, -61, -71, -74, -70, -65, -62, -63, -67, -72, -82, -88, 
-92, -90, -82, -67, -57, -46, -34, -24, -18, -20, -25, -32, -43, -56, -69, -77, 
-72, -62, -49, -36, -18, -6, 4, 9, 7, -3, -27, -43, -49, -45, -32, -16, 
0, 3, 1, -4, -9, -7, 1, 11, 17, 16, 9, 1, 1, 3, 6, 5, 
5, 7, 12, 19, 24, 27, 26, 21, 10, -5, -20, -33, -46, -52, -52, -49, 
-44, -38, -41, -45, -49, -49, -49, -54, -58, -64, -67, -67, -66, -62, -59, -53, 
-49, -46, -46, -47, -46, -45, -45, -46, -45, -42, -39, -38, -43, -49, -52, -49, 
-44, -44, -48, -53, -57, -60, -67, -74, -77, -63, -49, -38, -34, -35, -36, -41, 
-47, -54, -59, -60, -57, -56, -58, -59, -53, -43, -33, -34, -39, -43, -46, -49, 
-54, -56, -54, -48, -42, -40, -36, -32, -26, -23, -24, -29, -29, -25, -19, -16, 
-15, -18, -20, -25, -32, -38, -41, -36, -29, -23, -19, -17, -16, -16, -16, -15, 
-13, -8, 1, 4, 5, 4, 1, -5, -10, -15, -16, -14, -7, 8, 12, 12, 
8, 3, 1, 2, 5, 7, 7, 7, 6, 4, 4, 5, 10, 16, 22, 24, 
24, 22, 19, 15, 10, 8, 9, 13, 16, 20, 21, 22, 20, 16, 11, 11, 
15, 19, 21, 19, 15, 9, 6, 3, 0, -2, -5, -7, -10, -13, -16, -19, 
-25, -31, -38, -44, -47, -49, -52, -53, -52, -51, -49, -50, -52, -54, -54, -50, 
-47, -40, -34, -25, -13, 0, 12, 25, 31, 37, 40, 42, 42, 44, 50, 56, 
59, 61, 65, 68, 72, 72, 71, 69, 68, 68, 68, 69, 70, 74, 76, 77, 
78, 82, 88, 101, 107, 111, 114, 117, 120, 121, 121, 121, 121, 123, 124, 123, 
121, 117, 112, 106, 98, 95, 93, 89, 84, 77, 71, 66, 60, 55, 53, 56, 
60, 65, 70, 76, 81, 87, 87, 88, 89, 90, 91, 88, 85, 81, 78, 74, 
63, 56, 51, 49, 49, 51, 53, 55, 55, 54, 51, 49, 51, 54, 59, 63, 
67, 74, 80, 85, 89, 91, 93, 92, 89, 85, 77, 70, 63, 59, 55, 50, 
46, 41, 29, 19, 8, -4, -17, -28, -41, -43, -42, -41, -40, -49, -58, -67, 
-72, -75, -75, -76, -75, -70, -57, -37, -17, 6, 14, 19, 23, 27, 37, 46, 
58, 73, 87, 98, 101, 98, 95, 95, 95, 91, 65, 38, 8, -21, -42, -58, 
-58, -52, -40, -26, -14, -7, -12, -22, -36, -49, -62, -79, -87, -89, -86, -78, 
-63, -53, -46, -43, -49, -62, -86, -96, -99, -97, -97, -100, -102, -97, -81, -60, 
-39, -17, -10, -9, -10, -13, -12, 1, 18, 38, 54, 67, 75, 70, 58, 40, 
20, -1, -24, -30, -25, -11, 9, 29, 51, 63, 69, 70, 65, 54, 50, 51, 
54, 59, 65, 72, 71, 64, 53, 41, 30, 15, 9, 6, 7, 9, 4, -8, 
-25, -43, -60, -76, -97, -106, -111, -112, -111, -111, -108, -101, -94, -93, -99, -116, 
-119, -118, -116, -113, -109, -91, -76, -67, -65, -67, -66, -52, -40, -29, -21, -16, 
-19, -33, -56, -82, -104, -116, -115, -110, -102, -91, -78, -63, -46, -42, -42, -47, 
-54, -67, -72, -71, -67, -59, -48, -33, -26, -21, -20, -22, -25, -29, -30, -27, 
-20, -8, 11, 20, 26, 28, 21, 8, -18, -33, -43, -48, -47, -41, -21, -6, 
4, 6, -3, -30, -47, -60, -68, -69, -62, -41, -27, -22, -24, -31, -35, -34, 
-35, -40, -46, -47, -38, -31, -26, -24, -22, -20, -21, -26, -33, -36, -35, -31, 
-31, -32, -31, -29, -26, -25, -28, -33, -37, -43, -50, -55, -51, -43, -33, -25, 
-15, -7, 5, 17, 25, 28, 24, 19, 14, 9, 2, -3, -10, -16, -23, -28, 
-33, -36, -38, -40, -45, -50, -55, -63, -68, -69, -68, -64, -61, -59, -57, -54, 
-49, -45, -41, -40, -38, -36, -33, -33, -35, -37, -38, -39, -40, -43, -45, -45, 
-44, -40, -34, -25, -19, -14, -12, -14, -17, -16, -13, -7, 0, };

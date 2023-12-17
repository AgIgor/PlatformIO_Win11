const unsigned int sampleRate = 22050;
const unsigned int sampleCount = 3818;
const signed char samples[] = {
0, 10, 20, 9, 14, 14, -3, 10, 36, 41, 38, 45, 23, 1, 13, 36,
37, 27, 25, 18, 20, 33, 37, 33, 44, 51, 42, 36, 42, 49, 35, 25, 
29, 36, 39, 23, -1, 0, 25, 28, -5, 5, 6, -28, -45, -20, -11, -23, 
-4, 9, -22, -58, -30, -11, -22, -37, -39, -40, -43, -50, -58, -60, -61, -65, 
-61, -55, -49, -46, -63, -65, -48, -43, -55, -51, -42, -57, -58, -47, -49, -50, 
-22, -13, -30, -55, -61, -44, -36, -28, -30, -48, -54, -27, -27, -38, -35, -33, 
-35, -14, 1, 2, -3, -11, -15, -5, 3, 14, 27, 23, -2, -1, 10, 19, 
23, 19, 3, 5, 19, 31, 28, 8, 15, 25, 23, 19, 22, 18, 15, 27, 
48, 61, 60, 51, 50, 52, 60, 76, 79, 63, 60, 72, 83, 84, 81, 75, 
65, 61, 66, 70, 66, 61, 60, 64, 66, 64, 64, 61, 55, 57, 68, 82, 
82, 82, 77, 66, 57, 67, 75, 74, 73, 75, 76, 69, 57, 52, 55, 55, 
51, 55, 56, 48, 37, 34, 39, 38, 32, 28, 28, 27, 29, 34, 32, 26, 
24, 29, 27, 22, 24, 27, 27, 32, 40, 41, 37, 35, 28, 27, 30, 28, 
25, 28, 30, 24, 21, 19, 15, 22, 27, 25, 24, 25, 22, 22, 24, 26, 
30, 29, 25, 27, 36, 41, 38, 32, 30, 27, 19, 13, 17, 21, 15, 15, 
17, 18, 19, 22, 23, 19, 18, 26, 32, 22, 21, 29, 30, 26, 26, 24, 
15, 10, 8, 1, -5, -5, -14, -30, -37, -39, -43, -44, -47, -58, -62, -52, 
-42, -46, -52, -59, -64, -56, -41, -47, -54, -48, -43, -55, -60, -51, -42, -42, 
-47, -53, -53, -49, -46, -46, -45, -42, -42, -43, -42, -38, -33, -36, -41, -41, 
-35, -24, -11, -14, -19, -19, -15, 3, 14, 11, 4, 3, 9, 22, 34, 39, 
39, 41, 46, 46, 47, 53, 59, 63, 59, 55, 56, 62, 65, 60, 54, 61, 
68, 69, 69, 67, 55, 52, 52, 48, 51, 64, 51, 37, 44, 50, 41, 34, 
39, 44, 46, 46, 49, 58, 54, 48, 54, 66, 68, 65, 57, 49, 55, 65, 
64, 69, 76, 73, 65, 66, 68, 59, 54, 51, 47, 62, 66, 48, 28, 27, 
30, 23, 36, 49, 37, 21, 19, 24, 26, 25, 19, 22, 49, 40, 11, 1, 
17, 26, 0, -10, -10, -14, -15, -9, -33, -52, -46, -46, -61, -49, -43, -63, 
-75, -70, -76, -77, -52, -46, -63, -65, -55, -66, -65, -54, -59, -75, -69, -70, 
-83, -82, -72, -81, -89, -71, -73, -94, -96, -99, -124, -124, -105, -105, -110, -89, 
-87, -87, -82, -90, -100, -84, -75, -78, -87, -92, -74, -66, -68, -67, -71, -78, 
-57, -52, -67, -75, -82, -105, -98, -82, -92, -94, -84, -104, -107, -87, -81, -97, 
-111, -105, -91, -81, -76, -78, -82, -63, -45, -56, -79, -72, -27, -19, -29, -47, 
-52, -40, -40, -38, -26, -33, -53, -47, -18, -26, -28, -18, -15, -21, -19, -18, 
-23, -27, -12, 3, -23, -37, -16, 5, 0, -14, -15, -13, -6, -8, -24, -19, 
-17, -25, -26, -14, -10, -15, -10, -1, -3, -8, 3, -1, -4, 13, 22, -14, 
-4, 32, 34, 10, 7, 12, 13, 25, 26, 9, 4, 16, 12, 13, 25, 24, 
9, 12, 20, 31, 37, 32, 28, 37, 44, 38, 31, 33, 41, 46, 40, 30, 
39, 62, 56, 53, 55, 53, 57, 70, 55, 48, 72, 88, 69, 84, 105, 97, 
81, 86, 102, 105, 109, 106, 90, 82, 103, 101, 85, 81, 90, 91, 89, 85, 
71, 68, 81, 76, 64, 69, 71, 64, 68, 87, 78, 60, 57, 64, 64, 59, 
52, 38, 26, 29, 32, 16, 7, 6, -2, -9, -11, -26, -40, -38, -29, -30, 
-34, -36, -35, -28, -21, -33, -38, -26, -12, -14, -24, -24, -18, -17, -15, -21, 
-43, -44, -35, -35, -44, -48, -48, -53, -53, -52, -60, -67, -57, -50, -50, -48, 
-44, -36, -27, -16, -14, -17, -13, -3, 0, 6, 10, 14, 24, 32, 28, 35, 
49, 47, 33, 41, 48, 44, 38, 31, 16, 23, 33, 30, 27, 31, 30, 23, 
24, 28, 31, 40, 40, 33, 36, 49, 52, 55, 67, 72, 67, 68, 77, 79, 
72, 66, 60, 58, 69, 78, 73, 58, 53, 57, 53, 52, 53, 46, 44, 60, 
53, 37, 33, 36, 32, 37, 38, 24, 12, 14, 19, 17, 7, -7, -16, -15, 
-2, -5, -19, -24, -13, -5, -13, -15, -15, -19, -18, -7, -5, -8, -9, -15, 
-15, -3, -8, -18, -17, -9, -7, -19, -28, -32, -25, -17, -19, -27, -27, -19, 
-6, 1, -16, -22, -9, 5, 11, 14, 12, 10, 19, 30, 31, 31, 39, 39, 
47, 63, 64, 50, 60, 76, 82, 78, 70, 62, 71, 85, 86, 77, 77, 87, 
81, 70, 65, 66, 71, 74, 72, 60, 53, 58, 56, 48, 45, 43, 41, 45, 
47, 34, 27, 29, 29, 34, 36, 32, 28, 31, 33, 23, 14, 6, 4, 6, 
1, -15, -23, -30, -36, -38, -53, -65, -64, -56, -60, -70, -69, -66, -63, -53, 
-46, -46, -44, -35, -28, -27, -33, -36, -25, -14, -19, -32, -40, -40, -36, -42, 
-57, -62, -55, -62, -72, -73, -64, -53, -42, -47, -52, -41, -24, -19, -24, -21, 
-12, -3, 2, 1, 0, 2, -2, -18, -24, -1, -11, -39, -41, -19, -18, -49, 
-54, -61, -72, -61, -23, -31, -55, -69, -66, -54, -42, -44, -39, -29, -35, -53, 
-54, -50, -59, -58, -33, -27, -63, -87, -79, -69, -80, -83, -57, -43, -60, -88, 
-102, -97, -85, -76, -81, -86, -69, -72, -84, -89, -89, -85, -56, -52, -74, -87, 
-78, -69, -78, -89, -91, -79, -70, -89, -100, -97, -87, -84, -95, -105, -103, -98, 
-93, -91, -90, -87, -89, -92, -82, -67, -76, -70, -56, -61, -60, -48, -65, -66, 
-58, -62, -56, -43, -68, -76, -64, -68, -74, -55, -61, -69, -65, -60, -49, -47, 
-63, -43, -8, -15, -38, -18, -10, -12, 2, 9, 2, 23, 32, 12, 2, 12, 
14, 14, 20, 22, 18, 14, 12, 15, 25, 28, 24, 29, 30, 22, 26, 37, 
32, 29, 46, 48, 39, 44, 44, 33, 40, 52, 48, 46, 60, 62, 64, 61, 
52, 55, 67, 58, 56, 69, 71, 58, 66, 77, 73, 59, 52, 62, 63, 56, 
48, 43, 45, 67, 61, 44, 47, 58, 59, 63, 57, 50, 61, 73, 65, 67, 
70, 72, 81, 84, 71, 79, 80, 66, 62, 66, 57, 55, 59, 64, 71, 60, 
48, 53, 62, 58, 53, 62, 67, 70, 68, 59, 58, 64, 66, 60, 50, 50, 
54, 36, 19, 17, 25, 30, 6, -12, -6, 10, 0, -27, -24, -17, -12, -13, 
-27, -25, -9, -14, -27, -25, -17, -15, -20, -29, -28, -18, -28, -34, -25, -24, 
-36, -39, -37, -44, -46, -47, -49, -46, -48, -57, -53, -43, -42, -51, -54, -54, 
-51, -44, -44, -47, -42, -37, -35, -36, -44, -42, -29, -20, -29, -38, -24, -13, 
-19, -29, -30, -19, -5, -11, -18, -17, -15, -19, -18, -16, -13, -8, -8, -7, 
6, 14, 10, 8, 17, 21, 17, 18, 22, 26, 32, 31, 27, 26, 34, 35, 
16, 13, 16, 19, 23, 27, 19, 12, 15, 20, 25, 30, 25, 25, 36, 46, 
50, 61, 65, 61, 58, 64, 69, 68, 70, 69, 64, 62, 63, 59, 55, 52, 
48, 45, 44, 39, 36, 38, 39, 37, 37, 34, 36, 46, 46, 23, 25, 39, 
43, 35, 33, 42, 39, 33, 36, 41, 39, 39, 40, 42, 51, 55, 44, 49, 
58, 58, 57, 62, 59, 52, 58, 70, 72, 66, 62, 66, 68, 57, 44, 45, 
50, 49, 44, 36, 33, 37, 35, 33, 36, 35, 28, 35, 41, 35, 33, 39, 
40, 35, 33, 33, 30, 25, 23, 24, 20, 14, 14, 12, 4, -2, -3, -3, 
-1, -11, -17, -13, -11, -19, -24, -26, -35, -43, -42, -46, -59, -58, -55, -59, 
-66, -67, -65, -69, -74, -79, -83, -84, -75, -72, -79, -86, -85, -81, -81, -84, 
-91, -98, -99, -95, -103, -115, -117, -112, -113, -119, -120, -123, -127, -126, -123, -124, 
-121, -118, -119, -118, -108, -104, -107, -109, -105, -100, -93, -93, -95, -94, -90, -86, 
-89, -88, -83, -81, -82, -80, -80, -80, -76, -72, -71, -66, -65, -66, -64, -60, 
-62, -63, -59, -53, -48, -47, -48, -44, -37, -34, -34, -33, -26, -19, -13, -9, 
-5, 4, 8, 11, 16, 19, 20, 21, 22, 23, 25, 25, 22, 17, 19, 20, 
16, 13, 15, 17, 17, 17, 20, 23, 28, 31, 33, 35, 36, 39, 42, 46, 
52, 53, 50, 51, 50, 48, 47, 44, 40, 44, 44, 36, 29, 28, 31, 27, 
21, 20, 20, 19, 19, 17, 13, 12, 12, 11, 11, 9, 7, 7, 6, 1, 
2, 5, 5, 4, 2, 1, 5, 9, 9, 9, 10, 11, 12, 11, 10, 10, 
13, 12, 9, 8, 8, 9, 8, 6, 4, 2, 3, 5, 1, -1, -2, -1, 
3, 7, 6, 7, 9, 12, 15, 18, 16, 18, 23, 28, 30, 29, 30, 32, 
35, 36, 36, 36, 37, 36, 36, 40, 41, 39, 38, 38, 37, 35, 34, 32, 
33, 38, 38, 25, 18, 18, 20, 23, 23, 15, 11, 15, 20, 18, 12, 11, 
14, 16, 21, 22, 12, 13, 20, 22, 17, 13, 10, 10, 9, 3, -5, -2, 
4, -4, -13, -14, -14, -16, -19, -18, -11, -6, -9, -15, -13, -9, -6, -5, 
-8, -5, 5, 12, 13, 13, 16, 23, 30, 31, 27, 30, 42, 45, 48, 48, 
45, 42, 43, 41, 42, 51, 54, 43, 46, 54, 54, 46, 43, 51, 58, 61, 
58, 57, 62, 65, 65, 62, 66, 76, 79, 76, 77, 78, 84, 93, 94, 95, 
102, 101, 89, 89, 93, 94, 97, 94, 86, 90, 93, 85, 80, 81, 84, 91, 
82, 67, 70, 81, 65, 58, 61, 60, 59, 63, 62, 63, 66, 65, 58, 53, 
57, 57, 52, 50, 54, 48, 38, 33, 27, 23, 31, 21, 0, -1, 5, -2, 
-8, -5, -13, -19, -17, -21, -37, -38, -37, -40, -42, -42, -50, -55, -51, -47, 
-52, -54, -50, -51, -50, -53, -63, -66, -59, -58, -61, -65, -70, -67, -72, -86, 
-86, -74, -75, -85, -86, -89, -84, -76, -93, -94, -79, -77, -88, -89, -82, -77, 
-70, -73, -82, -77, -59, -58, -62, -62, -58, -46, -43, -48, -54, -49, -38, -44, 
-52, -44, -34, -37, -36, -32, -33, -28, -23, -26, -20, -10, -7, -8, -3, 2, 
9, 13, 13, 13, 16, 20, 26, 28, 26, 26, 30, 38, 37, 32, 36, 46, 
48, 47, 52, 50, 49, 58, 57, 49, 57, 62, 49, 41, 52, 47, 43, 45, 
41, 33, 39, 34, 22, 23, 31, 28, 27, 25, 22, 30, 38, 26, 23, 33, 
39, 36, 32, 32, 34, 33, 27, 18, 11, 13, 15, 10, 0, -5, -10, -14, 
-16, -21, -28, -27, -21, -31, -36, -26, -25, -28, -13, -9, -26, -33, -25, -25, 
-24, -23, -31, -32, -20, -26, -45, -48, -39, -36, -47, -55, -54, -45, -39, -42, 
-49, -46, -46, -48, -44, -40, -37, -40, -51, -55, -40, -32, -47, -49, -40, -43, 
-56, -59, -54, -49, -49, -57, -60, -56, -59, -56, -50, -58, -74, -69, -64, -67, 
-70, -69, -67, -72, -73, -66, -68, -85, -81, -75, -83, -86, -78, -82, -83, -73, 
-75, -96, -101, -77, -89, -106, -100, -91, -104, -96, -86, -99, -108, -98, -100, -104, 
-93, -87, -94, -95, -85, -83, -86, -94, -96, -70, -70, -89, -94, -77, -68, -83, 
-77, -63, -68, -78, -69, -58, -70, -69, -54, -51, -52, -36, -34, -46, -43, -28, 
-21, -26, -26, -21, -9, 3, -5, -5, 6, 14, 13, 17, 20, 24, 32, 36, 
32, 37, 45, 48, 48, 52, 57, 60, 61, 65, 69, 71, 76, 74, 72, 80, 
88, 85, 81, 86, 90, 90, 88, 86, 93, 93, 89, 92, 98, 97, 99, 100, 
99, 102, 106, 101, 102, 104, 103, 103, 106, 100, 99, 107, 109, 103, 99, 102, 
103, 99, 98, 99, 95, 92, 92, 94, 93, 86, 76, 79, 80, 74, 67, 65, 
63, 61, 65, 61, 48, 43, 45, 40, 30, 26, 26, 23, 17, 12, 9, 6, 
5, 5, 4, 2, -3, -9, -7, -6, -15, -23, -21, -18, -19, -22, -31, -41, 
-41, -37, -39, -40, -42, -46, -47, -50, -57, -60, -55, -52, -54, -57, -60, -59, 
-55, -54, -55, -53, -51, -47, -43, -41, -45, -45, -40, -36, -37, -37, -35, -32, 
-28, -29, -33, -34, -31, -27, -28, -29, -29, -27, -25, -23, -21, -24, -28, -25, 
-23, -19, -17, -22, -23, -16, -13, -18, -19, -12, -3, -3, -4, -7, -7, 1, 
3, 3, 3, 0, -6, -10, -9, -11, -14, -13, -12, -12, -9, -12, -16, -11, 
-4, -7, -7, -6, -3, 0, 3, 0, 0, 5, 7, 5, 10, 9, 4, 6, 
14, 13, 9, 11, 13, 10, 9, 9, 7, 6, 6, 7, 8, 10, 15, 20, 
19, 17, 23, 29, 32, 35, 41, 45, 46, 50, 55, 55, 54, 57, 58, 58, 
60, 61, 63, 69, 70, 69, 67, 67, 68, 73, 76, 76, 76, 77, 77, 74, 
72, 73, 78, 81, 76, 77, 82, 85, 84, 82, 82, 81, 80, 79, 78, 81, 
81, 75, 73, 76, 74, 62, 60, 59, 56, 54, 51, 42, 40, 37, 31, 25, 
16, 11, 9, 5, -2, -3, -3, -8, -11, -9, -10, -15, -15, -16, -22, -27, 
-29, -33, -39, -43, -45, -47, -50, -54, -58, -65, -69, -69, -70, -74, -74, -75, 
-75, -74, -78, -80, -81, -82, -82, -81, -82, -83, -82, -82, -85, -87, -89, -89, 
-87, -85, -86, -91, -95, -96, -93, -90, -90, -89, -86, -82, -80, -79, -77, -72, 
-68, -65, -62, -59, -56, -58, -61, -59, -51, -45, -47, -47, -39, -31, -30, -37, 
-35, -25, -26, -28, -20, -13, -22, -25, -18, -13, -10, -7, -5, 0, 4, 2, 
-3, 1, 6, 5, 10, 21, 3, -15, -3, 12, 2, -6, 26, 26, 7, -4, 
-11, -7, 13, 15, 2, 3, 14, -3, -7, 1, -8, -23, -15, 8, 3, -4, 
-12, -19, 0, 12, 4, -7, -8, -2, -10, -11, 3, 7, -4, -2, 7, -14, 
-27, -15, -6, -19, -23, -22, -20, -25, -36, -31, -30, -32, -24, -30, -40, -9, 
-29, -55, -25, -2, -30, -11, 2, -34, -52, -23, -13, -21, -18, -29, -39, -24, 
-9, -25, -27, -7, -8, -47, -28, 0, -11, -30, -28, -38, -27, 4, -8, -48, 
-43, -25, -27, -4, -4, -42, -29, -3, -13, -16, -1, -1, -8, -16, -25, -3, 
16, -9, -24, -6, -6, -9, -7, -22, -22, -19, -29, -27, -14, -34, -32, -12, 
-11, -14, -8, -18, -25, -19, -23, -29, -8, -2, -8, -13, -22, -23, -8, -22, 
-38, -30, -15, -11, -9, -18, -25, -8, 12, -1, -2, 15, 20, 11, 14, 31, 
34, 41, 43, 35, 39, 49, 48, 44, 42, 40, 42, 54, 59, 50, 42, 44, 
48, 56, 68, 65, 54, 69, 81, 76, 69, 71, 72, 80, 90, 87, 82, 90, 
98, 85, 82, 92, 98, 97, 98, 99, 98, 96, 96, 89, 74, 78, 86, 85, 
79, 77, 77, 74, 70, 71, 78, 79, 69, 68, 77, 83, 84, 77, 73, 79, 
86, 80, 73, 76, 69, 63, 71, 79, 69, 62, 56, 52, 52, 51, 40, 39, 
44, 40, 20, 15, 36, 31, 20, 16, 11, 13, 24, 20, 8, 11, 14, 0, 
12, 17, 2, -5, 2, -1, -7, -6, -4, -3, -18, -30, -24, -16, -24, -37, 
-34, -33, -40, -46, -45, -47, -54, -51, -48, -50, -49, -49, -48, -42, -46, -59, 
-50, -18, -33, -49, -45, -42, -39, -37, -42, -40, -38, -50, -54, -42, -46, -61, 
-64, -60, -54, -47, -52, -58, -51, -43, -45, -42, -38, -37, -37, -29, -20, -18, 
-28, -36, -29, -27, -31, -27, -20, -17, -23, -26, -12, 2, -4, -11, -1, -3, 
-6, 1, 4, 5, 23, 19, 9, 15, 23, 14, 17, 34, 47, 40, 27, 37, 
38, 32, 42, 62, 63, 47, 47, 46, 48, 54, 51, 56, 68, 66, 55, 56, 
69, 62, 55, 62, 72, 66, 49, 52, 59, 60, 62, 76, 72, 62, 59, 65, 
71, 65, 65, 72, 75, 68, 56, 55, 60, 59, 52, 43, 45, 45, 41, 38, 
36, 33, 32, 31, 28, 23, 20, 20, 32, 34, 29, 32, 40, 27, 23, 27, 
29, 32, 39, 30, 25, 29, 26, 18, 19, 17, 11, 12, 10, 0, -9, -14, 
-16, -7, -7, -22, -22, -17, -23, -26, -19, -26, -37, -37, -35, -41, -47, -38, 
-26, -23, -30, -37, -44, -42, -38, -45, -52, -43, -31, -42, -47, -44, -54, -67, 
-53, -44, -52, -67, -82, -84, -67, -72, -74, -63, -64, -82, -70, -67, -86, -83, 
-56, -72, -92, -77, -64, -78, -86, -68, -72, -81, -82, -78, -80, -85, -87, -89, 
-89, -84, -79, -85, -81, -75, -90, -111, -86, -65, -69, -80, -83, -79, -82, -84, 
-81, -81, -87, -81, -77, -88, -93, -83, -75, -85, -86, -82, -82, -88, -79, -69, 
-79, -93, -82, -60, -63, -73, -75, -70, -65, -65, -59, -50, -50, -51, -39, -48, 
-63, -39, -14, -31, -47, -19, -24, -39, -24, -2, -3, -20, -15, -1, 9, 7, 
6, 7, 10, 22, 22, 8, 24, 38, 32, 28, 33, 35, 43, 49, 43, 38, 
47, 59, 52, 44, 47, 60, 62, 54, 61, 63, 60, 58, 54, 62, 71, 62, 
52, 63, 76, 65, 55, 55, 61, 69, 65, 58, 59, 59, 58, 60, 50, 48, 
58, 61, 52, 47, 47, 45, 40, 38, 42, 43, 35, 34, 38, 35, 32, 35, 
27, 22, 32, 34, 18, 22, 27, 22, 16, 19, 19, 13, 16, 20, 14, 6, 
15, 17, 11, 13, 20, 15, 13, 21, 25, 19, 15, 20, 22, 22, 20, 19, 
21, 19, 15, 16, 18, 18, 11, 11, 15, 18, 14, 10, 13, 16, 18, 19, 
13, 12, 20, 18, 13, 13, 15, 17, 18, 12, 5, 7, 11, 4, 3, 7, 
10, 10, 2, -2, 2, 10, 6, -3, 2, 9, 6, 2, 4, 7, 6, 4, 
1, -1, 1, -8, -16, -12, -9, -16, -20, -12, -20, -27, -24, -23, -27, -22, 
-20, -28, -34, -29, -22, -25, -29, -29, -27, -27, -24, -25, -29, -26, -19, -22, 
-23, -17, -14, -18, -16, -9, -5, -4, -6, -5, -1, 4, 4, 6, 4, -2, 
3, 4, -2, -2, 9, 14, 8, 10, 12, 14, 20, 27, 26, 26, 33, 39, 
39, 39, 45, 50, 51, 52, 55, 54, 56, 60, 61, 55, 50, 48, 50, 54, 
55, 49, 44, 48, 52, 52, 48, 46, 52, 53, 52, 52, 50, 50, 54, 54, 
51, 46, 45, 43, 40, 43, 48, 46, 44, 49, 47, 44, 46, 44, 41, 49, 
46, 36, 34, 39, 35, 31, 33, 29, 22, 26, 33, 23, 19, 26, 25, 16, 
19, 24, 18, 13, 18, 21, 14, 12, 14, 13, 13, 12, 5, 3, 7, 7, 
3, 0, -4, -8, -7, -5, -12, -15, -12, -10, -13, -18, -21, -21, -19, -16, 
-17, -18, -14, -16, -17, -17, -20, -16, -9, -10, -13, -10, -7, -11, -9, -8, 
-11, -13, -10, -13, -16, -17, -20, -23, -20, -20, -24, -26, -22, -22, -25, -18, 
-16, -25, -30, -20, -22, -24, -19, -19, -21, -15, -20, -29, -30, -26, -24, -25, 
-36, -48, -40, -23, -32, -50, -53, -45, -41, -44, -50, -54, -57, -55, -49, -52, 
-62, -58, -51, -50, -51, -56, -65, -62, -50, -46, -54, -59, -61, -65, -59, -54, 
-66, -87, -74, -59, -58, -68, -81, -75, -56, -44, -54, -71, -74, -59, -41, -38, 
-50, -52, -33, -40, -51, -49, -45, -47, -45, -46, -56, -64, -53, -29, -43, -61, 
-46, -15, -17, -46, -44, -39, -37, -37, -57, -53, -21, 1, -9, -25, -35, -34, 
-17, -1, -18, -57, -61, -26, -1, -9, -40, -45, -12, 9, -3, -35, -62, -39, 
-9, -17, -54, -73, -55, -16, -25, -61, -84, -71, -39, -36, -57, -97, -110, -72, 
-39, -73, -101, -93, -71, -52, -54, -67, -83, -85, -61, -39, -71, -98, -85, -50, 
-32, -66, -93, -86, -53, -29, -59, -90, -87, -61, -43, -52, -86, -83, -44, 0, 
1, -37, -66, -36, 5, 19, 1, -17, 3, 28, 42, 34, 12, 3, 31, 59, 
57, 29, 14, 46, 66, 64, 52, 42, 46, 73, 87, 67, 47, 56, 77, 84, 
89, 80, 70, 82, 98, 90, 78, 62, 59, 94, 99, 81, 64, 54, 54, 84, 
91, 73, 59, 68, 81, 71, 48, 37, 50, 73, 75, 55, 45, 53, 66, 68, 
44, 29, 30, 42, 53, 55, 42, 31, 32, 46, 56, 44, 31, 25, 28, 40, 
50, 39, 31, 37, 43, 40, 37, 33, 20, 23, 43, 42, 12, 15, 23, 24, 
20, 13, 13, 33, 39, 17, 6, 17, 19, 12, 10, 0, -4, 23, 25, 11, 
3, 3, 2, 14, 16, 4, -2, 10, 30, 27, 20, 17, 18, 18, 18, 20, 
21, 16, 6, 3, 2, 0, -1, -8, -18, -18, -12, -15, -21, -22, -22, -22, 
-21, -20, -21, -22, -23, -22, -26, -32, -32, -25, -26, -35, -36, -27, -25, -32, 
-33, -32, -40, -48, -44, -36, -41, -49, -49, -36, -20, -22, -39, -43, -32, -22, 
-24, -34, -41, -43, -36, -28, -27, -31, -36, -38, -32, -27, -30, -22, -14, -16, 
-13, -3, -1, 3, 14, 16, 9, 13, 28, 26, 28, 33, 32, 29, 39, 48, 
48, 45, 51, 63, 62, 60, 58, 60, 70, 86, 85, 81, 82, 88, 106, 111, 
101, 92, 102, 118, 120, 112, 106, 104, 111, 120, 108, 90, 88, 101, 110, 97, 
83, 85, 102, 117, 116, 96, 94, 107, 122, 121, 103, 84, 98, 118, 122, 107, 
83, 87, 98, 102, 91, 76, 70, 75, 78, 69, 49, 36, 44, 46, 38, 27, 
17, 10, 10, 3, -8, -13, -9, -5, -11, -23, -34, -33, -26, -35, -48, -55, 
-51, -39, -36, -46, -51, -47, -42, -44, -50, -53, -54, -54, -52, -54, -58, -57, 
-50, -44, -44, -59, -64, -56, -45, -44, -54, -69, -68, -60, -56, -57, -49, -40, 
-35, -32, -31, -36, -40, -35, -34, -41, -45, -43, -44, -51, -54, -53, -53, -53, 
-55, -59, -58, -55, -55, -54, -55, -61, -68, -70, -69, -64, -66, -68, -63, -59, 
-66, -71, -75, -80, -81, -81, -91, -93, -88, -83, -83, -89, -98, -100, -97, -91, 
-94, -106, -101, -94, -98, -100, -97, -99, -94, -83, -86, -98, -98, -89, -88, -84, 
-75, -66, -65, -62, -57, -65, -80, -72, -47, -60, -74, -76, -82, -80, -51, -53, 
-64, -61, -54, -51, -38, -29, -36, -33, -10, 0, };

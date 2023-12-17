const unsigned int knockSampleRate = 22050;
const unsigned int knockSampleCount = 1617;
const signed char knockSamples[] = {
0, 3, 9, 4, 4, 5, 5, 10, 12, 13, 20, 25, 23, 23, 15, 6,
3, -5, 1, 10, 11, 18, 24, 29, 31, 22, 16, 18, 12, 3, 7, 0, 
-10, -14, -21, -22, -18, -16, -10, -4, -7, 1, 13, 16, 23, 34, 33, 36, 
34, 21, 16, 6, -5, -4, -9, -19, -20, -27, -34, -40, -49, -47, -35, -20, 
-6, 1, 0, 10, 24, 24, 28, 30, 27, 31, 27, 23, 22, 13, 12, 28, 
41, 49, 58, 56, 55, 55, 44, 45, 46, 38, 45, 52, 45, 49, 45, 41, 
54, 57, 56, 58, 51, 48, 49, 44, 52, 61, 61, 68, 73, 66, 67, 68, 
68, 78, 83, 78, 77, 72, 69, 81, 83, 90, 101, 108, 119, 127, 126, 127, 
126, 126, 127, 121, 115, 111, 99, 88, 71, 58, 55, 54, 46, 41, 43, 39, 
44, 50, 51, 64, 66, 63, 68, 73, 68, 63, 54, 40, 31, 20, 13, 8, 
-4, -10, -11, -10, -4, -9, -18, -22, -24, -23, -8, 0, 8, 17, 15, 11, 
18, 16, 24, 32, 27, 31, 28, 12, 5, -2, -18, -28, -43, -60, -62, -65, 
-76, -71, -75, -84, -81, -77, -68, -54, -50, -45, -35, -30, -15, -12, -14, -12, 
-14, -21, -20, -22, -26, -23, -24, -24, -13, -12, -18, -20, -26, -20, -9, -11, 
-3, 12, 14, 21, 21, 12, 14, 14, 10, 20, 22, 17, 16, 13, 25, 34, 
30, 33, 39, 34, 46, 54, 57, 73, 82, 75, 78, 71, 58, 52, 48, 47, 
52, 46, 36, 33, 21, 1, -3, -12, -14, -14, -26, -24, -24, -29, -28, -20, 
-10, 0, 11, 20, 26, 25, 28, 30, 29, 28, 31, 34, 39, 44, 46, 50, 
54, 53, 54, 52, 49, 47, 27, 23, 32, 38, 42, 48, 42, 38, 39, 36, 
30, 27, 10, 0, 1, -3, -8, -12, -17, -17, -15, -12, -6, -2, -3, -4, 
-8, -12, -18, -27, -26, -23, -24, -25, -23, -24, -22, -18, -8, 2, -2, -6, 
-7, -2, 0, -1, -8, -13, -16, -18, -22, -25, -32, -41, -45, -45, -38, -27, 
-20, -15, -17, -16, -12, -20, -28, -34, -40, -37, -36, -42, -41, -45, -57, -69, 
-78, -79, -77, -78, -86, -95, -102, -105, -106, -109, -109, -101, -97, -85, -68, -56, 
-47, -42, -41, -35, -34, -39, -37, -35, -38, -36, -27, -23, -27, -26, -21, -14, 
-17, -26, -18, -16, -11, -5, -14, -23, -27, -29, -29, -29, -31, -33, -29, -20, 
-11, -11, -19, -27, -30, -29, -24, -17, -12, -3, 1, 4, 11, 2, -11, -8, 
-12, -12, -9, -15, -16, -13, -12, -6, -4, -15, -13, -9, -6, 1, 5, 6, 
16, 21, 22, 24, 14, -12, -29, -39, -41, -41, -23, -15, -17, -8, 7, 8, 
9, 16, 21, 35, 49, 46, 45, 49, 49, 58, 66, 68, 71, 67, 61, 61, 
58, 43, 36, 27, 21, 21, 16, 11, 7, -3, -7, -9, -21, -24, -34, -45, 
-45, -50, -67, -66, -68, -74, -72, -67, -65, -60, -61, -57, -46, -46, -44, -37, 
-34, -28, -18, 0, 13, 19, 14, 8, 10, 19, 25, 35, 44, 45, 37, 32, 
29, 26, 26, 28, 21, 14, 7, 5, 6, 3, 5, 13, 7, -2, -1, -17, 
-29, -36, -48, -53, -50, -51, -46, -50, -61, -62, -58, -54, -45, -43, -44, -37, 
-25, -27, -27, -26, -28, -22, -13, -8, -2, -9, -17, -13, -14, -9, -2, -3, 
-4, 3, 7, 17, 19, 10, 6, 5, 7, 6, 2, 2, 7, 8, 11, 14, 
9, 2, -4, -13, -23, -33, -39, -35, -32, -31, -24, -17, -11, -2, 4, 15, 
27, 33, 43, 54, 53, 59, 55, 43, 42, 45, 44, 46, 46, 46, 40, 30, 
26, 21, 13, 11, 9, 4, 3, -3, -12, -16, -23, -30, -33, -41, -54, -64, 
-70, -66, -61, -57, -47, -31, -31, -31, -31, -32, -32, -20, -5, 10, 22, 35, 
45, 46, 43, 35, 31, 37, 33, 27, 35, 45, 48, 47, 39, 41, 41, 28, 
18, 15, 5, -6, -14, -23, -32, -43, -56, -71, -84, -87, -85, -86, -86, -83, 
-82, -81, -81, -81, -79, -77, -73, -64, -58, -52, -42, -40, -38, -33, -30, -29, 
-24, -14, -9, -8, -1, 1, -3, -3, 1, 11, 20, 31, 38, 41, 42, 37, 
34, 31, 22, 10, -4, -13, -19, -19, -21, -28, -33, -29, -26, -27, -28, -27, 
-22, -12, -8, -12, -16, -21, -26, -24, -24, -26, -21, -16, -19, -17, -18, -22, 
-12, -9, -6, -2, 1, 7, 18, 21, 23, 25, 20, 14, 4, 3, 7, 9, 
7, 4, 7, 16, 14, 3, -2, -7, -11, -13, -15, -13, -8, -10, -6, 3, 
4, 3, 10, 8, 12, 14, 7, 1, -13, -25, -29, -32, -34, -36, -30, -27, 
-29, -29, -27, -24, -20, -14, -10, -5, -2, -8, -8, -5, -2, -2, -10, -23, 
-19, -16, -19, -21, -16, -9, -2, 0, -3, -8, -7, -7, -10, -10, -16, -32, 
-46, -44, -49, -56, -59, -54, -47, -40, -32, -20, -8, 2, 15, 26, 23, 23, 
33, 39, 38, 35, 32, 32, 23, 19, 22, 23, 21, 22, 20, 18, 19, 19, 
15, 15, 27, 32, 34, 33, 34, 33, 25, 19, 13, 3, -8, -25, -36, -45, 
-47, -45, -44, -47, -51, -46, -38, -38, -43, -48, -49, -44, -45, -43, -36, -37, 
-41, -45, -47, -40, -28, -20, -6, 10, 18, 27, 29, 38, 48, 50, 55, 64, 
66, 74, 80, 76, 75, 69, 58, 58, 55, 44, 39, 29, 18, 14, 8, 0, 
4, -6, -13, -10, -11, -12, -13, -9, 1, 2, -2, 6, 3, 1, 7, 9, 
12, 17, 13, 20, 32, 33, 39, 45, 52, 68, 81, 81, 89, 92, 93, 102, 
102, 92, 78, 67, 58, 54, 46, 39, 38, 26, 17, 8, -5, -5, -9, -14, 
-14, -22, -28, -18, -16, -11, -4, -3, 2, 1, -11, -22, -33, -45, -53, -56, 
-54, -50, -51, -50, -33, -28, -26, -23, -24, -9, 12, 23, 35, 53, 63, 68, 
73, 76, 77, 74, 68, 67, 64, 58, 56, 51, 44, 40, 35, 31, 30, 32, 
32, 31, 26, 20, 16, 8, 1, -3, -1, 1, -1, -5, -3, 4, 16, 28, 
40, 59, 68, 78, 82, 84, 90, 86, 80, 73, 70, 73, 66, 66, 70, 68, 
65, 63, 64, 59, 50, 45, 44, 34, 30, 32, 32, 32, 31, 23, 19, 19, 
20, 24, 31, 50, 60, 69, 73, 74, 72, 67, 68, 76, 79, 75, 69, 66, 
63, 60, 58, 60, 54, 43, 43, 44, 33, 22, 18, 11, 14, 19, 17, 9, 
-2, -13, -22, -26, -24, -23, -28, -33, -35, -36, -38, -40, -43, -41, -41, -43, 
-42, -41, -48, -53, -50, -44, -34, -30, -30, -31, -28, -31, -39, -37, -33, -33, 
-26, -22, -21, -23, -30, -35, -45, -67, -74, -75, -73, -74, -75, -77, -83, -83, 
-79, -77, -74, -74, -77, -77, -75, -70, -64, -59, -54, -51, -49, -49, -41, -32, 
-29, -25, -23, -26, -32, -36, -35, -39, -35, -29, -28, -25, -19, -20, -28, -24, 
-21, -20, -18, -18, -10, -8, -9, -4, 0, -8, -7, -10, -21, -27, -32, -45, 
-50, -61, -76, -85, -94, -95, -89, -90, -93, -92, -98, -92, -78, -64, -46, -32, 
-25, -14, 0, 8, 18, 26, 28, 32, 27, 20, 22, 27, 35, 43, 52, 65, 
74, 83, 86, 82, 80, 82, 80, 69, 63, 64, 65, 60, 51, 45, 35, 26, 
20, 11, -1, -1, 3, 8, 9, 5, 5, 1, -9, -11, -10, -2, 5, 8, 
14, 22, 32, 51, 58, 67, 80, 81, 75, 76, 71, 67, 68, 62, 55, 50, 
42, 42, 46, 45, 50, 48, 45, 43, 36, 30, 30, 26, 28, 39, 42, 48, 
57, 57, 57, 58, 53, 48, 43, 36, 41, 50, 50, 51, 50, 49, 47, 41, 
31, 20, 10, 4, -4, -16, -35, -40, -42, -43, -40, -49, -60, -66, -70, -65, 
-53, -45, -40, -44, -54, -56, -58, -74, -83, -84, -81, -75, -63, -61, -60, -59, 
-52, -35, -17, -7, 5, 8, 17, 30, 33, 34, 27, 11, 1, -14, -25, -32, 
-42, -43, -37, -47, -56, -64, -74, -78, -82, -93, -91, -85, -79, -79, -92, -99, 
-97, -95, -95, -89, -78, -70, -61, -58, -53, -50, -51, -45, -35, -25, -14, 0, 
2, 7, 14, 21, 29, 36, 38, 45, 52, 55, 63, 67, 67, 68, 68, 79, 
94, 92, 96, 91, 76, 69, 66, 61, 59, 53, 46, 44, 44, 49, 56, 55, 
53, 53, 44, 38, 44, 54, 61, 65, 68, 65, 57, 51, 47, 36, 32, 25, 
18, 14, 15, 19, 22, 20, 17, 18, 10, 6, 3, 1, 7, 18, 33, 35, 
35, 41, 48, 57, 61, 69, 80, 86, 89, 88, 88, 85, 76, 70, 64, 64, 
69, 64, 50, 38, 17, 12, 10, -3, -15, -19, -28, -32, -32, -35, -40, -54, 
-60, -55, -55, -53, -42, -35, -26, -17, -15, -14, -11, -6, 0, 2, -9, -26, 
-47, -52, -49, -47, -48, -48, -54, -60, -60, -61, -60, -54, -63, -68, -66, -71, 
-73, -69, -71, -65, -60, -71, -80, -74, -71, -62, -54, -51, -41, -32, -24, -11, 
-10, -12, -8, -7, -2, -1, -4, -5, -21, -33, -39, -44, -44, -37, -34, -32, 
-29, -32, -34, -39, -41, -39, -41, -44, -43, -41, -42, -40, -42, -49, -52, -57, 
-65, -68, -70, -71, -69, -73, -76, -78, -80, -79, -72, -68, -67, -65, -59, -49, 
-38, -38, -43, -45, -40, -34, -29, -26, -28, -30, -29, -31, -34, -37, -43, -47, 
-45, -45, -46, -49, -61, -70, -74, -75, -70, -72, -84, -96, -106, -50, -30, -15,
0, };

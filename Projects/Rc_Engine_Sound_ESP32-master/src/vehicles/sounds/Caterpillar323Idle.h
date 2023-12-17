const unsigned int sampleRate = 22050;
const unsigned int sampleCount = 3136;
const signed char samples[] = {//0
0, 3, 6, 8, 9, 10, 11, 13, 17, 20, 23, 26, 28, 27, 27, 25, //16
22, 19, 17, 16, 17, 19, 22, 29, 33, 39, 43, 49, 54, 60, 62, 63, //32
63, 62, 61, 59, 56, 53, 48, 43, 36, 33, 31, 30, 30, 31, 36, 41, //48
46, 53, 61, 72, 76, 78, 78, 77, 76, 71, 67, 63, 58, 55, 54, 55, //64
56, 56, 58, 59, 58, 56, 54, 52, 48, 42, 32, 24, 17, 13, 12, 13, //80
19, 25, 30, 35, 39, 45, 47, 46, 44, 42, 39, 38, 40, 42, 45, 48, //96
50, 51, 48, 44, 38, 29, 15, 7, -1, -6, -9, -12, -15, -17, -17, -15, //112
-13, -10, -7, -6, -6, -6, -8, -8, -7, -3, 1, 4, 7, 12, 13, 13, //128
10, 7, 5, 5, 6, 10, 17, 25, 38, 44, 48, 50, 48, 45, 37, 31, //144
24, 18, 11, 5, 4, 4, 5, 7, 7, 9, 7, 5, 0, -8, -16, -27, //160
-36, -43, -48, -54, -58, -58, -56, -50, -45, -39, -28, -23, -17, -13, -12, -12, //176
-16, -20, -24, -28, -31, -30, -27, -24, -20, -16, -11, -7, -5, -4, -4, -6, //192
-8, -13, -15, -15, -15, -12, -5, 0, 1, 1, 1, 1, 3, 6, 11, 16, //208
21, 26, 33, 35, 35, 35, 33, 26, 21, 16, 14, 15, 17, 21, 23, 25, //224
28, 32, 37, 43, 48, 54, 59, 63, 66, 63, 60, 56, 50, 44, 33, 28, //240
27, 29, 33, 38, 45, 47, 47, 45, 40, 25, 16, 8, 2, -1, -1, 0, //256
3, 8, 13, 19, 23, 27, 27, 24, 20, 16, 6, 1, -5, -14, -21, -27, //272
-35, -35, -33, -30, -25, -20, -10, 0, 10, 18, 27, 35, 37, 36, 30, 22, //288
10, -12, -27, -40, -50, -57, -56, -50, -43, -31, -18, -7, 7, 11, 8, 1, //304
-8, -20, -39, -54, -68, -80, -91, -104, -106, -104, -99, -90, -78, -59, -47, -37, //320
-30, -27, -26, -27, -30, -33, -36, -40, -41, -40, -38, -34, -27, -19, -6, 0, //336
2, 3, 4, 3, 2, -1, -2, -3, -3, 0, 3, 6, 11, 16, 22, 31, //352
36, 41, 45, 50, 54, 59, 57, 55, 50, 41, 29, 22, 14, 8, 2, -3, //368
-5, -3, -2, 2, 5, 5, 4, 1, -1, -3, -5, -7, -7, -7, -6, -6, //384
-5, -2, -1, 0, 3, 5, 7, 14, 17, 19, 20, 20, 20, 16, 9, 0, //400
-9, -15, -21, -24, -25, -26, -26, -25, -24, -22, -20, -17, -13, -5, -1, 4, //416
9, 13, 16, 18, 17, 13, 8, 1, -6, -13, -12, -8, -1, 9, 27, 36, //432
45, 51, 52, 50, 39, 27, 14, 1, -14, -30, -36, -37, -34, -28, -23, -17, //448
-15, -16, -17, -21, -27, -36, -42, -47, -51, -56, -61, -63, -65, -67, -69, -69, //464
-72, -73, -75, -76, -73, -69, -59, -54, -49, -48, -49, -55, -61, -67, -73, -78, //480
-83, -88, -86, -81, -74, -63, -51, -35, -23, -16, -12, -10, -14, -19, -26, -33, //496
-40, -45, -47, -44, -39, -33, -26, -21, -12, -8, -2, 6, 11, 16, 19, 19, //512
19, 19, 19, 20, 19, 18, 14, 9, 5, 0, -2, -4, -5, -7, -7, -5, //528
-3, -3, -3, -2, 1, 3, 3, 2, 1, 1, 1, 1, 2, 5, 11, 22, //544
30, 38, 44, 49, 52, 53, 50, 46, 40, 34, 29, 20, 16, 13, 13, 13, //560
13, 14, 13, 11, 10, 11, 13, 16, 19, 21, 24, 28, 32, 37, 40, 41, //576
38, 29, 20, 12, 6, 3, 2, 9, 17, 25, 33, 41, 49, 51, 49, 44, //592
39, 33, 25, 20, 14, 9, 5, 3, 2, 2, 3, 3, 3, 4, 4, 5, //608
7, 10, 13, 15, 14, 14, 15, 17, 20, 25, 28, 31, 33, 36, 37, 34, //624
32, 29, 22, 18, 15, 14, 15, 17, 20, 23, 31, 35, 37, 39, 41, 42, //640
44, 45, 46, 49, 53, 60, 64, 68, 70, 71, 70, 66, 62, 58, 54, 51, //656
49, 49, 49, 49, 51, 53, 52, 49, 42, 33, 24, 16, 7, 3, 0, -1, //672
-1, 3, 6, 10, 14, 18, 22, 28, 31, 36, 39, 40, 39, 36, 32, 29, //688
26, 22, 13, 7, 0, -8, -14, -19, -23, -24, -25, -24, -23, -22, -18, -14, //704
-9, -4, 2, 9, 13, 17, 20, 20, 17, 11, 5, -2, -10, -20, -30, -40, //720
-44, -46, -45, -43, -40, -39, -37, -36, -36, -36, -39, -43, -49, -55, -61, -70, //736
-74, -79, -82, -81, -78, -70, -63, -55, -46, -38, -32, -27, -27, -28, -29, -32, //752
-38, -44, -50, -55, -59, -61, -64, -65, -65, -65, -65, -66, -68, -70, -71, -70, //768
-71, -72, -73, -74, -73, -68, -64, -51, -42, -35, -29, -26, -24, -19, -15, -13, //784
-9, -5, 1, 5, 10, 14, 18, 22, 28, 31, 33, 36, 36, 36, 32, 30, //800
30, 31, 34, 42, 45, 46, 45, 41, 35, 24, 16, 8, 1, -4, -7, -9, //816
-8, -7, -3, 2, 8, 12, 14, 16, 18, 19, 20, 21, 23, 26, 26, 27, //832
30, 32, 37, 40, 43, 47, 49, 52, 54, 53, 50, 44, 39, 38, 38, 40, //848
46, 61, 71, 81, 89, 92, 92, 87, 78, 66, 52, 36, 15, 4, -3, -6, //864
-5, -1, 9, 17, 22, 26, 30, 30, 28, 25, 20, 17, 14, 11, 9, 10, //880
11, 11, 14, 14, 14, 15, 17, 21, 29, 33, 36, 37, 35, 29, 14, 1, //896
-12, -24, -33, -37, -36, -34, -29, -22, -13, -2, 4, 8, 7, 6, 3, -1, //912
-3, -4, -4, -1, 5, 10, 12, 12, 10, 5, -6, -13, -20, -26, -27, -25, //928
-20, -15, -9, -1, 5, 12, 14, 12, 7, 3, 0, -6, -9, -12, -15, -15, //944
-15, -15, -14, -13, -13, -13, -16, -20, -27, -32, -38, -43, -46, -45, -41, -35, //960
-28, -22, -13, -11, -11, -15, -22, -41, -55, -70, -83, -92, -96, -92, -86, -80, //976
-73, -67, -62, -60, -60, -65, -74, -82, -93, -98, -100, -100, -97, -92, -82, -75, //992
-69, -63, -60, -60, -59, -57, -55, -50, -46, -39, -34, -30, -24, -20, -17, -18, //1008
-20, -26, -31, -35, -41, -45, -45, -45, -45, -46, -46, -48, -49, -51, -56, -59, //1024
-61, -59, -56, -53, -49, -44, -39, -35, -31, -27, -22, -18, -17, -18, -21, -26, //1040
-31, -38, -41, -44, -46, -48, -50, -53, -55, -57, -56, -53, -48, -43, -36, -27, //1056
-17, -8, 3, 7, 9, 9, 8, 6, 2, -2, -6, -8, -10, -10, -8, -5, //1072
0, 7, 17, 33, 44, 53, 58, 62, 62, 61, 60, 57, 56, 55, 53, 54, //1088
57, 60, 62, 63, 61, 58, 55, 53, 51, 52, 53, 54, 58, 63, 66, 75, //1104
81, 87, 93, 97, 97, 93, 89, 86, 85, 85, 84, 84, 85, 85, 86, 87, //1120
84, 83, 81, 77, 76, 75, 74, 75, 79, 83, 88, 94, 94, 96, 95, 93, //1136
90, 81, 74, 67, 60, 54, 52, 49, 50, 51, 50, 48, 42, 37, 32, 26, //1152
22, 19, 15, 16, 17, 21, 28, 35, 46, 53, 58, 64, 69, 75, 75, 73, //1168
69, 63, 56, 44, 37, 30, 23, 18, 12, 9, 8, 9, 10, 11, 11, 10, //1184
10, 9, 9, 8, 9, 10, 11, 14, 17, 19, 19, 15, 9, 4, -4, -14, //1200
-21, -28, -33, -38, -42, -44, -45, -44, -41, -36, -25, -17, -10, -6, -2, 0, //1216
-5, -9, -15, -24, -32, -37, -46, -50, -51, -50, -46, -34, -25, -15, -7, -3, //1232
-1, -4, -9, -16, -20, -22, -21, -16, -10, -3, 3, 8, 13, 13, 11, 7, //1248
3, -2, -9, -13, -15, -18, -18, -16, -14, -12, -10, -10, -9, -6, -3, 1, //1264
4, 5, 7, 10, 12, 13, 13, 13, 13, 11, 11, 11, 11, 13, 16, 16, //1280
14, 10, 5, -1, -9, -14, -19, -23, -28, -32, -37, -37, -35, -30, -23, -13, //1296
-8, -4, -1, -1, 0, 1, 0, -1, -6, -11, -17, -31, -39, -47, -53, -54, //1312
-54, -51, -43, -36, -25, -12, 1, 10, 17, 18, 16, 8, 0, -9, -15, -21, //1328
-26, -30, -32, -31, -26, -21, -14, -6, -4, -3, -5, -9, -17, -22, -28, -32, //1344
-36, -40, -45, -47, -49, -52, -53, -52, -46, -41, -35, -29, -22, -14, -11, -11, //1360
-14, -20, -27, -42, -54, -66, -78, -86, -90, -91, -86, -81, -74, -65, -50, -41, //1376
-31, -25, -22, -18, -15, -12, -7, -4, 0, 5, 8, 10, 13, 13, 16, 19, //1392
18, 18, 16, 12, 7, -2, -6, -6, -7, -8, -5, 1, 8, 16, 22, 28, //1408
33, 33, 31, 26, 19, 14, 8, 5, 3, 1, 1, 4, 14, 22, 34, 46, //1424
54, 67, 71, 71, 71, 69, 65, 60, 53, 45, 38, 32, 28, 28, 28, 30, //1440
34, 36, 39, 38, 36, 35, 33, 28, 19, 12, 5, -1, -7, -11, -16, -18, //1456
-22, -28, -33, -39, -40, -40, -40, -39, -38, -38, -37, -37, -38, -38, -38, -38, //1472
-38, -39, -39, -38, -37, -36, -36, -36, -38, -40, -40, -38, -33, -28, -23, -18, //1488
-15, -14, -15, -15, -15, -17, -16, -14, -13, -13, -15, -20, -23, -25, -26, -26, //1504
-29, -32, -36, -40, -43, -45, -44, -42, -39, -37, -34, -33, -33, -34, -35, -37, //1520
-38, -41, -43, -45, -48, -50, -50, -48, -45, -43, -43, -45, -47, -49, -49, -48, //1536
-48, -47, -46, -48, -52, -56, -61, -66, -72, -74, -76, -75, -72, -66, -54, -43, //1552
-31, -22, -16, -12, -12, -12, -12, -13, -13, -11, -9, -7, -6, -7, -9, -13, //1568
-14, -13, -10, -7, -1, 5, 11, 16, 20, 23, 24, 24, 23, 20, 19, 19, //1584
20, 23, 26, 29, 32, 35, 37, 38, 40, 41, 38, 37, 34, 33, 33, 32, //1600
29, 26, 24, 23, 23, 25, 30, 36, 44, 53, 60, 65, 70, 70, 67, 61, //1616
53, 36, 24, 14, 5, 0, -2, 2, 7, 14, 23, 32, 39, 47, 51, 53, //1632
52, 49, 41, 35, 29, 23, 15, 9, 1, -2, -2, -1, 4, 12, 26, 35, //1648
42, 47, 52, 58, 60, 62, 66, 69, 71, 74, 75, 75, 78, 81, 84, 89, //1664
89, 91, 90, 88, 84, 77, 71, 63, 54, 48, 39, 36, 38, 42, 47, 54, //1680
65, 74, 85, 95, 103, 111, 113, 111, 108, 105, 98, 86, 77, 68, 62, 59, //1696
61, 70, 79, 89, 95, 95, 86, 72, 57, 43, 28, 15, 0, -7, -9, -6, //1712
1, 12, 29, 39, 47, 51, 52, 48, 43, 38, 34, 33, 35, 41, 47, 53, //1728
56, 58, 59, 55, 50, 43, 34, 25, 12, 1, -9, -20, -31, -40, -48, -50, //1744
-48, -42, -35, -27, -17, -12, -7, -4, -4, -7, -11, -17, -25, -32, -40, -48, //1760
-51, -54, -55, -55, -50, -46, -42, -41, -41, -43, -50, -57, -67, -77, -89, -100, //1776
-113, -120, -123, -123, -118, -107, -96, -85, -74, -65, -57, -50, -49, -51, -57, -67, //1792
-78, -97, -109, -119, -125, -127, -123, -117, -107, -97, -85, -72, -56, -49, -45, -46, //1808
-49, -52, -58, -57, -55, -54, -51, -44, -40, -34, -27, -23, -18, -17, -19, -24, //1824
-30, -39, -46, -56, -62, -65, -66, -67, -69, -68, -67, -66, -62, -55, -44, -34, //1840
-25, -19, -12, -6, 3, 7, 9, 10, 9, 6, 2, -6, -13, -21, -29, -38, //1856
-40, -41, -40, -37, -37, -35, -33, -31, -29, -27, -26, -26, -25, -23, -22, -19, //1872
-15, -14, -13, -13, -15, -15, -17, -17, -16, -14, -11, -7, -5, -4, -1, 4, //1888
11, 21, 27, 31, 35, 38, 40, 41, 42, 43, 43, 43, 42, 42, 41, 40, //1904
40, 41, 39, 36, 32, 27, 23, 19, 18, 19, 20, 22, 24, 30, 32, 32, //1920
32, 31, 28, 24, 21, 18, 17, 16, 19, 24, 31, 41, 50, 56, 64, 64, //1936
62, 59, 54, 47, 41, 41, 40, 40, 41, 36, 33, 31, 26, 22, 17, 10, //1952
6, 4, 4, 8, 14, 24, 28, 32, 36, 38, 39, 38, 35, 30, 26, 21, //1968
17, 18, 20, 23, 27, 31, 36, 39, 41, 40, 38, 34, 30, 29, 29, 29, //1984
29, 32, 34, 36, 36, 34, 29, 20, 15, 8, 2, -3, -10, -12, -13, -13, //2000
-13, -12, -11, -10, -9, -9, -9, -9, -9, -7, -5, -3, -1, -1, -2, -5, //2016
-10, -15, -21, -31, -35, -41, -45, -47, -48, -50, -52, -56, -60, -65, -75, -81, //2032
-87, -91, -91, -87, -78, -69, -60, -51, -41, -34, -32, -34, -38, -45, -52, -60, //2048
-66, -71, -75, -77, -78, -75, -71, -67, -62, -56, -48, -42, -38, -37, -39, -42, //2064
-49, -53, -54, -54, -55, -54, -54, -54, -55, -55, -54, -52, -49, -47, -47, -47, //2080
-49, -54, -54, -54, -54, -53, -50, -44, -40, -37, -37, -39, -42, -45, -47, -49, //2096
-52, -54, -55, -53, -49, -43, -36, -29, -23, -22, -23, -24, -24, -23, -20, -16, //2112
-12, -7, 0, 9, 14, 20, 24, 27, 28, 27, 26, 24, 23, 24, 29, 32, //2128
38, 43, 49, 55, 66, 74, 80, 84, 87, 88, 89, 89, 91, 94, 97, 102, //2144
103, 104, 102, 98, 92, 83, 74, 66, 58, 50, 44, 38, 36, 36, 39, 44, //2160
54, 58, 64, 67, 70, 74, 78, 78, 76, 73, 70, 67, 64, 62, 62, 63, //2176
64, 70, 72, 73, 73, 70, 66, 61, 56, 51, 44, 36, 27, 15, 11, 8, //2192
8, 10, 14, 17, 22, 26, 29, 33, 36, 37, 39, 39, 39, 40, 39, 39, //2208
38, 38, 39, 39, 39, 40, 41, 45, 49, 53, 55, 54, 53, 49, 42, 38, //2224
34, 30, 26, 20, 12, 9, 10, 13, 18, 24, 35, 40, 45, 47, 46, 41, //2240
34, 25, 17, 9, 1, -11, -17, -23, -26, -28, -28, -22, -16, -9, 0, 11, //2256
21, 26, 30, 31, 33, 34, 33, 31, 26, 17, 10, 2, -7, -10, -14, -14, //2272
-11, -4, 1, 7, 12, 14, 14, 15, 14, 14, 15, 15, 15, 15, 14, 14, //2288
15, 16, 18, 19, 18, 15, 9, 4, -7, -16, -24, -33, -39, -43, -46, -46, //2304
-46, -49, -53, -59, -62, -63, -62, -60, -57, -48, -39, -31, -24, -19, -16, -17, //2320
-18, -21, -27, -33, -47, -56, -64, -68, -70, -69, -61, -53, -43, -33, -27, -23, //2336
-24, -27, -32, -37, -46, -60, -68, -74, -78, -79, -77, -71, -66, -59, -54, -50, //2352
-47, -46, -47, -48, -50, -53, -56, -58, -60, -59, -55, -49, -40, -32, -24, -19, //2368
-15, -14, -15, -18, -22, -26, -32, -40, -44, -48, -49, -48, -46, -41, -38, -35, //2384
-34, -36, -36, -38, -40, -41, -45, -47, -50, -51, -51, -51, -51, -52, -50, -48, //2400
-44, -39, -33, -25, -21, -20, -20, -21, -23, -24, -27, -30, -34, -38, -40, -42, //2416
-40, -36, -29, -22, -9, -2, 1, 1, -2, -8, -14, -18, -21, -22, -25, -24, //2432
-19, -14, -8, -3, 2, 9, 12, 15, 18, 21, 24, 29, 33, 37, 40, 41, //2448
40, 38, 35, 33, 30, 26, 21, 16, 13, 13, 14, 18, 28, 34, 40, 46, //2464
49, 52, 54, 54, 53, 51, 50, 46, 44, 41, 40, 42, 44, 47, 46, 44, //2480
42, 39, 37, 34, 31, 28, 27, 25, 26, 30, 36, 41, 47, 51, 54, 54, //2496
54, 54, 54, 54, 55, 56, 57, 59, 61, 64, 66, 66, 64, 60, 56, 51, //2512
47, 44, 41, 38, 37, 34, 31, 27, 26, 26, 26, 28, 29, 30, 32, 34, //2528
34, 31, 27, 19, 12, -2, -12, -23, -33, -41, -48, -53, -52, -50, -45, -39, //2544
-33, -25, -21, -16, -13, -10, -11, -11, -10, -9, -6, -4, -6, -9, -13, -18, //2560
-25, -32, -40, -43, -44, -43, -40, -39, -38, -38, -39, -42, -44, -50, -52, -52, //2576
-51, -46, -39, -28, -20, -13, -7, -1, 4, 5, 4, 0, -4, -9, -18, -22, //2592
-25, -27, -27, -25, -25, -26, -27, -30, -33, -36, -37, -36, -35, -36, -36, -39, //2608
-44, -45, -47, -46, -45, -43, -41, -38, -35, -32, -27, -26, -26, -28, -34, -41, //2624
-52, -59, -62, -62, -62, -58, -49, -41, -30, -22, -13, -1, 4, 6, 6, 4, //2640
1, -2, -5, -5, -6, -6, -3, -2, -1, -1, -3, -7, -14, -18, -22, -25, //2656
-27, -26, -26, -25, -23, -22, -19, -14, -9, -5, 0, 3, 6, 9, 11, 13, //2672
15, 18, 22, 30, 32, 37, 42, 44, 47, 45, 41, 36, 30, 22, 13, 7, //2688
2, 1, -2, -4, -3, -2, 1, 6, 8, 14, 18, 20, 24, 26, 28, 33, //2704
36, 42, 48, 55, 63, 78, 86, 92, 97, 100, 103, 105, 107, 108, 107, 106, //2720
101, 95, 89, 83, 76, 70, 65, 62, 61, 60, 60, 61, 62, 63, 62, 59, //2736
56, 51, 46, 42, 37, 31, 26, 23, 23, 25, 29, 33, 38, 41, 43, 45, //2752
47, 46, 44, 41, 38, 36, 35, 33, 31, 30, 29, 28, 24, 18, 13, 6, //2768
0, -6, -11, -10, -8, -6, -1, 3, 5, 8, 7, 4, 0, -6, -19, -26, //2784
-34, -38, -38, -34, -26, -19, -12, -4, 3, 9, 11, 9, 6, 2, -4, -14, //2800
-22, -29, -33, -34, -33, -25, -20, -16, -11, -6, -2, 0, -4, -10, -16, -28, //2816
-44, -54, -66, -76, -85, -93, -101, -106, -108, -108, -107, -101, -94, -89, -84, -79, //2832
-74, -71, -70, -70, -71, -70, -70, -70, -68, -67, -65, -62, -63, -65, -66, -68, //2848
-68, -67, -65, -63, -63, -63, -63, -64, -66, -68, -69, -71, -71, -69, -68, -65, //2864
-63, -63, -63, -62, -62, -63, -63, -65, -69, -77, -82, -86, -89, -93, -96, -95, //2880
-93, -91, -87, -83, -78, -74, -71, -66, -59, -51, -36, -24, -14, -6, -1, 3, //2896
2, -2, -9, -19, -32, -49, -57, -60, -57, -51, -42, -26, -16, -7, 0, 4, //2912
5, 3, 0, -2, -7, -12, -17, -19, -18, -15, -13, -12, -8, -7, -6, -3, //2928
-1, 4, 8, 13, 20, 28, 38, 48, 51, 51, 50, 46, 41, 38, 35, 36, //2944
42, 50, 66, 75, 84, 92, 97, 98, 97, 92, 84, 77, 69, 56, 48, 43, //2960
39, 37, 39, 46, 51, 56, 60, 65, 69, 72, 72, 70, 68, 66, 62, 57, //2976
51, 44, 38, 34, 34, 35, 37, 41, 47, 53, 62, 69, 76, 82, 87, 95, //2992
97, 99, 99, 97, 96, 95, 92, 90, 87, 82, 78, 73, 69, 67, 65, 63, //3008
58, 54, 51, 49, 45, 41, 37, 34, 33, 32, 32, 33, 36, 39, 42, 46, //3024
47, 45, 42, 38, 33, 26, 20, 13, 10, 9, 9, 10, 10, 9, 7, 3, //3040
-1, -4, -8, -11, -11, -11, -9, -5, -1, 2, 5, 8, 10, 12, 12, 13, //3056
14, 14, 16, 17, 16, 15, 11, 5, -2, -14, -21, -28, -35, -41, -45, -49, //3072
-49, -47, -44, -41, -34, -33, -34, -37, -41, -44, -50, -54, -58, -61, -63, -64, //3088
-62, -60, -56, -52, -49, -43, -40, -37, -37, -38, -42, -53, -64, -77, -90, -103, //3104
-118, -122, -120, -114, -106, -95, -76, -63, -48, -36, -28, -23, -26, -30, -37, -45, //3120
-52, -59, -58, -55, -49, -43, -36, -25, -20, -16, -12, -9, -7, -4, -2, 0, };

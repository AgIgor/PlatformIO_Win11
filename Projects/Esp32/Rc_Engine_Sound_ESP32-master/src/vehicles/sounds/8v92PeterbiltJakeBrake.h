const unsigned int jakeBrakeSampleRate = 22050;
const unsigned int jakeBrakeSampleCount = 3759;
const signed char jakeBrakeSamples[] = {//0
0, -1, -1, -1, -2, -2, -2, -2, -3, -3, -3, -4, -4, -4, -4, -4, //16
-4, -4, -4, -4, -4, -3, -3, -3, -3, -3, -3, -3, -2, -1, 0, 1, //32
1, 2, 3, 4, 5, 7, 8, 9, 9, 10, 10, 11, 11, 11, 12, 13, //48
13, 14, 15, 15, 16, 17, 19, 20, 21, 22, 23, 23, 23, 24, 25, 27, //64
27, 27, 28, 28, 28, 28, 28, 29, 29, 29, 29, 30, 31, 31, 31, 31, //80
32, 32, 31, 30, 29, 29, 29, 29, 28, 28, 28, 28, 27, 27, 27, 26, //96
26, 25, 24, 24, 24, 23, 22, 22, 23, 22, 21, 20, 19, 19, 19, 19, //112
19, 21, 24, 25, 25, 27, 28, 30, 31, 32, 34, 36, 38, 41, 44, 46, //128
48, 51, 53, 56, 58, 60, 61, 62, 65, 66, 67, 67, 68, 68, 67, 66, //144
64, 63, 62, 61, 61, 61, 61, 60, 59, 59, 59, 58, 58, 58, 59, 59, //160
59, 59, 59, 59, 58, 58, 57, 57, 55, 54, 52, 52, 52, 52, 52, 51, //176
50, 48, 46, 45, 43, 40, 39, 38, 37, 36, 34, 33, 32, 31, 31, 32, //192
32, 32, 31, 31, 31, 32, 33, 33, 33, 32, 30, 28, 26, 25, 24, 23, //208
22, 21, 20, 19, 19, 18, 18, 18, 18, 17, 16, 15, 14, 14, 13, 12, //224
11, 9, 7, 4, 2, 0, -2, -4, -5, -6, -6, -6, -7, -8, -9, -8, //240
-8, -9, -10, -11, -11, -11, -11, -11, -12, -14, -14, -15, -15, -15, -15, -17, //256
-18, -18, -18, -19, -19, -20, -20, -21, -22, -22, -23, -23, -24, -24, -24, -24, //272
-25, -24, -24, -24, -24, -23, -23, -22, -22, -22, -21, -22, -21, -20, -19, -17, //288
-16, -15, -14, -14, -12, -10, -8, -6, -5, -4, -4, -4, -3, -3, -1, 0, //304
1, 2, 4, 5, 5, 5, 6, 7, 8, 9, 9, 10, 10, 11, 11, 11, //320
12, 12, 12, 11, 11, 10, 10, 9, 9, 9, 9, 8, 7, 6, 5, 3, //336
1, -1, -2, -2, -4, -6, -8, -9, -10, -11, -13, -14, -15, -15, -16, -17, //352
-19, -20, -20, -21, -21, -22, -23, -24, -25, -25, -25, -25, -26, -27, -27, -26, //368
-25, -24, -24, -25, -25, -24, -23, -23, -24, -25, -25, -25, -26, -26, -27, -27, //384
-27, -27, -26, -26, -25, -25, -25, -24, -23, -24, -24, -24, -22, -22, -22, -22, //400
-23, -23, -24, -24, -24, -24, -25, -26, -28, -29, -30, -30, -30, -32, -33, -34, //416
-35, -37, -39, -42, -43, -44, -45, -46, -46, -47, -47, -47, -48, -49, -49, -49, //432
-50, -50, -51, -52, -53, -54, -54, -55, -55, -55, -56, -57, -58, -58, -58, -58, //448
-57, -57, -57, -57, -57, -55, -54, -53, -52, -51, -51, -50, -49, -48, -47, -46, //464
-45, -44, -43, -41, -40, -38, -34, -33, -32, -31, -30, -30, -29, -29, -28, -26, //480
-25, -24, -23, -23, -22, -21, -20, -18, -17, -16, -15, -15, -14, -14, -13, -13, //496
-13, -12, -11, -10, -9, -9, -9, -8, -8, -7, -8, -8, -8, -7, -7, -7, //512
-6, -6, -6, -6, -6, -7, -7, -7, -7, -7, -6, -4, -4, -3, -2, 0, //528
1, 2, 2, 4, 7, 9, 10, 12, 13, 14, 16, 17, 19, 21, 22, 23, //544
25, 26, 28, 30, 31, 33, 35, 36, 37, 38, 39, 41, 41, 43, 44, 46, //560
49, 49, 50, 51, 53, 55, 58, 60, 62, 64, 66, 68, 72, 74, 76, 78, //576
80, 81, 81, 80, 80, 79, 77, 74, 71, 67, 63, 60, 56, 53, 50, 47, //592
45, 44, 43, 43, 42, 41, 40, 38, 36, 35, 34, 33, 32, 30, 29, 27, //608
24, 22, 19, 17, 15, 12, 10, 8, 6, 5, 5, 3, 2, 1, 1, 0, //624
0, 0, 1, 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 14, 18, //640
20, 21, 21, 22, 23, 23, 23, 23, 22, 22, 21, 20, 19, 18, 18, 18, //656
17, 16, 15, 15, 14, 14, 12, 12, 11, 10, 9, 8, 6, 5, 4, 2, //672
1, 0, -1, -3, -4, -6, -7, -9, -10, -11, -12, -12, -13, -14, -14, -15, //688
-15, -16, -17, -18, -20, -21, -22, -23, -24, -24, -25, -25, -25, -25, -24, -24, //704
-23, -23, -23, -22, -22, -21, -20, -19, -18, -16, -16, -17, -17, -17, -16, -16, //720
-17, -18, -18, -18, -18, -19, -19, -18, -18, -17, -17, -16, -15, -15, -15, -14, //736
-14, -14, -14, -15, -15, -14, -14, -15, -15, -14, -13, -12, -12, -12, -11, -10, //752
-10, -11, -11, -11, -10, -10, -10, -10, -11, -12, -13, -13, -14, -14, -14, -14, //768
-14, -14, -14, -15, -15, -15, -15, -16, -16, -17, -18, -20, -21, -22, -23, -23, //784
-24, -24, -25, -25, -26, -26, -26, -27, -27, -27, -27, -27, -27, -27, -28, -29, //800
-29, -30, -31, -31, -31, -31, -32, -32, -32, -31, -31, -30, -29, -28, -27, -27, //816
-25, -25, -24, -24, -23, -23, -22, -22, -22, -22, -22, -23, -23, -23, -24, -24, //832
-25, -26, -27, -27, -28, -29, -29, -30, -32, -33, -35, -36, -37, -38, -39, -39, //848
-40, -42, -43, -44, -44, -45, -47, -47, -47, -47, -48, -48, -49, -50, -51, -52, //864
-52, -52, -51, -51, -52, -53, -53, -53, -53, -52, -51, -51, -50, -50, -49, -49, //880
-48, -46, -45, -44, -44, -43, -42, -40, -39, -38, -36, -35, -35, -34, -32, -31, //896
-29, -29, -28, -26, -24, -23, -22, -21, -20, -18, -17, -16, -15, -13, -12, -12, //912
-11, -10, -8, -6, -6, -6, -5, -5, -5, -5, -4, -3, -2, -2, -2, -3, //928
-2, -1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, -1, -1, 0, 1, //944
1, 2, 4, 5, 5, 5, 6, 6, 7, 8, 9, 10, 12, 12, 13, 14, //960
15, 15, 15, 15, 15, 16, 16, 16, 16, 18, 19, 20, 21, 22, 23, 25, //976
26, 27, 29, 30, 30, 30, 31, 32, 32, 31, 32, 32, 33, 33, 32, 32, //992
31, 32, 33, 34, 35, 35, 35, 35, 36, 37, 37, 37, 37, 38, 38, 38, //1008
37, 36, 35, 35, 36, 35, 34, 33, 32, 32, 31, 31, 31, 32, 32, 32, //1024
32, 31, 31, 30, 30, 32, 33, 33, 33, 33, 33, 34, 36, 37, 39, 40, //1040
42, 44, 45, 46, 47, 50, 52, 53, 55, 57, 59, 61, 64, 65, 66, 66, //1056
66, 67, 68, 69, 69, 69, 70, 70, 70, 69, 68, 68, 68, 66, 64, 63, //1072
62, 60, 59, 58, 56, 55, 55, 54, 53, 52, 50, 49, 48, 47, 46, 44, //1088
42, 40, 38, 36, 35, 34, 33, 31, 30, 29, 29, 29, 28, 27, 26, 25, //1104
25, 24, 24, 24, 23, 23, 23, 22, 22, 21, 21, 22, 21, 21, 20, 20, //1120
21, 21, 21, 21, 21, 20, 20, 20, 19, 19, 18, 18, 18, 18, 18, 18, //1136
17, 17, 17, 17, 17, 17, 16, 15, 14, 14, 14, 14, 15, 15, 15, 15, //1152
15, 14, 12, 12, 12, 12, 12, 11, 9, 8, 6, 5, 4, 3, 2, 1, //1168
0, -1, -2, -2, -2, -3, -3, -3, -4, -5, -5, -5, -5, -5, -5, -6, //1184
-6, -7, -7, -7, -8, -9, -9, -10, -10, -10, -10, -11, -11, -11, -11, -11, //1200
-10, -10, -9, -8, -8, -7, -6, -5, -4, -4, -4, -5, -5, -5, -5, -5, //1216
-4, -4, -4, -4, -4, -3, -2, -1, 0, 1, 2, 2, 3, 4, 6, 9, //1232
11, 13, 13, 13, 13, 14, 14, 15, 15, 16, 15, 15, 14, 14, 14, 15, //1248
15, 15, 14, 13, 11, 10, 9, 8, 7, 5, 4, 3, 2, -1, -3, -5, //1264
-6, -8, -9, -11, -12, -12, -14, -15, -17, -19, -20, -21, -22, -23, -24, -25, //1280
-27, -28, -29, -29, -29, -29, -30, -30, -31, -31, -30, -30, -29, -29, -29, -27, //1296
-26, -25, -25, -26, -27, -27, -27, -26, -26, -25, -25, -24, -24, -24, -24, -23, //1312
-22, -22, -22, -23, -23, -24, -24, -24, -24, -24, -25, -27, -28, -28, -29, -29, //1328
-30, -32, -32, -33, -34, -35, -36, -37, -38, -39, -41, -42, -43, -44, -45, -46, //1344
-48, -49, -51, -51, -52, -53, -53, -53, -54, -55, -55, -55, -55, -55, -55, -55, //1360
-54, -54, -55, -55, -54, -53, -52, -52, -50, -48, -47, -46, -45, -44, -42, -41, //1376
-40, -38, -37, -35, -34, -33, -32, -31, -30, -29, -28, -27, -27, -27, -26, -25, //1392
-23, -22, -21, -21, -20, -20, -19, -19, -19, -19, -18, -17, -15, -15, -14, -13, //1408
-13, -12, -11, -10, -10, -9, -8, -8, -7, -7, -7, -7, -6, -6, -6, -7, //1424
-7, -7, -7, -6, -6, -6, -6, -6, -6, -6, -5, -4, -4, -4, -4, -4, //1440
-3, -3, -3, -3, -2, -2, -1, -2, -3, -3, -4, -4, -4, -4, -6, -7, //1456
-7, -8, -8, -8, -8, -9, -9, -10, -10, -10, -10, -10, -10, -10, -9, -9, //1472
-9, -9, -9, -8, -6, -6, -5, -4, -4, -4, -3, -3, -2, -1, 0, 2, //1488
3, 4, 4, 6, 7, 8, 10, 10, 11, 11, 12, 13, 14, 14, 15, 16, //1504
18, 19, 20, 20, 20, 20, 20, 20, 20, 21, 21, 20, 19, 19, 18, 17, //1520
16, 15, 14, 14, 14, 14, 14, 14, 14, 15, 15, 17, 18, 19, 20, 21, //1536
23, 26, 29, 32, 35, 38, 42, 45, 50, 53, 56, 60, 65, 69, 75, 78, //1552
81, 84, 86, 88, 89, 90, 90, 89, 89, 88, 87, 86, 85, 84, 83, 82, //1568
81, 79, 77, 75, 72, 71, 70, 69, 67, 65, 61, 58, 55, 53, 51, 49, //1584
47, 45, 43, 41, 40, 37, 35, 33, 31, 29, 27, 24, 22, 20, 17, 16, //1600
14, 11, 9, 7, 6, 5, 5, 5, 5, 5, 5, 6, 6, 5, 5, 4, //1616
4, 4, 2, 1, 0, 0, 0, -1, -2, -3, -4, -5, -7, -9, -10, -12, //1632
-13, -15, -16, -18, -19, -21, -23, -25, -28, -29, -31, -34, -36, -37, -38, -40, //1648
-42, -44, -45, -47, -48, -49, -50, -51, -53, -55, -56, -56, -57, -58, -59, -60, //1664
-61, -62, -62, -63, -64, -64, -63, -64, -64, -65, -66, -66, -66, -66, -66, -66, //1680
-66, -65, -65, -65, -65, -65, -64, -64, -64, -64, -64, -63, -62, -62, -62, -62, //1696
-62, -62, -63, -63, -63, -63, -63, -62, -62, -62, -63, -62, -62, -61, -60, -60, //1712
-59, -59, -57, -56, -54, -53, -52, -49, -47, -45, -44, -42, -40, -37, -35, -33, //1728
-32, -30, -28, -25, -24, -22, -21, -20, -19, -19, -17, -16, -15, -15, -14, -13, //1744
-12, -11, -10, -10, -9, -8, -8, -8, -8, -9, -9, -10, -10, -10, -10, -11, //1760
-11, -12, -12, -12, -12, -12, -13, -14, -14, -14, -15, -16, -16, -16, -17, -18, //1776
-20, -20, -21, -21, -21, -21, -21, -21, -21, -20, -19, -17, -17, -16, -15, -14, //1792
-13, -11, -11, -9, -8, -7, -6, -6, -5, -4, -3, -2, -1, 0, 1, 2, //1808
2, 3, 4, 5, 6, 6, 7, 8, 8, 8, 8, 9, 9, 9, 8, 7, //1824
7, 6, 5, 4, 4, 4, 2, 1, -1, -1, -2, -3, -4, -4, -5, -6, //1840
-8, -9, -9, -10, -11, -12, -12, -13, -13, -14, -14, -14, -14, -14, -15, -16, //1856
-16, -16, -16, -16, -15, -13, -13, -13, -13, -12, -11, -11, -11, -10, -9, -8, //1872
-8, -8, -8, -7, -7, -7, -7, -7, -6, -6, -6, -5, -5, -5, -5, -5, //1888
-4, -3, -2, -2, -3, -3, -2, -2, -2, -1, 0, 0, 1, 1, 2, 3, //1904
3, 4, 5, 5, 6, 7, 8, 9, 10, 10, 10, 11, 11, 12, 13, 14, //1920
15, 15, 16, 17, 18, 19, 20, 21, 22, 22, 23, 23, 23, 24, 26, 27, //1936
27, 27, 28, 29, 30, 30, 31, 32, 33, 34, 35, 36, 37, 38, 38, 38, //1952
38, 39, 40, 40, 40, 39, 39, 39, 39, 39, 40, 40, 40, 40, 40, 40, //1968
41, 41, 41, 41, 42, 42, 40, 40, 40, 40, 40, 40, 40, 40, 41, 41, //1984
42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 41, 40, 40, 40, 39, 38, //2000
37, 36, 35, 34, 34, 34, 34, 33, 32, 31, 30, 29, 28, 27, 27, 26, //2016
26, 25, 25, 24, 23, 23, 22, 22, 21, 22, 23, 24, 25, 25, 27, 28, //2032
28, 29, 30, 32, 33, 35, 37, 39, 42, 43, 46, 48, 50, 51, 52, 53, //2048
54, 55, 56, 56, 57, 58, 59, 59, 58, 58, 59, 60, 60, 60, 60, 61, //2064
62, 62, 62, 63, 63, 63, 63, 62, 62, 62, 62, 61, 60, 59, 58, 57, //2080
56, 55, 54, 53, 51, 49, 47, 45, 44, 43, 42, 41, 39, 38, 37, 36, //2096
35, 34, 33, 32, 31, 31, 31, 30, 30, 30, 29, 29, 28, 27, 26, 26, //2112
26, 25, 25, 24, 24, 25, 25, 26, 26, 28, 29, 30, 31, 32, 32, 32, //2128
32, 32, 32, 31, 30, 29, 28, 27, 25, 24, 22, 22, 21, 20, 18, 17, //2144
17, 16, 16, 16, 15, 14, 14, 13, 12, 10, 8, 6, 4, 1, -1, -3, //2160
-6, -7, -8, -9, -10, -11, -14, -16, -17, -19, -21, -22, -25, -26, -27, -28, //2176
-29, -30, -30, -31, -32, -32, -33, -34, -35, -35, -35, -35, -36, -36, -35, -35, //2192
-36, -36, -36, -37, -37, -37, -37, -37, -37, -36, -35, -34, -33, -32, -31, -31, //2208
-31, -30, -30, -29, -28, -27, -27, -26, -25, -24, -23, -22, -21, -20, -18, -17, //2224
-17, -17, -17, -16, -16, -16, -16, -15, -14, -13, -12, -12, -13, -13, -14, -15, //2240
-16, -16, -17, -17, -17, -19, -20, -21, -22, -23, -23, -24, -25, -27, -28, -29, //2256
-30, -31, -32, -33, -34, -35, -37, -38, -40, -41, -43, -44, -47, -48, -49, -51, //2272
-52, -52, -52, -52, -52, -53, -53, -54, -54, -54, -53, -53, -52, -52, -51, -51, //2288
-50, -49, -49, -48, -48, -48, -48, -48, -46, -45, -44, -43, -42, -41, -39, -38, //2304
-37, -36, -35, -34, -33, -33, -33, -32, -31, -31, -31, -30, -30, -30, -30, -31, //2320
-31, -32, -32, -33, -35, -37, -38, -39, -39, -39, -40, -40, -40, -41, -42, -43, //2336
-43, -44, -45, -46, -46, -47, -48, -48, -49, -49, -50, -50, -50, -50, -50, -50, //2352
-50, -51, -51, -51, -51, -50, -50, -49, -48, -48, -47, -46, -45, -44, -43, -43, //2368
-42, -41, -40, -39, -38, -37, -37, -36, -35, -34, -34, -33, -32, -31, -30, -29, //2384
-28, -27, -25, -25, -24, -23, -23, -22, -21, -20, -19, -18, -17, -17, -16, -15, //2400
-14, -12, -11, -9, -8, -7, -6, -5, -4, -2, -1, -1, 0, 1, 1, 2, //2416
3, 4, 4, 5, 5, 5, 5, 5, 4, 4, 5, 6, 6, 7, 7, 7, //2432
8, 9, 9, 8, 8, 9, 9, 9, 10, 10, 9, 10, 10, 11, 11, 11, //2448
11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 15, 16, 18, 20, 22, 23, //2464
25, 26, 29, 30, 32, 34, 37, 41, 43, 45, 48, 50, 53, 57, 60, 64, //2480
69, 73, 78, 85, 90, 94, 99, 104, 112, 117, 122, 127, 127, 127, 127, 127, //2496
127, 127, 127, 127, 127, 127, 127, 127, 127, 121, 112, 104, 97, 90, 84, 77, //2512
73, 70, 66, 63, 58, 54, 50, 46, 41, 36, 28, 22, 17, 12, 9, 7, //2528
3, 1, -2, -6, -9, -12, -13, -14, -15, -15, -16, -16, -16, -17, -17, -17, //2544
-17, -16, -15, -15, -15, -15, -14, -13, -11, -9, -7, -4, 0, 3, 5, 8, //2560
10, 12, 14, 14, 14, 13, 12, 9, 8, 7, 7, 6, 5, 5, 5, 5, //2576
5, 4, 4, 3, 2, 1, -1, -3, -7, -10, -14, -17, -21, -25, -31, -34, //2592
-37, -38, -40, -42, -45, -47, -48, -50, -51, -53, -53, -54, -54, -55, -55, -56, //2608
-57, -57, -58, -58, -58, -58, -58, -58, -58, -57, -56, -56, -56, -55, -55, -55, //2624
-55, -54, -54, -53, -53, -53, -52, -51, -51, -50, -50, -50, -49, -48, -47, -47, //2640
-47, -47, -47, -47, -47, -46, -45, -43, -42, -41, -40, -39, -38, -37, -36, -35, //2656
-33, -31, -29, -27, -25, -24, -23, -21, -19, -16, -13, -10, -8, -3, -1, 1, //2672
2, 4, 6, 8, 9, 10, 10, 10, 10, 9, 9, 8, 7, 6, 4, 3, //2688
2, 2, 2, 2, 1, 0, -1, -3, -4, -6, -8, -10, -12, -15, -19, -23, //2704
-25, -28, -32, -35, -38, -42, -43, -44, -44, -45, -45, -46, -46, -46, -46, -46, //2720
-48, -49, -50, -51, -52, -53, -55, -56, -55, -55, -55, -53, -51, -49, -47, -44, //2736
-42, -39, -37, -36, -35, -34, -33, -33, -33, -32, -31, -30, -28, -27, -26, -25, //2752
-24, -23, -22, -21, -20, -19, -19, -19, -20, -21, -21, -21, -22, -23, -23, -24, //2768
-25, -26, -27, -28, -30, -31, -32, -32, -32, -33, -34, -34, -34, -33, -32, -32, //2784
-32, -31, -29, -28, -27, -26, -25, -23, -22, -20, -20, -18, -17, -16, -14, -11, //2800
-10, -8, -8, -7, -6, -5, -4, -4, -4, -3, -2, -2, -1, 0, 1, 3, //2816
5, 7, 8, 9, 10, 11, 12, 13, 13, 13, 13, 12, 12, 12, 12, 12, //2832
11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 13, 14, 15, 16, //2848
17, 18, 20, 20, 21, 22, 22, 23, 23, 23, 24, 25, 26, 27, 28, 28, //2864
29, 29, 30, 32, 32, 33, 34, 35, 36, 37, 37, 38, 39, 40, 41, 42, //2880
42, 43, 43, 43, 43, 43, 43, 43, 44, 44, 45, 44, 43, 42, 42, 42, //2896
42, 42, 41, 41, 40, 39, 38, 36, 35, 35, 34, 32, 31, 29, 27, 25, //2912
25, 25, 24, 23, 22, 22, 21, 21, 20, 20, 20, 20, 20, 20, 20, 20, //2928
20, 21, 22, 23, 23, 22, 21, 20, 21, 21, 22, 23, 25, 27, 28, 29, //2944
30, 31, 32, 33, 34, 35, 36, 36, 37, 37, 39, 40, 41, 43, 45, 46, //2960
48, 49, 50, 52, 52, 52, 53, 53, 52, 52, 51, 51, 50, 49, 48, 46, //2976
45, 44, 43, 43, 41, 41, 41, 41, 41, 41, 42, 42, 42, 42, 43, 44, //2992
44, 45, 45, 46, 47, 49, 51, 53, 55, 56, 58, 61, 63, 64, 66, 68, //3008
72, 74, 76, 78, 80, 82, 85, 87, 90, 92, 95, 98, 102, 105, 109, 112, //3024
115, 120, 123, 125, 127, 127, 127, 127, 127, 127, 127, 126, 124, 121, 119, 117, //3040
115, 112, 107, 104, 101, 98, 95, 92, 88, 85, 83, 80, 76, 71, 64, 60, //3056
56, 53, 50, 45, 42, 38, 35, 32, 29, 25, 22, 20, 17, 14, 12, 8, //3072
6, 4, 1, -1, -4, -7, -8, -9, -10, -10, -12, -13, -14, -15, -15, -15, //3088
-14, -14, -14, -15, -16, -17, -17, -17, -16, -15, -15, -15, -15, -15, -15, -16, //3104
-16, -17, -18, -19, -20, -22, -26, -28, -30, -31, -32, -34, -35, -37, -38, -40, //3120
-41, -42, -42, -43, -44, -45, -47, -49, -50, -50, -50, -50, -50, -51, -52, -53, //3136
-54, -54, -54, -54, -54, -54, -54, -54, -54, -55, -54, -54, -54, -54, -55, -56, //3152
-57, -57, -57, -57, -57, -57, -56, -55, -54, -53, -52, -51, -51, -50, -50, -49, //3168
-49, -49, -48, -48, -47, -47, -47, -48, -48, -47, -47, -46, -46, -46, -45, -44, //3184
-43, -42, -41, -40, -38, -37, -37, -36, -35, -34, -33, -32, -31, -30, -30, -29, //3200
-28, -26, -24, -23, -22, -22, -20, -20, -20, -20, -19, -19, -20, -20, -21, -21, //3216
-22, -23, -24, -25, -26, -27, -29, -30, -31, -32, -33, -35, -36, -39, -41, -42, //3232
-43, -44, -46, -48, -49, -51, -53, -55, -58, -59, -61, -62, -64, -65, -67, -69, //3248
-70, -71, -73, -76, -77, -79, -80, -81, -81, -82, -82, -82, -83, -83, -83, -83, //3264
-83, -83, -84, -84, -83, -83, -83, -83, -83, -82, -82, -81, -81, -81, -80, -80, //3280
-79, -79, -78, -78, -77, -76, -76, -75, -75, -75, -74, -73, -72, -72, -71, -70, //3296
-69, -66, -65, -64, -64, -64, -64, -63, -63, -62, -61, -60, -59, -58, -58, -58, //3312
-57, -56, -53, -51, -49, -48, -46, -44, -43, -41, -40, -40, -39, -38, -36, -35, //3328
-33, -32, -31, -30, -29, -28, -27, -26, -24, -23, -22, -22, -21, -21, -20, -20, //3344
-20, -19, -18, -17, -17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -5, //3360
-4, -3, -2, -1, 0, 3, 4, 5, 6, 7, 9, 10, 12, 15, 17, 19, //3376
21, 23, 26, 28, 30, 33, 35, 37, 39, 42, 44, 48, 51, 55, 59, 62, //3392
65, 71, 75, 79, 82, 86, 90, 93, 94, 96, 98, 99, 101, 103, 104, 105, //3408
105, 106, 107, 107, 108, 108, 108, 106, 106, 106, 105, 103, 102, 99, 97, 94, //3424
91, 89, 87, 83, 80, 77, 75, 73, 69, 67, 65, 63, 62, 60, 58, 56, //3440
54, 52, 51, 49, 47, 45, 44, 43, 40, 38, 36, 35, 34, 33, 32, 31, //3456
30, 30, 29, 29, 30, 30, 31, 32, 32, 32, 32, 32, 31, 31, 32, 32, //3472
32, 31, 31, 31, 31, 31, 31, 31, 31, 30, 29, 28, 27, 26, 25, 23, //3488
22, 21, 20, 19, 18, 17, 16, 15, 13, 12, 11, 10, 9, 8, 6, 5, //3504
4, 2, 0, -1, -2, -2, -3, -4, -5, -6, -6, -7, -8, -9, -10, -11, //3520
-12, -14, -15, -15, -15, -15, -15, -16, -15, -14, -13, -13, -12, -11, -10, -11, //3536
-11, -11, -11, -11, -13, -14, -14, -14, -14, -14, -13, -12, -12, -12, -11, -11, //3552
-10, -10, -10, -9, -8, -7, -6, -6, -6, -6, -6, -5, -4, -3, -2, -1, //3568
-1, 0, 0, 0, 1, 2, 3, 4, 5, 5, 5, 5, 6, 6, 6, 6, //3584
6, 5, 5, 4, 3, 2, 0, -1, -2, -2, -4, -5, -6, -7, -9, -10, //3600
-12, -13, -16, -18, -20, -21, -22, -23, -24, -26, -27, -27, -28, -30, -31, -32, //3616
-33, -34, -35, -36, -37, -37, -39, -40, -42, -43, -44, -45, -46, -47, -47, -46, //3632
-46, -46, -46, -46, -45, -45, -45, -45, -45, -45, -43, -42, -42, -41, -41, -41, //3648
-40, -40, -40, -40, -40, -39, -37, -37, -36, -35, -35, -36, -36, -36, -36, -36, //3664
-35, -35, -34, -34, -34, -34, -35, -35, -35, -35, -35, -36, -37, -38, -39, -41, //3680
-41, -42, -43, -44, -44, -44, -43, -43, -43, -42, -41, -40, -39, -38, -38, -37, //3696
-36, -35, -35, -35, -36, -36, -36, -36, -35, -34, -33, -31, -29, -27, -25, -23, //3712
-21, -20, -18, -17, -16, -15, -14, -13, -12, -12, -11, -10, -9, -9, -8, -7, //3728
-6, -6, -6, -5, -5, -4, -4, -4, -3, -3, -3, -2, -2, -2, -2, -2, //3744
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, };

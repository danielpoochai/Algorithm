1. 學號：
b05901030
2. 姓名：
陳欽安
3. 使用之程式語言：< C++ >

4. 使用之編譯器：< GNU g++ >

5. 檔案壓縮方式: <zip b05901030 b05901030/*>

6. 各檔案說明:
	b05901030/src/insertionSort.cpp:純文字主程式
	b05901030/src/mergeSort.cpp:純文字主程式
	b05901030/src/heapSort.cpp:純文字主程式
	b05901030/src/quickSort.cpp:純文字主程式
	b05901030/report.docx: 程式報告
	b05901030/readme: 程式執行說明
	b05901030/insertionSort.exe:執行檔
	b05901030/mergeSort.exe:執行檔
	b05901030/heapSort.exe:執行檔
	b05901030/quickSort.exe:執行檔
7.編譯方式說明
	insertion sort: g++ insertionSort.cpp parser.cpp -o insertionSort.exe -O3
	merge sort: g++ mergeSort.cpp parser.cpp -o mergeSort.exe -O3
	heap sort: g++ heapSort.cpp parser.cpp -o heapSort.exe -O3
	quick sort: g++ quickSort.cpp parser.cpp -o quickSort.exe -O3
8.執行、使用方式說明
	insertion sort: ./insertionSort.exe [input file name] [output file name]
	mergeion sort: ./mergeSort.exe [input file name] [output file name]
	heapion sort: ./heapSort.exe [input file name] [output file name]
	quickion sort: ./quickSort.exe [input file name] [output file name]

*because there are getchat() at the end of the program, we can press 'enter' to terminate the program.
9.執行結果說明
如果要看執行時間，在執行時前方輸入 time ex:time ./insertionSort.exe case1.dat insertionSort.txt
則結果會出現real time, user time, sys time.本次report中，我是採用real time作為complexity的判斷依據。
如果要看memory usage,在執行後開啟terminal,輸入top, 看VIRT的值。
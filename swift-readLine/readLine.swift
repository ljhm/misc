import Foundation

// open file
func openFile(_ path: String) -> Int {
    errno = 0
    if freopen(path, "r", stdin) == nil {
        perror(path)
        return 1
    }
    return 0
}

// read text file line by line
func example(){
    let path = "/Users/jianhuali/temp/Newfile.txt"
    if openFile(path) == 0 {
        while let line = readLine() {
            // do something with lines...
            printLog(line)
        }
    }
}

/*
 [2019-09-24 09:39:20.972 +0800] main.swift:6 (example) - hello world 1
 [2019-09-24 09:39:20.975 +0800] main.swift:6 (example) - hello world 2
 [2019-09-24 09:39:20.975 +0800] main.swift:6 (example) - hello world 3
 */

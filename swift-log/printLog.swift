import Foundation

func printLog(_ items: Any..., file: String = #file, line: Int = #line, function: String = #function){
    // date
    let format = DateFormatter()
    format.dateFormat = "yyyy-MM-dd HH:mm:ss.SSS Z"
    let date = format.string(from: Date())
    
    // file
    var start = file.lastIndex(of: "/")
    if start == nil {
        start = file.startIndex
    } else {
        start = file.index(start!, offsetBy: 1)
    }
    var end: String.Index? = file.endIndex
    let file = file[start!..<end!]
    
    // function
    start = function.startIndex
    end = function.firstIndex(of: "(")
    if end == nil {
        end = function.endIndex
    }
    let function = function[start!..<end!]
        
    // print
    print("\(date) \(file):\(line) (\(function)): ", terminator: "")
    for it in items {
        print("\(it) ", terminator: "")
    }
    print()
}

//printLog("hello", 3.14, [1:1, 2:2, 3:3])
//2019-09-27 18:50:05.294 +0800 main.swift:2 (hello_swift): hello 3.14 [2: 2, 1: 1, 3: 3]

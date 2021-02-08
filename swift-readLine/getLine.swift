import Foundation

// use freopen() with readLine() instead of this

// read text file line by line
class File {
    init? (_ path: String) {
        errno = 0
        file = fopen(path, "r")
        if file == nil {
            perror(path)
            return nil
        }
    }
    
    deinit {
        fclose(file)
    }
    
    // read an entire line. lines should be with line terminators '\n' at the end
    func getLine() -> String? {
        var line = ""
        repeat {
            var buf = [CChar](repeating: 0, count: 1024)
            errno = 0
            if fgets(&buf, Int32(buf.count), file) == nil {
                if ferror(file) != 0 {
                    perror(nil)
                }
                return nil
            }
            line += String(cString: buf)
        } while line.lastIndex(of: "\n") == nil
        return line
    }
    
    private var file: UnsafeMutablePointer <FILE>?
}

/*
let path = "/Users/jianhuali/temp/Newfile.txt"
if let file = File(path){
    while let line = file.getLine() {
        print(line, terminator: "")
    }
}
*/

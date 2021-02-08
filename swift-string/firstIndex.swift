import Foundation

extension String {
    //return the index of the substring start at the specified position
    func firstIndex(of: String, at: Int) -> Int? {
        let array = Array(self)
        var start = at
        
        if at < 0 {
            return nil
        }
        
        while start + of.count - 1 < array.endIndex {
            if String(array[start..<start+of.count]) == of {
                return start
            }
            start += 1
        }
        return nil
    }
}

/*
//find the second "disk" and place "samsung" before it
var diskinfo = "hhd disk ssd disk xxx disk..."
var start = diskinfo.firstIndex(of: "disk", at: 10)
var index = diskinfo.index(diskinfo.startIndex, offsetBy: start!)

print("old: \(diskinfo)")
diskinfo.insert(contentsOf: "samsung ", at: index)
print("new: \(diskinfo)")

//old: hhd disk ssd disk xxx disk...
//new: hhd disk ssd samsung disk xxx disk...
*/

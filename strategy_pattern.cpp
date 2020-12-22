#include <iostream>
#include <string>
#include <cstdio>
#include <memory>

class IWriter {
    public:
    virtual ~IWriter() = default;
    virtual void write(std::string&& result) = 0;
};

class ConsoleWriter : public IWriter {
    public:
    void write(std::string&& result) {
        std::cout << result << "\n";
    }
};

// Custom Deleter for the OutFile
struct FileCloser {
    void operator()(FILE* pFile) const {
        if(pFile != nullptr) {
            std::fclose(pFile);
        }
    }
};


class FileWriter : public IWriter {
    using FILE_unique_ptr = std::unique_ptr<std::FILE, FileCloser>;
    FILE_unique_ptr outFilePtr;
    std::string path;
    public:
    FileWriter(std::string filePath) : path {std::move(filePath)} {
        std::FILE *fileHandle = std::fopen(path.c_str(), "a+");
        outFilePtr = (!fileHandle) ? nullptr : FILE_unique_ptr(fileHandle);
    } 

    void write(std::string&& result) {
        result += "\n";
        if(outFilePtr != nullptr) {
            std::fwrite(result.c_str(), sizeof result[0], result.size(), outFilePtr.get());
        } else {
            std::cout << "\nCouldn't write " << result << " to file";
        }
    }
};

class Simulation {
    IWriter* p_writer;
    public:
    Simulation(IWriter* writer) : p_writer {writer} {}
    void write(std::string&& result) {
        p_writer->write(std::forward<std::string>(result));
    }
};

int main() {
    // auto fWriter = FileWriter(std::string("a.txt"));
    // auto sim = Simulation(&fWriter);
    auto cWriter = ConsoleWriter();
    auto sim = Simulation(&cWriter);
    for(const auto& i : {1, 2, 3, 4, 5}) {
        sim.write(std::to_string(i));
    }
    return 0;
}
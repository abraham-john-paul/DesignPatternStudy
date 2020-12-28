#include <iostream>
#include <memory>
#include <string>
#include <algorithm>

using namespace std;

struct ITextParser {
    virtual ~ITextParser() {}
    virtual int getWordCount() = 0;
};

struct TextParser : ITextParser {
    string mTextContent;
    TextParser(string text) : mTextContent(move(text)) {} // Let this be an expensive op
    int getWordCount() override {
        int count = 0;

        auto beginItr = find_if(begin(mTextContent), end(mTextContent), [](char c) { return c != ' '; });
        auto endItr = find_if(rbegin(mTextContent), rend(mTextContent), [](char c) { return c != ' '; }).base();
        
        while(true) {
            beginItr = find_if(beginItr, endItr, 
                    [](char c) { return c == ' '; });
            if(beginItr != endItr) {
                count += 1;
                beginItr += 1;
            } else {
                return count != 0 ? count + 1 : count;
            }
        }
    }
};

struct LazyTextParserProxy : ITextParser {
    unique_ptr<TextParser> pTextParser = nullptr;
    string mTextContent;
    LazyTextParserProxy(string text) : mTextContent(move(text)) {}
    int getWordCount() override {
        if(pTextParser == nullptr) {
            pTextParser = make_unique<TextParser>(mTextContent);
        }
        return pTextParser->getWordCount();
    }
};

int main() {
    string s = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book.";
    auto pLazyParser = make_unique<LazyTextParserProxy>(move(s));
    cout << pLazyParser->getWordCount();
}

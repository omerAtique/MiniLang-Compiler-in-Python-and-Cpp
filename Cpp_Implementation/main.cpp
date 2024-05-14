#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

enum class TokenType {
  INTEGER,
  BOOLEAN,
  IDENTIFIER,
  OPERATOR,
  KEYWORD,
  LITERAL,
  COMMENT,
  ERROR,
  DATATYPE
};

struct Token {
  TokenType type;
  string lexeme;
};

class MiniLangScanner {
public:
  vector<Token> scanFile(const string& filename) {
    ifstream inputFile(filename);
    vector<Token> tokens;

    if (!inputFile.is_open()) {
      cerr << "Error opening file: " << filename << endl;
      return tokens;
    }

    string line;
    while (getline(inputFile, line)) {
      tokens.push_back(scanLine(line));
    }

    inputFile.close();
    return tokens;
  }

private:
  Token scanLine(const string& line) {
    vector<Token> lineTokens;
    for (size_t i = 0; i < line.size(); ++i) {
      char currentChar = line[i];
      processChar(currentChar, lineTokens, i);
    }
    return mergeLineTokens(lineTokens);
  }

  void processChar(char currentChar, vector<Token>& tokens, size_t& index) {
    
  }

  Token mergeLineTokens(const vector<Token>& lineTokens) {
    
  }
};

int main() {
  string filename = "example.minilang";
  MiniLangScanner scanner;
  vector<Token> tokens = scanner.scanFile(filename);

  // Rest of the code remains the same (saving lexemes and printing tokens)

  return 0;
}

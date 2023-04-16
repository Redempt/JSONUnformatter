#include <iostream>
#include <sstream>
using namespace std;

string unformat(string json) {
    return json;
}

void padLine(stringstream* s, int indent) {
    *s << '\n';
    for (int i = 0; i < indent; i++) {
        *s << '\t';
    }
}

string insertIndentation(string json) {
    int depth = 0;
    stringstream out;
    bool quoted = false;
    for (int i = 0; i < json.length(); i++) {
        char c = json[i];
        switch (c) {
            case '"':
                quoted = !quoted;
                out << c;
                break;
            case '\\':
                out << c;
                out << json[i];
                i++;
                break;
            case '{':
            case '[':
            case ']':
            case '}':
                if (i > 0) {
                    depth++;
                    padLine(&out, depth);
                }
                out << c;
                if (c == '{' || c == '[') {
                    depth++;
                    padLine(&out, depth);
                }
                break;
            case ',':
                out << c;
                depth++;
                padLine(&out, depth);
                break;
            default:
                out << c;
                break;
        }
    }
    return out.str();
}

string sPoNgEbObCaSe(string json) {
    stringstream out;
    bool quoted = false;
    bool upper = true;
    for (int i = 0; i < json.length(); i++) {
        char c = json[i];
        switch (c) {
            case '\\':
                out << c;
                out << json[i + 1];
                i++;
                break;
            case '"':
                quoted = !quoted;
                if (quoted) {
                    upper = true;
                }
                out << c;
                break;
            default:
                if (quoted) {
                    c = upper ? toupper(c) : tolower(c);
                    upper = !upper;
                }
                out << c;
                break;
        }
    }
    return out.str();
}

bool equalToClose(char character) {
  if (character == ']' || character == '}') {
    return true;
  }
  return false;
}

string trailingCommas(string json) {
  string commaString = "";
  bool comma = true;
  for (int i = 0; i < json.length(); i++) {
    if (equalToClose(json[i]) && comma) {
      commaString += ",";
      comma = false;
    } else if (equalToClose(json[i])) {
      comma = true;
    }
    commaString += json[i];
  }
  return commaString;
}

vector<string> splitByChar(string str, char delim) {
  vector<string> split;
  string data;
  stringstream ss(str);
  while (getline(ss, data, delim)) {
    split.push_back(data);
  }
  return split;
}

vector<string> makeShuffleableList(string json) {
  string noBrackets = json.substr(1, json.length() - 2);
  vector<string> splitData = splitByChar(noBrackets, ':');
  vector<string> totalSplit;
  for (int i = 0; i < splitData.size(); i++) {
    vector<string> holder = splitByChar(splitData[i], ',');
    for (int y = 0; y < holder.size(); y++) {
      totalSplit.push_back(holder[y]);
    }
  }
  return totalSplit;
}

string makeString(vector<string> vecstr) {
  string total = "";
  for (int i = 0; i < vecstr.size(); i++) {
    total += vecstr[i];
  }
  return total;
}

string shuffleKeys(string json) {
  vector<string> splitData = makeShuffleableList(json);
  vector<string> random;
  for (int i = 0; i < splitData.size(); i += 2) {
    int num = rand() % 2;
    if (num == 0) {
      random.insert(random.begin(), splitData[i + 1]);
      random.insert(random.begin(), splitData[i]);
    } else {
      random.push_back(splitData[i + 1]);
      random.push_back(splitData[i]);
    }
  }
  return makeString(random);
}

#include <iostream>
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
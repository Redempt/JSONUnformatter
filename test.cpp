//
// Created by redempt on 4/12/23.
//
#include <iostream>
#include <vector>
#include <sstream>
#include "main.cpp"

using namespace std;

template <typename T>
struct StringConverter {
    string toString(T data) {
        return std::to_string(data);
    }
};

template <typename T>
struct StringConverter<vector<T>> {
    string toString(vector<T> data) {
        stringstream s;
        s << "[";
        for (T elem : data) {
            s << elem << ", ";
        }
        string str = s.str();
        str = str.substr(0, str.length() - 2);
        return str + "]";
    }
};

template <typename T>
void assertEquals(T a, T b) {
    if (a == b) {
        return;
    }
    cout << "Assertion failed: " << a << " != " << b << endl;
    throw false;
}

template <typename T>
void assertNotEquals(T a, T b) {
    if (a != b) {
        return;
    }
    auto strconv = StringConverter<T>{};
    cout << "Assertion failed: " << strconv.toString(a) << " == " << strconv.toString(b) << endl;
    throw false;
}

void runTest(string name, void (*test) ()) {
    try {
        test();
        cout << name << " PASS" << endl;
    } catch (bool e) {
        cout << name << " FAIL" << endl;
    }
}

void testIndent() {
    string jsonString = "{\"Dog\": {\"Name\" : \"Daisy\", \"Breed\" : \"Beagle\"}}";
    string expectedFormat = "{\n\t\"Dog\": \n\t\t{\n\t\t\t\"Name\" : \"Daisy\",\n\t\t\t\t \"Breed\" : \"Beagle\"\n\t\t\t\t\t}\n\t\t\t\t\t\t}";
    assertEquals(expectedFormat, insertIndentation(jsonString));
}

vector<string> getKeys(string json) {
    vector<string> keys;
    bool quoted = false;
    int quoteStart = 0;
    for (int i = 0; i < json.length(); i++) {
        switch (json[i]) {
            case '\\':
                i++;
                continue;
            case '"':
                quoted = !quoted;
                if (quoted) {
                    quoteStart = i + 1;
                } else {
                    keys.push_back(json.substr(quoteStart, i - quoteStart));
                }
                break;
        }
    }
    return keys;
}

void testShuffleKeys() {
    string json = R"({"a": 1, "b": 2, "c": 3, "d": 4, "e": 5, "f": 6, "g": 7, "h": 8, "i": 9, "j": 10})";
    auto keys = getKeys(json);
    string unformatted = unformat(json);
    auto shuffledKeys = getKeys(unformatted);
    assertNotEquals(keys, shuffledKeys);
}

void testSpecialFeature1() {
    string json = R"([1, 2])";
    string expected = R"([1, 2,])";
    assertEquals(unformat(json), expected);
    json = R"([1, 2, [3, 4]])";
    expected = R"([1, 2, [3, 4,]])";
    assertEquals(unformat(json), expected);
    json = R"([1, 2, [3, 4], [5, 6]])";
    expected = R"([1, 2, [3, 4,] [5, 6],])";
    assertEquals(unformat(json), expected);
}

void testSpecialFeature2() {
  string json =
      "{\"Dog\": \"daisy\", \"Cat\": \"Garfield\", \"Fish\": \"Nemo\"}";
  string expected =
      "{\"DoG\": \"DaIsY\", \"cAt\": \"GaRfIeLd\", \"FiSh\": \"NeMo\"}";
  assertEquals(sPoNgEbObCaSe(json), expected);
}

int main() {
    runTest("testShuffleKeys", testShuffleKeys);
    runTest("testIndent", testIndent);
    runTest("testSpecialFeature1", testSpecialFeature1);
}

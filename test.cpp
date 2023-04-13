//
// Created by redempt on 4/12/23.
//
#include <iostream>

using namespace std;

template <typename T>
void assertEquals(T a, T b) {
    if (a == b) {
        return;
    }
    cout << "Assertion failed: " << a << " != " << b << endl;
    throw false;
}

void run_test(string name, void (*test) ()) {
    try {
        test();
        cout << name << " PASS" << endl;
    } catch (bool e) {
        cout << name << " FAIL" << endl;
    }
}

void testIndent() {
    string jsonString = "{\"Dog\": {\"Name\" : \"Daisy\", \"Breed\" : \"Beagle\"}}";
    string expectedFormat = "{\n\t\"Dog\":\n\t\t{\n\t\t\"Name\" : \"Daisy\",\n\t\t\"Breed\" : \"Beagle\"\n\t\t}\n}";
    assertEquals(expectedFormat, insertIndentation(jsonString));
}

void test1() {
    assertEquals("1", "2");
}

int main() {
    run_test("test1", test1);
    run_test("testIndent", testIndent);
}

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

#include "evaluator.h"

using namespace std;

void show_help() {
    cout << "f = \\x . x  -- set a name f to represent an expression (\\x . "
            "x)\n";
    cout << "? EXPR      -- evaluate the value of EXPR\n";
    cout << "?? EXPR    -- evaluate the value of EXPR and printing the intermediate steps\n";
    cout << "del x       -- delete a name x which is already set\n";
    cout << "help        -- show this help\n";
    cout << "exit        -- exit\n";
    cout << '\n';
}

int main() {
    ostream &err = cerr;

    cout << "- Lambda calculus evaluator -" << endl << endl;

    while (!cin.eof()) {
        cout << ">>> ";
        string s;
        getline(cin, s);

        if (s.substr(0, 5) == "save ") {
            ofstream fout(s.substr(5));
            for (const auto &pr : global_env) {
                fout << pr.first << SPACE << ASSIGN << SPACE;
                print_node(pr.second, cerr, fout);
                fout << '\n';
            }
            continue;
        } else if (s.substr(0, 5) == "read ") {
            ifstream fin(s.substr(5));
            while (!fin.eof()) {
                getline(fin, s);
                auto parts = tokenize(std::move(s));
                if (parts.size() < 3) continue;
                if (get_name(parts[0])) {
                    cerr << parts[0] << " is already set. del it first.\n";
                    continue;
                }
                auto expr = parse(parts.begin() + 2, parts.end());
                if (!expr) continue;
                expr = check(expr);
                if (!expr) continue;
                expr = super_eval(expr);
                if (!expr) continue;
                set_name(parts[0], expr);
                cout << parts[0] << SPACE << ASSIGN << SPACE;
                print_node(expr);
                cout << '\n';
            }
            cout << '\n';
        }

        auto parts = tokenize(std::move(s));
        if (parts.empty()) continue;

#ifdef PRINT_PARTS
        for (auto part : parts) cout << '[' << part << ']' << ' ';
        cout << endl;
#endif

        if (parts.size() == 1 && parts[0] == "exit") {
            break;
        } else if (parts.size() == 1 && parts[0] == "help") {
            show_help();
            continue;
        }

        if (parts[0][0] == PRINT) {
            PNode expr;
            bool print_intermediate = true;
            if (parts.size() > 2 && parts[1][0] == PRINT) {
                expr = parse(parts.begin() + 2, parts.end());
            } else {
                expr = parse(parts.begin() + 1, parts.end());
                print_intermediate = false;
            }
            if (!expr) continue;
            expr = check(expr);
            if (!expr) continue;
            if (print_intermediate) {
                cout << SPACE << SPACE;
                print_node(expr);
                cout << '\n';
                auto pr = evaluate(expr);
                while (pr.first && pr.second) {
                    cout << ASSIGN << SPACE;
                    print_node(pr.second);
                    cout << '\n';
                    pr = evaluate(pr.second);
                }
            } else {
                expr = super_eval(expr);
                if (!expr) continue;
                cout << SPACE << SPACE;
                print_node(expr);
                cout << '\n';
            }
        } else if (parts.size() >= 2 && isalpha(parts[0][0]) &&
                   parts[1][0] == ASSIGN) {
            if (get_name(parts[0])) {
                cerr << parts[0] << " is already set. del it first.\n";
                continue;
            }
            PNode expr = parse(parts.begin() + 2, parts.end());
            if (!expr) continue;
            expr = check(expr);
            if (!expr) continue;
            expr = super_eval(expr);
            if (!expr) continue;
            set_name(parts[0], expr);
        } else if (parts.size() == 2 && parts[0] == "del" &&
                   isalpha(parts[1].front())) {
            unset_name(parts[1]);
        } else {
            err
              << "Wrong format. Maybe you want to put a '?' at the front?\n";
        }
    }

    return 0;
}

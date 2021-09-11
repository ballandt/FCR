#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

bool fileExists(const string&);

string info = "FCR File creator\n===============\n\nFile creator is a software that creates files in command promt.\nfcr <filename> <option>\nOptions:\n\n-n\t\t\t Opens file with notepad\n-s\t\t\t Starts file with default application\n-w\t\t\t Allows to write file in console\n--version\t\t Shows version";
string version = "1.0.0";

int main(int argc, char* argv[]) {
    // Loop to convert argv to string vector for easier handling
    vector<string> args;
    string c_arg;
    args.resize(argc);
    for(int i=0; i<argc; i++) {
        c_arg = argv[i];
        args.at(i) = c_arg;
    }
    
    // Different methods of interaction
    if(argc == 1) { /* Info statement is printed if no parameter is specified. */
        cout << info << endl;
        return 0;
    }
    
    else if(argc == 2) { /* Two parameter cases */
        if(args[1] == "--version") { /* Version is printed */
            cout << "FCR version " << version << endl;
        }
        else { /* File is created without any actions */
            ofstream file{args[1]};
        }
    }
    
    else if(argc > 2) { /* File creation with parameters */
        
        if(args[2] == "-n"){ /* -n (Opened with notepad) */
            if(fileExists(args[1])) { /* If file already exists */
                string com = "notepad " + args[1];
                system(com.c_str());
            } else {
                ofstream file{args[1]};
                file.close();
                string com = "notepad " + args[1];
                system(com.c_str());
            }
            }
        
        else if(args[2] == "-s") { /* -s (Opened with standard app) */
            if(fileExists(args[1])) { /* If file already exists */
                string com = "start " + args[1];
                system(com.c_str());
            } else {
                ofstream file{args[1]};
                file.close();
                string com = "start " + args[1];
                system(com.c_str());                
            }
        }
        
        else if(args[2] == "-w") { /* -w (Writen in console) */
            cout << "========== " << args[1] << " ==========" << endl;
            if(fileExists(args[1])) { /* If file already exists */
                ifstream file{args[1]};
                char content;
                if(file.is_open()) {
                    while(file) {
                        content = file.get();
                        cout << content;
                    }
                    file.close();
                }
            }
            bool loop = true;
            string input = "";
            ofstream file(args[1], ios::app);
            do { /* Loops through until '/end' is entered */
                cin >> input;
                if(input == "/end") {
                    loop = false;
                } else{
                    file << input << endl;
                } 
            } while(loop == true);
            file.close();        
        }
    }
    return 0;
}
    
bool fileExists(const string& arg) { /* Manager if file exists */
    fs::path file{arg};
    if(fs::exists(file)) {
        string answer;
        cout << arg << " already exists. Type 'e' to edit or 'o' to overwrite:  ";
        cin >> answer;
        cout << endl;
        if(answer == "e") {
            return true;
        } else {
            return false;
        }  
    } else {
        return false;
    }
}

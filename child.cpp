
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>



using namespace std;

int main(int argc, char **argv) {
    int count = 0;
    string result = "";
    int period = stoi(argv[3])*1000;//microseconds
    int period_count = 0;
    int remainder = 0;

    bool start = stoi(argv[2]);
    if (start) {
        count = stoi(argv[1]);
    } else {
        ifstream fin("output.txt", ios::in);
        if(fin.is_open()) {
            fin.seekg(0,std::ios_base::end);
            char ch = ' ';
            while(ch != '\n'){
                fin.seekg(-2,std::ios_base::cur);
                //will NOT check the last character
                if((int)fin.tellg() <= 0){
                    fin.seekg(0);
                    break;
                }
                fin.get(ch);
            }
            ch = ' ';
            while(ch != '\n'){
                fin.seekg(-2,std::ios_base::cur);

                if((int)fin.tellg() <= 0){
                    fin.seekg(0);
                    break;
                }
                fin.get(ch);
            }
            std::getline(fin,result);
            fin.close();
            count = stoi(result);
        }
        fin.close();

    }
    ofstream output_file("output.txt", ios::out | ios::app);

    //output_file >> count;
    cout << "CHILD: hello" << endl << "id of the child: " << getpid() << endl;
    output_file << "CHILD: hello" << endl << "id of the child: " << getpid() << endl;
    if(start)
    {
        cout << count << endl;
        output_file << count << endl;
    }
    //each iteration fits exactly 1 second
    while (true) {
        period_count = static_cast<int>((1e6 - remainder)/period );
        if(remainder)
        {
            usleep(remainder);
            count++;
        }

        for(int i = 0; i < period_count; ++i)
        {
            usleep(period);
            count++;
        }
        usleep(1e6 - (period_count*period + remainder));
        if((1e6 - (period_count*period + remainder)) != 0)
            remainder = period - (1e6 - (period_count*period + remainder));
        cout << count << endl;
        output_file << count << endl;


    }


    exit(3);
}


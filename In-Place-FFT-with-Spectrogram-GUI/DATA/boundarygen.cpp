#include <fstream>
#include <iostream>
using namespace std;

int main(void)
{
    ifstream INFILE;
    INFILE.open("C:\\PROJECT\\FFT\\STFT\\GUI\\.resampler\\sample1.txt");
    if(!INFILE)
    {
        cout << "There is no file\n";
        exit(100);
    }
    float bf;
    float max;
    float min;
    INFILE >> bf;
    max = bf;
    min = bf;
    while(!INFILE.eof())
    {
        INFILE >> bf;
        if(max < bf)
            max = bf;
        if (min > bf)
            min = bf;
    }
    INFILE.close();

    cout << "max: " << max << "\n" << "min: " << min;
    return 0;
}
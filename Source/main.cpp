#include <iostream>
#include "Plot.h"
#include <vector>
#include <cmath>
#include <complex>
#include <ctime>


std::vector<double> convertToDecibels(const std::vector<double>& signal, double referenceValue = 1.0) {
    std::vector<double> decibels;
    decibels.reserve(signal.size());

    for (auto value : signal) {
        if (value == 0) {
            decibels.push_back(-100);
        }
        else {
            double dB = 20.0 * log10(fabs(value) / referenceValue);
            decibels.push_back(dB);
        }
    }

    return decibels;
}

//int main(int argv, char* argc[]) {
//
//
//}
//////////////////////////////////////////////////////////////////////////////ASK
int main(int argv, char* argc[]) {
    srand(0);
    Plot* plot = new Plot;

    const double pi = M_PI;
    double start = 0;
    double stop = 10;

    std::vector<double> signal;
    std::vector<int> bitStream;

    double time = 0;
    double fn = 1;
    double fs = 2000;
    double fc = 2;
    double A1 = 1;
    double A2 = 2;

    double W = 0;
    double bitTime = 1.0 / fc;
    double fn1 = (W + 1) / bitTime;
    double fn2 = (W + 2) / bitTime;



    int num_samples = (stop - start) * fs;
    int num_bits = (stop - start) * fc;


    for (int i = 0; i < num_bits; ++i) {
        bitStream.push_back(rand() % 2);
    }
    double phase_shift;

    for (int i = 0; i < num_samples; ++i) {
        time = i / fs;
        int bit_index = static_cast<int>(time * fc);

        //ASK
        switch (bitStream[bit_index])
        {
        case 0:
            signal.push_back(A1 * sin(2 * pi * fn * time));
            break;
        case 1:
            signal.push_back(A2 * sin(2 * pi * fn * time));
            break;

        }

        //PSK
        /*switch (bitStream[bit_index])
        {
        case 0:
            signal.push_back(sin(2 * pi * fn * time));
            break;
        case 1:
            signal.push_back(sin(2 * pi * fn * time + pi));
            break;

        }*/

        //FSK
        /*switch (bitStream[bit_index])
        {
        case 0:
            signal.push_back(sin(2 * pi * fn1 * time));
            break;
        case 1:
            signal.push_back(sin(2 * pi * fn2 * time));
            break;

        }*/

    }


    plot->Start(1000, 600);
    //plot->Start(600, 400);
    plot->Tittle("ASK ORGINALNY Z(T)");
    plot->CreateFunction(start, fs, signal, 'r');
    //program.CreateFunction(start, fm, signal2, 'b');
    //program.CreatePoints(start, fm, signal, 'b',5);
    //program.CreatePoints(start, fm, signal2, 'g', 5);
    plot->Show();
    delete plot;


    double A = 1;
    double devaluator = 0;

    std::vector<double> signal2;
    for (int i = 0; i < signal.size(); i++)
    {
        time = i / fs;
        devaluator = A * sin(2 * pi * fn * time);
        signal2.push_back(
            signal[i] * devaluator
        );
    }


    Plot* plot2 = new Plot();
    plot2->Start(1400, 900);
    plot2->Tittle("ASK X.T");
    plot2->CreateFunction(start, fs, signal2, 'r');
    plot2->Show();

    delete plot2;


    int h = num_samples / bitStream.size();
    std::cout << "H : " << h << "\n";
    std::vector<double> calculusVector;

    for (int i = 0; i < bitStream.size(); i++) {
        double sum = 0;
        for (int j = 0; j < h - 1; j++) {
            int index = i * h + j;
            sum += (signal2[index] + signal2[index + 1]) / 2;
        }
        calculusVector.push_back(sum);
    }

    std::cout << "BITS SIZE: " << bitStream.size() << "\n";

    std::vector<int> demodulatedBits;

    std::cout << "Intergrals:\n ";
    for (const auto& integral : calculusVector)
    {
        std::cout << integral << "\n";
    }

    for (const auto& integral : calculusVector) {
        if (integral < h - 1) {
            demodulatedBits.push_back(0);
        }
        else {
            demodulatedBits.push_back(1);
        }
    }


    std::cout << "Original Bits\n";
    for (const auto it : bitStream) {
        std::cout << it << "\n";
    }

    std::cout << "Demodulated Bits\n";
    for (const auto it : demodulatedBits) {
        std::cout << it << "\n";
    }

    Plot* plot3 = new Plot;
    plot3->Start(1400, 900);
    plot3->Tittle("ASK P.T");
    plot3->CreateFunction(start, fs, calculusVector, 'b');
    plot3->Show();

    delete plot3;

    std::vector<double> bitsOrginal;
    std::vector<double> bitsRegained;
    for (auto it : bitStream)
    {
        bitsOrginal.push_back(it);
    }
    for (auto it : demodulatedBits)
    {
        bitsRegained.push_back(it);
    }

    Plot* plot4 = new Plot;
    plot4->Start(1400, 900);
    plot4->Tittle("ASK ORGINALNE BITY");
    plot4->CreatePoints(start, num_samples, bitsOrginal, 'b', 10);
    plot4->Show();

    delete plot4;


    Plot* plot5 = new Plot;
    plot5->Start(1400, 900);
    plot5->Tittle("ASK ODZYSKANE BITY");
    plot5->CreatePoints(start, num_samples, bitsRegained, 'r', 10);
    plot5->Show();

    delete plot5;

    return 0;
}

//////////////////////////////////////////////////////////////////////////////PSK
/*int main(int argv, char* argc[]) {
    srand(0);
    Program *program = new Program;

    const double pi = M_PI;
    double start = 0;
    double stop = 10;

    std::vector<double> signal;
    std::vector<int> bitStream;

    double time = 0;
    double fn = 1;
    double fs = 2000;
    double fc = 2;
    double A1 = 1;
    double A2 = 2;

    double W = 0;
    double bitTime = 1.0 / fc;
    double fn1 = (W + 1) / bitTime;
    double fn2 = (W + 2) / bitTime;



    int num_samples = (stop - start) * fs;
    int num_bits = (stop - start) * fc;


    for (int i = 0; i < num_bits; ++i) {
        bitStream.push_back(rand() % 2);
    }
    double phase_shift;

    for (int i = 0; i < num_samples; ++i) {
        time = i / fs;
        int bit_index = static_cast<int>(time * fc);
        //double fn1 = (i + 1)/time;
        //double fn2 = (i + 2)/time;
        //std::cout << fn1 << "\n";
        //std::cout << fn2 << "\n";

        //ASK

        /*switch (bitStream[bit_index])
        {
        case 0:
            signal.push_back(A1 * sin(2 * pi * fn * time));
            break;
        case 1:
            signal.push_back(A2 * sin(2 * pi * fn * time));
            break;

        }

        //PSK
        switch (bitStream[bit_index])
        {
        case 0:
            signal.push_back(sin(2 * pi * fn * time));
            break;
        case 1:
            signal.push_back(sin(2 * pi * fn * time + pi));
            break;

        }

        //FSK
        /*switch (bitStream[bit_index])
        {
        case 0:
            signal.push_back(sin(2 * pi * fn1 * time));
            break;
        case 1:
            signal.push_back(sin(2 * pi * fn2 * time));
            break;

        }

    }


    program->Start(1400, 900);
    program->Tittle("PSK ORGINALNY Z.T");
    program->CreateFunction(start, fs, signal,'r');
    //program.CreateFunction(start, fm, signal2, 'b');
    //program.CreatePoints(start, fm, signal, 'b',5);
    //program.CreatePoints(start, fm, signal2, 'g', 5);
    program->Show();
    delete program;


    double A = 1;
    double devaluator = 0;

    std::vector<double> signal2;
    for (int i = 0; i < signal.size(); i++)
    {
        time = i / fs;
        devaluator = A * sin(2 * pi * fn * time);
        signal2.push_back(
            signal[i] * devaluator
        );
    }


    Program* program2 = new Program();
    program2->Start(1400, 900);
    program2->Tittle("PSK X.T");
    program2->CreateFunction(start, fs, signal2, 'r');
    program2->Show();

    delete program2;


    int h = num_samples / bitStream.size();
    std::cout << "H : " << h << "\n";
    std::vector<double> calculusVector;

    for (int i = 0; i < bitStream.size(); i++) {
        double sum = 0;
        for (int j = 0; j < h - 1; j++) {
            int index = i * h + j;
            sum += (signal2[index] + signal2[index + 1]) / 2;
        }
        calculusVector.push_back(sum);
    }

    std::cout << "BITS SIZE: " << bitStream.size() << "\n";

    double threshold = 0.0; 
    std::vector<int> demodulatedBits;

    for (const auto& integral : calculusVector) {
        if (integral > threshold) {
            demodulatedBits.push_back(0);
        }
        else {
            demodulatedBits.push_back(1);
        }
    }


    std::cout << "Original Bits\n";
    for (const auto it : bitStream) {
        std::cout << it << "\n";
    }

    std::cout << "Demodulated Bits\n";
    for (const auto it :demodulatedBits) {
        std::cout << it << "\n";
    }

    Program* program3 = new Program;
    program3->Start(1400, 900);
    program3->Tittle("PSK P.T");
    program3->CreateFunction(start, fs, calculusVector, 'b');
    program3->Show();

    delete program3;

    std::vector<double> bitsOrginal;
    std::vector<double> bitsRegained;
    for (auto it:bitStream)
    {
        bitsOrginal.push_back(it);
    }
    for (auto it : demodulatedBits)
    {
        bitsRegained.push_back(it);
    }

    Program* program4 = new Program;
    program4->Start(1400, 900);
    program4->Tittle("PSK ORGINALNE BITY");
    program4->CreatePoints(start, num_samples, bitsOrginal, 'b',10);
    program4->Show();

    delete program4;


    Program* program5 = new Program;
    program5->Start(1400, 900);
    program5->Tittle("PSK ODZYSKANE BITY");
    program5->CreatePoints(start, num_samples, bitsRegained, 'r', 10);
    program5->Show();

    delete program5;

    return 0;
}*/


//////////////////////////////////////////////////////////////////////////////FSK
/*int main(int argv, char* argc[]) {
    srand(0);
    Program* program = new Program;

    const double pi = M_PI;
    double start = 0;
    double stop = 10;

    std::vector<double> signal;
    std::vector<int> bitStream;

    double time = 0;
    double fn = 1;
    double fs = 2000;
    double fc = 2;
    double A1 = 1;
    double A2 = 2;

    double W = 0;
    double bitTime = 1.0 / fc;
    double fn1 = (W + 1) / bitTime;
    double fn2 = (W + 2) / bitTime;



    int num_samples = (stop - start) * fs;
    int num_bits = (stop - start) * fc;


    for (int i = 0; i < num_bits; ++i) {
        bitStream.push_back(rand() % 2);
    }
    double phase_shift;

    for (int i = 0; i < num_samples; ++i) {
        time = i / fs;
        int bit_index = static_cast<int>(time * fc);
        //double fn1 = (i + 1)/time;
        //double fn2 = (i + 2)/time;
        //std::cout << fn1 << "\n";
        //std::cout << fn2 << "\n";

        //ASK
        /*switch (bitStream[bit_index])
        {
        case 0:
            signal.push_back(A1 * sin(2 * pi * fn * time));
            break;
        case 1:
            signal.push_back(A2 * sin(2 * pi * fn * time));
            break;

        }*/

        //PSK
        /*switch (bitStream[bit_index])
        {
        case 0:
            signal.push_back(sin(2 * pi * fn * time));
            break;
        case 1:
            signal.push_back(sin(2 * pi * fn * time + pi));
            break;

        }

        //FSK
        /*switch (bitStream[bit_index])
        {
        case 0:
            signal.push_back(sin(2 * pi * fn1 * time));
            break;
        case 1:
            signal.push_back(sin(2 * pi * fn2 * time));
            break;

        }

    }


    program->Start(1400, 900);
    program->Tittle("FSK ORGINALNY Z.T");
    program->CreateFunction(start, fs, signal, 'r');
    //program.CreateFunction(start, fm, signal2, 'b');
    //program.CreatePoints(start, fm, signal, 'b',5);
    //program.CreatePoints(start, fm, signal2, 'g', 5);
    program->Show();
    delete program;


    double A = 1;
    double devaluator = 0;

    std::vector<double> signal2;
    for (int i = 0; i < signal.size(); i++)
    {
        time = i / fs;
        devaluator = A * sin(2 * pi * fn1 * time);
        signal2.push_back(
            signal[i] * devaluator
        );
    }

    std::vector<double> signal2_1;
    for (int i = 0; i < signal.size(); i++)
    {
        time = i / fs;
        devaluator = A * sin(2 * pi * fn2 * time);
        signal2_1.push_back(
            signal[i] * devaluator
        );
    }


    Program* program2 = new Program();
    program2->Start(1400, 900);
    program2->Tittle("FSK X.T");
    program2->CreateFunction(start, fs, signal2, 'r');
    program2->Show();

    delete program2;


    Program* program2_1 = new Program();
    program2_1->Start(1400, 900);
    program2_1->Tittle("FSK X.T_2");
    program2_1->CreateFunction(start, fs, signal2_1, 'g');
    program2_1->Show();

    delete program2_1;


    std::cout << "BITS SIZE: " << bitStream.size() << "\n";

    int h = num_samples / bitStream.size();
    std::cout << "H : " << h << "\n";
    std::vector<double> calculusVector;
    std::vector<double> calculusVector2;
    std::vector<double> calculusVectorMain;
    ///
    for (int i = 0; i < bitStream.size(); i++) {
        double sum = 0;
        for (int j = 0; j < h - 1; j++) {
            int index = i * h + j;
            sum += (signal2[index] + signal2[index + 1]) / 2;
        }
        calculusVector.push_back(sum);
    }


    std::cout << "Intergrals:\n ";
    for (const auto& integral : calculusVector)
    {
        std::cout << integral << "\n";
    }

    /////
    ///
    for (int i = 0; i < bitStream.size(); i++) {
        double sum = 0;
        for (int j = 0; j < h - 1; j++) {
            int index = i * h + j;
            sum += (signal2[index] + signal2[index + 1]) / 2;
        }
        calculusVector2.push_back(sum);
    }


    std::cout << "Intergrals2:\n ";
    for (const auto& integral : calculusVector2)
    {
        std::cout << integral << "\n";
    }

    /////
    std::cout << "IntergralsMain:\n ";
    for (int i = 0; i < calculusVector.size(); i++)
    {
        calculusVectorMain.push_back(
            calculusVector2[i] - calculusVector[i]
        );
    }
    /////
    for (const auto& integral : calculusVectorMain)
    {
        std::cout << integral << "\n";
    }


    std::vector<int> demodulatedBits;

    for (const auto& integral : calculusVector) {
        if (integral > 1) {
            demodulatedBits.push_back(0);
        }
        else {
            demodulatedBits.push_back(1);
        }
    }


    std::cout << "Original Bits\n";
    for (const auto it : bitStream) {
        std::cout << it << "\n";
    }

    std::cout << "Demodulated Bits\n";
    for (const auto it : demodulatedBits) {
        std::cout << it << "\n";
    }

    Program* program3 = new Program;
    program3->Start(1400, 900);
    program3->Tittle("FSK P.T");
    program3->CreateFunction(start, fs, calculusVector, 'b');
    program3->Show();

    delete program3;

    std::vector<double> bitsOrginal;
    std::vector<double> bitsRegained;
    for (auto it : bitStream)
    {
        bitsOrginal.push_back(it);
    }
    for (auto it : demodulatedBits)
    {
        bitsRegained.push_back(it);
    }

    Program* program4 = new Program;
    program4->Start(1400, 900);
    program4->Tittle("FSK ORGINALNE BITY");
    program4->CreatePoints(start, num_samples, bitsOrginal, 'b', 10);
    program4->Show();

    delete program4;


    Program* program5 = new Program;
    program5->Start(1400, 900);
    program5->Tittle("FSK ODZYSKANE BITY");
    program5->CreatePoints(start, num_samples, bitsRegained, 'r', 10);
    program5->Show();

    delete program5;

    return 0;
}*/
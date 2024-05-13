#include <iostream>
#include "Program.h"
#include <vector>
#include <cmath>
#include <complex>
#include <ctime>

/*std::vector<std::complex<double>> DFT(const std::vector<std::complex<double>>& signal) {
    std::vector<std::complex<double>> spectrum(signal.size());
    const std::complex<double> I(0, 1);

    for (int k = 0; k < signal.size(); ++k) {
        std::complex<double> sum = 0.0;

        for (int n = 0; n < signal.size(); ++n) {
            double angle = -2 * M_PI * k * n / signal.size();
            sum += signal[n] * std::exp(I * angle);
        }

        spectrum[k] = sum;
    }

    return spectrum;
}

std::vector<double> calculateAmplitudeSpectrum(const std::vector<std::complex<double>>& spectrum) {
    std::vector<double> amplitude(spectrum.size());
    for (size_t i = 0; i < amplitude.size(); ++i) {
        amplitude[i] = std::abs(spectrum[i]);
    }
    return amplitude;
}*/

/*std::vector<double> toDecibel(const std::vector<double>& amplitude) {
    std::vector<double> decibel(amplitude.size());
    for (size_t i = 0; i < amplitude.size(); ++i) {
        std::cout << amplitude[i] << "\n";
        decibel[i] = 10 * log10(std::fabs(amplitude[i]));
    }
    for (size_t i = 0; i < amplitude.size(); ++i) {
        decibel[i] *= -1;
    }
    return decibel;
}*/

/*std::vector<double> toDecibel(const std::vector<double>& amplitude) {
    std::vector<double> decibel(amplitude.size());
    for (size_t i = 0; i < amplitude.size(); ++i) {
        decibel[i] = amplitude[i] * std::pow(10.0f,10 * 0.05f);
        //std::cout << decibel[i] << "\n";
    }
    return decibel;
}*/

/*std::vector<double> toDecibel(const std::vector<double>& amplitude) {
    std::vector<double> decibel(amplitude.size());
    for (size_t i = 0; i < amplitude.size(); ++i) {
        if (amplitude[i] <= 0) {
            throw std::domain_error("Amplitude must be positive for logarithmic conversion.");
        }
        decibel[i] = 20 * std::log10(amplitude[i]);
    }
    return decibel;
}*/


std::vector<double> toDecibel(const std::vector<double>& signal) {
    std::vector<double> decibel(signal.size());
    for (size_t i = 0; i < signal.size(); ++i) {
        double power = signal[i] * signal[i];
        if (power == 0) {
            decibel[i] = -std::numeric_limits<double>::infinity();
        }
        else {
            decibel[i] = 10 * std::log10(power);
        }
    }
    return decibel;
}

int main(int argv, char* argc[]) {

    // Faza pocz¹tkowa dla g³ównej funkcji cosinus (phi) to start pêtli
    // Czas trwania to ró¿nica pomiêdzy startem a warunkiem przerwania pêtli
    // Czêstotliwoœæ próbkowania oznacza ile razy i musi zostaæ zwiêkszone aby z np 2 zmieni³o siê na 3
    // Iloœæ próbek to czas trwania razy czêstotliwoœæ

    const double pi = 3.14;
    double start = 0;
    double stop = 3;

    Program program;

    std::vector<double> signal;
    std::vector<double> signal2;
    std::vector<int> bitStream;

    double mt = 0;

    double kA = 30;
    double kP = 7.5;
    double KF = 7.4;

    double fn = 1000;
    double fm = fn * 2.5;


    int A1 = 2; // Losowa Liczba
    int A2 = 10;// Losowa Liczba różna od A1

    int random = 0;


    for (double i = start; i < stop; i += 1 / fn) {
        random = rand() % 2;
        bitStream.push_back(random);
    }
    int counter = 0;

    for (double i = start; i < stop; i += 1 / fn)
    {
        mt = sin(2 * pi * fn * i);
        switch (bitStream[counter])
        {
            case 0:
                signal.push_back(
                    A1 * mt
                );
                break;
            case 1:
                signal.push_back(
                    A2 * mt
                );
                break;
        }
        counter++;
        //////////////////////////////////AMPLITUDA
        signal.push_back(
            ((kA * mt + 1)) //cos(2 * pi * fm * i))
        );

        signal2.push_back(
            (kA * mt +1) * cos(2*pi*fn * i)
        );


    }

    std::vector<double> decibel = toDecibel(signal2);


    program.Start(1400, 900);
    program.CreateFunction(start, fm, signal,'r');
    //program.CreateFunction(start, fm, signal2, 'b');
    //program.CreatePoints(start, fm, signal, 'b',5);
    //program.CreatePoints(start, fm, signal2, 'g', 5);

    program.Show();

    return 0;
}
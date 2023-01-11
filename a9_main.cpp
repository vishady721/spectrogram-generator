#include <iostream>

#include "a9.h"
#include <iostream>
#include "AudioFile.h"
#include <cmath>

using namespace std;

Image spectrogramImage(string path) {
  vector<complex<double>> samples = get_samples(path);
  vector<vector<float>> stfts = stft(1500, 2048, samples);
  Image spectro = bitmap_to_spectrogram(stfts);
  return spectro;
};

int main()
{
    // Test your intermediate functions
    Image spect1 = spectrogramImage("Input/taylorswift.wav");
    spect1.write("Output/taylorswift.png");
    Image spect2 = spectrogramImage("Input/dizzygillespie.wav");
    spect2.write("Output/dizzygillespie.png");
    Image spect3 = spectrogramImage("Input/westonestate.wav");
    spect3.write("Output/westonestate.png");
    Image spect4 = spectrogramImage("Input/fredo.wav");
    spect4.write("Output/fredo.png");
    return EXIT_SUCCESS;
}

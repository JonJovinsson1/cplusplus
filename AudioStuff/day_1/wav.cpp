// https://www.youtube.com/@ferrabacus2980/videos
// https://www.youtube.com/watch?v=rHqkeLxAsTc

#include <iostream>
#include <fstream>
#include <cmath>

using  namespace std;

// Riff chunk
const string chunk_id = "RIFF";
const string chunk_size = "----";
const string format = "WAVE";

// FMT sub chunk
const string subchunk1_id = "fmt ";
const int subchunk1_size = 16;
const int audio_format = 1;
const int num_channels = 2;
const int sample_rate = 44100;
const int byte_rate = sample_rate * num_channels * (subchunk1_size / 8);
const int block_align = num_channels * (subchunk1_size / 8);
const int bits_per_sample = 16;

// Data sub chunk
const string subchunk2_id = "data";
const string subchunk2_size = "----";

const int duration = 2;
const int max_amplitude = 32760;
const double frequency = 250;

void write_as_byte(ofstream &file, int value, int byte_size){
    file.write(reinterpret_cast<const char*>(&value), byte_size);
}

int main() {

    ofstream wav;
    wav.open("test.wav", ios::binary);

    if(wav.is_open()){
        wav << chunk_id;
        wav << chunk_size;
        wav << format;

        wav << subchunk1_id;
        write_as_byte(wav, subchunk1_size, 4);
        write_as_byte(wav, audio_format,2);
        write_as_byte(wav, num_channels, 2);
        write_as_byte(wav, sample_rate, 4);
        write_as_byte(wav, byte_rate, 4);
        write_as_byte(wav, block_align, 2);
        write_as_byte(wav, bits_per_sample,2);


        wav << subchunk2_id;
        wav << subchunk2_size;

        int start_audio = wav.tellp();

        for(int i = 0; i < sample_rate * duration; i++) {
            // respect max amplitude
            // operate as a wave
            double amplitude = (double)i / sample_rate * max_amplitude;
            double value = sin((2 * 3.14 * i * frequency) / sample_rate);

            double channel1 = amplitude * value / 2;
            double channel2 = (max_amplitude - amplitude) * value;

            write_as_byte(wav, channel1, 2);
            write_as_byte(wav, channel2, 2);

        }

        int end_audio = wav.tellp();
        wav.seekp(start_audio - 4);
        write_as_byte(wav, end_audio - start_audio, 4);

        wav.seekp(4, ios::beg);
        write_as_byte(wav, end_audio - 8, 4); 
    }
    wav.close();
    return 0;
}
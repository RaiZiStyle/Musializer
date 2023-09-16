#include <assert.h>
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define ARRAY_LEN(xs) sizeof(xs) / sizeof(xs[0])


typedef struct {
    float left;
    float right;
} Frame;

Frame global_frames[4410*2] = {};  // Contain 2 channels
size_t global_frames_count = 0;

// Used to take the current sound wave (or frames, or sample) and copy it to global_frames.
// QUESTION: Why does *bufferData is Empty ?  it point to nothing
void callback(void *bufferData, unsigned int frames) {
    size_t capacity = ARRAY_LEN(global_frames);
    // Used to do kinda a Ring buffer
    if (frames <= capacity - global_frames_count) {
        memcpy(global_frames + global_frames_count, bufferData, sizeof(Frame) * frames);
        global_frames_count += frames;
        // Shifting doing here.
    } else if (frames <= capacity) {
        memmove(global_frames, global_frames + frames, sizeof(Frame) * (capacity - frames));
        memcpy(global_frames + (capacity - frames), bufferData, sizeof(Frame) * frames);
    } else {
        memcpy(global_frames, bufferData, sizeof(Frame) * capacity);
        global_frames_count = capacity;
    }
}

int main() {
    InitWindow(800, 600, "Musializer");
    SetTargetFPS(60);

    InitAudioDevice();
    // Music music = LoadMusicStream("file_example.ogg");
    // Music music = LoadMusicStream("Example.ogg");
    Music music = LoadMusicStream("1vs0_JuniorGroove.ogg");

    assert(music.stream.sampleSize == 16);
    assert(music.stream.channels == 2);

    printf("music.frameCount = %u\n", music.frameCount);
    printf("music.sampleRate = %u\n", music.stream.sampleRate);
    printf("music.stream.sampleSize = %u\n", music.stream.sampleSize);
    printf("music.stream.channels = %u\n", music.stream.channels);

    sleep(3);

    PlayMusicStream(music);
    SetMusicVolume(music, 1);
    AttachAudioStreamProcessor(music.stream, callback);
    while (!WindowShouldClose()) {
        UpdateMusicStream(music);
        if (IsKeyPressed(KEY_SPACE)) {
            if (IsMusicStreamPlaying(music)) {
                PauseMusicStream(music);

            } else {
                ResumeMusicStream(music);
            }
        }

        int w = GetRenderWidth();
        int h = GetRenderHeight();

        BeginDrawing();
        ClearBackground(CLITERAL(Color){0x18, 0x18, 0x18, 0xFF});

        float cell_width = (float)w / global_frames_count;  // Get cell Width based on global_frames
        for (size_t i = 0; i < global_frames_count; i++) {
            // Size global_frames is 32bits, this will take either one of the channel and take a sample
            // int16_t sample = *(int16_t *)&global_frames[i];
            float t = global_frames[i].left;    

            // The normalizeation. We need to map the value of the sample based on the sreens.
            // Drawing Positif sample
            if (t > 0) {
                // float t = (float)sample / INT16_MAX;  // Round value between 0 and 1
                DrawRectangle(i * cell_width, h / 2 - h / 2 * t, 1, h / 2 * t, RED);
                // Drawing Negatif sample
            } else {
                // float t = (float)sample / INT16_MIN;
                DrawRectangle(i * cell_width, h / 2, 1, h / 2 * t, RED);
            }
            printf("s : %f\t", t );
        }
        printf("\n");


        EndDrawing();
    }

    return 0;
}

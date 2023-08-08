#include <assert.h>
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define ARRAY_LEN(xs) sizeof(xs) / sizeof(xs[0])

uint32_t global_frames[1024] = {};  // Contain 2 channels
size_t global_frames_count = 0;

// Used to take the current sound wave (or frames, or sample) and copy it to global_frames.
void callback(void *bufferData, unsigned int frames) {
    // Size we have a fixed size of global frames, we need to check if the frames will fit in global_frames[]
    if (frames > ARRAY_LEN(global_frames)) {
        frames = ARRAY_LEN(global_frames);
    }
    // QUESTION: Why does *bufferData is Empty ?  it point to nothing
    memcpy(global_frames, bufferData, sizeof(uint32_t) * frames);
    global_frames_count = frames;
    // printf("Callback(frames = %u)\n", frames);
}

int main() {
    InitWindow(800, 600, "Musializer");
    SetTargetFPS(60);

    InitAudioDevice();
    Music music = LoadMusicStream("file_example.ogg");

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

        float cell_width = (float) w / global_frames_count; // Get cell Width based on global_frames
        for (size_t i = 0; i < global_frames_count; i++) {
            // Size global_frames is 32bits, this will take either one of the channel and take a sample
            int16_t sample = *(int16_t *)&global_frames[i];
            // The normalizeation. We need to map the value of the sample based on the sreens.
            float t = (float)sample/INT16_MAX; 
            if (sample > 0) {
                DrawRectangle( i *cell_width , h / 2 -  h /2*t, cell_width , h/2*t , RED);
            }else {
                float t = (float)sample/INT16_MIN;
                DrawRectangle( i * cell_width , h/2, cell_width , h/2*t, RED);
            }
            // printf("%d ", sample);
        }
        // printf("\n");
        // if (global_frames_count > 0 ) exit(1);

        EndDrawing();
    }

    return 0;
}

#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>

#define ARRAY_LEN(xs) sizeof(xs) / sizeof(xs[0])

uint32_t global_frames[1024] = {};
size_t global_frames_count = 0;

void callback(void *bufferData, unsigned int frames) {
    // Size we have a fixed size of global frames, we need to check if the frames will fit in global_frames[]
    if (frames > ARRAY_LEN(global_frames)) {
        frames = ARRAY_LEN(global_frames);
    }
    memcpy(global_frames, bufferData, frames * sizeof(uint32_t) * frames);
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
        if (IsKeyPressed(KEY_SPACE)) {
            if (IsMusicStreamPlaying(music)) {
                PauseMusicStream(music);

            } else {
                ResumeMusicStream(music);
            }
        }

        UpdateMusicStream(music);

        BeginDrawing();
        ClearBackground(CLITERAL(Color) {0x18, 0x18, 0x18 , 0xFF});
        
        
        for (size_t i = 0; i < global_frames_count; i++){

        }


        EndDrawing();
    }

    return 0;
}

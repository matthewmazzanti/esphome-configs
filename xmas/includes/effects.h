#include "esphome.h"

using namespace esphome;

void candle(light::LightState *state, float brightness = 1.0) {
    static const int candle_dist[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 2, 4, 8, 16, 32, 64, 128, 256
    };

    // Total size of our distribution
    static const int count = sizeof(candle_dist) / sizeof(candle_dist[0]);
    // Range of our random generation
    static const int range = []() {
        int range = 0;
        for (int i = 0; i < count; i++) {
            range += candle_dist[i];
        }
        return range;
    }();

    auto call = state->turn_on();

    // Pseudo-random uniform distribution [0-count]
    int random = rand() % range;
    // Brightness step
    float brightness_step = state->remote_values.get_brightness() / count;

    // Reverse iteration, since last items have higher probabilities
    int total = 0;
    for (int i = count - 1; i >= 0; i--) {
        total += candle_dist[i];

        if (total > random) {
            call.set_brightness(brightness_step * (i + 1));
            break;
        }
    }

    // Transition length is longer than interval for a low-pass filter effect
    call.set_transition_length(150);
    // Do not publish to homeassistant
    call.set_publish(false);
    call.set_save(false);
    call.set_state(true);
    call.perform();
}

#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

#include "acdb_data.h"

#define LIB_AUDIO_HAL "audio.primary." BOARD_PLATFORM ".so"

typedef int (*platform_get_snd_device_acdb_id_t)(int);
typedef int (*platform_get_snd_device_index_t)(char *);

int main() {
    platform_get_snd_device_acdb_id_t platform_get_snd_device_acdb_id = NULL;
    platform_get_snd_device_index_t platform_get_snd_device_index = NULL;
    void *handle = NULL;
    int i;

    /* Try ld path first */
    handle = dlopen(LIB_AUDIO_HAL, RTLD_LAZY);
    if (handle == NULL) {
        char audio_hal[1024] = {0};

        snprintf(audio_hal, sizeof(audio_hal),
                 "/vendor/lib/hw/%s", LIB_AUDIO_HAL);

        handle = dlopen(audio_hal, RTLD_LAZY);
        if (handle == NULL) {
            fprintf(stderr, "%s\n", dlerror());
            return 1;
        }
        fprintf(stderr, "Loaded %s\n\n", audio_hal);
    } else {
        fprintf(stderr, "Loaded %s\n\n", LIB_AUDIO_HAL);
    }

    platform_get_snd_device_acdb_id = (platform_get_snd_device_acdb_id_t) dlsym(handle, "platform_get_snd_device_acdb_id");
    if (platform_get_snd_device_acdb_id == NULL)  {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    platform_get_snd_device_index =
        (platform_get_snd_device_index_t)dlsym(handle, "platform_get_snd_device_index");
    if (platform_get_snd_device_index == NULL)  {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    printf("    <acdb_ids>\n");
    for (i = 1; i < SND_DEVICE_MAX; i++) {
        int dev = platform_get_snd_device_index(device_table[i]);
        int acdb_id = platform_get_snd_device_acdb_id(dev);

        if (acdb_id <= 0) {
            continue;
        }

        printf("        <device name=\"%s\" acdb_id=\"%d\"/>\n",
               device_table[i], acdb_id);
    }
    printf("    </acdb_ids>\n");

    dlclose(handle);
    return 0;
}

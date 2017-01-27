#include <stdlib.h>
#include <dlfcn.h>

#include "acdb_data.h"

typedef int (*platform_get_snd_device_acdb_id_t)(int);

int main() {
    void *handle;
    const char *error;
    platform_get_snd_device_acdb_id_t platform_get_snd_device_acdb_id;

    handle = dlopen("/system/lib/hw/audio.primary.msm8952.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    dlerror(); /* Clear any existing error */

    platform_get_snd_device_acdb_id = (platform_get_snd_device_acdb_id_t)dlsym(handle, "platform_get_snd_device_acdb_id");

    error = dlerror();
    if (error != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    for (int dev = 1; dev < SND_DEVICE_MAX; dev++)
        printf("%s: %i\n", device_table[dev], platform_get_snd_device_acdb_id(dev));

    dlclose(handle);
    exit(EXIT_SUCCESS);
}

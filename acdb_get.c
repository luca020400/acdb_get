#include <stdlib.h>
#include <dlfcn.h>

#include "acdb_data.h"

typedef int snd_device_t;

int main() {
    void *handle;
    const char *error;
    snd_device_t (*snd_device)(snd_device_t);

    handle = dlopen("/system/lib/hw/audio.primary.msm8952.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    dlerror(); /* Clear any existing error */

    snd_device = (snd_device_t (*)(snd_device_t)) dlsym(handle, "platform_get_snd_device_acdb_id");

    error = dlerror();
    if (error != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    int dev;
    for (dev = 0; dev < SND_DEVICE_MAX; dev++)
        printf("%s: %i\n", device_table[dev], (*snd_device)(dev));

    dlclose(handle);
    exit(EXIT_SUCCESS);
}

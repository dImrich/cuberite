
#pragma once

#define BUILD_ID

#ifdef BUILD_ID

#undef BUILD_ID

#define BUILD_SERIES_NAME "local build"
#define BUILD_ID          "Unknown"
#define BUILD_COMMIT_ID   "approx: 19302eeb87e6b915786ea7fa156ac3bc2ce451b4"
#define BUILD_DATETIME    "approx: 2021-01-21 22:51:55 +0000"
#endif


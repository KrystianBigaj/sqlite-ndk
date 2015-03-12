SQLite-NDK is a VFS (http://www.sqlite.org/vfs.html),
that gives you access to SQLite databases stored in .apk 'assets' directory (you don't need to copy database to SD card). Asset files in .apk are read-only, so database can be opened only as SQLITE\_OPEN\_READONLY.

Requires Android 2.3+, you must link with 'android' library in your Android.mk:
LOCAL\_LDLIBS = -landroid ...

Usage (see sqlite-ndk/example/jni for complete example):
```
#include <sqlite3.h>
#include <sqlite3ndk.h>
...

void android_main(struct android_app* app)
{
  // Initialize (call it only once)
  sqlite3_ndk_init(app->activity->assetManager);
  ...
  // Next you can use sqlite3_open_v2 with 4th parameter as SQLITE_NDK_VFS_NAME
  // to open your SQLite database from .apk 'assets' directory
  sqlite3_open_v2("my-example-db.sqlite3", &db, SQLITE_OPEN_READONLY,
			SQLITE_NDK_VFS_NAME) 
  ...
```
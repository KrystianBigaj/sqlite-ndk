*** SQLite-NDK

SQLite-NDK is a VFS (http://www.sqlite.org/vfs.html),
that gives you access to SQLite database stored in .apk 'asset' directory.

Requires Android 2.3+, you must link with 'android' library in your Android.mk:
LOCAL_LDLIBS = -landroid ...

Project page: http://code.google.com/p/sqlite-ndk/
Author: Krystian Bigaj
Email: krystian.bigaj@gmail.com
License: MPL 1.1/GPL 2.0/LGPL 2.1

#include <jni.h>
#include <errno.h>

#include <android/sensor.h>
#include <android/asset_manager.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include <sqlite3.h>
#include <sqlite3ndk.h>

#ifndef LOG_TAG
#define LOG_TAG "sqlite-ndk"
#endif

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))

void SQLiteNDKTest(void)
{
	sqlite3 *db;
	sqlite3_stmt *stmt;

	LOGI("sqlite3_open_v2(my-example-db.sqlite3)");

	// Open database: my-example-db.sqlite3
	// Path is relative to 'assets' directory (.../example/assets)
	// Database can be opened only as read-only (SQLITE_OPEN_READONLY)
	// Last parameter is VFS name (SQLITE_NDK_VFS_NAME),
	// which can be used after inital call to: sqlite3_ndk_init (see below android_main)
	if (sqlite3_open_v2("my-example-db.sqlite3", &db, SQLITE_OPEN_READONLY,
			SQLITE_NDK_VFS_NAME) == SQLITE_OK)
	{
		LOGI("sqlite3_open_v2 SQLITE_OK");

		LOGI("sqlite3_prepare_v2(SELECT Value FROM MyTable)");
		if (sqlite3_prepare_v2(db, "SELECT Value FROM MyTable", -1, &stmt, NULL)
				== SQLITE_OK)
		{
			LOGI("SQLITE_OK");

			int err;
			LOGI("sqlite3_step");
			while ((err = sqlite3_step(stmt)) == SQLITE_ROW)
			{
				LOGI("sqlite3_step SQLITE_ROW");

				LOGI("sqlite3_column_text");

				// This should print:
				// Value: Hello world!
				LOGI("Value: %s\n\n", sqlite3_column_text(stmt, 0));
			}

			if (err != SQLITE_DONE)
			{
				LOGI("Query execution failed: %s\n",
						sqlite3_errmsg(db));
			}

			LOGI("sqlite3_finalize");
			sqlite3_finalize(stmt);
		}
		else
		{
			LOGI("Can't execute query: %s\n", sqlite3_errmsg(db));
		}
	}
	else
	{
		LOGI("Can't open database: %s\n", sqlite3_errmsg(db));
	}

	LOGI("sqlite3_close");
	sqlite3_close(db);
}

void android_main(struct android_app* app)
{
	LOGI("sqlite3_ndk_init...");

	// Call sqlite3_ndk_init only once before using VFS (SQLITE_NDK_VFS_NAME),
	// it will register VFS into SQLite
	if (sqlite3_ndk_init(app->activity->assetManager) != SQLITE_OK)
	{
		LOGI("sqlite3_ndk_init failed!");
		return;
	}
	LOGI("sqlite3_ndk_init OK");

	SQLiteNDKTest();

	// Make sure glue isn't stripped.
	app_dummy();
}

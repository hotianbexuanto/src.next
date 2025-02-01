// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/android/content_uri_utils.h"

#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "base/base_jni_headers/ContentUriUtils_jni.h"

using base::android::ConvertUTF8ToJavaString;
using base::android::ScopedJavaLocalRef;

namespace base {
<<<<<<< HEAD

namespace internal {
=======
>>>>>>> chromium

bool ContentUriExists(const FilePath& content_uri) {
  JNIEnv* env = base::android::AttachCurrentThread();
  ScopedJavaLocalRef<jstring> j_uri =
      ConvertUTF8ToJavaString(env, content_uri.value());
  return Java_ContentUriUtils_contentUriExists(env, j_uri);
}

<<<<<<< HEAD
bool ContentUriGetFileInfo(const FilePath& content_uri,
                           FileEnumerator::FileInfo* info) {
  JNIEnv* env = android::AttachCurrentThread();
  std::vector<FileEnumerator::FileInfo> list;
  Java_ContentUriUtils_getFileInfo(env, content_uri.value(),
                                   reinterpret_cast<jlong>(&list));
  // Java will call back sync to AddFileInfoToVector(&list).
  if (list.empty()) {
    return false;
  }
  // Android can return -1 for unknown size, which
  // we can't deal with, so we will consider that the file wasn't found.
  if (list[0].GetSize() < 0) {
    LOG(ERROR) << "Unknown file length for " << content_uri;
    return false;
  }
  *info = std::move(list[0]);
  return true;
}

std::vector<FileEnumerator::FileInfo> ListContentUriDirectory(
    const FilePath& content_uri) {
  JNIEnv* env = android::AttachCurrentThread();
  std::vector<FileEnumerator::FileInfo> result;
  Java_ContentUriUtils_listDirectory(env, content_uri.value(),
                                     reinterpret_cast<jlong>(&result));
  // Java will call back sync to AddFileInfoToVector(&result).
  return result;
}

bool DeleteContentUri(const FilePath& content_uri) {
  DCHECK(content_uri.IsContentUri());
  JNIEnv* env = android::AttachCurrentThread();
  return Java_ContentUriUtils_delete(env, content_uri.value());
}

bool IsDocumentUri(const FilePath& content_uri) {
  DCHECK(content_uri.IsContentUri());
  JNIEnv* env = android::AttachCurrentThread();
  return Java_ContentUriUtils_isDocumentUri(env, content_uri.value());
}

}  // namespace internal

void JNI_ContentUriUtils_AddFileInfoToVector(JNIEnv* env,
                                             jlong vector_pointer,
                                             std::string& uri,
                                             std::string& display_name,
                                             jboolean is_directory,
                                             jlong size,
                                             jlong last_modified) {
  auto* result =
      reinterpret_cast<std::vector<FileEnumerator::FileInfo>*>(vector_pointer);
  result->emplace_back(FilePath(uri), FilePath(display_name), is_directory,
                       size,
                       Time::FromMillisecondsSinceUnixEpoch(last_modified));
}

std::string GetContentUriMimeType(const FilePath& content_uri) {
  JNIEnv* env = android::AttachCurrentThread();
  return Java_ContentUriUtils_getMimeType(env, content_uri.value());
=======
File OpenContentUriForRead(const FilePath& content_uri) {
  JNIEnv* env = base::android::AttachCurrentThread();
  ScopedJavaLocalRef<jstring> j_uri =
      ConvertUTF8ToJavaString(env, content_uri.value());
  jint fd = Java_ContentUriUtils_openContentUriForRead(env, j_uri);
  if (fd < 0)
    return File();
  return File(fd);
}

std::string GetContentUriMimeType(const FilePath& content_uri) {
  JNIEnv* env = base::android::AttachCurrentThread();
  ScopedJavaLocalRef<jstring> j_uri =
      ConvertUTF8ToJavaString(env, content_uri.value());
  ScopedJavaLocalRef<jstring> j_mime =
      Java_ContentUriUtils_getMimeType(env, j_uri);
  if (j_mime.is_null())
    return std::string();

  return base::android::ConvertJavaStringToUTF8(env, j_mime.obj());
>>>>>>> chromium
}

bool MaybeGetFileDisplayName(const FilePath& content_uri,
                             std::u16string* file_display_name) {
  if (!content_uri.IsContentUri()) {
    return false;
  }

  DCHECK(file_display_name);

  JNIEnv* env = base::android::AttachCurrentThread();
  ScopedJavaLocalRef<jstring> j_uri =
      ConvertUTF8ToJavaString(env, content_uri.value());
  ScopedJavaLocalRef<jstring> j_display_name =
      Java_ContentUriUtils_maybeGetDisplayName(env, j_uri);

  if (j_display_name.is_null()) {
    return false;
  }

  *file_display_name = base::android::ConvertJavaStringToUTF16(j_display_name);
  return true;
}

<<<<<<< HEAD
FilePath ContentUriBuildDocumentUriUsingTree(
    const FilePath& tree_uri,
    const std::string& encoded_document_id) {
  JNIEnv* env = android::AttachCurrentThread();
  std::string j_uri = Java_ContentUriUtils_buildDocumentUriUsingTree(
      env, tree_uri.value(), encoded_document_id);
  return FilePath(j_uri);
}

FilePath ContentUriGetChildDocumentOrQuery(const FilePath& parent,
                                           const std::string& display_name,
                                           const std::string& mime_type,
                                           bool is_directory,
                                           bool create) {
  JNIEnv* env = android::AttachCurrentThread();
  std::string j_uri = Java_ContentUriUtils_getChildDocumentOrQuery(
      env, parent.value(), display_name, mime_type, is_directory, create);
  return FilePath(j_uri);
}

bool ContentUriIsCreateChildDocumentQuery(const FilePath& content_uri) {
  JNIEnv* env = android::AttachCurrentThread();
  return Java_ContentUriUtils_isCreateChildDocumentQuery(env,
                                                         content_uri.value());
}

FilePath ContentUriGetDocumentFromQuery(const FilePath& content_uri,
                                        bool create) {
  JNIEnv* env = android::AttachCurrentThread();
  std::string j_uri = Java_ContentUriUtils_getDocumentFromQuery(
      env, content_uri.value(), create);
  return FilePath(j_uri);
=======
bool DeleteContentUri(const FilePath& content_uri) {
  DCHECK(content_uri.IsContentUri());
  JNIEnv* env = base::android::AttachCurrentThread();
  ScopedJavaLocalRef<jstring> j_uri =
      ConvertUTF8ToJavaString(env, content_uri.value());

  return Java_ContentUriUtils_delete(env, j_uri);
}

FilePath GetContentUriFromFilePath(const FilePath& file_path) {
  JNIEnv* env = base::android::AttachCurrentThread();
  ScopedJavaLocalRef<jstring> j_file_path =
      ConvertUTF8ToJavaString(env, file_path.value());
  ScopedJavaLocalRef<jstring> j_content_uri =
      Java_ContentUriUtils_getContentUriFromFilePath(env, j_file_path);
  if (j_content_uri.is_null())
    return FilePath();

  return FilePath(base::android::ConvertJavaStringToUTF8(env, j_content_uri));
>>>>>>> chromium
}

}  // namespace base

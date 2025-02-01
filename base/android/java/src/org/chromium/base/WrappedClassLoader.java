// Copyright 2021 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.base;

import dalvik.system.BaseDexClassLoader;

import org.chromium.build.annotations.NullMarked;
import org.chromium.build.annotations.Nullable;

/**
 * This class wraps two given BaseDexClassLoader's and delegates findClass() and findLibrary() calls
 * to the first one that returns a match.
 */
@NullMarked
public class WrappedClassLoader extends ClassLoader {
    private BaseDexClassLoader mPrimaryClassLoader;
    private BaseDexClassLoader mSecondaryClassLoader;

    public WrappedClassLoader(BaseDexClassLoader primary, BaseDexClassLoader secondary) {
        this.mPrimaryClassLoader = primary;
        this.mSecondaryClassLoader = secondary;
    }

    @Override
    protected Class<?> findClass(String name) throws ClassNotFoundException {
        try {
            return mPrimaryClassLoader.loadClass(name);
        } catch (ClassNotFoundException e) {
            return mSecondaryClassLoader.loadClass(name);
        }
    }

    @Override
<<<<<<< HEAD
    public @Nullable String findLibrary(String name) {
        String path = null;
        // BaseDexClassLoader has a public findLibrary method, but ClassLoader's is protected
        // so we can only do this for classloaders that actually do extend BaseDexClassLoader.
        // findLibrary is rarely used so it's fine to just check this each time.
        if (mPrimaryClassLoader instanceof BaseDexClassLoader) {
            path = ((BaseDexClassLoader) mPrimaryClassLoader).findLibrary(name);
            if (path != null) return path;
        }
        if (mSecondaryClassLoader instanceof BaseDexClassLoader) {
            path = ((BaseDexClassLoader) mSecondaryClassLoader).findLibrary(name);
        }
        return path;
=======
    public String findLibrary(String name) {
        String path = mPrimaryClassLoader.findLibrary(name);
        if (path != null) return path;

        return mSecondaryClassLoader.findLibrary(name);
>>>>>>> chromium
    }
}

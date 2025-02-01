// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.base;

import org.chromium.base.annotations.JNINamespace;
import org.chromium.base.annotations.MainDex;
import org.chromium.base.annotations.NativeMethods;

<<<<<<< HEAD
import org.chromium.build.annotations.CheckDiscard;
import org.chromium.build.annotations.NullMarked;
import org.chromium.build.annotations.Nullable;

/**
 * Utilities related to timestamps, including the ability to use fake time for tests via
 * FakeTimeTestRule.
 */
@NullMarked
=======
/** Time-related utilities. */
@JNINamespace("base::android")
@MainDex
>>>>>>> chromium
public class TimeUtils {
    private TimeUtils() {}

    // For conversion from MILLISECONDS use {@android.text.format.DateUtils#*_IN_MILLIS}
    public static final int NANOSECONDS_PER_MILLISECOND = 1000000;
    public static final int SECONDS_PER_MINUTE = 60;
    public static final int SECONDS_PER_HOUR = 3600; // 60 sec * 60 min
    public static final int SECONDS_PER_DAY = 86400;

    @NativeMethods
    public interface Natives {
        // 60 sec * 60 min * 24 h

<<<<<<< HEAD
    // Used by FakeTimeTestRule. Visibility is restricted to ensure tests use the rule, which
    // restores the value to null in its clean-up logic.
    static @Nullable FakeClock sFakeClock;

    /**
     * Wrapper for System.currentTimeMillis() (milliseconds since the epoch).
     * Can be faked in tests using FakeTimeTestRule.
     * See: https://developer.android.com/reference/android/os/SystemClock
     */
    @CheckDiscard("Should get inlined by R8.")
    public static long currentTimeMillis() {
        if (sFakeClock != null) {
            return sFakeClock.currentTimeMillis();
        }
        return System.currentTimeMillis();
    }

    /**
     * Wrapper for SystemClock.uptimeMillis() (uptime excluding deep sleep).
     * Can be faked in tests using FakeTimeTestRule.
     * See: https://developer.android.com/reference/android/os/SystemClock
     */
    @CheckDiscard("Should get inlined by R8.")
    public static long uptimeMillis() {
        if (sFakeClock != null) {
            return sFakeClock.uptimeMillis();
        }
        return SystemClock.uptimeMillis();
    }

    /**
     * Wrapper for SystemClock.elapsedRealtimeNanos() (uptime including deep sleep).
     * Can be faked in tests using FakeTimeTestRule.
     * See: https://developer.android.com/reference/android/os/SystemClock
     */
    @CheckDiscard("Should get inlined by R8.")
    public static long elapsedRealtimeNanos() {
        if (sFakeClock != null) {
            return sFakeClock.elapsedRealtimeNanos();
        }
        return SystemClock.elapsedRealtimeNanos();
    }

    /**
     * Wrapper for SystemClock.elapsedRealtimeMillis() (uptime including deep sleep).
     * Can be faked in tests using FakeTimeTestRule.
     * See: https://developer.android.com/reference/android/os/SystemClock
     */
    @CheckDiscard("Should get inlined by R8.")
    public static long elapsedRealtimeMillis() {
        if (sFakeClock != null) {
            return sFakeClock.elapsedRealtimeNanos() / NANOSECONDS_PER_MILLISECOND;
        }
        return SystemClock.elapsedRealtime();
    }

    /**
     * Wrapper for SystemClock.currentThreadTimeMillis() (excludes blocking time).
     * Can be faked in tests using FakeTimeTestRule.
     * See: https://developer.android.com/reference/android/os/SystemClock
     */
    @CheckDiscard("Should get inlined by R8.")
    public static long currentThreadTimeMillis() {
        if (sFakeClock != null) {
            return sFakeClock.currentThreadTimeMillis();
        }
        return SystemClock.currentThreadTimeMillis();
=======
        /** Returns TimeTicks::Now() in microseconds. */
        long getTimeTicksNowUs();
>>>>>>> chromium
    }
}

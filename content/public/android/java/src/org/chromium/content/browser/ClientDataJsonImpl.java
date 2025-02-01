// Copyright 2021 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.content.browser;

<<<<<<< HEAD
import org.jni_zero.JNINamespace;
import org.jni_zero.NativeMethods;

=======
import androidx.annotation.Nullable;

import org.chromium.base.annotations.JNINamespace;
import org.chromium.base.annotations.NativeMethods;
>>>>>>> chromium
import org.chromium.blink.mojom.PaymentOptions;
import org.chromium.build.annotations.NullMarked;
import org.chromium.build.annotations.Nullable;
import org.chromium.content_public.browser.ClientDataRequestType;

import java.nio.ByteBuffer;

/**
 * The implementation of ClientDataJson.
 */
@JNINamespace("content")
@NullMarked
public class ClientDataJsonImpl {
    /** The implementation of {@link ClientDataJson#buildClientDataJson}. */
<<<<<<< HEAD
    public static @Nullable String buildClientDataJson(
            @ClientDataRequestType int clientDataRequestType,
            String callerOrigin,
            byte[] challenge,
            boolean isCrossOrigin,
            @Nullable PaymentOptions paymentOptions,
            @Nullable String relyingPartyId,
            @Nullable Origin topOrigin) {
        return ClientDataJsonImplJni.get()
                .buildClientDataJson(
                        clientDataRequestType,
                        callerOrigin,
                        challenge,
                        isCrossOrigin,
                        paymentOptions == null ? null : paymentOptions.serialize(),
                        relyingPartyId,
                        topOrigin);
=======
    @Nullable
    public static String buildClientDataJson(@ClientDataRequestType int clientDataRequestType,
            String callerOrigin, byte[] challenge, boolean isCrossOrigin,
            PaymentOptions paymentOptions, String relyingPartyId, String topOrigin) {
        return ClientDataJsonImplJni.get().buildClientDataJson(clientDataRequestType, callerOrigin,
                challenge, isCrossOrigin,
                paymentOptions == null ? null : paymentOptions.serialize(), relyingPartyId,
                topOrigin);
>>>>>>> chromium
    }

    @NativeMethods
    public interface Natives {
<<<<<<< HEAD
        String buildClientDataJson(
                @ClientDataRequestType int clientDataRequestType,
                String callerOrigin,
                byte[] challenge,
                boolean isCrossOrigin,
                @Nullable ByteBuffer optionsByteBuffer,
                @Nullable String relyingPartyId,
                @Nullable Origin topOrigin);
=======
        String buildClientDataJson(@ClientDataRequestType int clientDataRequestType,
                String callerOrigin, byte[] challenge, boolean isCrossOrigin,
                ByteBuffer optionsByteBuffer, String relyingPartyId, String topOrigin);
>>>>>>> chromium
    }
}

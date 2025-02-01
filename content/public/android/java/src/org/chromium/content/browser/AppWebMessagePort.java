// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.content.browser;

import android.os.Handler;
import android.os.Looper;
<<<<<<< HEAD
import android.os.Message;
import android.util.Pair;

import androidx.annotation.MainThread;

import org.jni_zero.CalledByNative;
import org.jni_zero.JNINamespace;
import org.jni_zero.NativeMethods;

import org.chromium.base.Log;
import org.chromium.base.ThreadUtils;
import org.chromium.base.task.PostTask;
import org.chromium.base.task.TaskTraits;
import org.chromium.build.annotations.NullMarked;
import org.chromium.build.annotations.Nullable;
import org.chromium.content_public.browser.MessagePayload;
=======

import org.chromium.base.Log;
import org.chromium.base.annotations.CalledByNative;
import org.chromium.base.annotations.JNINamespace;
import org.chromium.base.annotations.NativeMethods;
import org.chromium.blink.mojom.CloneableMessage;
import org.chromium.blink.mojom.FileSystemAccessTransferToken;
import org.chromium.blink.mojom.MessagePortDescriptor;
import org.chromium.blink.mojom.SerializedArrayBufferContents;
import org.chromium.blink.mojom.SerializedBlob;
import org.chromium.blink.mojom.TransferableMessage;
>>>>>>> chromium
import org.chromium.content_public.browser.MessagePort;
import org.chromium.mojo.bindings.Connector;
import org.chromium.mojo.bindings.DeserializationException;
import org.chromium.mojo.bindings.Message;
import org.chromium.mojo.bindings.MessageHeader;
import org.chromium.mojo.bindings.MessageReceiver;
import org.chromium.mojo.system.Core;
import org.chromium.mojo.system.Pair;
import org.chromium.mojo_base.BigBufferUtil;
import org.chromium.skia.mojom.BitmapN32;

/**
 * Represents the MessageChannel MessagePort object. Inspired from
 * http://www.whatwg.org/specs/web-apps/current-work/multipage/web-messaging.html#message-channels
 *
 * State management:
 *
 * A message port can be in transferred state while a transfer is pending or complete. An
 * application cannot use a transferred port to post messages. If a transferred port
 * receives messages, they will be queued. This state is not visible to embedder app.
 *
 * A message port should be closed by the app when it is not needed any more. This will free
 * any resources used by it. A closed port cannot receive/send messages and cannot be transferred.
 * close() can be called multiple times. A transferred port cannot be closed by the application,
 * since the ownership is also transferred during the transfer. Closing a transferred port will
 * throw an exception.
 *
 * All methods are called on the UI thread, except for MessageHandler.handleMessage, which is
 * used to dispatch messages on a potentially separate thread.
 *
 * Restrictions:
 * The HTML5 message protocol is very flexible in transferring ports. However, this
 * sometimes leads to surprising behavior. For example, in current version of chrome (m41)
 * the code below
 *  1.  var c1 = new MessageChannel();
 *  2.  var c2 = new MessageChannel();
 *  3.  c1.port2.onmessage = function(e) { console.log("1"); }
 *  4.  c2.port2.onmessage = function(e) {
 *  5.     e.ports[0].onmessage = function(f) {
 *  6.          console.log("3");
 *  7.      }
 *  8.  }
 *  9.  c1.port1.postMessage("test");
 *  10. c2.port1.postMessage("test2",[c1.port2])
 *
 * prints 1 or 3 depending on whether or not line 10 is included in code. Further if
 * it gets executed with a timeout, depending on timeout value, the printout value
 * changes.
 *
 * To prevent such problems, this implementation limits the transfer of ports
 * as below:
 * A port is put to a "started" state if:
 * 1. The port is ever used to post a message, or
 * 2. The port was ever registered a handler to receive a message.
 * A started port cannot be transferred.
 *
 * This restriction should not impact postmessage functionality in a big way,
 * because an app can still create as many channels as it wants to and use it for
 * transferring data. As a return, it simplifies implementation and prevents hard
 * to debug, racy corner cases while receiving/sending data.
 */
<<<<<<< HEAD
@JNINamespace("content::android")
@NullMarked
=======
@JNINamespace("content")
>>>>>>> chromium
public class AppWebMessagePort implements MessagePort {
    private static final String TAG = "AppWebMessagePort";

    private static final MessageHeader MESSAGE_HEADER = new MessageHeader(0);

    // Implements the handler to handle messageport messages received from web.
    // These messages are dispatched on the main thread by |mConnector|. Applications
    // can pass a handler to setMessageCallback to have messages dispatched on a different
    // thread.
    private static class MessageHandler extends Handler implements MessageReceiver {
        // The |what| value for handleMessage.
        private static final int MESSAGE_RECEIVED = 1;

        private final MessageCallback mMessageCallback;

<<<<<<< HEAD
        MessageHandler(MessageCallback callback, @Nullable Handler handler) {
            super(handler == null ? Looper.getMainLooper() : handler.getLooper());
=======
        // Type for the |obj| value for handleMessage.
        private static class MessagePortMessage {
            public byte[] encodedMessage;
            public AppWebMessagePort[] ports;
        }

        public MessageHandler(Looper looper, MessageCallback callback) {
            super(looper);
>>>>>>> chromium
            mMessageCallback = callback;
        }

        @Override
<<<<<<< HEAD
        public void handleMessage(final Message msg) {
=======
        public void handleMessage(android.os.Message msg) {
>>>>>>> chromium
            if (msg.what == MESSAGE_RECEIVED) {
                MessagePortMessage message = (MessagePortMessage) msg.obj;
                String decodedMessage =
                        AppWebMessagePortJni.get().decodeStringMessage(message.encodedMessage);
                if (decodedMessage == null) {
                    Log.w(TAG, "Undecodable message received, dropping message");
                    return;
                }
                mMessageCallback.onMessage(decodedMessage, message.ports);
                return;
            }
            throw new IllegalStateException("undefined message");
        }

<<<<<<< HEAD
        @MainThread
        public void onMessage(
                final MessagePayload messagePayload, final MessagePort @Nullable [] sentPorts) {
            ThreadUtils.assertOnUiThread();
            sendMessage(obtainMessage(MESSAGE_RECEIVED, Pair.create(messagePayload, sentPorts)));
=======
        @Override
        public boolean accept(Message mojoMessage) {
            try {
                TransferableMessage msg = TransferableMessage.deserialize(
                        mojoMessage.asServiceMessage().getPayload());
                AppWebMessagePort[] ports = new AppWebMessagePort[msg.ports.length];
                for (int i = 0; i < ports.length; ++i) {
                    ports[i] = new AppWebMessagePort(new AppWebMessagePortDescriptor(msg.ports[i]));
                }
                MessagePortMessage portMsg = new MessagePortMessage();
                portMsg.encodedMessage =
                        BigBufferUtil.getBytesFromBigBuffer(msg.message.encodedMessage);
                portMsg.ports = ports;
                sendMessage(obtainMessage(MESSAGE_RECEIVED, portMsg));
            } catch (DeserializationException e) {
                Log.w(TAG, "Error deserializing message", e);
                return false;
            }
            return true;
>>>>>>> chromium
        }

        @Override
        public void close() {}
    }

<<<<<<< HEAD
    // Accessed on UI thread only.
    private long mNativeAppWebMessagePort;
    private @Nullable MessageHandler mMessageHandler;
=======
    private boolean mClosed;
    private boolean mTransferred;
    private boolean mStarted;
    private boolean mWatching;
>>>>>>> chromium

    private Core mMojoCore;
    private AppWebMessagePortDescriptor mDescriptor;
    private Connector mConnector;

    private AppWebMessagePort(AppWebMessagePortDescriptor messagePortDescriptor) {
        mMojoCore = messagePortDescriptor.getCore();
        mDescriptor = messagePortDescriptor;
        // Note that the AppWebMessagePortDescriptor sets the error handler. If
        // this class ever wants to set an error handler, then that code needs
        // reworking.
        mConnector = messagePortDescriptor.entangleWithConnector();
    }

    // Called to create an entangled pair of ports.
    public static AppWebMessagePort[] createPair() {
        Pair<AppWebMessagePortDescriptor, AppWebMessagePortDescriptor> descriptors =
                AppWebMessagePortDescriptor.createPair();
        AppWebMessagePort[] ports =
                new AppWebMessagePort[] {new AppWebMessagePort(descriptors.first),
                        new AppWebMessagePort(descriptors.second)};
        return ports;
    }

    // Called to create a port from a descriptor.
    public static AppWebMessagePort create(AppWebMessagePortDescriptor descriptor) {
        return new AppWebMessagePort(descriptor);
    }

    // See app_web_message_port.h. This is indirectly exposed to content/public
    // so that embedders can translate from blink::MessagePortDescriptors to
    // Java MessagePorts.
    @CalledByNative
    private static AppWebMessagePort[] createFromNativeBlinkMessagePortDescriptors(
            long[] nativeBlinkMessagePortDescriptors) {
        AppWebMessagePort[] ports = new AppWebMessagePort[nativeBlinkMessagePortDescriptors.length];
        for (int i = 0; i < ports.length; ++i) {
            ports[i] = new AppWebMessagePort(
                    AppWebMessagePortDescriptor.createFromNativeBlinkMessagePortDescriptor(
                            nativeBlinkMessagePortDescriptors[i]));
        }
        return ports;
    }

    private AppWebMessagePortDescriptor passDescriptor() {
        mTransferred = true;
        mDescriptor.disentangleFromConnector();
        mConnector = null;
        AppWebMessagePortDescriptor descriptor = mDescriptor;
        mDescriptor = null;
        return descriptor;
    }

    // See app_web_message_port.h. This is indirectly exposed to content/public
    // so that embedders can translate from Java MessagePorts to
    // blink::MessagePortDescriptors.
    @CalledByNative
    private long releaseNativeMessagePortDescriptor() {
        return passDescriptor().releaseNativeMessagePortDescriptor();
    }

    @Override
    public void close() {
        if (mTransferred) {
            throw new IllegalStateException("Port is already transferred");
        }
        if (mClosed) return;
        mClosed = true;

        // Give the connector back to the descriptor and close it from there. This ensures that the
        // instrumentation delegate is notified of all relevant events.
        mDescriptor.disentangleFromConnector();
        mDescriptor.close();
        mConnector.close();

        mDescriptor = null;
        mConnector = null;
    }

    @Override
    public boolean isClosed() {
        return mClosed;
    }

    @Override
    public boolean isTransferred() {
        return mTransferred;
    }

    @Override
    public boolean isStarted() {
        return mStarted;
    }

    // Only called on UI thread
    @Override
    public void setMessageCallback(MessageCallback messageCallback, Handler handler) {
        if (isClosed() || isTransferred()) {
            throw new IllegalStateException("Port is already closed or transferred");
        }
        mStarted = true;
        if (messageCallback == null) {
            mConnector.setIncomingMessageReceiver(null);
        } else {
            mConnector.setIncomingMessageReceiver(new MessageHandler(
                    handler == null ? Looper.getMainLooper() : handler.getLooper(),
                    messageCallback));
        }
        if (!mWatching) {
            mConnector.start();
            mWatching = true;
        }
    }

    @Override
<<<<<<< HEAD
    public void postMessage(MessagePayload messagePayload, MessagePort @Nullable [] sentPorts)
            throws IllegalStateException {
=======
    public void postMessage(String message, MessagePort[] sentPorts) throws IllegalStateException {
>>>>>>> chromium
        if (isClosed() || isTransferred()) {
            throw new IllegalStateException("Port is already closed or transferred");
        }
        MessagePortDescriptor[] ports =
                new MessagePortDescriptor[sentPorts == null ? 0 : sentPorts.length];
        if (sentPorts != null) {
            for (MessagePort port : sentPorts) {
                if (port.equals(this)) {
                    throw new IllegalStateException("Source port cannot be transferred");
                }
                if (port.isClosed() || port.isTransferred()) {
                    throw new IllegalStateException("Port is already closed or transferred");
                }
                if (port.isStarted()) {
                    throw new IllegalStateException("Port is already started");
                }
            }
            for (int i = 0; i < sentPorts.length; ++i) {
                ports[i] = ((AppWebMessagePort) sentPorts[i])
                                   .passDescriptor()
                                   .passAsBlinkMojomMessagePortDescriptor();
            }
        }
        mStarted = true;

<<<<<<< HEAD
    /**
     * A finalizer is required to ensure that the native object associated with this descriptor gets
     * torn down, otherwise there would be a memory leak.
     *
     * <p>This is safe because posting a task is fast.
     *
     * <p>TODO(chrisha): Chase down the existing offenders that don't call close, and flip this to
     * use LifetimeAssert. (also: https://crbug.com/40286193)
     *
     * @see java.lang.Object#finalize()
     */
    @Override
    @SuppressWarnings("Finalize")
    protected void finalize() throws Throwable {
        try {
            if (mNativeAppWebMessagePort == 0L) return;
            Log.d(TAG, "AppWebMessagePort was not closed before finalization");
            PostTask.postTask(
                    TaskTraits.UI_DEFAULT,
                    () -> {
                        if (mNativeAppWebMessagePort == 0L) return;
                        mClosed = true;
                        AppWebMessagePortJni.get().closeAndDestroy(mNativeAppWebMessagePort);
                    });
        } finally {
            super.finalize();
        }
    }

    @MainThread
    @CalledByNative
    private long getNativeObj() {
        ThreadUtils.assertOnUiThread();
        assert mNativeAppWebMessagePort != 0L;
        return mNativeAppWebMessagePort;
    }

    @MainThread
    @CalledByNative
    private void onMessage(MessagePayload payload, MessagePort @Nullable [] ports) {
        ThreadUtils.assertOnUiThread();
        if (mMessageHandler != null) {
            mMessageHandler.onMessage(payload, ports);
        } else {
            // Their will be a case that the Java listener is cleared, but listeners in C++ is not
            // cleared yet. We can safely ignore those messages and close the ports to avoid
            // relaying on GC.
            if (ports != null) {
                for (final MessagePort port : ports) {
                    port.close();
                }
            }
        }
    }

    // Called when native object is destroyed.
    @MainThread
    @CalledByNative
    private void nativeDestroyed() {
        ThreadUtils.assertOnUiThread();
        assert mNativeAppWebMessagePort != 0L;
        // When calling this method, the port must be closed or transferred.
        assert mClosed || mTransferred;
        mNativeAppWebMessagePort = 0L;
    }

    // Called when MessagePort is transferred. The native object will be destroyed later.
    @CalledByNative
    private void setTransferred() {
        assert !mStarted;
        mTransferred = true;
=======
        TransferableMessage msg = new TransferableMessage();
        msg.message = new CloneableMessage();
        msg.message.encodedMessage = BigBufferUtil.createBigBufferFromBytes(
                AppWebMessagePortJni.get().encodeStringMessage(message));
        msg.message.blobs = new SerializedBlob[0];
        msg.message.fileSystemAccessTokens = new FileSystemAccessTransferToken[0];
        msg.message.senderOrigin = null;
        msg.arrayBufferContentsArray = new SerializedArrayBufferContents[0];
        msg.imageBitmapContentsArray = new BitmapN32[0];
        msg.ports = ports;
        msg.streamChannels = new MessagePortDescriptor[0];
        mConnector.accept(msg.serializeWithHeader(mMojoCore, MESSAGE_HEADER));
>>>>>>> chromium
    }

    @NativeMethods
    interface Natives {
<<<<<<< HEAD

        AppWebMessagePort[] createPair();

        void postMessage(
                long nativeAppWebMessagePort,
                MessagePayload messagePayload,
                MessagePort @Nullable [] sentPorts);

        void setShouldReceiveMessages(long nativeAppWebMessagePort, boolean shouldReceiveMessage);

        void closeAndDestroy(long nativeAppWebMessagePort);
=======
        String decodeStringMessage(byte[] encodedData);
        byte[] encodeStringMessage(String message);
>>>>>>> chromium
    }
}

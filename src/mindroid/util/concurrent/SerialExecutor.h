/*
 * Copyright (C) 2011 Daniel Himmelein
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MINDROID_UTIL_CONCURRENT_SERIALEXECUTOR_H_
#define MINDROID_UTIL_CONCURRENT_SERIALEXECUTOR_H_

#include <mindroid/util/concurrent/Executor.h>
#include <mindroid/os/HandlerThread.h>

namespace mindroid {

class Handler;

class SerialExecutor :
        public Executor {
public:
    explicit SerialExecutor(const char* name) :
            SerialExecutor(String::valueOf(name), true) {
    }
    explicit SerialExecutor(const char* name, bool shutdownAllowed) :
            SerialExecutor(String::valueOf(name), shutdownAllowed) {
    }
    explicit SerialExecutor(const sp<String>& name) :
            SerialExecutor(name, true) {
    }
    explicit SerialExecutor(const sp<String>& name, bool shutdownAllowed);
    virtual ~SerialExecutor();
    SerialExecutor(const SerialExecutor&) = delete;
    SerialExecutor& operator=(const SerialExecutor&) = delete;

    virtual void execute(const sp<Runnable>& runnable);
    virtual bool cancel(const sp<Runnable>& runnable);

    bool shutdown() {
        return shutdown(mShutdownAllowed);
    }

private:
    void start();
    bool shutdown(bool shutdownAllowed);

    static const char* const TAG;

    sp<String> mName;
    const bool mShutdownAllowed;
    sp<HandlerThread> mHandlerThread;
    sp<Handler> mHandler;
};

} /* namespace mindroid */

#endif /* MINDROID_UTIL_CONCURRENT_SERIALEXECUTOR_H_ */

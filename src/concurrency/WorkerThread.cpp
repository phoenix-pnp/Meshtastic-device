#include "WorkerThread.h"

namespace concurrency {

void WorkerThread::doRun()
{
    startWatchdog();

    while (!wantExit) {
        stopWatchdog();
        block();
        startWatchdog();

        // no need - startWatchdog is guaranteed to give us one full watchdog interval
        // serviceWatchdog(); // Let our loop worker have one full watchdog interval (at least) to run

#ifdef DEBUG_STACK
        static uint32_t lastPrint = 0;
        if (millis() - lastPrint > 10 * 1000L) {
            lastPrint = millis();
            meshtastic::printThreadInfo("net");
        }
#endif

        loop();
    }

    stopWatchdog();
}

} // namespace concurrency

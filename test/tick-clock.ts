export type ClockEventCallback = () => void;

/**
 * Linked list of pending clock events. We use a linked in instead of an array for performance,
 * similar to how AVR8js implements clock events:
 * https://github.com/wokwi/avr8js/commit/968a6ee0c90498077888c7f09c58983598937570
 */
interface IClockEventEntry {
  cycles: number;
  callback: ClockEventCallback;
  next: IClockEventEntry | null;
}

/* Dummy implementation, to be compatible with rp2040js interface */
class Timer {
  constructor(readonly callback: ClockEventCallback) {}

  pause() {}
  resume() {}
}

export class RPClock {
  private nextClockEvent: IClockEventEntry | null = null;
  private readonly clockEventPool: IClockEventEntry[] = []; // helps avoid garbage collection

  skippedCycles = 0;
  cpu: { cycles: number } = { cycles: 0 };

  constructor(readonly frequency = 125e6) {}

  get micros() {
    return this.nanos / 1000;
  }

  get nanos() {
    return (this.cpu.cycles / this.frequency) * 1e9;
  }

  addEvent(nanos: number, callback: ClockEventCallback) {
    const cycles = Math.round((nanos / 1e9) * this.frequency);
    return this.addEventCycles(cycles, callback);
  }

  clearEvent(callback: ClockEventCallback) {
    let { nextClockEvent: clockEvent } = this;
    if (!clockEvent) {
      return false;
    }
    const { clockEventPool } = this;
    let lastItem: IClockEventEntry | null = null;
    while (clockEvent) {
      if (clockEvent.callback === callback) {
        if (lastItem) {
          lastItem.next = clockEvent.next;
        } else {
          this.nextClockEvent = clockEvent.next;
        }
        if (clockEventPool.length < 10) {
          clockEventPool.push(clockEvent);
        }
        return true;
      }
      lastItem = clockEvent;
      clockEvent = clockEvent.next;
    }
    return false;
  }

  addEventCycles(cycles: number, callback: ClockEventCallback) {
    const { clockEventPool } = this;
    cycles = this.cpu.cycles + Math.max(1, cycles);
    const maybeEntry = clockEventPool.pop();
    const entry: IClockEventEntry = maybeEntry ?? { cycles, callback, next: null };
    entry.cycles = cycles;
    entry.callback = callback;
    let { nextClockEvent: clockEvent } = this;
    let lastItem: IClockEventEntry | null = null;
    while (clockEvent && clockEvent.cycles < cycles) {
      lastItem = clockEvent;
      clockEvent = clockEvent.next;
    }
    if (lastItem) {
      lastItem.next = entry;
      entry.next = clockEvent;
    } else {
      this.nextClockEvent = entry;
      entry.next = clockEvent;
    }
    return callback;
  }

  /** @deprecated */
  pause() {
    /* Not really used; Kept for compatibility with rp2040js clock */
  }

  /** @deprecated */
  resume() {
    /* Not really used; Kept for compatibility with rp2040js clock */
  }

  tick() {
    const { nextClockEvent } = this;
    if (nextClockEvent && nextClockEvent.cycles <= this.cpu.cycles) {
      this.nextClockEvent = nextClockEvent.next;
      if (this.clockEventPool.length < 10) {
        this.clockEventPool.push(nextClockEvent);
      }
      nextClockEvent.callback();
    }
  }

  createTimer(deltaMicros: number, callback: () => void) {
    const timer = new Timer(callback);
    this.addEvent(deltaMicros * 1000, callback);
    return timer;
  }

  deleteTimer(timer: any) {
    if (timer instanceof Timer) {
      this.clearEvent(timer.callback);
    }
  }

  createEvent(callback: () => void) {
    const clock = this;
    return {
      schedule(nanos: number) {
        clock.clearEvent(callback);
        clock.addEvent(nanos, callback);
      },
      unschedule() {
        clock.clearEvent(callback);
      },
    };
  }

  skipToNextEvent() {
    const { nextClockEvent } = this;
    if (nextClockEvent) {
      this.cpu.cycles = nextClockEvent.cycles;
      this.nextClockEvent = nextClockEvent.next;
      if (this.clockEventPool.length < 10) {
        this.clockEventPool.push(nextClockEvent);
      }
      nextClockEvent.callback();
    }
  }

  get nextClockEventCycles() {
    return this.nextClockEvent?.cycles ?? 0;
  }
}